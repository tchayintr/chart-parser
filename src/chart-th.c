/*
 *  $ JAIST: chart.c,v 0.1000 1995/10/04 20:04:01 $
 *
 *  @(#)chart.c  04/10/1995  By Thanaruk Theeramunkong
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "def.h"
#include "chart-th.h"
#include "gram-th.h"


// #define DEBUG
// #define ERROR


#define INFO1	//DEBUG No. input sentence

#define INFO2	//DEBUG No. parse for each sentence 


#define SENTENCE "S"

void pmemi();
void pmema();
void pmemlb();
void pedge_parse_i(Edgeptr);
void pedge_parse_a(Edgeptr);
void freememi();
void freemema();
int tcond(Edgeptr);
int tcounter(Edgeptr);
int tcounter_f(Edgeptr);
int tconst(Edgeptr);
void parse();
void provoke(Edgeptr);
void combine(Edgeptr eptr1,Edgeptr eptr2);
int dup_check(Edgeptr);
void initiate();
int breakoff(char*);
size_t strlength(const char*);
void print_edge(Edgeptr eptr);

// char inactivehead[] = "/usr/local/tmp/_i";
// char activehead[]   = "/usr/local/tmp/_a";

char inactivehead[] = "./outputs-t/_i-";
char activehead[]   = "./outputs-t/_a-";
char lbhead[] = "./outputs-t/_lb-";  //labeled bracketing

FILE *ifp,*afp,*lbfp;

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

int noSentence = 0;

int main( argc, argv )
int  argc;
char **argv;
{
	char ifname[FNameLen],afname[FNameLen],lbfname[FNameLen]; /* output inactive and active fname*/
	int  i,j,topcatnum, sentencenum=1;
	long k;

