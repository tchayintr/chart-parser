/*
 *  $ JAIST: gram.h,v 0.1000 1995/10/04 20:04:01 $
 *
 *  @(#)gram.h  10/10/1995  By Thanaruk Theeramunkong
 */



#define GramNum      272
#define CatNum        73
#define TermNum       18
#define NonTermNum    55


/* This is a header for C-chart parser */
/* Category Table */
static char ctab[76][64] = {
	""              ,
	"ADV"           ,   /*    1 */
	"NOUN"          ,   /*    2 */
	"ART"           ,   /*    3 */
	"DEMO"          ,   /*    4 */
	"INDEF"         ,   /*    5 */
	"CONJ"          ,   /*    6 */
	"NUM"           ,   /*    7 */
	"UNIT"          ,   /*    8 */
	"PRON"          ,   /*    9 */
	"WH"            ,   /*   10 */
	"ADJ"           ,   /*   11 */
	"VT"            ,   /*   12 */
	"VI"            ,   /*   13 */
	"AUX"           ,   /*   14 */
	"PREP"          ,   /*   15 */
	"PTCL"          ,   /*   16 */
	"BE"            ,   /*   17 */
	"ITJ"           ,   /*   18 */
	"_L1N1"         ,   /*   19 */
	"_L1N2"         ,   /*   20 */
	"_L1N3"         ,   /*   21 */
	"_L1N4"         ,   /*   22 */
	"_L1N5"         ,   /*   23 */
	"_L1N6"         ,   /*   24 */
	"_L1N7"         ,   /*   25 */
	"_L1N8"         ,   /*   26 */
	"_L1N9"         ,   /*   27 */
	"_L1N10"        ,   /*   28 */
	"_L1N11"        ,   /*   29 */
	"_L1N12"        ,   /*   30 */
	"_L1N13"        ,   /*   31 */
	"_L1N14"        ,   /*   32 */
	"_L1N15"        ,   /*   33 */
	"_L1N16"        ,   /*   34 */
	"_L1N17"        ,   /*   35 */
	"_L1N18"        ,   /*   36 */
	"_L1N19"        ,   /*   37 */
	"_L1N21"        ,   /*   38 */
	"_L1N23"        ,   /*   39 */
	"_L1N24"        ,   /*   40 */
	"_L1N25"        ,   /*   41 */
	"_L1N26"        ,   /*   42 */
	"_L1N27"        ,   /*   43 */
	"_L1N28"        ,   /*   44 */
	"_L1N29"        ,   /*   45 */
	"_L1N30"        ,   /*   46 */
	"_L1N31"        ,   /*   47 */
	"_L1N32"        ,   /*   48 */
	"_L1N33"        ,   /*   49 */
	"_L1N34"        ,   /*   50 */
	"_L1N36"        ,   /*   51 */
	"_L1N37"        ,   /*   52 */
	"_L2N2"         ,   /*   53 */
	"_L2N3"         ,   /*   54 */
	"_L2N4"         ,   /*   55 */
	"_L2N6"         ,   /*   56 */
	"_L2N7"         ,   /*   57 */
	"_L2N8"         ,   /*   58 */
	"_L2N9"         ,   /*   59 */
	"_L2N10"        ,   /*   60 */
	"_L3N1"         ,   /*   61 */
	"_L3N2"         ,   /*   62 */
	"_L3N3"         ,   /*   63 */
	"_L3N4"         ,   /*   64 */
	"_L3N5"         ,   /*   65 */
	"_L3N6"         ,   /*   66 */
	"_L3N7"         ,   /*   67 */
	"_L3N8"         ,   /*   68 */
	"_L3N9"         ,   /*   69 */
	"_L4N1"         ,   /*   70 */
	"_L4N2"         ,   /*   71 */
	"_L4N3"         ,   /*   72 */
	"_L4N4"         ,   /*   73 */
	""
};

