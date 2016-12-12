/*
 *  This program for compile CFG grammar to a simple format.
 *  Use for chart parsing
 *
 *  @(#)gcompile.c  15/11/1995  By Thanaruk Theeramunkong
 */

/* line 264 "strlen" give incorect Thai word length */
/* Fixed by size_t strlength(str) */
/* 
  Since Thai character comsume 3 bytes for one character CatLen, GLen,
  need to increasing
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BufSize  2048 /* The size of buffer */
#define CatLen     64 /* The limited length of category name */ /* Increased 16 --> 64 */
#define NumCat   1024 /* The number of categories */
#define NonTerm   128 /* The number of nonterminal categories */
#define Term      128 /* The number of terminal categories */
#define Gram     4096 /* The number of grammar rules */
#define GLen       48 /* The limited length of rules */ /* Increased 12 --> 48 */

void printrawgram();
void printnumber();
void printheader();
void printcattab();
void printgram();
void assignnum();
void reassigncat();
void findterminal();
void parse(char*);
size_t strlength(const char*);

char cat[NumCat][CatLen]; /* Categories */
char term[Term][CatLen];  /* Terminal categories */
char nonterm[NonTerm][CatLen];  /* Nonterminal categories */
char gram[Gram][GLen][CatLen];  /* Grammar rules */
char rgram[Gram][GLen*CatLen];  /* The raw form of grammar rules */
int  gramlen[Gram];   /* The length of each grammar rule */
int  grammar[Gram][GLen]; /* The converted form of grammar rules */
int  maxgramlen=0;

int cn=0, nn=0;   /* cn = cat counter, nn = nonterminal cat. counter */
int tn=0, gn=0;   /* tn = terminal cat. counter, gn = grammar counter */
int gl=0, maxlen=0; /* gl = grammar length, maxlen = maximum length  */

int main()
{
  char Buffer[BufSize];
  int  i, j;

  while( NULL != fgets(Buffer,BufSize,stdin) ){
    // printf("%s\n", Buffer);
    if( strlen(Buffer) != 1 ){ 
      gl=0;   /* Set grammar length = 0 */
      parse(Buffer);  /* Parse an input and find
         the number of categories,
         the number of nonterminals,
         the number of grammars,
         and grammar length */
    }
  }

  findterminal(); /* Find terminal categories */
  reassigncat();  /* Reassignment to the order of
         Terminal cat. and Nonterminal cat */
  assignnum();    /* Assign NUMBER to Categories */
  printheader();  /* Print Header */
  printnumber();  /* Print the number of term, nonterm, cat */
  printcattab();  /* Print category table */
  printgram();    /* Output the tranformed grammar rules */
  printrawgram();

  exit(0);
}

void checkvar(){
  printf("---------------------checkvar()called---------------------\n");
  printf("cn(cat counter), nn(nonterminal cat. counter) = %d, %d\n", cn, nn);
  printf("tn(terminal cat. counter), gn(grammar counter) = %d, %d\n", tn, gn);
  printf("gl(grammar length), maxlen(maximum length) = %d, %d\n", gl, maxlen);
  printf("maxgramlen = %d\n", maxgramlen);
  printf("----------------------------------------------------------\n\n");
}

void printrawgram()
{
  int i;

  printf("static char gramtext[%d][%d] = {\n",gn+2,maxgramlen+1);
  printf("\t\t\"\",\n");
  for( i=0 ; i<gn ; i++ ){
    printf("/* %4d */\t\"%s\",\n", i+1, rgram[i]);
  }
  printf("\t\t\"\"\n};");
}

void printnumber()
{
    printf("#define GramNum     %4d\n",gn);
    printf("#define CatNum      %4d\n",cn);
    printf("#define TermNum     %4d\n",tn);
    printf("#define NonTermNum  %4d\n\n\n",nn);
}

void printheader()
{
    printf("/*\n");
    printf(" *  $ JAIST: gram.h,v 0.1000 1995/10/04 20:04:01 $\n");
    printf(" *\n");
    printf(" *  @(#)gram.h  10/10/1995  By Thanaruk Theeramunkong\n");
    printf(" */\n\n\n\n");
}

void printcattab()  /* Print category table */
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

