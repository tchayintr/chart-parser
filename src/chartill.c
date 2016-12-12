/*
 *  $ JAIST: chart.c,v 0.1000 1995/10/04 20:04:01 $
 *
 *  @(#)chart.c  04/10/1995  By Thanaruk Theeramunkong
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "def.h"
#include "chart.h"
#include "gram.h"


#define DEBUG
// #define ERROR
// #define INFO1
// #define MEM

#define INFO2
#define INFO3

#define SENTENCE "sentence"
#define PARSELEN 4096

void initialcomparse();
void pmemi();
void pmema();
void pmemc();
void pmemas();
void pedge_parse_i(Edgeptr);
void pedge_parse_a(Edgeptr);
void pedge_parse_ci(Edgeptr);
void pedge_parse_ca(Edgeptr);
void freememi();
void freemema();
void freeagenda();
int tcounter(Edgeptr);
void provoke(Edgeptr);
void combine(Edgeptr eptr1, Edgeptr eptr2);
int dup_check(Edgeptr);
void initiate();
int breakoff(char*);
void fd_cats_betw(int s, int e, int* exc, int* nex1, int* nex2, int* nec, int* nnc1, int* nnc2);
void pilledge();
void parse();
void parse_ill();
int seterror(int type,int s,int e);
void provoke_ill(Edgeptr);
void insert_agenda(Edgeptr eptr, EListptr elistptr);
void copy_edge(Edgeptr eptr1, Edgeptr eptr2);
int tfindgram(int lhs, int rhs);
int expandtree(Edgeptr eptr, int n);

// char inactivehead[] = "/usr/tmp/__i";
// char activehead[]   = "/usr/tmp/__a";
// char comphead[] = "/usr/tmp/__c";

char inactivehead[] = "./outputs/__i";
char activehead[]   = "./outputs/__a";
char comphead[] = "./outputs/__c";

FILE *ifp,*afp,*cfp;

char cinsent[SentLen][CatLen];    /* Categories in Sentence */
char word[SentLen][WordLen];    /* Words in Sentence */
EListptr ichart[SentLen][SentLen];  /* Inactive Edge pointer */
EListptr achart[SentLen][SentLen];  /* Active Edge pointer */
EListptr agenda[MaxAgenda];   /* agenda which are a set of lists
                                           indexed by the number of errors */
Edgeptr  ordichart[ChartMax];   /* i edge indexed by ordinal */
Edgeptr  ordachart[ChartMax];           /* a edge indexed by ordinal */
int      comiparse[ChartMax];   /* complete i parses used */
int      comaparse[ChartMax];   /* complete a parses used */
int      comsparse[ChartMax];   /* complete assumptions used */
int      wordcat[MaxCat];   /* All categories of a word */
int  gcounter[GramNum+1];   /* grammar counter */
int      allgcounter;     /* Counter all used grammar */

struct EList tail = {NULL, NULL, NULL}; /* the tail cell of an edge list */
struct Edge tailedge = {0, 0, 0, 0, 0, 0, 0, 0, "", NULL, NULL};
                                        /* the tail edge */
struct ListTree tailtree = {NULL, NULL, NULL}; /* the tail tree */
EListptr freeelist=&tail;   /* A list of Free Edge list cells */
Edgeptr  freeedge=&tailedge;    /* A list of Free Edges */
ListTreeptr  freeltree=&tailtree; /* A list of Free Trees */
int  nc;        /* The number of categories in Sent */
int  niedge=1;        /* The ordinal number of inactive */
int  naedge=1;        /* The ordinal number of active */
int  minlength=100,maxlength=0;   /* The max-min length of sentence */
EListptr tmpelptr;      /* Temporary edge list pointer */
char buffer[BufSize];     /* Temporary buffer */
int  elimit;              /* elimit => limit error */
int  wlimit;        /* wlimit => wide limit */
int  illflag=0;       /* illflag=1 for ill-formed input */
int  info=0;        /* info=1 when print out edges */
int  topcatnum;       /* Top category number */
int  sentencenum;     /* current sentence number */

/* For count the number of alloc and free memory */
int  anumedge=0;
int  anumelist=0;
int  anumltree=0;
int  fnumedge=0;
int  fnumelist=0;
int  fnumltree=0;

/* For count the list of memory */

int  medgelen=0;
int  mlistlen=0;
int  mtreelen=0;

