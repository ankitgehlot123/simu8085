#ifndef OPINTER_H_INCLUDED
#define OPINTER_H_INCLUDED
/**one_line_command_storage**/
struct line{
    char addr[5];
    char  op[3];
    char data[5];
} *line;
/**register**/
struct regis{
    char A[4],
         B[4],C[4],
         D[4],E[4],
         H[4],L[4],
         PC[4];
} *Reg;
/**Flag**/
struct Flag {
    int CY;    // CARRY FLAG
    int Z;     // ZERO FLAG
    int S;     // SIGN FLAG

}*flag;
typedef struct line cmdline;

int len;
/*********************FILE_INPUT****************************/
void input();
/*********************RESET_FUNCTION_TO_FREE_MEMORY**********************/
void reset();
/*********************PRINT_INPUT_PROGRAM_TABLE**************************/
void printProg();
/*********************SEARCH_OPCODE_AND_EXECUTE_COMMAND******************/
void op();
/*********************SEARCH_INDEX_OF_ADDRESS****************************/
int search(int i);
/*********************DEC_TO_HEX*****************************************/
void ToHex(int N,char T[]);
/*********************COUNTS_NO_OF_DIGITS_IN_INTEGERS********************/
int NumDigits(int x);


#endif // OPINTER_H_INCLUDED
