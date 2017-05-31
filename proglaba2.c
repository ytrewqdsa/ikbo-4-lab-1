#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INC 1
#define DEC 2
#define MOVL 3
#define MOVR 4
#define PRINT 5
#define GET 6
#define PRINTC 7
#define BEGIN 8
#define END 9

typedef struct node
{
    unsigned char sym;
    struct node *next;
    struct node *prev;
} node;

typedef struct linel
{
    struct node *head;
    struct node *tail;
    int length;
} linel;

void pushback(linel *list, unsigned char c)
{
    node *temp = (node*)malloc(sizeof(node));
    if (temp==0) exit(1);
    temp->sym=c;
    temp->next = 0;
    temp->prev = list->tail;
    if (list->tail)
        list->tail->next = temp;

    list->tail = temp;

    if (list->head == 0)
        list->head = temp;
    ++list->length;
}

void pushfront(linel *list, unsigned char c)
{
    node *temp = (node*)malloc(sizeof(node));
    if (temp==0) exit(1);
    temp->sym=c;
    temp->next = list->head;
    temp->prev = 0;
    if (list->head)
        list->head->prev = temp;

    list->head = temp;

    if (list->tail == 0)
        list->tail = temp;
    ++list->length;
}

unsigned char popfront(linel *list)
{
    unsigned char c;
    node *prev;
    if (list->head == 0)
        return 0;
    prev = list->head;
    list->head = list->head->next;
    if (list->head)
    {
        list->head->prev = 0;
    }
    if (prev == list->tail)
    {
        list->tail = 0;
    }
    c=prev->sym;
    free(prev);
    --list->length;
    return c;
}

unsigned char popback(linel *list)
{
    unsigned char c;
    node *next;
    if (list->tail==0)
        return 0;
    next=list->tail;
    list->tail=list->tail->prev;
    if (list->tail)
        list->tail->next=0;
    if (next==list->head)
        list->head=0;
    c=next->sym;
    free(next);
    --list->length;
    return c;
}

node* getptr(linel* mlist,node *list, int dir)
{
    if (dir==MOVR)
    {
        if (list->next==0)
        {
            pushback(mlist,0);
        }
        return (list->next);
    }
    else if (dir==MOVL)
    {
        if (list->prev==0)
            pushfront(mlist,0);
        return (list->prev);
    }
    return 0;
}

linel * createlinel()
{
    linel *temp=(linel*)malloc(sizeof(linel));
    temp->length=0;
    temp->head=temp->tail=0;
    return temp;
}

void deletelinel(linel **list)
{
    if (!(*list)) return;
    node *temp = (*list)->head;
    node *next = 0;
    while (temp)
    {
        next=temp->next;
        free(temp);
        temp=next;
    }
    free(*list);
    (*list)=0;
}
char *getcommands(FILE *f)
{
    char c, *commands=0,temp[256];
    int i,j,flag=0,len=0;
    linel *templist=0;
    templist=createlinel();

    while ((c=fgetc(f))!=EOF)
    {
        if (c=='\n')
        {
            if (flag==2)
                ++len;
            flag=0;
            continue;
        }
        if (c=='*') flag=1;
        if (flag==1) continue;
        if ((!(c==' '))&&(!(c=='\t'))) flag = 2;
    }

    fseek(f,ftell(f)-2,SEEK_SET);
    c=fgetc(f);
    if ((c=='\n')&&(fgetc(f)==EOF));
    else ++len;
    commands=(char*)malloc((len+1)*sizeof(char));
    commands[len]=0;
    fseek(f,SEEK_SET,0);
    flag=0;
    i=0;

    while ((c=fgetc(f))!=EOF)
    {
        if (c=='\n')
        {
            if (flag==2)
            {
                for (j=0; templist->length; ++j)
                {
                    temp[j]=popfront(templist);
                }
                temp[j]='\0';
                if (!strcmp("inc",temp)) commands[i]=INC;
                if (!strcmp("dec",temp)) commands[i]=DEC;
                if (!strcmp("movl",temp)) commands[i]=MOVL;
                if (!strcmp("movr",temp)) commands[i]=MOVR;
                if (!strcmp("get",temp)) commands[i]=GET;
                if (!strcmp("print",temp)) commands[i]=PRINT;
                if (!strcmp("printc",temp)) commands[i]=PRINTC;
                if (!strcmp("begin",temp)) commands[i]=BEGIN;
                if (!strcmp("end",temp)) commands[i]=END;
                ++i;
            }
            flag=0;
            continue;
        }
        if (c=='*') flag=1;
        if (flag==1) continue;
        if ((c==' ')||(c=='\t')) continue;
        else flag=2;
        pushback(templist,c);
    }
    return commands;
}

int main()
{
    int flag=5;
    FILE *f;
    char *commands=0, *c,*filename;
    node *ptr=0;
    linel *line=0;
    filename=(char*)malloc(500*sizeof(char));
    printf("Enter file name.\n");
    fgets(filename,500*sizeof(char),stdin);
    c=filename;
    while ((*(c))!='\n') ++c;
    *c='\0';
    system("CLS");
    while ((f = fopen(filename,"r"))==0)
    {
        printf("Enter correct file name!\n");
        fgets(filename,500*sizeof(char),stdin);
        c=filename;
        while ((*(c))!='\n') ++c;
        *c='\0';
        system("CLS");
    }

    line=createlinel();
    commands=getcommands(f);
    pushback(line,0);
    c=commands;
    ptr=line->head;

    while(flag)
    {
        switch (*c)
        {
        case INC:
        {
            if (ptr->sym<255)
                ++ptr->sym;
            else
            {
                printf("%s","Overflow!\n");
                ptr->sym=0;
            }
            ++c;
            break;
        }
        case DEC:
        {
            if (ptr->sym>0)
                --ptr->sym;
            else
            {
                printf("%s","Overflow2!\n");
                ptr->sym=255;
            }
            ++c;
            break;
        }
        case MOVL:
        {
            getptr(line,ptr,MOVL);
            ++c;
            break;
        }
        case MOVR:
        {
            getptr(line,ptr,MOVR);
            ++c;
            break;
        }
        case PRINT:
        {
            printf("%d",(int)ptr->sym);
            ++c;
            break;
        }
        case GET:
        {
            printf("Enter symbol:\n");
            ptr->sym=getchar();
            fflush(stdin);
            ++c;
            break;
        }
        case PRINTC:
        {
            printf("%c",ptr->sym);
            ++c;
            break;
        }
        case BEGIN:
        {
            if (ptr->sym==0)
                while ((*c)!=END)
                    ++c;
            ++c;
            break;
        }
        case END:
        {
            if (ptr->sym!=0)
                while((*c)!=BEGIN)
                    --c;
            else
                ++c;
            break;
        }
        case 0:
        {
            free(commands);
            deletelinel(&line);
            ptr=0;
            c=0;
            flag=0;
            break;
        }
        }
    }
    printf("\n");
    return 0;
}


