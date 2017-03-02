#include <stdlib.h>
#include <stdio.h>

struct pack
{
int num;
char str[255];
float fnum;
};

int main(int argc, char *argv[])
{
    unsigned int size=0,s=sizeof(struct pack);
    FILE *f;
    struct pack temp;
    if (!(argc>1)||((f = fopen(argv[1],"rb"))==0))
    {
    printf("Enter correct file name\n");
    return 0;
    }

    while ((fread(&temp,s,1,f)>0))
    {
        ++size;
        printf("%d\t%s\t%f\n",temp.num,temp.str,temp.fnum);
    }
    size*=s;
    printf("Size of file: %u bytes\n",size);
    return 0;
}