static int grammar[274][6] = {
	{   0,   0,   0,   0,   0,   0	},
	{  19,   1,   2,   0,   0,   0	}, /*    1 */
	{  19,   1,  19,   0,   0,   0	}, /*    2 */
	{  19,   1,  20,   0,   0,   0	}, /*    3 */
	{  19,   3,   2,   0,   0,   0	}, /*    4 */
	{  19,   3,  19,   0,   0,   0	}, /*    5 */
	{  19,   3,  20,   0,   0,   0	}, /*    6 */
	{  19,   3,  26,   0,   0,   0	}, /*    7 */
	{  19,   4,   2,   0,   0,   0	}, /*    8 */
	{  19,   4,  19,   0,   0,   0	}, /*    9 */
	{  19,   4,  20,   0,   0,   0	}, /*   10 */
	{  19,   5,   2,   0,   0,   0	}, /*   11 */
	{  19,   5,  19,   0,   0,   0	}, /*   12 */
	{  19,   5,  20,   0,   0,   0	}, /*   13 */
	{  19,   5,  22,   0,   0,   0	}, /*   14 */
	{  19,   2,   6,  20,   0,   0	}, /*   15 */
	{  19,   2,   2,   6,   2,   0	}, /*   16 */
	{  19,   2,   7,   0,   0,   0	}, /*   17 */
	{  19,   2,  19,   0,   0,   0	}, /*   18 */
	{  19,   7,   2,   0,   0,   0	}, /*   19 */
	{  19,   7,   8,   0,   0,   0	}, /*   20 */
	{  19,   7,  22,   0,   0,   0	}, /*   21 */
	{  19,   9,   2,   0,   0,   0	}, /*   22 */
	{  19,   9,  20,   0,   0,   0	}, /*   23 */
	{  19,   9,  22,   0,   0,   0	}, /*   24 */
	{  19,  10,  38,   0,   0,   0	}, /*   25 */
	{  19,  10,  22,   0,   0,   0	}, /*   26 */
	{  19,  19,   1,   0,   0,   0	}, /*   27 */
	{  19,  19,   6,  19,   0,   0	}, /*   28 */
	{  19,  19,  19,   0,   0,   0	}, /*   29 */
	{  19,  19,  19,   0,   0,   0	}, /*   30 */
	{  19,  19,  38,   0,   0,   0	}, /*   31 */
	{  19,  19,  22,   0,   0,   0	}, /*   32 */
	{  19,  37,   2,   0,   0,   0	}, /*   33 */
	{  19,  20,   1,   0,   0,   0	}, /*   34 */
	{  19,  20,   6,   2,   0,   0	}, /*   35 */
	{  19,  20,   6,  20,   0,   0	}, /*   36 */
	{  19,  20,  19,   0,   0,   0	}, /*   37 */
	{  19,  20,  22,   0,   0,   0	}, /*   38 */
	{  19,  42,  20,   0,   0,   0	}, /*   39 */
	{  19,  22,  19,   0,   0,   0	}, /*   40 */
	{  19,  23,   2,   0,   0,   0	}, /*   41 */
	{  20,  11,   5,   0,   0,   0	}, /*   42 */
	{  20,  11,   2,   0,   0,   0	}, /*   43 */
	{  20,  11,  19,   0,   0,   0	}, /*   44 */
	{  20,  11,  20,   0,   0,   0	}, /*   45 */
	{  20,  11,  26,   0,   0,   0	}, /*   46 */
	{  20,   2,   1,   0,   0,   0	}, /*   47 */
	{  20,   2,   6,   2,   0,   0	}, /*   48 */
	{  20,   2,   2,   0,   0,   0	}, /*   49 */
	{  20,   2,  12,   0,   0,   0	}, /*   50 */
	{  20,   2,  20,   0,   0,   0	}, /*   51 */
	{  20,   2,  22,   0,   0,   0	}, /*   52 */
	{  20,   7,  20,   0,   0,   0	}, /*   53 */
	{  20,  13,   2,   0,   0,   0	}, /*   54 */
	{  20,  19,   2,   0,   0,   0	}, /*   55 */
	{  20,  19,  20,   0,   0,   0	}, /*   56 */
	{  20,  20,   2,   0,   0,   0	}, /*   57 */
	{  20,  20,  20,   0,   0,   0	}, /*   58 */
	{  20,  22,   2,   0,   0,   0	}, /*   59 */
	{  20,  27,   2,   0,   0,   0	}, /*   60 */
	{  20,  27,  20,   0,   0,   0	}, /*   61 */
	{  21,   1,  21,   0,   0,   0	}, /*   62 */
	{  21,  14,  12,   0,   0,   0	}, /*   63 */
	{  21,  14,  31,   0,   0,   0	}, /*   64 */
	{  21,  30,  12,   0,   0,   0	}, /*   65 */
	{  21,  31,  12,   0,   0,   0	}, /*   66 */
	{  22,  11,  22,   0,   0,   0	}, /*   67 */
	{  22,   1,   1,   0,   0,   0	}, /*   68 */
	{  22,   1,  22,   0,   0,   0	}, /*   69 */
	{  22,  14,   9,   0,   0,   0	}, /*   70 */
	{  22,   6,   1,   0,   0,   0	}, /*   71 */
	{  22,   6,   2,   0,   0,   0	}, /*   72 */
	{  22,   6,  20,   0,   0,   0	}, /*   73 */
	{  22,   6,  38,   0,   0,   0	}, /*   74 */
	{  22,   6,  22,   0,   0,   0	}, /*   75 */
	{  22,   6,  26,   0,   0,   0	}, /*   76 */
	{  22,  15,  11,   0,   0,   0	}, /*   77 */
	{  22,  15,   1,   0,   0,   0	}, /*   78 */
	{  22,  15,   4,   0,   0,   0	}, /*   79 */
	{  22,  15,   5,   0,   0,   0	}, /*   80 */
	{  22,  15,   2,   0,   0,   0	}, /*   81 */
	{  22,  15,   7,   0,   0,   0	}, /*   82 */
	{  22,  15,   9,   0,   0,   0	}, /*   83 */
	{  22,  15,  13,   0,   0,   0	}, /*   84 */
	{  22,  15,  19,   0,   0,   0	}, /*   85 */
	{  22,  15,  20,   0,   0,   0	}, /*   86 */
	{  22,  15,  38,   0,   0,   0	}, /*   87 */
	{  22,  15,  40,   0,   0,   0	}, /*   88 */
	{  22,  15,  22,   0,   0,   0	}, /*   89 */
	{  22,  15,  26,   0,   0,   0	}, /*   90 */
	{  22,  16,  13,   0,   0,   0	}, /*   91 */
	{  22,  16,  26,   0,   0,   0	}, /*   92 */
	{  22,  10,  26,   0,   0,   0	}, /*   93 */
	{  22,  30,   9,   0,   0,   0	}, /*   94 */
	{  22,  33,   9,   0,   0,   0	}, /*   95 */
	{  22,  22,   1,   0,   0,   0	}, /*   96 */
	{  22,  22,  22,   0,   0,   0	}, /*   97 */
	{  22,  24,   2,   0,   0,   0	}, /*   98 */
	{  22,  24,  19,   0,   0,   0	}, /*   99 */
	{  22,  24,  20,   0,   0,   0	}, /*  100 */
	{  22,  25,   2,   0,   0,   0	}, /*  101 */
	{  22,  25,  19,   0,   0,   0	}, /*  102 */
	{  22,  25,  20,   0,   0,   0	}, /*  103 */
	{  23,   3,  11,   0,   0,   0	}, /*  104 */
	{  24,  11,  15,   0,   0,   0	}, /*  105 */
	{  24,   1,  15,   0,   0,   0	}, /*  106 */
	{  24,  15,   2,  15,   0,   0	}, /*  107 */
	{  25,  16,  12,   0,   0,   0	}, /*  108 */
	{  25,  16,  31,   0,   0,   0	}, /*  109 */
	{  26,   1,  13,   0,   0,   0	}, /*  110 */
	{  26,   1,  26,   0,   0,   0	}, /*  111 */
	{  26,  14,  17,  12,   0,   0	}, /*  112 */
	{  26,  14,  13,   0,   0,   0	}, /*  113 */
	{  26,  14,  26,   0,   0,   0	}, /*  114 */
	{  26,  17,  11,   0,   0,   0	}, /*  115 */
	{  26,  17,   2,   0,   0,   0	}, /*  116 */
	{  26,  17,  13,   0,   0,   0	}, /*  117 */
	{  26,  17,  12,   0,   0,   0	}, /*  118 */
	{  26,  17,  19,   0,   0,   0	}, /*  119 */
	{  26,  17,  31,   0,   0,   0	}, /*  120 */
	{  26,  17,  20,   0,   0,   0	}, /*  121 */
	{  26,  17,  22,   0,   0,   0	}, /*  122 */
	{  26,  17,  26,   0,   0,   0	}, /*  123 */
	{  26,  17,  27,   0,   0,   0	}, /*  124 */
	{  26,  13,  11,   0,   0,   0	}, /*  125 */
	{  26,  13,   1,   0,   0,   0	}, /*  126 */
	{  26,  13,  16,   0,   0,   0	}, /*  127 */
	{  26,  13,  19,   0,   0,   0	}, /*  128 */
	{  26,  13,  20,   0,   0,   0	}, /*  129 */
	{  26,  13,  22,   0,   0,   0	}, /*  130 */
	{  26,  13,  27,   0,   0,   0	}, /*  131 */
	{  26,  12,  11,   0,   0,   0	}, /*  132 */
	{  26,  12,   1,   0,   0,   0	}, /*  133 */
	{  26,  12,   2,   0,   0,   0	}, /*  134 */
	{  26,  12,   9,   0,   0,   0	}, /*  135 */
	{  26,  12,  19,   0,   0,   0	}, /*  136 */
	{  26,  12,  20,   0,   0,   0	}, /*  137 */
	{  26,  12,  22,   0,   0,   0	}, /*  138 */
	{  26,  30,  13,   0,   0,   0	}, /*  139 */
	{  26,  30,  26,   0,   0,   0	}, /*  140 */
	{  26,  31,   2,   0,   0,   0	}, /*  141 */
	{  26,  31,   9,   0,   0,   0	}, /*  142 */
	{  26,  31,  19,   0,   0,   0	}, /*  143 */
	{  26,  31,  20,   0,   0,   0	}, /*  144 */
	{  26,  32,  11,   0,   0,   0	}, /*  145 */
	{  26,  32,  12,   0,   0,   0	}, /*  146 */
	{  26,  32,  19,   0,   0,   0	}, /*  147 */
	{  26,  33,  11,   0,   0,   0	}, /*  148 */
	{  26,  33,  12,   0,   0,   0	}, /*  149 */
	{  26,  21,   2,   0,   0,   0	}, /*  150 */
	{  26,  21,  19,   0,   0,   0	}, /*  151 */
	{  26,  21,  20,   0,   0,   0	}, /*  152 */
	{  26,  21,  22,   0,   0,   0	}, /*  153 */
	{  26,  26,  11,   0,   0,   0	}, /*  154 */
	{  26,  26,   1,   0,   0,   0	}, /*  155 */
	{  26,  26,   2,   0,   0,   0	}, /*  156 */
	{  26,  26,  19,   0,   0,   0	}, /*  157 */
	{  26,  26,  20,   0,   0,   0	}, /*  158 */
	{  26,  26,  22,   0,   0,   0	}, /*  159 */
	{  27,  11,  11,   0,   0,   0	}, /*  160 */
	{  27,  11,   6,  11,   0,   0	}, /*  161 */
	{  27,   1,  11,   0,   0,   0	}, /*  162 */
	{  27,   1,  27,   0,   0,   0	}, /*  163 */
	{  27,   2,  11,   0,   0,   0	}, /*  164 */
	{  28,  16,  17,   0,   0,   0	}, /*  165 */
	{  29,   2,  15,   0,   0,   0	}, /*  166 */
	{  30,  14,   1,   0,   0,   0	}, /*  167 */
	{  31,   1,  12,   0,   0,   0	}, /*  168 */
	{  31,   1,  31,   0,   0,   0	}, /*  169 */
	{  31,  13,  15,   0,   0,   0	}, /*  170 */
	{  31,  12,  15,   0,   0,   0	}, /*  171 */
	{  31,  12,  16,   0,   0,   0	}, /*  172 */
	{  31,  12,  25,   0,   0,   0	}, /*  173 */
	{  31,  26,  15,   0,   0,   0	}, /*  174 */
	{  32,  14,  17,   0,   0,   0	}, /*  175 */
	{  33,  17,   1,   0,   0,   0	}, /*  176 */
	{  34,   1,  17,   0,   0,   0	}, /*  177 */
	{  34,   1,  32,   0,   0,   0	}, /*  178 */
	{  35,   9,  11,   0,   0,   0	}, /*  179 */
	{  36,   2,   6,   0,   0,   0	}, /*  180 */
	{  37,   1,   7,   0,   0,   0	}, /*  181 */
	{  38,   2,  26,   0,   0,   0	}, /*  182 */
	{  38,   9,  13,   0,   0,   0	}, /*  183 */
	{  38,   9,  12,   0,   0,   0	}, /*  184 */
	{  38,   9,  26,   0,   0,   0	}, /*  185 */
	{  38,   9,  55,   0,   0,   0	}, /*  186 */
	{  38,  19,  13,   0,   0,   0	}, /*  187 */
	{  38,  19,  26,   0,   0,   0	}, /*  188 */
	{  38,  20,  26,   0,   0,   0	}, /*  189 */
	{  39,   3,   5,   0,   0,   0	}, /*  190 */
	{  40,  11,   7,   0,   0,   0	}, /*  191 */
	{  41,   1,   6,   0,   0,   0	}, /*  192 */
	{  42,   3,   2,  15,   0,   0	}, /*  193 */
	{  42,  19,  15,   0,   0,   0	}, /*  194 */
	{  43,   5,  11,   0,   0,   0	}, /*  195 */
	{  44,   6,  11,   0,   0,   0	}, /*  196 */
	{  45,  10,   2,   0,   0,   0	}, /*  197 */
	{  46,  10,  11,   0,   0,   0	}, /*  198 */
	{  47,  14,  16,   0,   0,   0	}, /*  199 */
	{  48,   3,   1,   0,   0,   0	}, /*  200 */
	{  49,  10,  17,   0,   0,   0	}, /*  201 */
	{  50,   9,  17,   0,   0,   0	}, /*  202 */
	{  51,   9,  14,   0,   0,   0	}, /*  203 */
	{  52,  12,   5,   0,   0,   0	}, /*  204 */
	{  53,  19,  12,   0,   0,   0	}, /*  205 */
	{  54,  26,  16,   0,   0,   0	}, /*  206 */
	{  55,  21,   9,   0,   0,   0	}, /*  207 */
	{  56,   9,  21,   0,   0,   0	}, /*  208 */
	{  57,  42,   2,   0,   0,   0	}, /*  209 */
	{  58,  19,  11,   0,   0,   0	}, /*  210 */
	{  59,  25,   9,   0,   0,   0	}, /*  211 */
	{  60,   6,  19,   0,   0,   0	}, /*  212 */
	{  61,   1,  38,   0,   0,   0	}, /*  213 */
	{  61,   1,  61,   0,   0,   0	}, /*  214 */
	{  61,  14,  38,   0,   0,   0	}, /*  215 */
	{  61,  14,  61,   0,   0,   0	}, /*  216 */
	{  61,   6,  61,   0,   0,   0	}, /*  217 */
	{  61,   4,  26,   0,   0,   0	}, /*  218 */
	{  61,   5,  26,   0,   0,   0	}, /*  219 */
	{  61,  18,  38,   0,   0,   0	}, /*  220 */
	{  61,  18,  26,   0,   0,   0	}, /*  221 */
	{  61,   2,  63,   0,   0,   0	}, /*  222 */
	{  61,   9,  63,   0,   0,   0	}, /*  223 */
	{  61,  10,  61,   0,   0,   0	}, /*  224 */
	{  61,  10,  63,   0,   0,   0	}, /*  225 */
	{  61,  19,  63,   0,   0,   0	}, /*  226 */
	{  61,  30,  38,   0,   0,   0	}, /*  227 */
	{  61,  20,  38,   0,   0,   0	}, /*  228 */
	{  61,  20,  63,   0,   0,   0	}, /*  229 */
	{  61,  38,   1,   0,   0,   0	}, /*  230 */
	{  61,  38,  19,   0,   0,   0	}, /*  231 */
	{  61,  38,  38,   0,   0,   0	}, /*  232 */
	{  61,  38,  22,   0,   0,   0	}, /*  233 */
	{  61,  38,  26,   0,   0,   0	}, /*  234 */
	{  61,  38,  61,   0,   0,   0	}, /*  235 */
	{  61,  22,  38,   0,   0,   0	}, /*  236 */
	{  61,  22,  61,   0,   0,   0	}, /*  237 */
	{  61,  61,  22,   0,   0,   0	}, /*  238 */
	{  61,  64,  22,   0,   0,   0	}, /*  239 */
	{  62,  27,  22,   0,   0,   0	}, /*  240 */
	{  63,   1,  63,   0,   0,   0	}, /*  241 */
	{  63,  17,  38,   0,   0,   0	}, /*  242 */
	{  63,  12,  19,   0,   0,   0	}, /*  243 */
	{  63,  12,  38,   0,   0,   0	}, /*  244 */
	{  63,  12,  26,   0,   0,   0	}, /*  245 */
	{  63,  12,  61,   0,   0,   0	}, /*  246 */
	{  63,  31,  22,   0,   0,   0	}, /*  247 */
	{  63,  31,  26,   0,   0,   0	}, /*  248 */
	{  63,  33,  19,   0,   0,   0	}, /*  249 */
	{  63,  33,  22,   0,   0,   0	}, /*  250 */
	{  63,  21,  38,   0,   0,   0	}, /*  251 */
	{  63,  21,  26,   0,   0,   0	}, /*  252 */
	{  63,  22,  26,   0,   0,   0	}, /*  253 */
	{  63,  26,   6,  26,   0,   0	}, /*  254 */
	{  63,  26,   9,   0,   0,   0	}, /*  255 */
	{  63,  26,  38,   0,   0,   0	}, /*  256 */
	{  63,  26,  26,   0,   0,   0	}, /*  257 */
	{  63,  26,  27,   0,   0,   0	}, /*  258 */
	{  63,  26,  61,   0,   0,   0	}, /*  259 */
	{  63,  55,  22,   0,   0,   0	}, /*  260 */
	{  63,  63,  22,   0,   0,   0	}, /*  261 */
	{  64,  34,  19,   0,   0,   0	}, /*  262 */
	{  64,  34,  20,   0,   0,   0	}, /*  263 */
	{  65,  26,  12,   0,   0,   0	}, /*  264 */
	{  66,  26,  25,   0,   0,   0	}, /*  265 */
	{  67,   2,  38,   0,   0,   0	}, /*  266 */
	{  68,  20,  12,   0,   0,   0	}, /*  267 */
	{  69,   9,  31,   0,   0,   0	}, /*  268 */
	{  70,   3,  38,   0,   0,   0	}, /*  269 */
	{  71,  16,  63,   0,   0,   0	}, /*  270 */
	{  72,   9,  19,   0,   0,   0	}, /*  271 */
	{  73,  55,  19,   0,   0,   0	}, /*  272 */
	{   0,   0,   0,   0,   0,   0	}
};