int main( argc, argv )
int  argc;
char **argv;
{
  char ifname[FNameLen],afname[FNameLen]; /* output inactive and active fname*/
  char cfname[FNameLen] ;
  int  i,j,initelimit,initwlimit;
  long k;

  initelimit=0; initwlimit=2;
  medgelen=0; mlistlen=0; mtreelen=0;
  sentencenum=1; allgcounter=0;

/* find the index of the category SENTENCE */
  i=0; j=0; info=0;
  for( j=1 ; j<2*MaxCat ; j++ ){
      if( ctab[j][0] == '\0' ){
    fprintf(stderr,"\"%s\" is not a vilid category\n",\
      SENTENCE);
    exit(0);
      }
      if( !strcmp(ctab[j],SENTENCE) ){
    topcatnum = j;
    break;   }
  }
  if( argc > 5 || argc == 1) {
      fprintf(stderr,"Usage: %s [arg1] [no.err] [wlimit] [info]\n",*argv);
      fprintf(stderr,"       (info for printing edge info. to a file)\n");
      exit(0); }
  if( argc == 5 ){
      info = atoi(*(argv+4));
  }
  if( argc == 2 || info == 1 || info==2 || info==3 ){
      strcpy(ifname,inactivehead);
      strcpy(afname,activehead);
      strcpy(cfname,comphead);
      strcat(ifname,*(argv+1));   /* Argv+1 is the ordinal number. */
      strcat(afname,*(argv+1));   /* Argv+1 is the ordinal number. */
      strcat(cfname,*(argv+1));   /* Argv+1 is the ordinal number. */
  }
  
  if( argc >= 3 ){
      initelimit = atoi(*(argv+2));
      fprintf(stderr,    "No.of errors    is set to %d\n",initelimit);
      if( argc >= 4 ){
    initwlimit = atoi(*(argv+3));
    fprintf(stderr,"The error width is set to %d\n",initwlimit);
      }
  }
  if( info==2 || info==3){
      open_file_write(cfname,&cfp);
      fprintf(stderr,"cfname = %s \n",cfname);
  }

  for( i=0 ; i<MaxAgenda ; i++ ){
      agenda[i] = &tail;
  }
  for( i=0; i<ChartMax; i++ ){
      comiparse[i]=0; comaparse[i]=0; comsparse[i]=0;
  }
  for( i=0; i<GramNum+1; i++ ){
      gcounter[i]=0;
  }

  while( NULL != fgets(buffer,BufSize,stdin) ){
      anumedge=0;
      anumelist=0;
      anumltree=0;
      fnumedge=0;
      fnumelist=0;
      fnumltree=0;

      elimit=initelimit;  wlimit=initwlimit;
      k=0;
#ifdef DEBUG
      fprintf(stderr,"In While loop:Buffer = %s",buffer);
#endif
#ifdef INFO1
      fprintf(stderr,"%d\n",sentencenum);
#endif

      if( buffer[0] == 10 ){ break; }
      for( i=0 ; i<SentLen ; i++ ){
        for( j=0 ; j<SentLen ; j++ ){
         ichart[i][j] = NULL;
         achart[i][j] = NULL; } 
      }
      
      nc = breakoff(buffer);  /* Break off sentence into array */
      niedge=1;     /* The ordinal number of inactive */
      naedge=1;     /* The ordinal number of active */

      initiate();
#ifdef DEBUG
      fprintf(stderr,"begin parse\n");
#endif
      parse();
#ifdef DEBUG
      fprintf(stderr,"end   parse\n");
#endif

      illflag=0;
      tmpelptr = ichart[0][nc];
      while( tmpelptr != NULL ){
    if(tmpelptr->edge->gram == topcatnum){ 
        comiparse[tmpelptr->edge->num]=1;
        k=tcounter(tmpelptr->edge);
#ifdef INFO2
        printf("Sentence No.%d[%d] has %d errors and ",\
          sentencenum,nc,0);
        printf("the number of parse is %d\n",k);
#endif        
/*        illflag=0; */
        break;
    }
    tmpelptr = tmpelptr->next;
      }
      if( tmpelptr==NULL ){ illflag=1; }
      if( illflag==1 && elimit != 0 ){
#ifdef DEBUG
    printf("In ill parsing\n");
    fprintf(stderr,"begin ill-formed parsing process\n");
#endif
    pilledge();
    parse_ill();
#ifdef DEBUG
    fprintf(stderr,"end   ill-formed parsing process\n");
#endif
    tmpelptr = ichart[0][nc];
    while( tmpelptr != NULL ){
        if(tmpelptr->edge->gram == topcatnum){ 
      comiparse[tmpelptr->edge->num]=1;
      k=tcounter(tmpelptr->edge);
#ifdef INFO2
      printf("Sentence No.%d[%d] has %d errors and ",\
        sentencenum,nc,elimit);
      printf("the number of parse is %d\n",k);
#endif        
                  /* taking each tree from the parse forest */
      for( i=0; i<k; i++ ){
          expandtree(tmpelptr->edge,i);
      }
      break;
        }
        tmpelptr = tmpelptr->next;
    }
      }
      if( argc == 2 || info == 1){
    open_file_write(ifname,&ifp);
    open_file_write(afname,&afp);
    open_file_write(cfname,&cfp);

    fprintf(stderr,"ifname = %s \n",ifname);
    fprintf(stderr,"afname = %s \n",afname);
    fprintf(stderr,"cfname = %s \n",cfname);
    pmemi();    /* print inactive edge */
    pmema();    /* print active edge */
    if( illflag==1 ){ 
        pmemas();   /* print assumption parse */
    }else {
        pmemc();    /* print complete parse */
    }
    fclose(afp);
    fclose(ifp);
    fclose(cfp);
      }
      if( info==2 ){
    if( illflag==1 ){ 
        pmemas();   /* print assumption parse */
    }
      }
      if( info==3 ){
    if( illflag==1 ){ 
        pmemas();   /* print assumption parse */
        pmemc();    /* print complete parse */
    }
      }

      freememi(); /* Free Memory in Inactive Chart */
      freemema(); /* Free Memory in Active Chart   */
      freeagenda(); /* Free all members in Agenda    */

      sentencenum++; /* Increase the ordinal number of the sentence */
      if( nc>maxlength ){ maxlength = nc; }
      if( nc<minlength && nc != 0 ){ minlength = nc; }

#ifdef MEM
      printf("anumedge  = %d : fnumedge  = %d\n",anumedge,fnumedge);
      printf("anumelist = %d : fnumelist = %d\n",anumelist,fnumelist);
      printf("anumltree = %d : fnumltree = %d\n",anumltree,fnumltree);
      initialcomparse();
#endif
  }
#ifdef INFO1
  fprintf(stderr,"minlength = %d, maxlength = %d\n",minlength,maxlength); 
#endif
  if( info==2 ){ fclose(cfp); }
#ifdef INFO3
  // printf("illflag: %d\n", illflag);
  if( illflag==0 ){ 
      for( i=0; i<GramNum+1; i++ ){
    if( gcounter[i]!=0 ){
        printf("[%d] %s is used for %d times\n",\
         i,gramtext[i],gcounter[i]);
    }
    allgcounter+=gcounter[i];
      }
      printf("The number of used grammar %d.\n",allgcounter);
  }
#endif
  exit(0);
}

