#include <stdio.h>
#include <ctype.h>
#include <sys/param.h>

main()
{
    char name[20];
    int namelen=20,i,j;

    i = gethostname(name,namelen);
    printf("Hostname is %d : %s\n",i,name);
}