static char gramtext[274][29] = {
		"",
/*    1 */	"_L1N1-->ADV,NOUN.",
/*    2 */	"_L1N1-->ADV,_L1N1.",
/*    3 */	"_L1N1-->ADV,_L1N2.",
/*    4 */	"_L1N1-->ART,NOUN.",
/*    5 */	"_L1N1-->ART,_L1N1.",
/*    6 */	"_L1N1-->ART,_L1N2.",
/*    7 */	"_L1N1-->ART,_L1N8.",
/*    8 */	"_L1N1-->DEMO,NOUN.",
/*    9 */	"_L1N1-->DEMO,_L1N1.",
/*   10 */	"_L1N1-->DEMO,_L1N2.",
/*   11 */	"_L1N1-->INDEF,NOUN.",
/*   12 */	"_L1N1-->INDEF,_L1N1.",
/*   13 */	"_L1N1-->INDEF,_L1N2.",
/*   14 */	"_L1N1-->INDEF,_L1N4.",
/*   15 */	"_L1N1-->NOUN,CONJ,_L1N2.",
/*   16 */	"_L1N1-->NOUN,NOUN,CONJ,NOUN.",
/*   17 */	"_L1N1-->NOUN,NUM.",
/*   18 */	"_L1N1-->NOUN,_L1N1.",
/*   19 */	"_L1N1-->NUM,NOUN.",
/*   20 */	"_L1N1-->NUM,UNIT.",
/*   21 */	"_L1N1-->NUM,_L1N4.",
/*   22 */	"_L1N1-->PRON,NOUN.",
/*   23 */	"_L1N1-->PRON,_L1N2.",
/*   24 */	"_L1N1-->PRON,_L1N4.",
/*   25 */	"_L1N1-->WH,_L1N21.",
/*   26 */	"_L1N1-->WH,_L1N4.",
/*   27 */	"_L1N1-->_L1N1,ADV.",
/*   28 */	"_L1N1-->_L1N1,CONJ,_L1N1.",
/*   29 */	"_L1N1-->_L1N1,_L1N1.",
/*   30 */	"_L1N1-->_L1N1,_L1N1.",
/*   31 */	"_L1N1-->_L1N1,_L1N21.",
/*   32 */	"_L1N1-->_L1N1,_L1N4.",
/*   33 */	"_L1N1-->_L1N19,NOUN.",
/*   34 */	"_L1N1-->_L1N2,ADV.",
/*   35 */	"_L1N1-->_L1N2,CONJ,NOUN.",
/*   36 */	"_L1N1-->_L1N2,CONJ,_L1N2.",
/*   37 */	"_L1N1-->_L1N2,_L1N1.",
/*   38 */	"_L1N1-->_L1N2,_L1N4.",
/*   39 */	"_L1N1-->_L1N26,_L1N2.",
/*   40 */	"_L1N1-->_L1N4,_L1N1.",
/*   41 */	"_L1N1-->_L1N5,NOUN.",
/*   42 */	"_L1N2-->ADJ,INDEF.",
/*   43 */	"_L1N2-->ADJ,NOUN.",
/*   44 */	"_L1N2-->ADJ,_L1N1.",
/*   45 */	"_L1N2-->ADJ,_L1N2.",
/*   46 */	"_L1N2-->ADJ,_L1N8.",
/*   47 */	"_L1N2-->NOUN,ADV.",
/*   48 */	"_L1N2-->NOUN,CONJ,NOUN.",
/*   49 */	"_L1N2-->NOUN,NOUN.",
/*   50 */	"_L1N2-->NOUN,VT.",
/*   51 */	"_L1N2-->NOUN,_L1N2.",
/*   52 */	"_L1N2-->NOUN,_L1N4.",
/*   53 */	"_L1N2-->NUM,_L1N2.",
/*   54 */	"_L1N2-->VI,NOUN.",
/*   55 */	"_L1N2-->_L1N1,NOUN.",
/*   56 */	"_L1N2-->_L1N1,_L1N2.",
/*   57 */	"_L1N2-->_L1N2,NOUN.",
/*   58 */	"_L1N2-->_L1N2,_L1N2.",
/*   59 */	"_L1N2-->_L1N4,NOUN.",
/*   60 */	"_L1N2-->_L1N9,NOUN.",
/*   61 */	"_L1N2-->_L1N9,_L1N2.",
/*   62 */	"_L1N3-->ADV,_L1N3.",
/*   63 */	"_L1N3-->AUX,VT.",
/*   64 */	"_L1N3-->AUX,_L1N13.",
/*   65 */	"_L1N3-->_L1N12,VT.",
/*   66 */	"_L1N3-->_L1N13,VT.",
/*   67 */	"_L1N4-->ADJ,_L1N4.",
/*   68 */	"_L1N4-->ADV,ADV.",
/*   69 */	"_L1N4-->ADV,_L1N4.",
/*   70 */	"_L1N4-->AUX,PRON.",
/*   71 */	"_L1N4-->CONJ,ADV.",
/*   72 */	"_L1N4-->CONJ,NOUN.",
/*   73 */	"_L1N4-->CONJ,_L1N2.",
/*   74 */	"_L1N4-->CONJ,_L1N21.",
/*   75 */	"_L1N4-->CONJ,_L1N4.",
/*   76 */	"_L1N4-->CONJ,_L1N8.",
/*   77 */	"_L1N4-->PREP,ADJ.",
/*   78 */	"_L1N4-->PREP,ADV.",
/*   79 */	"_L1N4-->PREP,DEMO.",
/*   80 */	"_L1N4-->PREP,INDEF.",
/*   81 */	"_L1N4-->PREP,NOUN.",
/*   82 */	"_L1N4-->PREP,NUM.",
/*   83 */	"_L1N4-->PREP,PRON.",
/*   84 */	"_L1N4-->PREP,VI.",
/*   85 */	"_L1N4-->PREP,_L1N1.",
/*   86 */	"_L1N4-->PREP,_L1N2.",
/*   87 */	"_L1N4-->PREP,_L1N21.",
/*   88 */	"_L1N4-->PREP,_L1N24.",
/*   89 */	"_L1N4-->PREP,_L1N4.",
/*   90 */	"_L1N4-->PREP,_L1N8.",
/*   91 */	"_L1N4-->PTCL,VI.",
/*   92 */	"_L1N4-->PTCL,_L1N8.",
/*   93 */	"_L1N4-->WH,_L1N8.",
/*   94 */	"_L1N4-->_L1N12,PRON.",
/*   95 */	"_L1N4-->_L1N15,PRON.",
/*   96 */	"_L1N4-->_L1N4,ADV.",
/*   97 */	"_L1N4-->_L1N4,_L1N4.",
/*   98 */	"_L1N4-->_L1N6,NOUN.",
/*   99 */	"_L1N4-->_L1N6,_L1N1.",
/*  100 */	"_L1N4-->_L1N6,_L1N2.",
/*  101 */	"_L1N4-->_L1N7,NOUN.",
/*  102 */	"_L1N4-->_L1N7,_L1N1.",
/*  103 */	"_L1N4-->_L1N7,_L1N2.",
/*  104 */	"_L1N5-->ART,ADJ.",
/*  105 */	"_L1N6-->ADJ,PREP.",
/*  106 */	"_L1N6-->ADV,PREP.",
/*  107 */	"_L1N6-->PREP,NOUN,PREP.",
/*  108 */	"_L1N7-->PTCL,VT.",
/*  109 */	"_L1N7-->PTCL,_L1N13.",
/*  110 */	"_L1N8-->ADV,VI.",
/*  111 */	"_L1N8-->ADV,_L1N8.",
/*  112 */	"_L1N8-->AUX,BE,VT.",
/*  113 */	"_L1N8-->AUX,VI.",
/*  114 */	"_L1N8-->AUX,_L1N8.",
/*  115 */	"_L1N8-->BE,ADJ.",
/*  116 */	"_L1N8-->BE,NOUN.",
/*  117 */	"_L1N8-->BE,VI.",
/*  118 */	"_L1N8-->BE,VT.",
/*  119 */	"_L1N8-->BE,_L1N1.",
/*  120 */	"_L1N8-->BE,_L1N13.",
/*  121 */	"_L1N8-->BE,_L1N2.",
/*  122 */	"_L1N8-->BE,_L1N4.",
/*  123 */	"_L1N8-->BE,_L1N8.",
/*  124 */	"_L1N8-->BE,_L1N9.",
/*  125 */	"_L1N8-->VI,ADJ.",
/*  126 */	"_L1N8-->VI,ADV.",
/*  127 */	"_L1N8-->VI,PTCL.",
/*  128 */	"_L1N8-->VI,_L1N1.",
/*  129 */	"_L1N8-->VI,_L1N2.",
/*  130 */	"_L1N8-->VI,_L1N4.",
/*  131 */	"_L1N8-->VI,_L1N9.",
/*  132 */	"_L1N8-->VT,ADJ.",
/*  133 */	"_L1N8-->VT,ADV.",
/*  134 */	"_L1N8-->VT,NOUN.",
/*  135 */	"_L1N8-->VT,PRON.",
/*  136 */	"_L1N8-->VT,_L1N1.",
/*  137 */	"_L1N8-->VT,_L1N2.",
/*  138 */	"_L1N8-->VT,_L1N4.",
/*  139 */	"_L1N8-->_L1N12,VI.",
/*  140 */	"_L1N8-->_L1N12,_L1N8.",
/*  141 */	"_L1N8-->_L1N13,NOUN.",
/*  142 */	"_L1N8-->_L1N13,PRON.",
/*  143 */	"_L1N8-->_L1N13,_L1N1.",
/*  144 */	"_L1N8-->_L1N13,_L1N2.",
/*  145 */	"_L1N8-->_L1N14,ADJ.",
/*  146 */	"_L1N8-->_L1N14,VT.",
/*  147 */	"_L1N8-->_L1N14,_L1N1.",
/*  148 */	"_L1N8-->_L1N15,ADJ.",
/*  149 */	"_L1N8-->_L1N15,VT.",
/*  150 */	"_L1N8-->_L1N3,NOUN.",
/*  151 */	"_L1N8-->_L1N3,_L1N1.",
/*  152 */	"_L1N8-->_L1N3,_L1N2.",
/*  153 */	"_L1N8-->_L1N3,_L1N4.",
/*  154 */	"_L1N8-->_L1N8,ADJ.",
/*  155 */	"_L1N8-->_L1N8,ADV.",
/*  156 */	"_L1N8-->_L1N8,NOUN.",
/*  157 */	"_L1N8-->_L1N8,_L1N1.",
/*  158 */	"_L1N8-->_L1N8,_L1N2.",
/*  159 */	"_L1N8-->_L1N8,_L1N4.",
/*  160 */	"_L1N9-->ADJ,ADJ.",
/*  161 */	"_L1N9-->ADJ,CONJ,ADJ.",
/*  162 */	"_L1N9-->ADV,ADJ.",
/*  163 */	"_L1N9-->ADV,_L1N9.",
/*  164 */	"_L1N9-->NOUN,ADJ.",
/*  165 */	"_L1N10-->PTCL,BE.",
/*  166 */	"_L1N11-->NOUN,PREP.",
/*  167 */	"_L1N12-->AUX,ADV.",
/*  168 */	"_L1N13-->ADV,VT.",
/*  169 */	"_L1N13-->ADV,_L1N13.",
/*  170 */	"_L1N13-->VI,PREP.",
/*  171 */	"_L1N13-->VT,PREP.",
/*  172 */	"_L1N13-->VT,PTCL.",
/*  173 */	"_L1N13-->VT,_L1N7.",
/*  174 */	"_L1N13-->_L1N8,PREP.",
/*  175 */	"_L1N14-->AUX,BE.",
/*  176 */	"_L1N15-->BE,ADV.",
/*  177 */	"_L1N16-->ADV,BE.",
/*  178 */	"_L1N16-->ADV,_L1N14.",
/*  179 */	"_L1N17-->PRON,ADJ.",
/*  180 */	"_L1N18-->NOUN,CONJ.",
/*  181 */	"_L1N19-->ADV,NUM.",
/*  182 */	"_L1N21-->NOUN,_L1N8.",
/*  183 */	"_L1N21-->PRON,VI.",
/*  184 */	"_L1N21-->PRON,VT.",
/*  185 */	"_L1N21-->PRON,_L1N8.",
/*  186 */	"_L1N21-->PRON,_L2N4.",
/*  187 */	"_L1N21-->_L1N1,VI.",
/*  188 */	"_L1N21-->_L1N1,_L1N8.",
/*  189 */	"_L1N21-->_L1N2,_L1N8.",
/*  190 */	"_L1N23-->ART,INDEF.",
/*  191 */	"_L1N24-->ADJ,NUM.",
/*  192 */	"_L1N25-->ADV,CONJ.",
/*  193 */	"_L1N26-->ART,NOUN,PREP.",
/*  194 */	"_L1N26-->_L1N1,PREP.",
/*  195 */	"_L1N27-->INDEF,ADJ.",
/*  196 */	"_L1N28-->CONJ,ADJ.",
/*  197 */	"_L1N29-->WH,NOUN.",
/*  198 */	"_L1N30-->WH,ADJ.",
/*  199 */	"_L1N31-->AUX,PTCL.",
/*  200 */	"_L1N32-->ART,ADV.",
/*  201 */	"_L1N33-->WH,BE.",
/*  202 */	"_L1N34-->PRON,BE.",
/*  203 */	"_L1N36-->PRON,AUX.",
/*  204 */	"_L1N37-->VT,INDEF.",
/*  205 */	"_L2N2-->_L1N1,VT.",
/*  206 */	"_L2N3-->_L1N8,PTCL.",
/*  207 */	"_L2N4-->_L1N3,PRON.",
/*  208 */	"_L2N6-->PRON,_L1N3.",
/*  209 */	"_L2N7-->_L1N26,NOUN.",
/*  210 */	"_L2N8-->_L1N1,ADJ.",
/*  211 */	"_L2N9-->_L1N7,PRON.",
/*  212 */	"_L2N10-->CONJ,_L1N1.",
/*  213 */	"_L3N1-->ADV,_L1N21.",
/*  214 */	"_L3N1-->ADV,_L3N1.",
/*  215 */	"_L3N1-->AUX,_L1N21.",
/*  216 */	"_L3N1-->AUX,_L3N1.",
/*  217 */	"_L3N1-->CONJ,_L3N1.",
/*  218 */	"_L3N1-->DEMO,_L1N8.",
/*  219 */	"_L3N1-->INDEF,_L1N8.",
/*  220 */	"_L3N1-->ITJ,_L1N21.",
/*  221 */	"_L3N1-->ITJ,_L1N8.",
/*  222 */	"_L3N1-->NOUN,_L3N3.",
/*  223 */	"_L3N1-->PRON,_L3N3.",
/*  224 */	"_L3N1-->WH,_L3N1.",
/*  225 */	"_L3N1-->WH,_L3N3.",
/*  226 */	"_L3N1-->_L1N1,_L3N3.",
/*  227 */	"_L3N1-->_L1N12,_L1N21.",
/*  228 */	"_L3N1-->_L1N2,_L1N21.",
/*  229 */	"_L3N1-->_L1N2,_L3N3.",
/*  230 */	"_L3N1-->_L1N21,ADV.",
/*  231 */	"_L3N1-->_L1N21,_L1N1.",
/*  232 */	"_L3N1-->_L1N21,_L1N21.",
/*  233 */	"_L3N1-->_L1N21,_L1N4.",
/*  234 */	"_L3N1-->_L1N21,_L1N8.",
/*  235 */	"_L3N1-->_L1N21,_L3N1.",
/*  236 */	"_L3N1-->_L1N4,_L1N21.",
/*  237 */	"_L3N1-->_L1N4,_L3N1.",
/*  238 */	"_L3N1-->_L3N1,_L1N4.",
/*  239 */	"_L3N1-->_L3N4,_L1N4.",
/*  240 */	"_L3N2-->_L1N9,_L1N4.",
/*  241 */	"_L3N3-->ADV,_L3N3.",
/*  242 */	"_L3N3-->BE,_L1N21.",
/*  243 */	"_L3N3-->VT,_L1N1.",
/*  244 */	"_L3N3-->VT,_L1N21.",
/*  245 */	"_L3N3-->VT,_L1N8.",
/*  246 */	"_L3N3-->VT,_L3N1.",
/*  247 */	"_L3N3-->_L1N13,_L1N4.",
/*  248 */	"_L3N3-->_L1N13,_L1N8.",
/*  249 */	"_L3N3-->_L1N15,_L1N1.",
/*  250 */	"_L3N3-->_L1N15,_L1N4.",
/*  251 */	"_L3N3-->_L1N3,_L1N21.",
/*  252 */	"_L3N3-->_L1N3,_L1N8.",
/*  253 */	"_L3N3-->_L1N4,_L1N8.",
/*  254 */	"_L3N3-->_L1N8,CONJ,_L1N8.",
/*  255 */	"_L3N3-->_L1N8,PRON.",
/*  256 */	"_L3N3-->_L1N8,_L1N21.",
/*  257 */	"_L3N3-->_L1N8,_L1N8.",
/*  258 */	"_L3N3-->_L1N8,_L1N9.",
/*  259 */	"_L3N3-->_L1N8,_L3N1.",
/*  260 */	"_L3N3-->_L2N4,_L1N4.",
/*  261 */	"_L3N3-->_L3N3,_L1N4.",
/*  262 */	"_L3N4-->_L1N16,_L1N1.",
/*  263 */	"_L3N4-->_L1N16,_L1N2.",
/*  264 */	"_L3N5-->_L1N8,VT.",
/*  265 */	"_L3N6-->_L1N8,_L1N7.",
/*  266 */	"_L3N7-->NOUN,_L1N21.",
/*  267 */	"_L3N8-->_L1N2,VT.",
/*  268 */	"_L3N9-->PRON,_L1N13.",
/*  269 */	"_L4N1-->ART,_L1N21.",
/*  270 */	"_L4N2-->PTCL,_L3N3.",
/*  271 */	"_L4N3-->PRON,_L1N1.",
/*  272 */	"_L4N4-->_L2N4,_L1N1.",
		""
};