/* Initiate complete parse */
void initialcomparse()
{
    int i;
    for( i=0; i<niedge; i++ ){
  comiparse[i]=0;
  comsparse[i]=0;
    }
    for( i=0; i<naedge; i++ ){
  comaparse[i]=0;
    }
}

/* Print Memory in Inactive Chart */
void pmemi()
{
  int i,j;

  fprintf(ifp,"%s",buffer);
  for( i=1 ; i<niedge ; i++ ){
      pedge_parse_i(ordichart[i]);
  }
}

/* Print Memory in Active Chart */
void pmema()
{
  int i,j;

  fprintf(afp,"%s",buffer);  
  for( i=1 ; i<naedge ; i++ ){
      pedge_parse_a(ordachart[i]);
  }
}

/* Print Edges which are used for Complete Parse Tree */
void pmemc()
{
  int i,j;

  fprintf(cfp,"%s",buffer);  
  fprintf(cfp,"==inactive==\n");  
  for( i=1 ; i<niedge ; i++ ){
      if(comiparse[i]==1){
    pedge_parse_ci(ordichart[i]);
      }
  }
  fprintf(cfp,"==active==\n");
  for( i=1 ; i<naedge ; i++ ){
      if(comaparse[i]==1){
    pedge_parse_ca(ordachart[i]);
      }
  }
}

/* Print Assumption Edge */
void pmemas()
{
  int i,j,buflen1;
  char tbuffer[BufSize];

  fprintf(cfp,"Sen.No.%d> 0 ",sentencenum);
  buflen1 = strlen(buffer);
  j=1;
  for( i=0; i<buflen1; i++ ){
      if( buffer[i] == ' ' ){
    fprintf(cfp," %d ",j++);
      }else{ fprintf(cfp,"%c",buffer[i]); }
  }      
  fprintf(cfp,"============ begin A ============\n");
  for( i=1 ; i<niedge ; i++ ){
      if(comsparse[i]==1){
    pedge_parse_ci(ordichart[i]);
      }
  }
  fprintf(cfp,"============  end A  ============\n");
}

void pedge_parse_i(eptr)
Edgeptr  eptr;
{
    ListTreeptr tltptr;
    int i;

    tltptr = eptr->parse;
    fprintf(ifp,"i%d ",eptr->num);
    fprintf(ifp,"%d ",eptr->from);
    fprintf(ifp,"%d ",eptr->to);
    if( eptr->gram==-1 ){ fprintf(ifp,"extra "); }else{
    fprintf(ifp,"%s ",ctab[eptr->gram]); }

    while(tltptr != NULL){
  if(tltptr->ltree == NULL){
      fprintf(ifp,"a0/"); 
  }else{
      fprintf(ifp,"a%d/",tltptr->ltree->num);
  }
  if(tltptr->rtree == NULL){
      fprintf(ifp,"i-1/"); 
  }else{
      fprintf(ifp,"i%d/",tltptr->rtree->num);
  }
  tltptr  = tltptr->next;
    }

    fprintf(ifp,"0/0 ");
    fprintf(ifp,"%d\n",eptr->err);
}

void pedge_parse_a(eptr)
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
  if(tltptr->rtree == NULL){
      fprintf(afp,"i-1/"); 
  }else{
      fprintf(afp,"i%d/",tltptr->rtree->num);
  }
  tltptr  = tltptr->next;
    }
    fprintf(afp,"0/0 ");
    fprintf(afp,"%d\n",eptr->err);
}

void pedge_parse_ci(eptr)
Edgeptr  eptr;
{
    ListTreeptr tltptr;
    int i;

    tltptr = eptr->parse;
    fprintf(cfp,"i%d ",eptr->num);
    fprintf(cfp,"%d ",eptr->type);
    fprintf(cfp,"%d ",eptr->from);
    fprintf(cfp,"%d ",eptr->to);
    if( eptr->gram==-1 ){ fprintf(cfp,"extra "); }else{
    fprintf(cfp,"%s ",ctab[eptr->gram]); }

    while(tltptr != NULL){
  if(tltptr->ltree == NULL){
      fprintf(cfp,"a0/"); 
  }else{
      fprintf(cfp,"a%d/",tltptr->ltree->num);
  }
  if(tltptr->rtree == NULL){
      fprintf(cfp,"i-1/"); 
  }else{
      fprintf(cfp,"i%d/",tltptr->rtree->num);
  }
  tltptr  = tltptr->next;
    }

    fprintf(cfp,"0/0 ");
    fprintf(cfp,"%d\n",eptr->err);
}

