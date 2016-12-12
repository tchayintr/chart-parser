/*
 *  This program for compile DCG grammar to a simple format.
 *  Use for chart parsing
 *
 *  @(#)gcompile.c  20/01/1996  By Thanaruk Theeramunkong
 */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE  2048	/* The size of a buffer */
#define RULELEN  8192	/* The length of a rule */
#define MAXRULE  1024	/* The maximum number of rules */
#define MAXARGL    24	/* The maximum length of an argument */
#define MAXAUGL   128	/* The maximum length of an augment */

#define CATLEN     16	/* The limited length of category name */
#define NUMCAT   1024	/* The number of categories */
#define NONTERM   128	/* The number of nonterminal categories */
#define TERM      128	/* The number of terminal categories */
#define GRAM     4096	/* The number of grammar rules */
#define GLEN       12	/* The limited length of rules */

char dcgrule[MAXRULE][RULELEN];	/* All Rules           */
char cfgrule[MAXRULE][RULELEN];	/* All Rules           */

int  curline;			/* Current Line Number */
int  numrule;			/* The Number of Rules */

char cat[NUMCAT][CATLEN];	/* Categories */
char term[TERM][CATLEN];	/* Terminal categories */
char nonterm[NONTERM][CATLEN];	/* Nonterminal categories */
char gram[GRAM][GLEN][CATLEN];	/* Grammar rules */
int  gramlen[GRAM];		/* The length of each grammar rule */
int  grammar[GRAM][GLEN];	/* The converted form of grammar rules */

int cn=0, nn=0;		/* cn = cat counter, nn = nonterminal cat. counter */
int tn=0, gn=0; 	/* tn = terminal cat. counter, gn = grammar counter */
int gl=0, maxlen=0;	/* gl = grammar length, maxlen = maximum length  */

main(argc, argv)
int    argc;
char **argv;
{
    int   i;

    loadinrules();
    dcg2cfg();

/*
    if(argc==2){
	for( i=0; i<numrule; i++ ){
	    printf("%s\n",dcgrule[i]);
	}
	for( i=0; i<numrule; i++ ){
	    printf("%s\n",cfgrule[i]);
	}
    }
*/
    if( argc==1 ){
	for( i=0; i<numrule; i++ ){
	    gl=0;
	    parse(cfgrule[i]);
	}
	findterminal();	/* Find terminal categories */
	reassigncat();	/* Reassignment to the order of
	                   Terminal cat. and Nonterminal cat */
	assignnum();	/* Assign NUMBER to Categories */
	printout();
    }

    makecheckproc();
    exit(0);
   
}


