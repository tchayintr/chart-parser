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

freeltreeproc(ltptr)
ListTreeptr   ltptr;
{
    fnumltree++;
    ltptr->next = freeltree;
    freeltree = ltptr;
}

freeelistproc(tmpelistptr)
EListptr tmpelistptr;
{
    fnumelist++;
    tmpelistptr->next = freeelist;
    freeelist = tmpelistptr;
}

freeedgeproc(tmpeptr)
Edgeptr   tmpeptr;
{
    fnumedge++;
    tmpeptr->next = freeedge;
    freeedge = tmpeptr;
}

allocedgelist(tmpelistptr)
EListptr  *tmpelistptr;
{
    anumelist++;
    if( freeelist != &tail ){
	*tmpelistptr = freeelist;
	freeelist = freeelist->next;
    }else{
	if( NULL == ( *tmpelistptr = (EListptr)malloc(sizeof(struct EList)) )){
	    printf("No enough memory\n");
	    exit(0);
	}}
}

allocedge(tmpeptr)
Edgeptr   *tmpeptr;
{
    anumedge++;
    if( freeedge != &tailedge ){
	*tmpeptr = freeedge;
	freeedge = freeedge->next;
    }else{
	if( NULL == ( *tmpeptr = (Edgeptr)malloc(sizeof(struct Edge)) ) ){
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
    }else{
	if( NULL == (*ltptr = (ListTreeptr)malloc(sizeof(struct ListTree)))){
	    printf("No enough memory\n");
	    exit(0);
	}}
}