void pedge_parse_ca(eptr)
Edgeptr  eptr;
{
    ListTreeptr tltptr;
    int i;

    tltptr = eptr->parse;
    fprintf(cfp,"a%d ",eptr->num);
    fprintf(cfp,"%d ",eptr->from);
    fprintf(cfp,"%d ",eptr->to);
    fprintf(cfp,"%s->",ctab[grammar[eptr->gram][0]]);
    for ( i=0; i<eptr->dot ; i++ ){
  fprintf(cfp,"%s,",ctab[grammar[eptr->gram][i+1]]);
    }
    fprintf(cfp,"|,");
    for ( i=eptr->dot; grammar[eptr->gram][i+1]!=0 ; i++ ){
  fprintf(cfp,"%s,",ctab[grammar[eptr->gram][i+1]]);
    }
    fprintf(cfp,"%d ",eptr->gram);
    while(tltptr != NULL){
  if(tltptr->ltree == NULL){
      fprintf(cfp,"a0/"); 
  }else{
      fprintf(cfp,"a%d/",tltptr->ltree->num);
  }
  if(tltptr->rtree == NULL){
      fprintf(cfp,"i-1/"); 
  }else{
      fprintf(cfp,"i%d/",tltptr->rtree->num);
  }
  tltptr  = tltptr->next;
    }
    fprintf(cfp,"0/0 ");
    fprintf(cfp,"%d\n",eptr->err);
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
        } } } }
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
        } } } }
}

void freeagenda()
{
    int       i;
    EListptr  tagendaptr;
    Edgeptr   teptr;

    for( i=0; i<MaxAgenda; i++ ){
  while(agenda[i] != &tail){
      teptr = agenda[i]->edge;
      tagendaptr = agenda[i];
      agenda[i] = agenda[i]->next;
      freeedge_parse(teptr);
      freeelistproc(tagendaptr);
  }
    }
}

int tcounter(eptr)
Edgeptr  eptr;
{
    int  result, i, j, g; /* g for the currently used grammar */
    int  type;  /* type stands for gram with 1 rhs =0 else =1 */
    ListTreeptr tltptr;

    result=0;
    if(eptr->numparses == 0){
  tltptr = eptr->parse;
  while(tltptr != NULL){
      if(tltptr->ltree==NULL){ i=1; type=0; }else{
    if( tltptr->ltree->type==2 ){
        comaparse[tltptr->ltree->num]=1;
    }else{ 
        comiparse[tltptr->ltree->num]=1;
        if( tltptr->ltree->type!=0 &&
            tltptr->ltree->type!=1 &&
            tltptr->ltree->type!=2 ){
      comsparse[tltptr->ltree->num]=1;
        }
    }
    type=1;
    i=tcounter(tltptr->ltree);
      }
      if(tltptr->rtree==NULL){ j=1; }else{
    if( tltptr->rtree->type==2 ){
        comaparse[tltptr->rtree->num]=1;
    }else{ 
        comiparse[tltptr->rtree->num]=1;
        if( tltptr->rtree->type!=0 &&
            tltptr->rtree->type!=1 &&
            tltptr->rtree->type!=2 ){
      comsparse[tltptr->rtree->num]=1;
        }
    }
    j=tcounter(tltptr->rtree);
      }
      if( illflag==0 && eptr->type==1 ){
    if( type==0 ){ g=tfindgram(eptr->gram,tltptr->rtree->gram); }
    else{ g=tltptr->ltree->gram; }
    gcounter[g]=gcounter[g]+(i*j);
      }
      result = result+(i*j);
      tltptr = tltptr->next;
    
  }
  eptr->numparses = result;
  return(result);
    }else{ return(eptr->numparses); }
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
      break; }
  if( grammar[i][1] == eptr->gram ){
      allocedge(&teptr);
      allocedgelist(&telistptr);
      allocltree(&(teptr->parse));
      teptr->from = eptr->from;  teptr->to = eptr->to;
      teptr->err  = eptr->err;
      teptr->numparses = 0;   /* initial value */
      if( grammar[i][2] == 0 ){
    teptr->type = 1;
    teptr->gram = grammar[i][0];
      }else{ teptr->type = 2; teptr->gram = i; teptr->dot = 1; }
      teptr->parse->ltree = NULL;
      teptr->parse->rtree = eptr;
      teptr->parse->next  = NULL;
      telistptr->edge = teptr;
      telistptr->previous = NULL;
      insert_agenda(teptr, telistptr);
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

    if( eptr2->gram==-1){
  if( (eptr1->err+eptr2->err) > elimit ){ return; }
  allocedge(&teptr);
  allocedgelist(&telistptr);
  allocltree(&(teptr->parse));
  teptr->from = eptr1->from;   teptr->to = eptr2->to;
  teptr->err  = (eptr1->err)+(eptr2->err);
  teptr->numparses = 0;    /* initial value */
  teptr->type = 2;
  teptr->gram = eptr1->gram;
  teptr->dot  = eptr1->dot;
  teptr->parse->ltree = eptr1;
  teptr->parse->rtree = eptr2;
  teptr->parse->next  = NULL;
  telistptr->edge = teptr;
  telistptr->previous = NULL;
  insert_agenda(teptr, telistptr);
  return;
    }
    if( grammar[eptr1->gram][(eptr1->dot)+1] == eptr2->gram ){
  if( ((eptr1->err)+(eptr2->err)) > elimit ){ return; }
  allocedge(&teptr);
  allocedgelist(&telistptr);
  allocltree(&(teptr->parse));
  teptr->from = eptr1->from;   teptr->to = eptr2->to;
  teptr->err  = (eptr1->err)+(eptr2->err);
  teptr->numparses = 0;    /* initial value */
  if( grammar[eptr1->gram][(eptr1->dot)+2] == 0 ){
      teptr->type = 1;
      teptr->gram = grammar[eptr1->gram][0];
  }else{ 
      teptr->type = 2;
      teptr->gram = eptr1->gram;
      teptr->dot = (eptr1->dot)+1; }
  teptr->parse->ltree = eptr1;
  teptr->parse->rtree = eptr2;
  teptr->parse->next  = NULL;
  telistptr->edge = teptr;
  telistptr->previous = NULL;
  insert_agenda(teptr, telistptr);
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
      if(eptr->gram == tmpptr->edge->gram ){
    if(eptr->err == tmpptr->edge->err){
        eptr->parse->next = tmpptr->edge->parse;
        tmpptr->edge->parse = eptr->parse;
        freeedgeproc(eptr);
    }else{
        if(eptr->err > tmpptr->edge->err){
      freeedge_parse(eptr);
        }else{
      freeparse(tmpptr->edge->parse);
      copy_edge(eptr,tmpptr->edge);
      freeedgeproc(eptr);
        }
    }
    return(1);
      }else{tmpptr = tmpptr->next;}
  }
  allocedgelist(&tmpptr);
/*  ichart[eptr->from][eptr->to]->previous =  tmpptr; */
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
    if(eptr->err == tmpptr->edge->err){
        eptr->parse->next = tmpptr->edge->parse;
        tmpptr->edge->parse = eptr->parse;
        freeedgeproc(eptr);
    }else{
        if(eptr->err > tmpptr->edge->err){
      freeedge_parse(eptr);
        }else{
      freeparse(tmpptr->edge->parse);
      copy_edge(eptr,tmpptr->edge);
      freeedgeproc(eptr);
        }
    }
    return(1);
      }else{tmpptr = tmpptr->next;}
  }
  allocedgelist(&tmpptr);
