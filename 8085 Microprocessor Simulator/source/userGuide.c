#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "userGuide.h"

void openExt()
{
    char c;
extmenu:
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t__________________USER GUIDE___________________\n\n");
    printf("\t\t\t\t\t1.Instructions\n\t\t\t\t\t2.Exit\n");
    printf("\t\t\t\t\t_______________________________________________\n");
    printf("\t\t\t\t\tEnter choice:");
    scanf("%c",&c);
    if(c=='1')
    {
        system("IF EXIST instructions.txt (notepad instructions.txt) ELSE (echo Error:instructions.txt missing.)");
        goto extmenu;
    }
    else if(c == '2')
    {
        system("cls");
        opSelect();
    }
    else
    {
        goto extmenu;
    }
}
