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
	printf("Enter to trancat(incat,wd,wc): %s, %s, %p\n", incat,wd,wc);
    int i=0, state=0;
    char tmpchar[CatLen], tmpchar2[CatLen];


    if( !strcmp(incat,"CC") ) {
		strcpy(tmpchar,"paraconj");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
		strcpy(tmpchar,"conj");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(!strcmp(incat, "CD")) {
		strcpy(tmpchar,"numbr");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(!strcmp(incat, "DT")) {
		if( ! strcmp(wd,"a") ){
		    strcpy(tmpchar,"a");
		    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		    (*wc)++;
		}
		else{
		    strcpy(tmpchar,"det");
		    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		    (*wc)++;
		}

		if( !strcmp(wd,"that")  ||
		    !strcmp(wd,"this")  ||
		    !strcmp(wd,"these") ||
		    !strcmp(wd,"those") ){
		    strcpy(tmpchar,"pron");
		    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		    (*wc)++;
		}
    }

    if(! strcmp(incat, "EX") ) {
		strcpy(tmpchar,"there");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "FW") ) {
		strcpy(tmpchar,"n");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "IN") ) {
		strcpy(tmpchar,"IN");
	    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
	    (*wc)++;
    }

    if(! strcmp(incat, "JJ") ) {
		if(!strcmp(wd, "much") ||
		   !strcmp(wd, "many") ||
		   !strcmp(wd, "little") ||
		   !strcmp(wd, "few") ) {
		    strcpy(tmpchar,"q");
		    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		    (*wc)++;
		}
		if(!strcmp(wd,"enough")) {
		    strcpy(tmpchar,"enough");
		    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		    (*wc)++;
		    strcpy(tmpchar,"adj");
		    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		    (*wc)++;
		}else{
		    strcpy(tmpchar,"adj");
		    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		    (*wc)++;
		}
    }

    if(! strcmp(incat, "JJR") ) {
		if(!strcmp(wd, "more") ||
		   !strcmp(wd, "less") ||
		   !strcmp(wd, "fewer") ) {
		    strcpy(tmpchar,"q_er");
		    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		    (*wc)++;
		}
		strcpy(tmpchar,"adj_er");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "JJS") ) {
		if(!strcmp(wd, "most") ||
		   !strcmp(wd, "least") ||
		   !strcmp(wd, "fewest") ) {
		    strcpy(tmpchar,"q_est");
		    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		    (*wc)++;
		}
		strcpy(tmpchar,"adj");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "LS") ) {
		strcpy(tmpchar,"n");
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
		strcpy(tmpchar,"n");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "PDT") ) {
		strcpy(tmpchar,"all");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "POS") ) {
		strcpy(tmpchar,"of");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "PRP") ) {
		strcpy(tmpchar,"pron");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "PRP$") ) {
		strcpy(tmpchar,"det");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "RB") ) {
		if(!strcmp(wd,"not") || 
		   !strcmp(wd,"n't") ){
		    strcpy(tmpchar,"nt");
		    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		    (*wc)++;
		    state = 1;
		}
		if(!strcmp(wd, "very")  ) {
		    strcpy(tmpchar,"qdet");
		    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		    (*wc)++;
		    state = 1;
		}
		if( state == 0 ){
		    strcpy(tmpchar,"adv");
		    wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		    (*wc)++;
		}
		state = 0;
    }

    if(! strcmp(incat, "RBR") ) {
		strcpy(tmpchar,"adj_er");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "RBS") ) {
		strcpy(tmpchar,"adj");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "RP") ) {
		strcpy(tmpchar,"adv");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "Sym") ) {
		strcpy(tmpchar,"n");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "TO") ) {
		strcpy(tmpchar,"to");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
		strcpy(tmpchar,"p");
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

    if(! strcmp(incat, "WDT") ) {
		strcpy(tmpchar,"whn");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
		strcpy(tmpchar,"relpro");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "WP") ) {
		strcpy(tmpchar,"whp");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
		strcpy(tmpchar,"relpro");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "WP$") ) {
		strcpy(tmpchar,"whdet");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
    }

    if(! strcmp(incat, "WRB") ) {
		strcpy(tmpchar,"how");
		wordcat[i] = conv_cat_numbr(tmpchar); i++ ;
		(*wc)++;
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