/*  achart[eptr->from][eptr->to]->previous =  tmpptr; */
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
void initiate()
{
    int  i, j, state=0, wc;
    Edgeptr   teptr;
    EListptr  telistptr;
    
    for( i=nc-1; i>=0; i-- ){
  state=0;
  wc=0;
  /* transfer cat from those of Tagger to those of grammar */
  trancat(&cinsent[i][0],&word[i][0],&wc);

#ifdef DEBUG
  fprintf(stderr,"cinsent[%d] = %s/%s, wc => %d :",\
    i,cinsent[i],word[i],wc);
  for( j=0; j<wc; j++ ){
      fprintf(stderr,"%d ,",wordcat[j]);
  }
  fprintf(stderr,"\n");
#endif

  for( j=0; j<wc; j++ ){
      allocedge(&teptr);          /* Allocate Area for Edge */
      allocedgelist(&telistptr); /* Allocate Area for Eptr(Agenda) */
      teptr->type = 0;
      teptr->err  = 0;
      teptr->from = i;
      teptr->to   = i+1;
      teptr->gram = wordcat[j];
      teptr->numparses = 1;    /* Number of parses */
      teptr->parse = NULL;     /* Lexical edge has null as its parse */
      strcpy(teptr->word, word[i]);
      telistptr->edge = teptr;
      telistptr->previous = NULL;
      insert_agenda(teptr, telistptr);
  }
    }
}

/* Break off sentence into array */
int breakoff(buffer)
char *buffer;
{
  int buflen;
  int i=0, j=0, p=0, n=0, m=0;

  while( buffer[p]==' ' | buffer[p]=='\t' |
   buffer[p]=='\n' ){
      p++; }          /* Deleting useless head */
  while( buffer[p]=='%' ){ return(0); }   /* For comment statement */

  buflen = strlen(buffer);
  while( p<=buflen ){       /* Seperate buffer and Keep
               tokens in cinsent */
      if( buffer[p] == '\t' | buffer[p] == ' ' |
    buffer[p] == '\n' ){
    word[i][j] = '\0';
    n=j;
    for( ; j>0 ; j-- ){
        if ( word[i][j] == '/' ){
      break; }
    }
    word[i][j++] = '\0';
    m=0;
    for( ; j<n ; j++ ){
        cinsent[i][m++]=word[i][j];
    }
    cinsent[i][m] = '\0';
    i++; j=0;
    while( buffer[p] == ' ' | buffer[p] == '\t' |
     buffer[p] == '\n' ){
        p++; }        /* Deleting useless tokens */
      }else{  
    word[i][j++] = buffer[p++]; 
      } 
  }
  return(i);
}

