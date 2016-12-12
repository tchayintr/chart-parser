/*
 *  $ JAIST: chart.c,v 0.1000 1995/10/04 20:04:01 $
 *
 *  @(#)chart.c  04/10/1995  By Thanaruk Theeramunkong
 *
 *  $Header: /home/fs100/ping/work/project/ill-formed/chart/src/RCS/chartpure.c,v 1.3 1996/12/06 16:59:44 ping Exp ping $
 *
 *  $Log: chartpure.c,v $
 *  Revision 1.3  1996/12/06 16:59:44  ping
 *  Modify the algorithm to deal with multiple top categories.
 *  For example, _L1N21 and _L3N1
 *
 *  Revision 1.2  1996/12/06 15:51:38  ping
 *  add revision
 *
 *  Revision 1.1  1996/12/06 15:42:49  ping
 *  Initial revision
 *
 *  $Revision: 1.3 $
 *
 *  $Id: chartpure.c,v 1.3 1996/12/06 16:59:44 ping Exp ping $
 *
 *  $Author: ping $
 *
 *  $Date: 1996/12/06 16:59:44 $
 *
 */

#include <stdio.h>
#include <ctype.h>
#include "def.h"
#include "chart.h"
#include "grampure.h"

/*
#define DEBUG
#define ERROR
#define INFO1
*/

#define INFO2

/*
#define SENTENCE "_L1N21"
*/

int  sent_cat_num = 2;
char *sentence[] = { "_L1N21", "_L3N1" } ;

char inactivehead[] = "/usr/tmp/_i";
char activehead[]   = "/usr/tmp/_a";

FILE *ifp,*afp;

char cinsent[SentLen][CatLen];		/* Categories in Sentence */
char word[SentLen][WordLen];		/* Words in Sentence */
EListptr ichart[SentLen][SentLen];	/* Inactive Edge pointer */
EListptr achart[SentLen][SentLen];	/* Active Edge pointer */
Edgeptr  ordichart[ChartMax];		/* i edge indexed by ordinal */
Edgeptr  ordachart[ChartMax];           /* a edge indexed by ordinal */
int wordcat[MaxCat];			/* All categories of a word */

struct EList tail = {NULL, NULL, NULL}; /* the tail cell of an edge list */
struct Edge tailedge = {0, 0, 0, 0, 0, 0, 0, 0, "", NULL, NULL};
                                        /* the tail edge */
struct ListTree tailtree = {NULL, NULL, NULL}; /* the tail tree */
EListptr agendaptr=&tail;		/* agenda which is a list */
EListptr freeelist=&tail;		/* A list of Free Edge list cells */
Edgeptr  freeedge=&tailedge;		/* A list of Free Edges */
ListTreeptr  freeltree=&tailtree;	/* A list of Free Trees */
int  nc;				/* The number of categories in Sent */
int  niedge=1;				/* The ordinal number of inactive */
int  naedge=1;				/* The ordinal number of active */
int  minlength=100,maxlength=0;		/* The max-min length of sentence */
EListptr tmpelptr;			/* Temporary edge list pointer */
char buffer[BufSize];			/* Temporary buffer */
int  anumedge=0;
int  anumelist=0;
int  anumltree=0;
int  fnumedge=0;
int  fnumelist=0;
int  fnumltree=0;

