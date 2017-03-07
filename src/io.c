/*
 *  $ JAIST: io.c,v 0.1000 1995/10/04 20:04:01 $
 *
 *  @(#)io.c  04/10/1995  By Thanaruk Theeramunkong
 */

#include <stdio.h>
#include <ctype.h>

/* Open Read File Procedure */
int open_file_read(file,fp)
char *file;
FILE **fp;
{
 	if(NULL == (*fp = fopen(file,"r"))){
   		return(0);
  	}
 	return(1);
}

int open_file_write(file,fp)
char *file;
FILE **fp;
{
 	if(NULL == (*fp = fopen(file,"a"))){
   		return(0);
 	}
 	return(1);
}


int clear_file_write(file,fp)
char* file;
FILE** fp;
{
	if(NULL == (*fp = fopen(file,"w"))){
   		return(0);
 	}
 	return(1);
}

