/*
 *  $ JAIST: chart.h,v 0.1000 1995/10/03 23:04:01 $
 *
 *  @(#)chart.h  03/10/1995  By Thanaruk Theeramunkong
 */

struct ListTree{
  struct Edge *ltree;      /* Pointer to the left tree of Type 2 */
  struct Edge *rtree;      /* Pointer to the right tree of Type 2 */
  struct ListTree *next;   /* Next Tree Pointer */
};

struct Edge{
  char type;               /* Lexical edge=0, Inactive=1, Active=2 */
                           /* Extra edge=3, Missing edge=4, Subs edge=5 */
  int num;                 /* Edge Number */
  int err;		   /* The number of Errors */
  int from;                /* Starting Position */
  int to;                  /* Ending Position */
  int gram;                /* Grammar Rule Number or Lexical Catagory */
  int dot;                 /* Dot Position */
  int numparses;	   /* The number of Parses */
  char word[WordLen];	   /* For Type 0 */
  struct ListTree *parse;  /* Parse Information */
  struct Edge *next;	   /* Next Edge */
};
 
struct EList {
  struct Edge  *edge;
  struct EList *next;
  struct EList *previous;
};

typedef struct ListTree *ListTreeptr;
typedef struct Edge *Edgeptr;
typedef struct EList *EListptr;