/* find the index of the category SENTENCE */
  	i=0; j=0;
	
	for( j=1 ; j<2*MaxCat ; j++ ){
		if( ctab[j][0] == '\0' ){
	  	fprintf(stderr,"\"%s\" is not a vilid category\n", SENTENCE);
	  	exit(0);
      }
      
      if( !strcmp(ctab[j],SENTENCE) ){
	  	topcatnum = j;   //Where "S" is belonging
	  	break;
	  }
  	}

  	if( argc > 2 ) { 
     	fprintf(stderr,"Usage: progname [arg1] \n"); exit(0); }
  	if( argc == 2 ){
     	strcpy(ifname,inactivehead);
     	strcpy(afname,activehead);
     	strcpy(lbfname,lbhead);
     	strcat(ifname,*(argv+1));  /* Argv+1 is the ordinal number. */
     	strcat(afname,*(argv+1));  /* Argv+1 is the ordinal number. */
     	strcat(lbfname,*(argv+1));  /* Argv+1 is the ordinal number. */
     	clear_file_write(ifname, &ifp);
     	clear_file_write(afname, &afp);
     	clear_file_write(lbfname, &lbfp);
     	fclose(afp);
		fclose(ifp);
		fclose(lbfp);
  	}
  
  	while( NULL != fgets(buffer,BufSize,stdin) ){
  		noSentence++;
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
	    		achart[i][j] = NULL;	
	   		} 
	   	}
      
      	nc = breakoff(buffer);		/* Break off sentence into array */
	  	printf("\nNumber of Content: %d\n", nc);
    	niedge=1;				/* The ordinal number of inactive */
     	naedge=1;				/* The ordinal number of active */

      	if( nc>maxlength ){ maxlength = nc; }
      	if( nc<minlength && nc != 0 ){ minlength = nc; }
      
      	initiate();
      	printf("Initiated\n");  
      
      	parse();
      	printf("Parsed\n");

      	tmpelptr = ichart[0][nc];

      	// EListptr tmpelptr2;
      	// tmpelptr2 = achart[0][nc];
     	// printf("num: %d\n", tmpelptr2->edge->num);
     	// printf("num parses: %d\n", tmpelptr2->edge->numparses);
     	// tmpelptr = tmpelptr->next;
     	// printf("num: %d\n", ichart[0][nc]->edge->num);
     	// printf("num parses: %d\n", tmpelptr->edge->numparses);
     	// tmpelptr = tmpelptr->next;
     	// printf("num: %d\n", ichart[0][nc]->edge->num);
     	// printf("num parses: %d\n", tmpelptr->edge->numparses);

     	// // walk in list tree example (ranking by bottom-up)
     	// printf("ltree no: a%d\n", tmpelptr->edge->parse->ltree->num);
     	// printf("rtree no: i%d\n", tmpelptr->edge->parse->rtree->num);
     	// printf("ltree next edge no: a%d\n", tmpelptr->next->edge->parse->ltree->num);
     	// printf("rtree next edge no: i%d\n", tmpelptr->next->edge->parse->rtree->num);
     	// printf("ltree next parse no: a%d\n", tmpelptr->edge->parse->next->ltree->num);
     	// printf("rtree next parse no: i%d\n", tmpelptr->edge->parse->next->rtree->num);
     	// exit(0);


      	// printf("nc=%d, tmpelptr->edge->num: %d\n", nc, tmpelptr->edge->num);

      	// int z=0;
      	// for(z = 0;z<nc;z++){
      	// 	printf("ichart[0][%d]: %s\n", z, ichart[0][z]->edge->word);
      	// }

      	while( tmpelptr != NULL ){
	      	// printf("nc=%d, tmpelptr->edge->num(inactive): %d\n", nc, tmpelptr->edge->num);
			printf("tcounter is started\n");
			k=tcounter(tmpelptr->edge);
			// printf("--------------------------------\n");

		 	if(tmpelptr->edge->gram == topcatnum){ 
		 		tcond(tmpelptr->edge);	 // Major change	
				#ifdef INFO2
		    	fprintf(stderr,"Sentence No.%d [S]: no-of-parses is %d\n", sentencenum,k); 
				#endif	      
			    break;
		  	}

		  	else{
		  		// tcond(tmpelptr->edge);	 // Major change	
		  		#ifdef INFO2
		    	fprintf(stderr,"**Phrase No.%d [%s] : no-of-parses is %d\n", sentencenum, ctab[tmpelptr->edge->gram], k); 
				#endif	      
			    // break;
		  	}
	  		tmpelptr = tmpelptr->next;
      	}

      	// tmpelptr = ichart[0][nc]
      	// tcond(tmpelptr->edge)
      	
     

      	// =========
   //    	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
   //    	EListptr tmp; int z;			/* Temporary edge list pointer */
   //    	tmp = ichart[0][nc];
   //    	while( tmp != NULL ){
	  //     	// printf("nc=%d, tmp->edge->num(inactive): %d\n", nc, tmp->edge->num);
			// if(tmp->edge->gram == topcatnum){
			// 	z=tconst(tmp->edge);
			// 	#ifdef INFO2
		 //    	fprintf(stderr,"Z: Sentence No.%d : no-of-parses is %d\n", sentencenum,z); 
			// 	#endif	
			// }
			
			
	  // 		tmp = tmp->next;
   //    	}
   //    	printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
      	// =========

      
      	if (argc == 2) {
		 	open_file_write(ifname,&ifp);
		 	open_file_write(afname,&afp);
		 	open_file_write(lbfname,&lbfp);
		 	fprintf(stderr,"ifname = %s \n",ifname);
		 	fprintf(stderr,"afname = %s \n",afname);
		 	fprintf(stderr,"lbfname = %s \n",lbfname);
		 	pmemi();		/* print inactive edge */
		 	pmema();		/* print active edge */
		 	pmemlb();		/* print labeled bracketing frimn*/
		 	fclose(afp);
		 	fclose(ifp);
		 	fclose(lbfp);
      	}

      	// Testing Label Bracket Printing
     	strcpy(lbfname,lbhead);
     	strcat(lbfname,"test");  /* Argv+1 is the ordinal number. */
     	clear_file_write(lbfname, &lbfp);
		fclose(lbfp);

      	open_file_write(lbfname,&lbfp);
      	pmemlb();
      	printf(stderr,"lbfname = %s \n",lbfname);
      	fclose(lbfp);

      	freememi();	/* Free Memory in Inactive Chart */
      	freemema();	/* Free Memory in Active Chart */
      	// freequeue(); /* Free Memory in Stack (Labeled Breacket Keeper) */
      	sentencenum++; /* Increase the ordinal number of the sentence */
      	printf("anumedge  = %d : fnumedge  = %d\n",anumedge,fnumedge);
      	printf("anumelist = %d : fnumelist = %d\n",anumelist,fnumelist);
      	printf("anumltree = %d : fnumltree = %d\n",anumltree,fnumltree);
	}

	#ifdef INFO1
  	fprintf(stderr,"minlength = %d, maxlength = %d\n",minlength,maxlength); 
	#endif
  
  	exit(0);
}



