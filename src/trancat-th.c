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
#include <string.h>
#include "def.h"
#include "gram-th.h"

int conv_cat_numbr(char*);

extern char cinsent[SentLen][CatLen];
extern int wordcat[MaxCat];

void trancat(incat,wd,wc)   /* Input CatofTagger and */
char *incat,*wd;
int *wc;
{
	// printf("Enter to trancat(incat,wd,wc): %s, %s, %p\n", incat,wd,wc);
    int i=0, state=0;
    char tmpchar[CatLen], tmpchar2[CatLen];

    if(!strcmp(incat, "NGAP")) {
	    strcpy(tmpchar,"NGAP");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
	    (*wc)++;
	
    }

    if( !strcmp(incat,"CC") ) {
		strcpy(tmpchar,"CC");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(!strcmp(incat, "CD")) {
		strcpy(tmpchar,"CD");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(!strcmp(incat, "DT")) {
	    strcpy(tmpchar,"DT");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
	    (*wc)++;
	
    }

    if(! strcmp(incat, "E") ) {
		strcpy(tmpchar,"E");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "IN") ) {
		strcpy(tmpchar,"IN");
	    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
	    (*wc)++;
    }

    if(! strcmp(incat, "JJ") ) {
		strcpy(tmpchar,"JJ");
	    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "MD") ) {
		strcpy(tmpchar,"MD");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "NN") ) {
		strcpy(tmpchar,"NN");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "NNS") ) {
		strcpy(tmpchar,"n");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "NNP") ) {
		strcpy(tmpchar,"NNP");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "NNPS") ) {
		strcpy(tmpchar,"NNPS");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "RB") ) {
	    strcpy(tmpchar,"RB");
	    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "RP") ) {
		strcpy(tmpchar,"RP");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "TO") ) {
		strcpy(tmpchar,"TO");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "UH") ) {
		wordcat[i] = 0; i++ ;
		(*wc)++;
    }

    if(! strncmp(incat, "VB", 2) ) { /* VB, VBD, VBG, VBN, VBP, VBZ */
		if(!strcmp(incat,"VB")){
		    strcpy(tmpchar,"VB");
		    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		    (*wc)++;
		}
    }
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
    return 0;
}