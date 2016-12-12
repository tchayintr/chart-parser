/*
 *  $ JAIST: trancat.h,v 0.1000 1995/11/18 11:25:18 $
 *
 *  @(#)trancat.h  28/11/1995  By Thanaruk Theeramunkong
 */

/* This program is an option used as the header of trancat.c
 * Notice trancat.c for more information.
 */

#define WLen 120

char catcortab[][2][WLen] = {
	{ ".",    "FULLSTOP"	},
	{ "VBD",  "VB"		},
	{ "VBG",  "VB"		},
	{ "VBN",  "VB"		},
	{ "VBP",  "VB"		},
	{ "VBZ",  "VB"		},
	{ "JJR",  "JJ"		},
	{ "JJS",  "JJ"		},
	{ "RBR",  "RB"		},
	{ "RBS",  "RB"		},
	{ "PRP$", "PRP"		},
	{ "WP$",  "WP"		},
	{ ""   ,  ""		}
};