makecheckproc()
{
    int  i, j, k, l, apos, bpos, cpos, dpos, tpos;
    int  state, curarg, buflen;
    int  tmpstate, tmplen;
    char arg[GLEN][MAXARGL],aug[GLEN][MAXAUGL];
    char tmpaug[MAXARGL];

    for( i=0; i<GLEN; i++ ){
	arg[i][0]= '\0'; aug[i][0] ='\0';
    }
    for( i=0; i<numrule; i++ ){
	printf("%s\n",dcgrule[i]);
	state=0; apos=0; bpos=0; cpos=0; curarg=0;
	buflen=strlen(dcgrule[i]);
	while( bpos<buflen ){
	    if( state==0 ){
		if( dcgrule[i][bpos] == '(' ){
		    bpos++;
		    while( dcgrule[i][bpos] != ',' ){
			arg[curarg][apos++]=dcgrule[i][bpos++];
		    }
		    arg[curarg][apos] = '\0';
		    curarg++; apos=0;
		}else{
		    if(dcgrule[i][bpos]=='{') {
			state=1;
		    }
		    bpos++;
		}
	    }else{ 
		if(dcgrule[i][bpos]=='}'){
		    aug[curarg-1][cpos]='\0';
		    bpos++; cpos=0; state=0;
		}else{ aug[curarg-1][cpos++] = dcgrule[i][bpos++]; }
	    }
	}
	for( j=0; j<curarg; j++ ){
	    printf("arg[%d]=%s : aug[%d]=%s\n",j,arg[j],j,aug[j]);
	    /* Deal with Augments */
	    dpos=0; tmpstate=0;
	    if( aug[j][0]!='\0' ){
		printf("\tcase %d:\n",j);
		printf("\t");
		tmplen=strlen(aug[j]);
		for( k=0; k<tmplen; k++ ){
		    if(tmpstate==0){
			if( aug[j][dpos] == '(' ){ tmpstate=1; }
			printf("%c",aug[j][dpos]);
			dpos++;
		    }else{
			if( aug[j][dpos] == ',' ||
			    aug[j][dpos] == ')' ){
			    tmpaug[tpos] == '\0';
			    for( l=1 ; l<=k ; l++ ){
				if(!strcmp(arg[l],tmpaug)){
				    printf("%d%c",l,aug[j][dpos]);
				    break;
				}
			    }
			    if(l==k+1){
				printf("%s%c",tmpaug,aug[j][dpos]);
			    }
			}else{
			    tmpaug[tpos++]=aug[j][dpos++];
			}

	    arg[j][0]= '\0'; aug[j][0] ='\0';
	}

	
    }
}


printout()
{
    printheader();	/* Print Header */
    printnumber();	/* Print the number of term, nonterm, cat */
    printcattab();	/* Print category table */
    printgram();	/* Output the tranformed grammar rules */
}


dcg2cfg()
{
    char Buffer[BUFSIZE];
    int  i, dpos, cpos, state;
    
    for( i=0; i<numrule; i++ ){
	state=0; dpos=0; cpos=0;
	while( dcgrule[i][dpos]!='\0' ) {
	    if( state==0 ) {
		if( dcgrule[i][dpos]=='(' ){
		    state=1; dpos++;
		}else{
		    if( dcgrule[i][dpos]=='{' ){
			state=2; dpos++;
		    }else{ cfgrule[i][cpos++]=dcgrule[i][dpos++]; }
		}
	    }else{
		if( dcgrule[i][dpos]==')' &&  state==1 ){
		    state=0; dpos++;
		}else{
		    if( state==2 ){
			if( dcgrule[i][dpos]  ==',' &&
			    dcgrule[i][dpos+1]=='!' ){
			    dpos+=2;
			}
		    }
		    if( dcgrule[i][dpos]=='}' && state==2 ){
		        if( dcgrule[i][dpos+1] == '.' ){
			    cfgrule[i][cpos-1] =  '.';	
			}
			dpos+=2; 
			state=0;
		    }else{ dpos++; }
	        }
	    }
	}
	cfgrule[i][cpos]='\0';
    }
}

loadinrules()
{
    char Buffer[BUFSIZE];
    int  i, j, state, bpos, rpos, buflen;

    curline=0;		/* Set current line number to 0 */
    state=0;		/* 0 for normal, 1 for unused area */
    rpos=0;		/* for the position in the rule line */
    numrule=0;		/* the current rule number */
    
    while( NULL != fgets(Buffer,BUFSIZE,stdin) ){
	curline++;
	bpos=0;		/* for the position in the buffer */
	buflen = strlen(Buffer)-1;
	Buffer[buflen]= '\0';
	if( buflen != 0 ){ 
	    for( ; bpos<buflen; ){
		if( Buffer[bpos]==' ' || Buffer[bpos]=='\t' ){ 
		    bpos++; continue; }
		if( Buffer[bpos]=='%' ){ break; }
		if( state==0 ){
		    if( Buffer[bpos]=='/' ){
			if( Buffer[bpos+1]=='*' ){ state=1; bpos+=2; }else{
			    printerr(1); exit(1); }
		    }else{
			if(Buffer[bpos]==',' && Buffer[bpos+1]=='!' ){
			    bpos+=2; continue; }
			dcgrule[numrule][rpos++]=Buffer[bpos];
			if( Buffer[bpos]=='.' ){ 
			    dcgrule[numrule][rpos]='\0';
			    numrule++; rpos=0; }
			bpos++;
		    }
		}else{
		    if( Buffer[bpos]=='/' && Buffer[bpos+1]=='*' ){
			printerr(2); exit(1); }
		    if( Buffer[bpos]=='*' && Buffer[bpos+1]=='/' ){
			bpos += 2;
			state=0;
		    }else{ bpos++; }
		}
	    }
	}	
    }
}    


printerr(errno)
int errno;
{
    switch(errno){
   case 1:
	fprintf(stderr,"ERROR: / is occurred without following by * at line no. %d\n",curline);
	break;
   case 2:
	fprintf(stderr,"ERROR: /* is occurred twice before */ at line no. %d\n",curline);
	break;
   default :
	fprintf(stderr,"ERROR: Some error is occured at line no. %d\n",curline);
    }
}

printnumber()
{
    printf("#define GramNum     %4d\n",gn);
    printf("#define CatNum      %4d\n",cn);
    printf("#define TermNum     %4d\n",tn);
    printf("#define NonTermNum  %4d\n\n\n",nn);
}

printheader()
{
    printf("/*\n");
    printf(" *  $ JAIST: gram.h,v 0.1000 1995/10/04 20:04:01 $\n");
    printf(" *\n");
    printf(" *  @(#)gram.h  10/10/1995  By Thanaruk Theeramunkong\n");
    printf(" */\n\n\n\n");
}

printcattab()	/* Print category table */
{
    int i,len;
    char tmpcat[CATLEN];

    printf("/* This is a header for C-chart parser */\n");
    printf("/* Category Table */\n");
    printf("static char ctab[%d][%d] = {\n",cn+3,CATLEN);
    printf("\t\"\"              ,\n");
    for( i=1 ; i<=cn ; i++ ){

	strcpy(tmpcat+1,cat[i]);
	tmpcat[0] = '\"';
	tmpcat[len=strlen(tmpcat)] = '\"';
	tmpcat[len+1] = '\0';

	printf("\t%-16s,   /* %4d */\n",tmpcat,i); 
    }
    printf("\t\"\"\n};\n\n");
}

printgram()    /* Output the tranformed grammar rules */
{
  int i, j;

  printf("static int grammar[%d][%d] = {\n",gn+2,maxlen+1);
  printf("\t{");

  for( i=0 ; i<maxlen ; i++ ){  printf("   0,"); }
  printf("   0\t},\n");

  for( i=0 ; i<gn ; i++ ){
    printf("\t{");
    for( j=0 ; j<gramlen[i] ; j++ ){
      printf("%4d,",grammar[i][j]);
    }
    for( ; j<maxlen ; j++ ){  printf("   0,");  }
    printf("   0\t}, /* %4d */\n",i+1);
  }

  printf("\t{");
  for( i=0 ; i<maxlen ; i++ ){  printf("   0,"); }
  printf("   0\t}\n");
  printf("};\n");
}
  
/* Assign NUMBER to Categories 
   cat[n] starts from n=1 and cat[0] has no meaning */
assignnum()
{
  int i,j,k;

  for( i=0 ; i<gn ; i++ ){
    for( j=0 ; j<gramlen[i] ; j++ ){
      for( k=1 ; k<=cn ; k++ ){
	if( !strcmp(gram[i][j],cat[k]) ){
	  grammar[i][j] = k;
	}
      }
    }
    if( maxlen < gramlen[i] ){ maxlen = gramlen[i]; }
  }
}

/* Reassignment to the order of Terminal cat. and Nonterminal cat */

reassigncat()
{
  int i, j=0;
  
  for( i=0 ; i<tn ; i++ ){ strcpy(cat[++j],term[i]); }
  for( i=0 ; i<nn ; i++ ){ strcpy(cat[++j],nonterm[i]); }
}

/* Find terminal categories: the Ex-set between the Cat and Nonterm */

findterminal()
{
  int i,j;

  for( i=0 ; i<cn ; i++ ){
    for( j=0 ; j<nn ; j++ ){ 
      if( !strcmp(cat[i],nonterm[j]) ){ break; }
    }
    if( j==nn ){ strcpy(term[tn++],cat[i]);  }
  }
}

/* Parse an input and find the number of categories,
   the number of nonterminals, the number of grammars,
                                    and grammar length */
parse(Buffer)
char *Buffer;
{
  int i=0, p=0;
  char tmp[CATLEN];

  while( Buffer[p] == ' ' ){ p++; }	/* Deleting useless space */
  while( Buffer[p] == '%' ){ return; }	/* For comment statement */

  while( Buffer[p] != '-' & Buffer[p] != ' ' ){
    tmp[i] = Buffer[p]; i++; p++;
  }					/* Skim the LHS of the grammar */
  tmp[i]='\0';
  strcpy(gram[gn][gl++],tmp);		/* Copy to store in gram array */

  for( i=0 ; i<nn ; i++ ){	/* Check it previously introduce or not */
      if( !strcmp(tmp,nonterm[i]) ){ break; } }
  if( i==nn ){  strcpy(nonterm[nn],tmp); nn++;  }

  while( Buffer[p] == '-' | Buffer[p] == '>' |  /* Scan out */
	 Buffer[p] == ' ' ){   p++;  }

  while( Buffer[p] != '.' ){		/* Continue until . */
    i=0; 
    while( Buffer[p] != ',' & Buffer[p] != '.' & Buffer[p] != ' ' ){
      tmp[i] = Buffer[p]; i++; p++;
    }					/* Parse the RHS part */
    tmp[i]='\0';
    strcpy(gram[gn][gl++],tmp);		/* Copy to keep in gram array */

    while( Buffer[p] == ',' | Buffer[p] == ' ' ){  p++;  } /* Scan out */

    for( i=0 ; i<cn ; i++ ) { 		/* Check it previously introduce */
	if( !strcmp(tmp,cat[i]) ){	/* as a category or not */
	    break; } }
    if( i==cn ){ strcpy(cat[i],tmp); cn++;  }
  }
  gramlen[gn] = gl;		/* Set the length of the current gram rule */
  gn++;				/* Increase the number of grammar rule */
}
