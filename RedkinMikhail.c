#include <stdlib.h>
#include <stdio.h>

typedef struct Packet
{
int num;
char str[255];
float fnum;
} Pack;

int main(int argc, char *argv[])
{
    FILE *f;
    Pack temp;
    if (argc>1)
        { if ((f = fopen(argv[1],"rb"))==0) { printf("Enter correct file name\n"); return 1; } }
    else {printf("Enter file name\n"); return 2;}

    while ((fread(&temp,sizeof(Pack),1,f)!=0))
        printf("%d\t%s\t%f\n",temp.num,temp.str,temp.fnum);
    return 0;
}
