#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <opSelect.h>

void opSelect()
{
    char uchoice;

menu:
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t__________________MENU___________________\n\n\t\t\t\t\t1.User Guide\n\t\t\t\t\t2.Simulate\n\t\t\t\t\t3.Exit\n\t\t\t\t\t_________________________________________\n");
    printf("\t\t\t\t\tEnter Choice:");
    scanf("%c",&uchoice);
    switch(uchoice)
    {
    case '1':
        openExt(); //userGuide-Instructions
        break;
    case '2':
        input();   //File-input
        break;
    case '3':
        exit_();  //exit
        break;
    default:
        printf("\t\t\t\t\tInvalid Choice!\n\t\t\t\t\t");
    }
    goto menu;
}
