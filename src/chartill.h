/*
 *  $ JAIST: chartill.h,v 0.1000 1995/10/03 23:04:01 $
 *
 *  @(#)chartill.h  03/10/1995  By Thanaruk Theeramunkong
 */

struct CList{
  int    type;		  /* Type of ill grammar */
  int	 gram;		  /* Grammar Rule Number */
  int	 dot;		  /* Dot in Grammar Rule */
  int    count;		  /* Current counts  */
  struct CList *next;     /* Next counter list */
};

typedef struct CList *CListptr;
