/*
 *  $ JAIST: gram.h,v 0.1000 1995/10/04 20:04:01 $
 *
 *  @(#)gram.h  10/10/1995  By Thanaruk Theeramunkong
 */



#define GramNum       38
#define CatNum        18
#define TermNum       11
#define NonTermNum     7


/* This is a header for C-chart parser */
/* Category Table */
static char ctab[21][64] = {
	""              ,
	"JJ"            ,   /*    1 */
	"CC"            ,   /*    2 */
	"RB"            ,   /*    3 */
	"E"             ,   /*    4 */
	"NGAP"          ,   /*    5 */
	"NN"            ,   /*    6 */
	"NNP"           ,   /*    7 */
	"IN"            ,   /*    8 */
	"MD"            ,   /*    9 */
	"VB"            ,   /*   10 */
	"RP"            ,   /*   11 */
	"ADJP"          ,   /*   12 */
	"ADVP"          ,   /*   13 */
	"EP"            ,   /*   14 */
	"NP"            ,   /*   15 */
	"PP"            ,   /*   16 */
	"S"             ,   /*   17 */
	"VP"            ,   /*   18 */
	""
};

static int grammar[40][6] = {
	{   0,   0,   0,   0,   0,   0	},
	{  12,   1,   2,   1,   0,   0	}, /*    1 */
	{  12,   1,   0,   0,   0,   0	}, /*    2 */
	{  13,   3,   0,   0,   0,   0	}, /*    3 */
	{  13,   3,  18,   0,   0,   0	}, /*    4 */
	{  14,   4,  15,  18,   0,   0	}, /*    5 */
	{  15,  12,  15,   0,   0,   0	}, /*    6 */
	{  15,  14,   0,   0,   0,   0	}, /*    7 */
	{  15,   5,   6,   0,   0,   0	}, /*    8 */
	{  15,   5,   0,   0,   0,   0	}, /*    9 */
	{  15,   6,   0,   0,   0,   0	}, /*   10 */
	{  15,   7,   0,   0,   0,   0	}, /*   11 */
	{  15,  15,  12,   0,   0,   0	}, /*   12 */
	{  15,  15,   2,  15,   0,   0	}, /*   13 */
	{  15,  15,   2,  18,   0,   0	}, /*   14 */
	{  15,  15,  15,   0,   0,   0	}, /*   15 */
	{  15,  15,  16,   0,   0,   0	}, /*   16 */
	{  15,  15,  18,   0,   0,   0	}, /*   17 */
	{  16,   8,  15,   8,  15,   0	}, /*   18 */
	{  16,   8,  15,   0,   0,   0	}, /*   19 */
	{  16,   8,  18,   0,   0,   0	}, /*   20 */
	{  16,   8,   0,   0,   0,   0	}, /*   21 */
	{  17,  15,  18,  16,   0,   0	}, /*   22 */
	{  17,  15,  18,   0,   0,   0	}, /*   23 */
	{  17,  16,  15,  18,   0,   0	}, /*   24 */
	{  17,  16,  15,   0,   0,   0	}, /*   25 */
	{  17,  18,  15,   0,   0,   0	}, /*   26 */
	{  18,   9,  10,   0,   0,   0	}, /*   27 */
	{  18,  10,   0,   0,   0,   0	}, /*   28 */
	{  18,  18,  13,   0,   0,   0	}, /*   29 */
	{  18,  18,   2,  18,   0,   0	}, /*   30 */
	{  18,  18,   9,   0,   0,   0	}, /*   31 */
	{  18,  18,  15,   0,   0,   0	}, /*   32 */
	{  18,  18,  15,  13,   0,   0	}, /*   33 */
	{  18,  18,  16,  13,   0,   0	}, /*   34 */
	{  18,  18,  16,   9,   0,   0	}, /*   35 */
	{  18,  18,  16,   0,   0,   0	}, /*   36 */
	{  18,  18,  11,  16,   0,   0	}, /*   37 */
	{  18,  18,  11,   0,   0,   0	}, /*   38 */
	{   0,   0,   0,   0,   0,   0	}
};


static char gramtext[40][18] = {
		"",
/*    1 */	"ADJP-->JJ,CC,JJ.",
/*    2 */	"ADJP-->JJ.",
/*    3 */	"ADVP-->RB.",
/*    4 */	"ADVP-->RB,VP.",
/*    5 */	"EP-->E,NP,VP.",
/*    6 */	"NP-->ADJP,NP.",
/*    7 */	"NP-->EP.",
/*    8 */	"NP-->NGAP,NN.",
/*    9 */	"NP-->NGAP.",
/*   10 */	"NP-->NN.",
/*   11 */	"NP-->NNP.",
/*   12 */	"NP-->NP,ADJP.",
/*   13 */	"NP-->NP,CC,NP.",
/*   14 */	"NP-->NP,CC,VP.",
/*   15 */	"NP-->NP,NP.",
/*   16 */	"NP-->NP,PP.",
/*   17 */	"NP-->NP,VP.",
/*   18 */	"PP-->IN,NP,IN,NP.",
/*   19 */	"PP-->IN,NP.",
/*   20 */	"PP-->IN,VP.",
/*   21 */	"PP-->IN.",
/*   22 */	"S-->NP,VP,PP.",
/*   23 */	"S-->NP,VP.",
/*   24 */	"S-->PP,NP,VP.",
/*   25 */	"S-->PP,NP.",
/*   26 */	"S-->VP,NP.",
/*   27 */	"VP-->MD,VB.",
/*   28 */	"VP-->VB.",
/*   29 */	"VP-->VP,ADVP.",
/*   30 */	"VP-->VP,CC,VP.",
/*   31 */	"VP-->VP,MD.",
/*   32 */	"VP-->VP,NP.",
/*   33 */	"VP-->VP,NP,ADVP.",
/*   34 */	"VP-->VP,PP,ADVP.",
/*   35 */	"VP-->VP,PP,MD.",
/*   36 */	"VP-->VP,PP.",
/*   37 */	"VP-->VP,RP,PP.",
/*   38 */	"VP-->VP,RP.",
		""
};