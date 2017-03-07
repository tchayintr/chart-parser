/*
 *  $ JAIST: def.h,v 0.1000 1995/12/25 03:04:01 $
 *
 *  @(#)def.h  25/12/1995  By Thanaruk Theeramunkong
 */

#define FNameLen	 128	/* The Maximum length of FileName */
#define BufSize		 1024	/* The Maximum length of Buffer   */
#define CatLen  	 512    /* The limited length of category names */  /* Increased 16 --> 64 --> 128 --> 512*/
#define WordLen  	 512    /* The limited length of words */			/* Increased 24 --> 96  --> 512*/
#define SentLen	  	 128	/* The Maximum length of Sentence */
#define MaxCat		 256	/* The Maximum Category's Number  */
#define MaxGram		 2048	/* The Maximum Category's Number  */
#define ChartMax     1000000    /* The maximum number of egdes in chart */
#define MaxAgenda	 128	/* The maximum number of agendas */

/* For Memory Management */

#define MemELimit   10000000	/* The limit of Memory of Edges     */ // +00
#define MemLLimit   10000000	/* The limit of Memory of EdgeLists */ // +00
#define MemTLimit   10000000	/* The limit of Memory of ListTree  */ // +00