/* Print Memory in Inactive Chart */
void pmemi()
{
	int i,j;
 	fprintf(ifp,"%d: %s\n",noSentence ,buffer);
 	for( i=1 ; i<niedge ; i++ ){
    	pedge_parse_i(ordichart[i]);
  	}
  	fprintf(ifp, "niedge: %d\n", niedge-1);
  	fprintf(ifp, "anumedge  = %d : fnumedge  = %d\n",anumedge,fnumedge);
    fprintf(ifp, "anumelist = %d : fnumelist = %d\n",anumelist,fnumelist);
    fprintf(ifp, "anumltree = %d : fnumltree = %d\n",anumltree,fnumltree);
    fprintf(ifp,"minlength = %d, maxlength = %d\n",minlength,maxlength); 
  	fprintf(ifp, "_____________________\n\n");
}

/* Print Memory in Acitve Chart */
void pmema()
{
 	int i,j;

 	fprintf(afp,"%d: %s\n", noSentence, buffer);  
 	for( i=1 ; i<naedge ; i++ ){
    	pedge_parse_a(ordachart[i]);
  	}
  	fprintf(afp, "naedge: %d\n", naedge-1);
  	fprintf(afp, "_____________________\n\n");
}

void pmemlb()
{
	//queue
    int i=0,j=0;
	
	fprintf(lbfp,"%d: %s\n", noSentence, buffer); 

	fprintf(lbfp,"(%d): ", ++i);	// No. of labeled bracketing (1st)
	printf("(%d): ", i);
	
	while(!isEmpty()){
		int k = removeData(); 

  		if(k > 0){
  			fprintf(lbfp,"[%s ", ctab[k]);
  			printf("[%s ", ctab[k]);
  		}
  		else if(k == 0){	// lexical
  			fprintf(lbfp,"%s ", word[j]);
  			printf("%s ", word[j++]);
  		}
  		else if(k == -1){	//newline 
  			printf("]\n");
  			fprintf(lbfp,"]\n");

  			/* No. of labeled bracketing (2nd++)*/
  			fprintf(lbfp,"(%d): ", ++i);
  			printf("(%d): ", i);

  			// fprintf(lbfp,"\n");
  			// printf("\n");

  			j=0;
  		}
  		else{	//bracket
  			fprintf(lbfp,"] ");
  			printf("] ");
  		}
  	}

  	printf("]\n");
  	fprintf(lbfp,"]\n");
}

/* Inactive Edge printing */
void pedge_parse_i(eptr)
Edgeptr  eptr;
{
    ListTreeptr tltptr;
    int i;
    int np; /* numparses */

    tltptr = eptr->parse;
    fprintf(ifp,"i%d ",eptr->num);
    fprintf(ifp,"%d ",eptr->from);
    fprintf(ifp,"%d ",eptr->to);
    fprintf(ifp,"%s ",ctab[eptr->gram]);
    while(tltptr != NULL){
		if(tltptr->ltree == NULL){
		    fprintf(ifp,"a0/"); 
		}
		else{
		    fprintf(ifp,"a%d/",tltptr->ltree->num);
		}
		
		fprintf(ifp,"i%d/",tltptr->rtree->num);
		tltptr  = tltptr->next;
    }
    np = tcounter_f(eptr);
    fprintf(ifp,"0/0  no.parses:%d\n", np);    
    // fprintf(ifp,"0/0\n"); //Original
}

