#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <opInter.h>

typedef struct line cmdline;

int len;

void input()
{
    FILE *f;
    int i=0;
    char c,*text=NULL;
    size_t length = 0;
    len=0;

    printf("\t\t\t\t\tEnter you program in Source file and save.\n");
_insert:
    system("IF EXIST source.txt (notepad source.txt) ELSE (echo Error:source.txt missing.)");
    f=fopen("source.txt","r");
    if(fgetc(f)==EOF)
    {
        printf("\t\t\t\t\tSource file is empty!\n\t\t\t\t\tpress '1' to Try again or press any key to return to menu..\b\b");
        if(getch()=='1')
            {goto _insert;}
        else{opSelect();}
        rewind(f);
    }
    else
    {
        while(getline(&text, &length, f) != -1)
        {
            len++;
        }
    }
    rewind(f);
    /***MEMORY_ALLOC***/
    line=(cmdline*)malloc(len*sizeof(cmdline));
    Reg=(struct regis*)malloc(sizeof(struct regis));
    flag=(struct Flag*)malloc(sizeof(struct Flag));

    while(getline(&text, &length, f) != -1)
    {
        strncpy(line[i].data,"\0",5);
        strncpy(line[i].op,"\0",2);
        sscanf(text,"%[^','],%[^','],%s",line[i].addr,line[i].op,line[i].data);
        i++;
    }

    /**** For testing purpose
    i=0;
    printf("\t\t\t\t\tENTERED PROGRAM\n\t\t\t\t\tADDRESS\tOPCODE\tDATA\n");
    while(i!=len)
    {
    printf("\t\t\t\t\t%s\t%s\t%s\n",line[i].addr,line[i].op,line[i].data);
    i++;
    }
    *****/

    fclose(f);
    opcSel();
    reset();
    getch();

}
/*********************Reset function to free memory*****************/
void reset()
{
    free(line);
    free(Reg);
    free(flag);
    sleep(4000);
    len=0;
}
/*************************Print input program table***********************/
void printProg()
{
    int i=0;
    printf("\n\t\t\t\t\tADDRESS\tOPCODE\tDATA\n");
    while(i!=len)
    {
        printf("\t\t\t\t\t%s\t%s\t%s\n",line[i].addr,line[i].op,line[i].data);
        i++;
    }
}
/***************search opcode and execute command*************************/
void opcSel()
{
    int i=0;
    printProg();
    i=0;

    printf("\t\t\t\t\t_________________program_________________\n");

    while(i<len)
    {
        if(strcmp(line[i].op,"21")==0)
        {
            printf("\t\t\t\t\tLXI H,%s\n",line[i].data);

            strcpy(Reg->PC,line[i].data);

            LXI(search(i));
        }
        else if(strcmp(line[i].op,"7E")==0)
        {
            printf("\t\t\t\t\tMOV A,M\n");
            MOV(0);
        }
        else if(strcmp(line[i].op,"72")==0)
        {
            printf("\t\t\t\t\tMOV M,A\n");
            MOV(1);
        }
        else if(strcmp(line[i].op,"3E")==0)
        {
            printf("\t\t\t\t\tMVI A,%s\n",line[i].data);
            MVI(0,i);
        }
        else if(strcmp(line[i].op,"2E")==0)
        {
            printf("\t\t\t\t\tMVI L,%s\n",line[i].data);
            MVI(1,i);
        }
        else if(strcmp(line[i].op,"85")==0)
        {
            printf("\t\t\t\t\tADD L\n");
            ADD();
        }
        else if(strcmp(line[i].op,"32")==0)
        {
            printf("\t\t\t\t\tSTA %s\n",line[i].data);
            STA(search(i));
        }
        else if(strcmp(line[i].op,"23")==0)
        {
            printf("\t\t\t\t\tINX H\n");
            INX();
        }
        else if(strcmp(line[i].op,"90")==0)
        {
            printf("\t\t\t\t\tSUB B\n");
            SUB();
        }
        else if(strcmp(line[i].op,"46")==0)
        {
            printf("\t\t\t\t\tMOV B,M\n");
            MOV(2);
        }
        else if(strcmp(line[i].op,"76")==0)
        {
            printf("\t\t\t\t\tHLT\n");
            HLT();
        }
        else                                //handle opcode selection errors
        {
            if(strcmp(line[i].op,"\0")==0)
            {
                printf("\t\t\t\t\tLine:%d  ERROR:-Address(%s) have no opcode\n",i+1,line[i].op);
            }
            printf("\t\t\t\t\tLine:%d  ERROR:-Invalid opcode:%s\n",i+1,line[i].op);
        }

        i++;
    }

}
/**************search index of address********************/
int search(int i)
{
    int j,err=0;

    for(j=0; j<len; j++)
    {
        if(strcmp(line[i].data,line[j].addr)==0)
        {
            err=0;
            break;
        }
        else
        {
            err=1;
        }
    }
    if(err)                                //handle error
    {
        printf("\t\t\t\t\tLine:%d  ERROR:-Invalid Address:%s\n",j,line[i].addr);
        printf("\n\t\t\t\tPress any key to return to menu...");
        reset();
        getch();
        opSelect();
    }
    else
    {
        return j;
    }
}

/*****************HEX to Dec***********************/
int ToDec(char HexVal[])
{
    int i=0,Res=0;
    while(HexVal[i])
    {
        if((HexVal[i]>=48)&&(HexVal[i]<=57))
            Res=(Res*16)+(HexVal[i]-48);
        else if((HexVal[i]>=65)&&(HexVal[i]<=70))
            Res=(Res*16)+(HexVal[i]-55);
        else return -1;
        i++;
    }
    return Res;
}
/*********************Dec to Hex***********************/
void ToHex(int N,char T[])
{
    int Temp1,i=0;
    while(N)
    {
        Temp1=N%16;
        if(Temp1<=9)
        {
            T[i]=Temp1+48;
            i++;
        }
        else
        {
            T[i]=Temp1+55;
            i++;
        }
        N/=16;
    }
    T[i]='\0';
    strrev(T);

}
/*******PC program counter*******/
int PC()
{
    int j=0,err=0;

    for(j=0; j<len; j++)
    {
        if(strcmp(Reg->PC,line[j].addr)==0)
        {
            err=0;
            break;
        }
        else
        {
            err=1;
        }
    }

    if(err)
    {
        printf("\t\t\t\t\tLine:%d  ERROR:-Invalid Address:%s\n",j,line[j].addr);
        printf("\n\t\t\t\t\tPress any key to return to menu...");
        reset();
        getch();
        opSelect();
    }
    return j;
}
/*********Counts no of digits in integer************/
int digCnt(int x)
{
    x = abs(x);
    return (x < 10 ? 1 :
            (x < 100 ? 2 :
             (x < 1000 ? 3 :
              (x < 10000 ? 4 :
               (x < 100000 ? 5 :
                (x < 1000000 ? 6 :
                 (x < 10000000 ? 7 :
                  (x < 100000000 ? 8 :
                   (x < 1000000000 ? 9 :
                    10)))))))));
}