main( argc, argv )
int  argc;
char **argv;
{
  char ifname[FNameLen],afname[FNameLen]; /* output inactive and active fname*/
  int  i,j,topcatnum[sent_cat_num], sentencenum=1, sflag=0, count_s=0;
  long k;

/* find the index of the category SENTENCE */
  i=0; j=0;
  for( j=1 ; j<2*MaxCat ; j++ ){
      if( ctab[j][0] == '\0' ){
	  fprintf(stderr,"\"%s\" is not a vilid category\n", sentence[0]);
	  exit(0);
      }
      for( i=0; i<sent_cat_num ; i++ ){
          if( !strcmp(ctab[j],sentence[i]) ){
	      topcatnum[i] = j;
	      count_s++;
	  }
      }
      if( count_s == sent_cat_num ){ break; }
  }

  if( argc > 2 ) { 
      fprintf(stderr,"Usage: progname [arg1] \n"); exit(0); }
  if( argc == 2 ){
      strcpy(ifname,inactivehead);
      strcpy(afname,activehead);
      strcat(ifname,*(argv+1));  /* Argv+1 is the ordinal number. */
      strcat(afname,*(argv+1));  /* Argv+1 is the ordinal number. */
  }
  
  while( NULL != fgets(buffer,BufSize,stdin) ){
      anumedge=0;
      anumelist=0;
      anumltree=0;
      fnumedge=0;
      fnumelist=0;
      fnumltree=0;

      if( buffer[0] == 10 ){ break; }
#ifdef INFO1
      fprintf(stderr,"%d\n",sentencenum);
#endif
#ifdef DEBUG
      fprintf(stderr,"Buffer = %s",buffer);
#endif
      for( i=0 ; i<SentLen ; i++ ){
	  for( j=0 ; j<SentLen ; j++ ){
	      ichart[i][j] = NULL;
	      achart[i][j] = NULL;	} }
      nc = breakoff(buffer);		/* Break off sentence into array */
      niedge=1;				/* The ordinal number of inactive */
      naedge=1;				/* The ordinal number of active */

      if( nc>maxlength ){ maxlength = nc; }
      if( nc<minlength && nc != 0 ){ minlength = nc; }
      
      initiate();
      parse();

      tmpelptr = ichart[0][nc];
      sflag=0;
      while( tmpelptr != NULL ){
	  k=tcounter(tmpelptr->edge);
	  for( i=0; i<sent_cat_num; i++ ){
	      if(tmpelptr->edge->gram == topcatnum[i]){
#ifdef INFO2
		  if( sflag==0 ){
		      fprintf(stderr,"Sentence No.%d :- %s (%d) ",\
			      sentencenum,sentence[i],k); 
		      sflag++;
		  }else{
		      fprintf(stderr,": %s (%d) ",sentence[i],k); 
		      sflag++;
		  }
#endif	      
		  break;
	      }
	  }
	  tmpelptr = tmpelptr->next;
      }
#ifdef INFO2
      if( sflag != 0 ){
	  fprintf(stderr,"\n");
      }
#endif

      if (argc == 2) {
	  open_file_write(ifname,&ifp);
	  open_file_write(afname,&afp);
	  pmemi();		/* print inactive edge */
	  pmema();		/* print inactive edge */
	  fclose(afp);
	  fclose(ifp);
      }
      freememi();	/* Free Memory in Inactive Chart */
      freemema();	/* Free Memory in Active Chart */
      sentencenum++; /* Increase the ordinal number of the sentence */
/*
      printf("anumedge  = %d : fnumedge  = %d\n",anumedge,fnumedge);
      printf("anumelist = %d : fnumelist = %d\n",anumelist,fnumelist);
      printf("anumltree = %d : fnumltree = %d\n",anumltree,fnumltree);
*/

  }
#ifdef INFO1
  fprintf(stderr,"minlength = %d, maxlength = %d\n",minlength,maxlength); 
#endif
#ifdef DEBUG
	  fprintf(stderr,"ifname = %s \n",ifname);
	  fprintf(stderr,"afname = %s \n",afname);
#endif
  exit(0);
}

/* Print Memory in Inactive Chart */
pmemi()
{
  int i,j;

  fprintf(ifp,"%s",buffer);
  for( i=1 ; i<niedge ; i++ ){
      pedge_parse_i(ordichart[i]);
  }
}

/* Print Memory in Acitve Chart */
pmema()
{
  int i,j;

  fprintf(afp,"%s",buffer);  
  for( i=1 ; i<naedge ; i++ ){
      pedge_parse_a(ordachart[i]);
  }
}

