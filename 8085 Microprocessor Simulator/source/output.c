#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "output.h"
#include "opInter.h"
void strForm()
{
    char s[5];
    int j,err=0;
out:
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t__________________OUTPUT___________________\n\n\t\t\t\t\tEnter Address:");
    scanf("%s",s);
    for(j=0; j<len; j++)
    {
        if(strcmp(s,line[j].addr)==0)
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
        printf("\t\t\t\t\tERROR:-Invalid Address:%s\n",s);
        goto xout;
    }
    printf("\n\t\t\t\t\tAddress\tdata\n\t\t\t\t\t%s\t%04s\n",line[j].addr,line[j].data);
xout:
    printf("\n\t\t\t\t\tPress q to return to menu or any other key to continue..");
    if(getch()=='q' ||getch()=='Q')
    {
//reset();
        opSelect();
    }
    else
    {
        goto out;
    }
}

