#include <stdio.h>
#include <ctype.h>
#include <malloc.h>
#include "def.h"
#include "chart.h"

extern struct EList tail;		/* the tail cell of an edge list */
extern struct Edge tailedge;		/* the tail edge */
extern struct ListTree tailtree;	/* the tail tree */
extern EListptr freeelist;		/* A list of Free Edge list cells */
extern Edgeptr  freeedge;		/* A list of Free Edges */
extern ListTreeptr  freeltree;		/* A list of Free Trees */

extern int  anumedge;
extern int  anumelist;
extern int  anumltree;
extern int  fnumedge;
extern int  fnumelist;
extern int  fnumltree;

extern int  medgelen;
extern int  mlistlen;
extern int  mtreelen;

freeedge_parse(eptr)
Edgeptr  eptr;
{
    ListTreeptr tltptr,tltptr2;

    tltptr = eptr->parse;
    while(tltptr != NULL){
	tltptr2 = tltptr;
	tltptr  = tltptr->next;
	freeltreeproc(tltptr2);
    }
    freeedgeproc(eptr);
}

freeparse(parse)
ListTreeptr  parse;
{
    ListTreeptr tmpparse;

    while(parse != NULL){
	tmpparse = parse;
	parse  = parse->next;
	freeltreeproc(tmpparse);
    }
}

freeedgeproc(tmpeptr)
Edgeptr   tmpeptr;
{
    fnumedge++;
    medgelen++;
    if( medgelen < MemELimit ){
	tmpeptr->next = freeedge;
	freeedge = tmpeptr;
    }else{ free(tmpeptr); }
}

freeelistproc(tmpelistptr)
EListptr tmpelistptr;
{
    fnumelist++;
    mlistlen++;
    if( mlistlen < MemLLimit ){
	tmpelistptr->next = freeelist;
	freeelist = tmpelistptr;
    }else{ free(tmpelistptr); }
}

freeltreeproc(tmpltptr)
ListTreeptr   tmpltptr;
{
    fnumltree++;
    mtreelen++;
    if( mtreelen < MemTLimit ){
	tmpltptr->next = freeltree;
	freeltree = tmpltptr;
    }else{ free(tmpltptr); }
}

allocedge(tmpeptr)
Edgeptr   *tmpeptr;
{
    anumedge++;
    if( freeedge != &tailedge ){
	*tmpeptr = freeedge;
	freeedge = freeedge->next;
	medgelen--;
    }else{
	if( NULL == ( *tmpeptr = (Edgeptr)malloc(sizeof(struct Edge)) ) ){
	    printf("No enough memory\n");
	    exit(0);
	}}
}

allocedgelist(tmpelistptr)
EListptr  *tmpelistptr;
{
    anumelist++;
    if( freeelist != &tail ){
	*tmpelistptr = freeelist;
	freeelist = freeelist->next;
	mlistlen--;
    }else{
	if( NULL == ( *tmpelistptr = (EListptr)malloc(sizeof(struct EList)) )){
	    printf("No enough memory\n");
	    exit(0);
	}}
}

allocltree(ltptr)
ListTreeptr   *ltptr;
{
    anumltree++;
    if( freeltree != &tailtree ){
	*ltptr = freeltree;
	freeltree = freeltree->next;
	mtreelen--;
    }else{
	if( NULL == (*ltptr = (ListTreeptr)malloc(sizeof(struct ListTree)))){
	    printf("No enough memory\n");
	    exit(0);
	}}
}
