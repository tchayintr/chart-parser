/*
 *  $ JAIST: trancat.c,v 0.1000 1995/11/18 11:24:14 $
 *
 *  @(#)trancat.c  28/11/1995  By Thanaruk Theeramunkong
 */

/* This program is an option. 
 * It helps us to change the category name to a proper one.
 * This dues to the (lexical) category name in Tagger and 
 *   that in the grammar rule is, in some case, not correspondent.
 * This program uses the correspondent table defined in `trancat.h'.
 * This program provides a function named trancat(incat,outcat).
 */

#include <stdio.h>
#include <ctype.h>
#include "def.h"
#include "grampure.h"

extern char cinsent[SentLen][CatLen];
extern int wordcat[MaxCat];

trancat(incat,wd,wc)   /* Input CatofTagger and */
char *incat,*wd;
int *wc;
{
    int i=0, state=0;
    char tmpchar[CatLen], tmpchar2[CatLen];

    strcpy(tmpchar,incat);
    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
    (*wc)++;
}

int conv_cat_numbr(cat)
char *cat;
{
    int  j;

    for( j=1; j<2*MaxCat; j++ ){
	if( ctab[j][0] == '\0' ){
#ifdef ERROR
	    fprintf(stderr,"sentence : %s",buffer);
	    fprintf(stderr,"%s is not a vilid category\n",cat);
#endif
	    return(0);
	}
	if( !strcmp(ctab[j],cat) ){
	    return(j);
	}
    }
}