void fd_cats_betw(s,e,exc,nex1,nex2,nec,nnc1,nnc2)
int s, e;      /* an array of (non)existing category between s,e */
int *exc, *nex1, *nex2, *nec, *nnc1, *nnc2;
{
    int i,j,state;
    EListptr  teptr;

    teptr = ichart[s][e];
    i=0; *nec=0, *nnc1=0, *nnc2=0;
    while(teptr != NULL){
  exc[i++] = teptr->edge->gram;
  teptr = teptr->next;
    }
    *nec=i;
    if( *nec == 0 ){ *nnc1=0; *nnc2=0; return; }
    for( i=1; i<=TermNum; i++ ){
  state=0;
  for( j=0; j<*nec; j++ ){
      if( i==exc[j] ){ state=1; break; }
  }
  if(state==0){ nex1[(*nnc1)++]=i; }
    }
    for( i=TermNum+1; i<=CatNum; i++ ){
  state=0;
  for( j=0; j<*nec; j++ ){
      if( i==exc[j] ){ state=1; break; }
  }
  if(state==0){ nex2[(*nnc2)++]=i; }
    }
}

void pilledge()   /* Propose ill-formed edges */
{
    int  i, j, k, s, state=0;
    int  nec=0, nnc1=0, nnc2=0; /* nec=existcat, nnc1(2)=nonexist(non)term */
    Edgeptr   teptr;
    EListptr  telistptr;
    int existc[MaxCat];                  /* existc = cats between i,j */
    int nonexistc1[MaxCat], nonexistc2[MaxCat]; 
                             /* nonexistc1(2) Nonexist (Non)Term cats */

    for( j=0; j<=nc; j++ ){
  /* Extra and Substituted Constitute edges */
  if(j-wlimit<0) { s=0; }else{ s = j-wlimit; }
  for(i=s; i<j; i++){
      fd_cats_betw(i,j,&existc[0],&nonexistc1[0],&nonexistc2, &nec,&nnc1,&nnc2);

      /* Extra */
      allocedge(&teptr);
      allocedgelist(&telistptr);
      teptr->type = 3;
      teptr->err  = seterror(3,i,j);
      teptr->from = i;
      teptr->to   = j;
      teptr->gram = -1;
      teptr->numparses = 1;
      teptr->parse=NULL;
      strcpy(teptr->word, "");
      telistptr->edge = teptr;
      telistptr->previous = NULL;
      insert_agenda(teptr, telistptr);

      if( nec!=0 ){
    /* Substituted */
    for( k=0; k<nnc2; k++ ){
        allocedge(&teptr);
        allocedgelist(&telistptr);
        allocltree(&(teptr->parse));
        teptr->type = 5;
        teptr->err  = seterror(5,i,j);
        teptr->from = i;
        teptr->to   = j;
        teptr->gram = nonexistc2[k];
        teptr->numparses = 1;
        teptr->parse->ltree = NULL;
        teptr->parse->rtree = NULL;
        teptr->parse->next = NULL;
        telistptr->edge = teptr;
        telistptr->previous = NULL;
        insert_agenda(teptr, telistptr);
    }
    if( j==i+1 ){
        for( k=0; k<nnc1; k++ ){
      allocedge(&teptr);
      allocedgelist(&telistptr);
      teptr->type = 5;
      teptr->err  = seterror(5,i,j);
      teptr->from = i;
      teptr->to   = j;
      teptr->gram = nonexistc1[k];
      teptr->numparses = 1;
      teptr->parse = NULL;
      strcpy(teptr->word,word[i]);
      telistptr->edge = teptr;
      telistptr->previous = NULL;
      insert_agenda(teptr, telistptr);
        }
    }
      }
  }
  /* Missing */
  for(k=1; k<=TermNum; k++){
      allocedge(&teptr);
      allocedgelist(&telistptr);
      teptr->type = 4;
      teptr->err  = seterror(4,j,j);
      teptr->from = j;
      teptr->to   = j;
      teptr->gram = k;
      teptr->numparses = 1;
      teptr->parse = NULL;
      strcpy(teptr->word, "");
      telistptr->edge = teptr;
      telistptr->previous = NULL;
      insert_agenda(teptr, telistptr);
  }
  for(k=TermNum+1; k<=CatNum; k++){
      allocedge(&teptr);
      allocedgelist(&telistptr);
      allocltree(&(teptr->parse));
      teptr->type = 4;
      teptr->err  = seterror(4,j,j);
      teptr->from = j;
      teptr->to   = j;
      teptr->gram = k;
      teptr->numparses = 1;
      teptr->parse->ltree = NULL;
      teptr->parse->rtree = NULL;
      teptr->parse->next = NULL;
      telistptr->edge = teptr;
      telistptr->previous = NULL;
      insert_agenda(teptr, telistptr);
  }
    }
}