pedge_parse_i(eptr)
Edgeptr  eptr;
{
    ListTreeptr tltptr;
    int i;

    tltptr = eptr->parse;
    fprintf(ifp,"i%d ",eptr->num);
    fprintf(ifp,"%d ",eptr->from);
    fprintf(ifp,"%d ",eptr->to);
    fprintf(ifp,"%s ",ctab[eptr->gram]);
    while(tltptr != NULL){
	if(tltptr->ltree == NULL){
	    fprintf(ifp,"a0/"); 
	}else{
	    fprintf(ifp,"a%d/",tltptr->ltree->num);
	}
	fprintf(ifp,"i%d/",tltptr->rtree->num);
	tltptr  = tltptr->next;
    }
    fprintf(ifp,"0/0\n");
}

pedge_parse_a(eptr)
Edgeptr  eptr;
{
    ListTreeptr tltptr;
    int i;

    tltptr = eptr->parse;
    fprintf(afp,"a%d ",eptr->num);
    fprintf(afp,"%d ",eptr->from);
    fprintf(afp,"%d ",eptr->to);
    fprintf(afp,"%s->",ctab[grammar[eptr->gram][0]]);
    for ( i=0; i<eptr->dot ; i++ ){
	fprintf(afp,"%s,",ctab[grammar[eptr->gram][i+1]]);
    }
    fprintf(afp,"|,");
    for ( i=eptr->dot; grammar[eptr->gram][i+1]!=0 ; i++ ){
	fprintf(afp,"%s,",ctab[grammar[eptr->gram][i+1]]);
    }
    fprintf(afp,"%d ",eptr->gram);
    while(tltptr != NULL){
	if(tltptr->ltree == NULL){
	    fprintf(afp,"a0/"); 
	}else{
	    fprintf(afp,"a%d/",tltptr->ltree->num);
	}
	fprintf(afp,"i%d/",tltptr->rtree->num);
	tltptr  = tltptr->next;
    }
    fprintf(afp,"0/0\n");
}

/* Free Memory in Inactive Chart */
freememi()
{
  int i,j;
  EListptr tmpelptr1,tmpelptr2;

  for( i=0 ; i<SentLen ; i++ ){
      for( j=0 ; j<SentLen ; j++ ){
	  if( ichart[i][j] != NULL ){
	      tmpelptr1 = ichart[i][j];
	      while( tmpelptr1 != NULL ){
		  tmpelptr2 = tmpelptr1;
		  tmpelptr1 = tmpelptr1->next;
		  freeedge_parse(tmpelptr2->edge);
		  freeelistproc(tmpelptr2);
	      } } } }
}

/* Free Memory in Acitve Chart */
freemema()
{
  int i,j;
  EListptr tmpelptr1,tmpelptr2;

  for( i=0 ; i<SentLen ; i++ ){
      for( j=0 ; j<SentLen ; j++ ){
	  if( achart[i][j] != NULL ){
	      tmpelptr1 = achart[i][j];
	      while( tmpelptr1 != NULL ){
		  tmpelptr2 = tmpelptr1;
		  tmpelptr1 = tmpelptr1->next;
		  freeedge_parse(tmpelptr2->edge); 
		  freeelistproc(tmpelptr2);
	      } } } }
}

int tcounter(eptr)
Edgeptr  eptr;
{
    int  result,i,j;
    ListTreeptr tltptr;

    result=0;
    if(eptr->numparses == 0){
	tltptr = eptr->parse;
	while(tltptr != NULL){
	    if(tltptr->ltree==NULL){ i=1; }else{
		i=tcounter(tltptr->ltree);
	    }
	    j=tcounter(tltptr->rtree);
	    result = result+(i*j);
	    tltptr = tltptr->next;
	}
	eptr->numparses = result;
	return(result);
    }else{ return(eptr->numparses); }
}

