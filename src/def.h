/*
 *  $ JAIST: def.h,v 0.1000 1995/12/25 03:04:01 $
 *
 *  @(#)def.h  25/12/1995  By Thanaruk Theeramunkong
 */

#define FNameLen	 128	/* The Maximum length of FileName */
#define BufSize		 1024	/* The Maximum length of Buffer   */
#define CatLen  	 128    /* The limited length of category names */  /* Increased 16 --> 64 --> 128*/
#define WordLen  	 96    /* The limited length of words */			/* Increased 24 --> 96 */
#define SentLen	  	 128	/* The Maximum length of Sentence */
#define MaxCat		 256	/* The Maximum Category's Number  */
#define MaxGram		 2048	/* The Maximum Category's Number  */
#define ChartMax     1000000    /* The maximum number of egdes in chart */
#define MaxAgenda	 128	/* The maximum number of agendas */

/* For Memory Management */

#define MemELimit   100000	/* The limit of Memory of Edges     */
#define MemLLimit   100000	/* The limit of Memory of EdgeLists */
#define MemTLimit   100000	/* The limit of Memory of ListTree  */
