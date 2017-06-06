#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <instructions.h>
#include <opInter.h>
/**************************************INSTRUCTIONS**********************************/
//LXI
void LXI(int j)
{
    strcpy(Reg->H,line[j].data);
    //printf("\t\t\t\t\tH->%s\n",Reg->H);
}
//MOV
void MOV(int c)
{
    if(!c)
    {
        strcpy(Reg->A,Reg->H);
        //printf("\t\t\t\t\tA->%s\n",Reg->A);
    }
    else if(c==1)
    {
        strcpy(Reg->H,Reg->A);
        strcpy(line[PC()].data,Reg->A);
        //printf("\t\t\t\t\tH->%s\n",Reg->H);
    }
    else
    {
        strcpy(Reg->B,Reg->H);
        //printf("\t\t\t\t\tB->%s\n",Reg->B);
    }
}
//MVI
void MVI(int c,int i)
{
    if(strcmp(line[i].data,"\0")!=0)
    {
        if(!c)
        {
            strcpy(Reg->A,line[i].data);
//printf("\t\t\t\t\tA->%s\n",Reg->A);
        }
        else
        {
            strcpy(Reg->L,line[i].data);
//printf("\t\t\t\t\tL->%s\n",Reg->L);
        }
    }
    else
    {
        printf("\t\t\t\t\tLine:%d  ERROR:-MVI:8bit data not found!\n",i);
        printf("\n\t\t\t\tPress any key to return to menu...");
        getch();
        opSelect();
    }
}
//STA
void STA(int j)
{
    strcpy(line[j].data,Reg->A);

//printf("\t\t\t\t\tSTA:%s->%s\n",line[j].addr,line[j].data);
}
//ADD 8-bit no without carry
void ADD()
{
    flag->CY=0;
    char *str;
    if(digCnt(ToDec(Reg->A)+ToDec(Reg->L))>2)
    {
        flag->CY=1;
        ToHex(ToDec(Reg->A)+ToDec(Reg->L),Reg->A);
        Reg->A[0]='0';
        Reg->A[1]='0';
    }
    else
    {
        ToHex(ToDec(Reg->A)+ToDec(Reg->L),Reg->A);
    }
//printf("\t\t\t\t\tAfter Add:%s\n",Reg->A);
    free(str);
}
//SUB 8-bit no without borrow
void SUB()
{
    flag->CY=0;
    if((ToDec(Reg->A)-ToDec(Reg->B))<0)
    {
        flag->CY=1;

        strcpy(Reg->A,"0");
        //printf("\t\t\t\t\tSUB:A->%s\n",Reg->A);
    }
    else
    {
        ToHex(ToDec(Reg->A)-ToDec(Reg->B),Reg->A);
        //printf("\t\t\t\t\tSUB:A->%s\n",Reg->A);
    }
//strpad(Reg->A);

}
//INX H
void INX()
{
    ToHex((ToDec(Reg->PC)+1),Reg->PC);
    strcpy(Reg->H,line[PC()].data);
// printf("\t\t\t\t\tH->%s\n",Reg->H);


}
//HLT
void HLT()
{
    printf("\t\t\t\t\tExecuted!\n\n\t\t\t\t\tpress any key to continue...");
    getch();
    strForm();
    reset();
}