void printgram()    /* Output the tranformed grammar rules */
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
void assignnum()
{
  int i,j,k;

  for( i=0 ; i<gn ; i++ ){
    for( j=0 ; j<gramlen[i] ; j++ ){
      for( k=1 ; k<=cn ; k++ ){
        // printf("gram[%d][%d] - cat[%d]: %s - %s\n", i,j,k, gram[i][j],cat[k]);
        if( !strcmp(gram[i][j],cat[k]) ){ 
          // printf("grammar[%d][%d]: %d\n", i,j,k);
          grammar[i][j] = k;
        }
      }
    }
    if( maxlen < gramlen[i] ){ maxlen = gramlen[i]; }
  }
}

/* Reassignment to the order of Terminal cat. and Nonterminal cat */

void reassigncat()
{
  int i, j=0;
  
  for( i=0 ; i<tn ; i++ ){ strcpy(cat[++j],term[i]); }
  for( i=0 ; i<nn ; i++ ){ strcpy(cat[++j],nonterm[i]); }
  cn = tn+nn;
}

/* Find terminal categories: the Ex-set between the Cat and Nonterm */

void findterminal()  // ex: n-->ฉัน, v-->เรียน
{
  int i,j;

  for( i=0 ; i<cn ; i++ ){
    for( j=0 ; j<nn ; j++ ){ 
      if( !strcmp(cat[i],nonterm[j]) ){ break; }
    }
    /* To making sure It's all checked */
    if( j==nn ){ strcpy(term[tn++],cat[i]);  }  
  }
  for (i = 0; i < tn; i++)
  {
    // printf("term[%d]: %s\n", i, term[i]);
  }
}

/* Parse an input and find the number of categories,
   the number of nonterminals, the number of grammars,
                                    and grammar length */
void parse(Buffer)
char *Buffer;
{
  int i=0, p=0, n=0, l=0;
  char tmp[CatLen];

  while( Buffer[p] == ' ' ){ p++; } /* Deleting useless space */
  while( Buffer[p] == '%' ){ return; }  /* For comment statement */

  while( Buffer[p] != '-' & Buffer[p] != ' ' ){
    tmp[i] = Buffer[p]; i++; p++;
  }         /* Skim the LHS of the grammar */
  tmp[i]='\0';
  strcpy(gram[gn][gl++],tmp);   /* Copy to store in gram array */
  // printf("1:%s\n", gram[gn][gl-1]);

  for( i=0 ; i<nn ; i++ ){  /* Check it previously introduce or not */
      if( !strcmp(tmp,nonterm[i]) ){ break; } }
  if( i==nn ){  strcpy(nonterm[nn],tmp); nn++;
    // printf("Nonterminal[%d]: %s\n", nn, nonterm[nn-1]);
  }

  while( Buffer[p] == '-' | Buffer[p] == '>' |  /* Scan out */
   Buffer[p] == ' ' ){   p++;  }

  while( Buffer[p] != '.' ){    /* Continue until . */
    i=0; 
    while( Buffer[p] != ',' & Buffer[p] != '.' & Buffer[p] != ' ' ){
      tmp[i] = Buffer[p]; i++; p++;
    }         /* Parse the RHS part */
    tmp[i]='\0';
    strcpy(gram[gn][gl++],tmp);   /* Copy to keep in gram array */
    // printf("2:%s\n", gram[gn][gl-1]);

    while( Buffer[p] == ',' | Buffer[p] == ' ' ){  p++;  } /* Scan out */

    for( i=0 ; i<cn ; i++ ) {     /* Check it previously introduce */
     if( !strcmp(tmp,cat[i]) ){ /* as a category or not */
       break; } }
    if( i==cn ){ strcpy(cat[i],tmp); cn++;  }
    // printf("cat[%d]: %s\n", i, cat[i]);
  }
  // checkvar();

  gramlen[gn] = gl;   /* Set the length of the current gram rule */
  strcpy(rgram[gn],gram[gn][0]);
  strcat(rgram[gn],"-->");

  for( i=1; i<gl; i++ ){
      strcat(rgram[gn],gram[gn][i]);
      strcat(rgram[gn],",");
  }
  rgram[gn][strlen(rgram[gn])-1] = '\0';
  strcat(rgram[gn],".");

  if( (l=strlength(rgram[gn])) > maxgramlen ){
      maxgramlen=l;
  }
  // printf("%s :: len %zu\n", rgram[gn], strlength(rgram[gn]));
  gn++;       /* Increase the number of grammar rule */
  // printf("_____END_____\n\n");
}

/* http://www.daemonology.net/blog/2008-06-05-faster-utf8-strlen.html */
/* Process only first byte of multi-byte character */

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