parse()
{
    int  i;
    Edgeptr eptr;
    EListptr  telistptr,tagendaptr;

    while(agendaptr != &tail){
	tagendaptr = agendaptr;
	eptr = agendaptr->edge;
	agendaptr = agendaptr->next;
/*	agendaptr->previous = NULL; */
	if( 0 == dup_check(eptr) ){
	    if( eptr->type != 2 ){
		provoke(eptr);
		for( i=0; i<=eptr->from; i++ ){
		    telistptr = achart[i][eptr->from];
		    while( telistptr != NULL ){
			combine(telistptr->edge,eptr);
			telistptr = telistptr->next;
		    }
		}
	    }else{
		for( i=eptr->to; i<=nc; i++ ){
		    telistptr = ichart[eptr->to][i];
		    while( telistptr != NULL ){
			combine(eptr,telistptr->edge);
			telistptr = telistptr->next;
		    }
		}
	    }
	}
 	freeelistproc(tagendaptr);
    }
}

provoke(eptr)
Edgeptr  eptr;
{
    int  i;
    Edgeptr   teptr;
    EListptr  telistptr;
    int j;

    for( i=1 ; i<MaxGram ; i++ ){
	if( grammar[i][0] == 0 ){  
	    break; }
	if( grammar[i][1] == eptr->gram ){
	    allocedge(&teptr);
	    teptr->from = eptr->from;
	    teptr->to   = eptr->to;
	    teptr->numparses = 0;  	/* initial value */
	    if( grammar[i][2] == 0 ){
		teptr->type = 1;
		teptr->gram = grammar[i][0];
	    }else{ teptr->type = 2; teptr->gram = i; teptr->dot = 1; }
	    allocltree(&(teptr->parse));
	    teptr->parse->ltree = NULL;
	    teptr->parse->rtree = eptr;
	    teptr->parse->next  = NULL;
	    allocedgelist(&telistptr);
	    agendaptr->previous = telistptr;
	    telistptr->edge = teptr;
	    telistptr->previous = NULL;
	    telistptr->next = agendaptr;
	    agendaptr = telistptr;
	}
    }
}

/* Combine eptr1 with eptr2 where eptr1 is an active edge and
   eptr2 is an inactive one. */
combine(eptr1,eptr2)
Edgeptr  eptr1,eptr2;
{
    int  i;
    Edgeptr   teptr;
    EListptr  telistptr;

    if( grammar[eptr1->gram][(eptr1->dot)+1] == eptr2->gram ){
	allocedge(&teptr);
	teptr->from = eptr1->from;
	teptr->to   = eptr2->to;
	teptr->numparses = 0;    /* initial value */
	if( grammar[eptr1->gram][(eptr1->dot)+2] == 0 ){
	    teptr->type = 1;
	    teptr->gram = grammar[eptr1->gram][0];
	}else{ 
	    teptr->type = 2;
	    teptr->gram = eptr1->gram;
	    teptr->dot = (eptr1->dot)+1; }
	allocltree(&(teptr->parse));
	teptr->parse->ltree = eptr1;
	teptr->parse->rtree = eptr2;
	teptr->parse->next  = NULL;
	allocedgelist(&telistptr);
	agendaptr->previous = telistptr;
	telistptr->edge = teptr;
	telistptr->previous = NULL;
	telistptr->next = agendaptr;
	agendaptr = telistptr;
    }
}

