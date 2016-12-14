# Chart-parser
<b>MacOS usage: </b>

<b>Copy malloc header to local</b>

	$ cp /usr/include/malloc/malloc.h /usr/local/include/malloc.h


/*********************
 =		     =
 =	README	     =
 =		     =
 *********************/

This directory composed of a set of basic programs of chart parsing.
You can use these programs as you like, but without any guarantee if
any inconvenience is occurred by these programs.

--
Explanation:

 * To compile this directory, type

   % make		             # for three versions: chart,chartill,chartpure <br>
   % make chart          # for chart     version <br>
   % make chartill       # for chartill  version <br>
   % make chartpure      # for chartpure version <br>
   % make chart-th		   # for chart Thai supported version <br>
   % make chartill-th	   # for chartill Thai supported version <br>

 * There are 3+2 versions of chart parsing algorithms in this
   directory: chart, chartill, chartpure, chart-th, chartill-th

   <b>- chart version:</b>
	      This program parses a sentence under a grammar given in
        'gram/gram'. There is two transverse tables to convert between
        EDR version's categories and PENNTREE version's categories.
        The tables are denoted in 'src/trancat.c' and 'src/trancat.h'.

   <b>- chartill  version:</b>
        This program is an extension of chart version to parse
        ill-formed inputs under the algorithm given in [1]-[3]. 

   <b>- chartpure version:</b>
        This program is a pure chart parsing algorithm. There is no
        convert table anymore. It seems to be the most general version
        which you can use for parsing a sentence under a grammar.

   <b>- chart-th version:</b>
	      This program parses a sentence under a grammar given in
        'gram/gram.th'.
        The tables are denoted in 'src/trancat-th.c' and 'src/trancat-th.h'.

   <b>- chartill-th version:</b>
        This program is an extension of chart-th version to parse

 * How to change a grammar and What is the form of input sentences ?

   == Chart and Chartill version ==

   <b>[Grammar]</b>
     You can change a grammar for parsing by replacing a grammar file
     located at 'gram/gram' with the one you want for chart and chartill
     version.

   <b>[Thai Grammar]</b>
     You can change a grammar for parsing by replacing a grammar file
     located at 'gram/gram.th' with the one you want for chart and chartill
     version OR Makefile.


   <b>[Input sentences]</b>
     In chart and chartill version, the sentence has to be in the form
     of 'word/category'. Be noted that, at the end of the sentences need to have 1 white space. 
     The following is an example:

"the/DT Secretariat/NNP for/IN the/DT first/JJ international/JJ conference/NN of/IN interpreting/VBG telephony/NN "
"ประเทศไทย/NNP ได้/MD มี/VB การปรับเปลี่ยนโครงสร้าง/NN ใน/IN การพัฒนาเศรษฐกิจ/NN ของ/IN ประเทศ/NN "


   == Chartpure version ==

   <b>[Grammar]</b>
     For chartpure version, you have to replace a grammar file named
     'gram/grampure' with the suitable one.

   <b>[Input sentences]</b>
     The sentence you want to parse should be in the form of 'a sequence
     of lexical tags' for chartpure version. An example is shown below.

     DT NNP IN DT JJ JJ NN IN VBG NN

 * How to run the program ?

   Ex.)

   % ./chart [outputfile DIR] < demo_example/ex_sentences

   % ./chartill 1 1 1 1 < demo_example/ex_sentences

   % ./chartpure 1 < demo_example/ex_sentences1

   % ./chart-th [outputfile DIR] < demo_example/ex_sentences

   % ./chartill 1 1 1 1 < demo_example/ex_sentences

   Note:  [outputfile DIR] in chart could be blank for displaying in STDOUT <br>
   		  ./chartill [outputfile DIR] [no.err] [wlimit] [info]

[Reference]

[1]-[3] are available in the Internet. The URL is 

            http://www.jaist.ac.jp/~ping/paper/paper.html

[1] A Parallel Chart-based Parser for Analysing Ill-formed Inputs,
    Journal of Japanese Society for Artificial Intelligence, 
    Vol.10, No.4, pp. 531-541, 1995

[2] Analysing Ill-formed Input with Parallel Chart-based Techniques
    The Sixth Annual conference of JSAI on Artificial Intelligent,
    pp. 543-546, 1994

[3] Analysing Ill-formed Input with Parallel Chart-based Techniques
    Proceedings of the International Conference in Commemoration of 
    20th KISS Anniversary (InfoScience'93), pp. 543-550, 1993


--
Copyright @ Thanaruk Theeramunkong
ping@jaist.ac.jp
1995-1996
Japan Advance Institute of Science and Technology (JAIST)
Graduate School of Information Science