/* Active Edge printing */
void pedge_parse_a(eptr)
Edgeptr  eptr;
{
	ListTreeptr tltptr;
 	int i;
 	int np; /* numparses */

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
		}
		else{
		    fprintf(afp,"a%d/",tltptr->ltree->num);
		}
		
		fprintf(afp,"i%d/",tltptr->rtree->num);
		tltptr  = tltptr->next;
    }
    np = tcounter_f(eptr);
    fprintf(afp,"0/0  no.parses:%d\n", np); 
    // fprintf(afp,"0/0\n"); //Original
}

/* Free Memory in Inactive Chart */
void freememi()
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
	      		}
	      	}
	      }
	  }
}

/* Free Memory in Acitve Chart */
void freemema()
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
	      		}
	      	}
	    }
	}
}



// Note: ltree=Active Edge, rtree=Inactive Edge, Edge Type(0)=lexical node
int tcond(eptr)
Edgeptr eptr; 
{
	int i, j, result;
	ListTreeptr tltptr; 

	// Type=0:lextical, Type=1:see ctab, Type=2:see gramtext in gram-th.h
	printf("eptr(type: (%d) | noedge: %d): %s(%d)\n", eptr->type, eptr->num, ctab[eptr->gram], eptr->gram);

	printf("numparses: %d\n", eptr->numparses);
	if(eptr->type == 0 || eptr->type == 1){
		// printf("[%s ", ctab[eptr->gram]);
		insert(eptr->gram);
		if (eptr->type == 0){
			// printf(" %s ", eptr->word);
			insert(0);	// lexical
		}
	}

	result = 0;
	if(eptr->numparses == 1){
		tltptr = eptr->parse;
		while(tltptr != NULL){		//tltptr==NULL when eptr is lextical
			if(tltptr->ltree == NULL){
				i=1;
				printf("ltree == NULL\n");
			}
			else if(tltptr->ltree != NULL){
				printf("\nLTREE: ");
				i = tcond(tltptr->ltree);
			}

			if(tltptr->rtree == NULL){
				printf("rtree == NULL\n");
			}
			else if(tltptr->rtree != NULL){
				printf("\nRTREE: ");
				tcond(tltptr->rtree);
			}

			result = result + i;
			tltptr = tltptr->next;
		}

		for(j=0;j<result;j++){
			insert(-99);	//bracket
		}

		printf("result: %d\n", result);
		return(result);		// number of bracket
	}

	if(eptr->numparses > 1){
		int np = eptr->numparses;
		int ArraySize = qsize();
		int c=1, tmpArray[ArraySize];
		copyData(tmpArray);		// Copy all global queue values to tmpArray
		printf("copyData()\n");

		tltptr = eptr->parse;
		while(tltptr != NULL){		//tltptr==NULL when eptr is lextical
			if(tltptr->ltree == NULL){
				i=1;
				printf("ltree>1 == NULL\n");
			}
			else if(tltptr->ltree != NULL){
				printf("\nLTREE>1: ");
				i = tcond(tltptr->ltree);
			}

			if(tltptr->rtree == NULL){
				printf("rtree>1 == NULL\n");
			}
			else if(tltptr->rtree != NULL){
				printf("\nRTREE>1: ");
				tcond(tltptr->rtree);
			}

			result = result + i;
			c++;
			printf("c: %d | numparses: %d | edge(type: %d, no: %d)\n", c, np, eptr->type, eptr->num);
			if(c == np){
				for(j=0;j<result;j++){
					insert(-99);	//bracket
				}
				printf("@re: %d Done one parse\n", result);
				insert(-1);	//newline
				insertCopyData(tmpArray, ArraySize);		//insert perfix of new parse
				printf("insertCopyData()\n");
			}
			tltptr = tltptr->next;
			// c++;
		}

		// if(result == 1){
		// 	insert(-99);
		// }
		for(j=0;j<result-1;j++){	//lame debug -1
			insert(-99);	//bracket
		}
		printf("result: %d\n", result);
		return(result);		// number of bracket
		
		free(tmpArray);
	}
	else{
		return 0;
	}

	printf("\n");


}