int dup_check(eptr)
Edgeptr  eptr;
{
    int  i;
    EListptr  tmpptr;

    if(eptr->type !=2){
	tmpptr = ichart[eptr->from][eptr->to];
	while(tmpptr != NULL){
	    if(eptr->gram == tmpptr->edge->gram){
		eptr->parse->next = tmpptr->edge->parse;
		tmpptr->edge->parse = eptr->parse;
		freeedgeproc(eptr);
		return(1);
	    }else{tmpptr = tmpptr->next;}
	}
	allocedgelist(&tmpptr);
/*	ichart[eptr->from][eptr->to]->previous =  tmpptr; */
	tmpptr->edge = eptr;
	ordichart[niedge] = eptr;
	eptr->num = niedge++;
	tmpptr->next = ichart[eptr->from][eptr->to];
	tmpptr->previous = NULL;
	ichart[eptr->from][eptr->to] = tmpptr;
	return(0);
    }else{
	tmpptr = achart[eptr->from][eptr->to];
	while(tmpptr != NULL){
	    if(eptr->gram == tmpptr->edge->gram &&
	       eptr->dot == tmpptr->edge->dot){
		eptr->parse->next = tmpptr->edge->parse;
		tmpptr->edge->parse = eptr->parse;
		freeedgeproc(eptr);
		return(1);
	    }else{tmpptr = tmpptr->next;}
	}
	allocedgelist(&tmpptr);
/*	achart[eptr->from][eptr->to]->previous =  tmpptr; */
	tmpptr->edge = eptr;
	ordachart[naedge] = eptr;
	eptr->num = naedge++;
	tmpptr->next = achart[eptr->from][eptr->to];
	tmpptr->previous = NULL;
	achart[eptr->from][eptr->to] = tmpptr;
	return(0);
    }
}

/* Insert Lexical Edge */
initiate()
{
    int  i, j, state=0, wc;
    Edgeptr   tmpeptr;
    EListptr  tagendaptr;
    char tmpcat[CatLen], tmpword[CatLen];
    
    for( i=nc-1; i>=0; i-- ){
	state=0;
	strcpy(tmpcat,cinsent[i]);
	strcpy(tmpword,word[i]);

	wc=0;
	/* transfer cat from those of Tagger to those of grammar */
	trancat(&cinsent[i][0],&word[i][0],&wc);

#ifdef DEBUG
	fprintf(stderr,"cinsent[%d] = %s/%s, wc => %d :",i,cinsent[i],word[i],wc);
	for( j=0; j<wc; j++ ){
	    fprintf(stderr,"%d ,",wordcat[j]);
	}
	fprintf(stderr,"\n");
#endif

	for( j=0; j<wc; j++ ){
	    allocedge(&tmpeptr);          /* Allocate Area for Edge */
	    allocedgelist(&tagendaptr);   /* Allocate Area for Eptr(Agenda) */
	    tmpeptr->gram = wordcat[j];
	    tmpeptr->type = 0;
	    tmpeptr->from = i;
	    tmpeptr->to   = i+1;
	    tmpeptr->numparses = 1;    /* Number of parses */
	    tmpeptr->parse = NULL;     /* Lexical edge has null as its parse */
	    strcpy(tmpeptr->word, word[i]);
	    agendaptr->previous = tagendaptr;
	    tagendaptr->edge = tmpeptr;
	    tagendaptr->previous = NULL;
	    tagendaptr->next = agendaptr;
	    agendaptr = tagendaptr;
	}
    }
}

/* Break off sentence into array */
int breakoff(buffer)
char *buffer;
{
  int buflen;
  int i=0, j=0, p=0, n=0, m=0;
  char tmpchar[CatLen];

  while( buffer[p]==' ' | buffer[p]=='\t' |
	 buffer[p]=='\n' ){
      p++; }	 			  /* Deleting useless head */
  while( buffer[p]=='%' ){ return(0); }   /* For comment statement */

  buflen = strlen(buffer);
  while( p<=buflen ){			  /* Seperate buffer and Keep
					     tokens in cinsent */
      if( buffer[p] == '\t' |
	  buffer[p] == ' '  |
	  buffer[p] == '\n'   ){
	  word[i][j] = '\0';
	  strcpy(*(cinsent+i),*(word+i));
	  i++; j=0;
	  while( buffer[p] == ' ' | buffer[p] == '\t' |
		 buffer[p] == '\n' ){
	      p++; }	 		  /* Deleting useless tokens */
      }else{  
	  word[i][j++] = buffer[p++]; 
      } 
  }
  return(i);
}