void parse()
{
    int  i;
    Edgeptr eptr;
    EListptr  telistptr,tagendaptr;

    while(agenda[0] != &tail){
  eptr = agenda[0]->edge;
  tagendaptr = agenda[0];
  agenda[0] = agenda[0]->next;
/*  agenda[0]->previous = NULL; */
  if( 0 == dup_check(eptr) ){
      if( eptr->type != 2 ){
    provoke(eptr);
    for( i=0 ; i<=eptr->from ; i++ ){
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

void parse_ill()
{
    int  i, j, fflag;   /* fflag is for discovery of sentence */
    int  count;
    Edgeptr eptr;
    EListptr  telistptr,tagendaptr;

    count=0; fflag=0;
    for( j=0; j<=elimit; j++ ){
#ifdef INFO1
  fprintf(stderr,"agenda[%d]  **start**",j);
#endif
  while(agenda[j] != &tail){
#ifdef INFO1
      if(count++==400){
    fprintf(stderr,".");
    count=0;
      }
#endif
      eptr = agenda[j]->edge;
      tagendaptr = agenda[j];
      agenda[j]=agenda[j]->next;

      /* If some sentence interpretation is discovered
         between i and nc, then set a new elimit  */
      if( fflag == 0 && eptr->type == 1 &&
          eptr->gram == topcatnum && eptr->from == 0 && 
          eptr->to == nc ){
    elimit = j;
    fflag  = 1;
#ifdef INFO1
    fprintf("Elimit is set to %d\n",elimit);
#endif
      }

      /*  agenda[j]->previous = NULL; */
      if( 0 == dup_check(eptr) ){
    if( eptr->type != 2 ){
        provoke_ill(eptr);
        for( i=0 ; i<=eptr->from ; i++ ){
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
}

int seterror(type, s, e)
int type, s, e;
{
  switch(type){
    case 3:     /* Extra */
     return(e-s);
     break;
    case 4:   /* Missing */
     return(1);
     break;
    case 5:   /* Substitute */
     return(1);
     break;
  }
}

void provoke_ill(eptr)
Edgeptr  eptr;
{
    int  i, j;
    Edgeptr   teptr;
    EListptr  telistptr,telistptr2;

    /* For Extra Error */
    if( eptr->gram==-1 ){
  for( i=1; i<=GramNum; i++ ){
      allocedge(&teptr);
      allocedgelist(&telistptr);
      allocltree(&(teptr->parse));
      teptr->from = eptr->from;  teptr->to = eptr->to;
      teptr->err  = eptr->err;
      teptr->numparses = 0;   /* initial value */
      teptr->type = 2; teptr->gram = i; teptr->dot = 0;
      teptr->parse->ltree = NULL;
      teptr->parse->rtree = eptr;
      teptr->parse->next  = NULL;
      telistptr->edge = teptr;
      telistptr->previous = NULL;
      insert_agenda(teptr, telistptr);
  }
  for( i=eptr->from; i>=0 ; i-- ){
      telistptr2 = ichart[i][eptr->from];
      while( telistptr2 != NULL ){
    allocedge(&teptr);
    allocedgelist(&telistptr);
    allocltree(&(teptr->parse));
    teptr->from = i;  teptr->to = eptr->to;
    teptr->err  = (eptr->err)+(telistptr2->edge->err);
    teptr->numparses = 0;   /* initial value */
    teptr->type = 1; teptr->gram = telistptr2->edge->gram;
    teptr->parse->ltree = telistptr2->edge;
    teptr->parse->rtree = eptr;
    teptr->parse->next  = NULL;
    telistptr->edge = teptr;
    telistptr->previous = NULL;
    insert_agenda(teptr, telistptr);
    telistptr2 = telistptr2->next;
      }
  }
    }else{
  for( i=1 ; i<MaxGram ; i++ ){
      if( grammar[i][0] == 0 ){  
    break; }
      if( grammar[i][1] == eptr->gram ){
    allocedge(&teptr);
    allocedgelist(&telistptr);
    allocltree(&(teptr->parse));
    teptr->from = eptr->from;  teptr->to = eptr->to;
    teptr->err  = eptr->err;
    teptr->numparses = 0;   /* initial value */
    if( grammar[i][2] == 0 ){
        teptr->type = 1;
        teptr->gram = grammar[i][0];
    }else{ teptr->type = 2; teptr->gram = i; teptr->dot = 1; }
    teptr->parse->ltree = NULL;
    teptr->parse->rtree = eptr;
    teptr->parse->next  = NULL;
    telistptr->edge = teptr;
    telistptr->previous = NULL;
    insert_agenda(teptr, telistptr);
      }
  }
  if(i+wlimit>nc) { j=nc; }else{ j = i+wlimit; }
  for(i=eptr->to+1; i<j; i++){
      telistptr2 = ichart[eptr->to][i];
      while( telistptr2 != NULL ){
    if( telistptr2->edge->gram==-1 ){
        allocedge(&teptr);
        allocedgelist(&telistptr);
        allocltree(&(teptr->parse));
        teptr->from = eptr->from;  teptr->to = i;
        teptr->err  = (eptr->err)+seterror(3,eptr->to,i);
        teptr->numparses = 0;   /* initial value */
        teptr->type = 1; teptr->gram = eptr->gram;
        teptr->parse->ltree = eptr;
        teptr->parse->rtree = telistptr2->edge;
        teptr->parse->next  = NULL;
        telistptr->edge = teptr;
        telistptr->previous = NULL;
        insert_agenda(teptr, telistptr);
        break;
    }
    telistptr2 = telistptr2->next;
      }
  }
    }
}

void insert_agenda(eptr, elistptr)
Edgeptr eptr;
EListptr elistptr;
{
    if( eptr->err<=elimit ){
  agenda[eptr->err]->previous = elistptr;
  elistptr->next = agenda[eptr->err];
  agenda[eptr->err] = elistptr;
    }else{ 
  freeelistproc(elistptr);
  freeedge_parse(eptr);
    }
}

void copy_edge(eptr1,eptr2)
Edgeptr eptr1,eptr2;
{
    eptr2->err   = eptr1->err;
    eptr2->numparses = eptr1->numparses;
    eptr2->parse = eptr1->parse;
}

int tfindgram(lhs,rhs)
int lhs,rhs;
{
    int   i;

    for( i=1; i<GramNum+1; i++ ){
  if( grammar[i][0]==lhs && grammar[i][1]==rhs &&
      grammar[i][2]==0 ){
      return(i);
  }
    }
    fprintf(stderr,"Error Occurred in tfindgram\n");
}
      
int expandtree(eptr,n)
Edgeptr  eptr;
int  n;
{
    int  i, j, g; /* g for the currently used grammar */
    int  type;  /* type stands for gram with 1 rhs =0 else =1 */
    ListTreeptr tltptr;
    int  a,c,c1,c2,d1,d2;

    c=0;
    a=n;
    tltptr = eptr->parse;
    while(tltptr != NULL){
  if(tltptr->ltree==NULL){ c1=1; }else{ c1=tltptr->ltree->numparses; }
  if(tltptr->rtree==NULL){ c2=1; }else{ c2=tltptr->rtree->numparses; }
  c=c1*c2;
/*  if(eptr->type==2){
      printf("eptr=%s, dot=%d, c=%d, c1=%d, c2=%d\n",gramtext[eptr->gram],eptr->dot,c,c1,c2); 
  }else{ if(eptr->type==1){
      printf("eptr=%s, c=%d, c1=%d, c2=%d\n",ctab[eptr->gram],c,c1,c2);
  }} */
  if( a>=c ){ a-=c; tltptr = tltptr->next; continue; }
  if( tltptr->ltree==NULL ){ 
      d2=a; 
      if(d2==0){
    if( tltptr->rtree==NULL ){
/*
        printf("g:%d, dot:0, type:3\n",eptr->gram); 
*/
    }else{
    if( tltptr->rtree->type==4 ||
              tltptr->rtree->type==5 ){
        if(eptr->type==1){
      g=tfindgram(eptr->gram,tltptr->rtree->gram);
        }else{
      g=eptr->gram;
        }
/*        assertill(g,0,tltptr->rtree->type); */
/*
        printf("g:%d, dot:0, f=%d, t=%d, cat=%s, type:%d\n",g,tltptr->rtree->from,tltptr->rtree->to,ctab[tltptr->rtree->gram],tltptr->rtree->type);
        printf("g:%d, dot:0, cat=%s, type:%d\n",g,ctab[tltptr->rtree->gram],tltptr->rtree->type);
*/
    }else{
        if( tltptr->rtree->type==3 ){
      if(eptr->type==1){
          printf("Error!!\n");
          exit(0);
      }else{
          g=eptr->gram;
      }
/*
      printf("g:%d, dot:0, type:3\n",g);
*/
/*      assertill(g,0,3); */
        }else{ 
      if( tltptr->rtree->type!=0 ){
          expandtree(tltptr->rtree,d2); }
        }
    }
      }
      }else{ expandtree(tltptr->rtree,d2); }
  }else{ 
      d1=a/c2; d2=a%c2; 
/*      printf("d1=%d, d2=%d\n",d1,d2); */
      expandtree(tltptr->ltree,d1); 
      if(d2==0){
    if( tltptr->ltree->type==1 ){
        if( tltptr->rtree->type==3 ){
      if(eptr->type==2){
          printf("Error!! 2\n");
          exit(0);
      }else{
          g=eptr->gram;
      }
/*      printf("g:%d-e, dot:0, f:%d, t:%d, type:%d\n",g,tltptr->rtree->from,tltptr->rtree->to,tltptr->rtree->type);
*/
/*      printf("g:%d-e, dot:0, type:%d\n",g,tltptr->rtree->type);
*/
/*      assertill(g,0,3); */
        }
    }else{
        if( tltptr->rtree->type==3 ||
            tltptr->rtree->type==4 ||
            tltptr->rtree->type==5 ){
      g=eptr->gram;
/*            assertill(g,1,tltptr->rtree->type); */
      if( tltptr->ltree->type==2 ){
          if(tltptr->rtree->type != 3){
/*        printf("g:%d, dot:%d, f=%d, t=%d, cat=%s, type:%d\n",g,tltptr->ltree->dot,tltptr->rtree->from,tltptr->rtree->to,ctab[tltptr->rtree->gram],tltptr->rtree->type);
*/
/*
        printf("g:%d, dot:%d, cat=%s, type:%d\n",g,tltptr->ltree->dot,ctab[tltptr->rtree->gram],tltptr->rtree->type);
*/
          }else{
/*        printf("g:%d, dot:%d, f=%d, t=%d, cat=extra, type:%d\n",g,tltptr->ltree->dot,tltptr->rtree->from,tltptr->rtree->to,tltptr->rtree->type);
*/
/*
        printf("g:%d, dot:%d, cat=extra, type:%d\n",g,tltptr->ltree->dot,tltptr->rtree->type);
*/
          }
/*          printf("*****gram:%d, dot:%d, type:%d\n",\
             g,eptr->dot,tltptr->rtree->type); */
      }
        }else{ 
      if( tltptr->rtree->type!=0 ){
/*          printf("here 2 !\n"); */
          expandtree(tltptr->rtree,d2); }
        }
    }
      }else{ expandtree(tltptr->rtree,d2); }
  }
  break;
    }
}