// numparses counter (get eptr->numparses==0)
int tcounter(eptr)
Edgeptr  eptr;
{
    int  result,i,j;
    ListTreeptr tltptr;
    // printf("Enter tcounter\n");
    // printf("Eptr->gram: %s\n", ctab[eptr->gram]);
    // print_edge(eptr);
    // exit(0);
    // printf("eptr->gram: %d\n", eptr->gram);
    result=0;
    if(eptr->numparses == 0){
    	// printf("eptr->numparses == 0\n");
		tltptr = eptr->parse;
		while(tltptr != NULL){
			// printf("Enter while tltptr!=NULL\n");
			// Left 
		    if(tltptr->ltree == NULL){ 
		    	i=1;
		    	// printf("x1 (if): %s\n", ctab[tltptr->ltree->gram]);
		    	// printf("ltree==null, i=1\n");
		    	// print_edge(eptr);
		    	// exit(0);
		    }
		    else{
		    	// printf("tcounter ltree\n");
		    	// printf("x1 (else): %s\n", ctab[tltptr->ltree->gram]);
		    	// printf("x1 (else): %s | ", ctab[tltptr->ltree->gram]);
		    	// printf("gram:%d, noedge:%d(type=%d), from:%d, to:%d\n", tltptr->ltree->gram, tltptr->ltree->num, tltptr->ltree->type, tltptr->ltree->from, tltptr->ltree->to);
				i=tcounter(tltptr->ltree);
		    	// exit(0);
		    }
		    
		    
		    // Right
		    // printf("Enter j tcounter\n");
		    j=tcounter(tltptr->rtree);
		    // printf("x2: %s | ", ctab[tltptr->rtree->gram]);
		    // printf("gram:%d, noedge:%d(type=%d), from:%d, to:%d\n", tltptr->rtree->gram, tltptr->rtree->num, tltptr->rtree->type, tltptr->rtree->from, tltptr->rtree->to);
		    // printf("i=%d, j=%d, result=%d\n", i,j,result+(i*j));
		    result = result+(i*j);
		   	tltptr = tltptr->next;
		}
		eptr->numparses = result;
		// printf("return result: %d\n", result);
		return(result);
    }
    else{ 
    	// printf("eptr->numparses != 0\n");
    	// printf("return numparses: %d\n", eptr->numparses);
    	return(eptr->numparses); // Lexical
    }
}

int tcounter_f(eptr)
Edgeptr  eptr;
{
    int  result,i,j;
    ListTreeptr tltptr;
    result=0;
    if(eptr->numparses == 0){
		tltptr = eptr->parse;
		while(tltptr != NULL){
		    if(tltptr->ltree == NULL){ 
		    	i=1;
		    }
		    else{
				i=tcounter_f(tltptr->ltree);
		    }

		    j=tcounter_f(tltptr->rtree);
		    result = result+(i*j);
		   	tltptr = tltptr->next;
		}
		eptr->numparses = result;
		return(result);
    }
    else{ 
    	return(eptr->numparses); // Lexical
    }
}

int tconst(eptr)
Edgeptr  eptr;
{
    int result,i,j;
    int a,b;
    ListTreeptr tltptr;
    // print_edge(eptr);

    result=0;
    if(eptr->numparses == 0){
		tltptr = eptr->parse;
		while(tltptr != NULL){
			// Left 
		    if(tltptr->ltree == NULL){ 
		    	i=1;
		    }
		    else{
				i=tconst(tltptr->ltree);
		    }
		    
		    // Right
		    j=tconst(tltptr->rtree);
		    result = result+(i*j);
		    tltptr = tltptr->next;
		}
		eptr->numparses = result;
		return(result);
    }
    else{ 
    	return(eptr->numparses); // Lexical
    }
}

