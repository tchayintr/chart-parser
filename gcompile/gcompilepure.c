/*
 *  This program for compile CFG grammar to a simple format.
 *  Use for chart parsing
 *
 *  @(#)gcompile.c  15/11/1995  By Thanaruk Theeramunkong
 */

#include <stdio.h>
#include <ctype.h>

#define BufSize  2048	/* The size of buffer */
#define CatLen     16	/* The limited length of category name */
#define NumCat   1024	/* The number of categories */
#define NonTerm   128	/* The number of nonterminal categories */
#define Term      128	/* The number of terminal categories */
#define Gram     4096	/* The number of grammar rules */
#define GLen       12	/* The limited length of rules */

char cat[NumCat][CatLen];	/* Categories */
char term[Term][CatLen];	/* Terminal categories */
char nonterm[NonTerm][CatLen];	/* Nonterminal categories */
char gram[Gram][GLen][CatLen];	/* Grammar rules */
char rgram[Gram][GLen*CatLen]; 	/* The raw form of grammar rules */
int  gramlen[Gram];		/* The length of each grammar rule */
int  grammar[Gram][GLen];	/* The converted form of grammar rules */
int  maxgramlen=0;

int cn=0, nn=0;		/* cn = cat counter, nn = nonterminal cat. counter */
int tn=0, gn=0; 	/* tn = terminal cat. counter, gn = grammar counter */
int gl=0, maxlen=0;	/* gl = grammar length, maxlen = maximum length  */

main()
{
  char Buffer[BufSize];
  int  i, j;

  while( NULL != fgets(Buffer,BufSize,stdin) ){
    if( strlen(Buffer) != 1 ){ 
      gl=0;		/* Set grammar length = 0 */
      parse(Buffer);	/* Parse an input and find
			   the number of categories,
			   the number of nonterminals,
			   the number of grammars,
			   and grammar length */
    }
  }
  findterminal();	/* Find terminal categories */
  reassigncat();	/* Reassignment to the order of
			   Terminal cat. and Nonterminal cat */
  assignnum();		/* Assign NUMBER to Categories */
  printheader();	/* Print Header */
  printnumber();	/* Print the number of term, nonterm, cat */
  printcattab();	/* Print category table */
  printgram();		/* Output the tranformed grammar rules */
  printrawgram();

  exit(0);
}

printrawgram()
{
  int i;

  printf("static char gramtext[%d][%d] = {\n",gn+2,maxgramlen+1);
  printf("\t\t\"\",\n");
  for( i=0 ; i<gn ; i++ ){
    printf("/* %4d */\t\"%s\",\n", i+1, rgram[i]);
  }
  printf("\t\t\"\"\n};");
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
    char tmpcat[CatLen];

    printf("/* This is a header for C-chart parser */\n");
    printf("/* Category Table */\n");
    printf("static char ctab[%d][%d] = {\n",cn+3,CatLen);
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
  printf("};\n\n\n");
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
  cn = tn+nn;
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
  int i=0, p=0, n=0, l=0;
  char tmp[CatLen];

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
  strcpy(rgram[gn],gram[gn][0]);
  strcat(rgram[gn],"-->");
  for( i=1; i<gl; i++ ){
      strcat(rgram[gn],gram[gn][i]);
      strcat(rgram[gn],",");
  }
  rgram[gn][strlen(rgram[gn])-1] = '\0';
  strcat(rgram[gn],".");
  if( (l=strlen(rgram[gn])) > maxgramlen ){
      maxgramlen=l;
  }
  gn++;				/* Increase the number of grammar rule */
}