void parse()
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
				    // printf("achart[%d][%d]: %s\n",i,eptr->from, achart[i][eptr->from]);
				    while( telistptr != NULL ){
				    	// printf("Combined\n");
						combine(telistptr->edge,eptr);
						telistptr = telistptr->next;
				    }
				}
		    }
		    else{
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

void provoke(eptr)
Edgeptr  eptr;
{
    int  i;
    Edgeptr   teptr;
    EListptr  telistptr;
    int j;

    for( i=1 ; i<MaxGram ; i++ ){
		if( grammar[i][0] == 0 ){ 
		    break; 
		}
		if( grammar[i][1] == eptr->gram ){
			// printf("grammar[%d][1]: %d, grammar[%d][1]: %d, eptr->gram: %d\n",i,grammar[i][0],i,grammar[i][1], eptr->gram);
			// exit(0);
	    	allocedge(&teptr);
		    teptr->from = eptr->from;
		    teptr->to   = eptr->to;
		    teptr->numparses = 0;  	/* initial value */
		    if( grammar[i][2] == 0 ){
				teptr->type = 1;
				teptr->gram = grammar[i][0];
		    }
		    else{ 
		    	teptr->type = 2; 
		    	teptr->gram = i; 
		    	teptr->dot = 1; 
		    }
		    
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
void combine(eptr1,eptr2)
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
	}
	else{ 
	    teptr->type = 2;
	    teptr->gram = eptr1->gram;
	    teptr->dot = (eptr1->dot)+1; 
	}

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

// Check whether If not duplicate create new edge to ichart or achart (ord(i|a)chart also) (1:dup, 0:otherwise)
int dup_check(eptr)
Edgeptr  eptr;
{
    int  i;
    EListptr  tmpptr;
    if(eptr->type !=2){ //When type != Active edge
    	// print_edge(eptr);
    	// printf("eptr->type is not active edge != 2\n");
		tmpptr = ichart[eptr->from][eptr->to];  // At the 1st will be NULL (Assigned)
		// printf("tmpptr: %s\n", tmpptr);
		// exit(0);
		while(tmpptr != NULL){   //tmp == NULL when eptr == lexical
		    if(eptr->gram == tmpptr->edge->gram){
		    	// printf("Enter IF statement: Gram Matched\n");
				eptr->parse->next = tmpptr->edge->parse;
				tmpptr->edge->parse = eptr->parse;
				freeedgeproc(eptr);
				// printf("return 1\n");
				return(1);
		    }
		    else{
		    	// printf("Enter ELSE statement: Gram Unmatched\n");		    	
		    	tmpptr = tmpptr->next;
		    }
		}

		// printf("Assigning Process\n");
		allocedgelist(&tmpptr);
	/*	ichart[eptr->from][eptr->to]->previous =  tmpptr; */
		tmpptr->edge = eptr;
		ordichart[niedge] = eptr;
		eptr->num = niedge++;
		tmpptr->next = ichart[eptr->from][eptr->to];
		tmpptr->previous = NULL;
		ichart[eptr->from][eptr->to] = tmpptr;
		// printf("return 0\n");
		// printf("END dup_check\n");
		return(0);
    }
    else{ //When type == Active edge
    	// printf("eptr->type is active edge == 2\n");
		tmpptr = achart[eptr->from][eptr->to];
		while(tmpptr != NULL){
		    if(eptr->gram == tmpptr->edge->gram && eptr->dot == tmpptr->edge->dot){
				eptr->parse->next = tmpptr->edge->parse;
				tmpptr->edge->parse = eptr->parse;
				freeedgeproc(eptr);
				return(1);
		    }
		    else{tmpptr = tmpptr->next;}
		}
		allocedgelist(&tmpptr);
	/*	achart[eptr->from][eptr->to]->previous =  tmpptr; */
		tmpptr->edge = eptr;
		ordachart[naedge] = eptr;
		eptr->num = naedge++;
		tmpptr->next = achart[eptr->from][eptr->to];
		tmpptr->previous = NULL;
		achart[eptr->from][eptr->to] = tmpptr;
		// printf("END dup_check\n");
		return(0);
    }
    
}

/* Insert Lexical Edge */
// Bug: Catlen is too short for some Thai word
void initiate()
{
    int  i, j, state=0, wc;
    Edgeptr   tmpeptr;
    EListptr  tagendaptr;
    char tmpcat[CatLen], tmpword[CatLen];
    
    for( i=nc-1; i>=0; i-- ){
		state=0;
		// printf("cinsent[%d]: %s\n", i, cinsent[i]);
		printf("word[%d]: %s\n", i, word[i]);
		strcpy(tmpcat,cinsent[i]);
		strcpy(tmpword,word[i]);

		// printf("\n-------------\nBefore Trancat.c\n");
		// printf("tmpcat:%s <-- cinsent[%d]: %s\n", tmpcat, i, cinsent[i]);
		// printf("tmpword:%s <-- wordcat[%d]: %s\n", tmpword, i, word[i]);
		// printf("-------------\n\n");

		wc=0;
		/* transfer cat from those of Tagger to those of grammar */
		trancat(&cinsent[i][0],&word[i][0],&wc);
		// printf("Done trancat.c!! | wc=%d\n", wc);
		// printwordcat();

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
		    // printf("agendaptr: %s\n", agendaptr->edge->word);
		}
		// printf("Done Allocate!!\n\n");
    }
}

/* Break off sentence into array */
/* Since each Thai character consists of 3 bytes, So need to use strlen (not strlength) */
/* Bug(breakoff01): A sentence need a whitespace at the end of the sentence -->  */
int breakoff(buffer)
char *buffer;
{
	int buflen;
 	int i=0, j=0, p=0, n=0, m=0;
 	char tmpchar[CatLen];

 	while( buffer[p]==' ' | buffer[p]=='\t' | buffer[p]=='\n' ){ p++; }	  /* Deleting useless head */
 	while( buffer[p]=='%' ){ return(0); }   /* For comment statement */

 	buflen = strlen(buffer);  
 	// printf("buflen: %d\n", buflen); 
 	// printf("%s: %d\n", buffer, buflen);
 	// printf("p = %d\n", p);
  	while( p<=buflen ){			  /* Seperate buffer and Keep tokens in cinsent */
    	if( buffer[p] == '\t' | buffer[p] == ' ' | buffer[p] == '\n' | buffer[p] == '\0' ){   /* Add "buffer[p] == ''" to conquer Bug(breakoff01) */
		  	word[i][j] = '\0';
		  	n=j;
		  	
	  		/* Finding a non-terminal (word eg. I You, ...) */
	  		for( ; j>0 ; j-- ){
	      		if ( word[i][j] == '/' ){ break; }
	  		}

		  	word[i][j++] = '\0';
		  	// printf("1 - word: %s\n", word[i]);
		  	m=0;
		  	
		  	/* Finding a (pre)-terminal (cat eg. n, v, ..) */
		  	for( ; j<n ; j++ ){
		      cinsent[i][m++]=word[i][j];
		  	}
		  	cinsent[i][m] = '\0';
		  	// printf("cinsent: %s\n", cinsent[i]);
		  	i++; j=0;
		  
		  	/* Add "buffer[p] == ''" to conquer Bug(breakoff01) */
		  	while( buffer[p] == ' ' | buffer[p] == '\t' | buffer[p] == '\n' | buffer[p] == '\0'){ p++; }	 /* Deleting useless tokens */ 
      	}
     	else{  
	  		word[i][j++] = buffer[p++]; 
	  	// printf("2 - word: %s\n", word[i]);
     	}
      	// printf("p: %d\n", p);
 	}
 	// printf("Return: %d\n", i);
 	return(i);
}

size_t strlength(str)
const char* str;
{
	int i=0,count=0;

 	while (str[i]) {
   		if ((str[i] & 0xC0) != 0x80) count++;
    	i++;
 	}
 	return (count);
}

void print_edge(eptr)
Edgeptr eptr;
{
	printf("=====Edge Printing====\n");
	printf("Edge Type: %d, Edge Number: %d, No.Error: %d\n", eptr->type, eptr->num, eptr->err);
	printf("From: %d, To: %d\n", eptr->from, eptr->to);
	printf("Grammar Rule Number: %d\n", eptr->gram);
	printf("Dot Position: %d\n", eptr->dot);
	printf("No.parses: %d\n", eptr->numparses);
	printf("Word: %s\n", eptr->word);
	printf("======================\n");

}


