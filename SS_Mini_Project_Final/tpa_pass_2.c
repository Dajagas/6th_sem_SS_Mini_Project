#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
int main()
{
    FILE *input_prog, *optable, *prog_length, *symbol_table;
    int i, length;
    char loc[5], symbol_address[5], symbol[10], opname[10], opcode[5], start[10],label[20], directives[10], operand[10];
    input_prog = fopen("nice_input.txt", "r");
    prog_length = fopen("length.txt", "r");
    optable = fopen("optab.txt", "r");
    symbol_table = fopen("symboltab.txt", "r");
    fscanf(input_prog, "%s%s%s%s", loc, label, directives, operand);
    if (strcmp(directives, "START") == 0)
    {
        strcpy(start, operand);
        fscanf(prog_length, "%d", &length);
    }
    printf("length: %d\n",length);
    printf("OBJECT PROGRAM\n");
    printf("H^%s  ^00%s^0000%d\nT^00%s^", label, start, length, start);
    fscanf(input_prog, "%s%s%s%s", loc, label, directives, operand);
    while (strcmp(directives, "END") != 0)
    {
        fscanf(optable, "%s%s", opname, opcode);
        while (!feof(optable))
        {
            if (strcmp(directives, opname) == 0)
            {
                fclose(optable);
                fscanf(symbol_table, "%s%s", symbol_address, symbol);
                while (!feof(symbol_table))
                {
                    if (strcmp(operand, symbol) == 0)
                    {
                        printf("%s%s^", opcode, symbol_address);
                        break;
                    }
                    else
                        fscanf(symbol_table, "%s%s", symbol_address, symbol);
                }
                break;
            }
            else
                fscanf(optable, "%s%s", opname, opcode);
        }
        if ((strcmp(directives, "BYTE") == 0) || (strcmp(directives, "WORD") == 0))
        {
            if (strcmp(directives, "WORD") == 0)
                printf("0000%s^", operand);
            else
            {
                //find length of string in the byte section
                length = strlen(operand);
                for (i = 2; i < length; i++)
                {
                    //convert to their ASCII codes
                    printf("%d", operand[i]);
                }
                printf("^");
            }
        }
        fscanf(input_prog, "%s%s%s%s", loc, label, directives, operand);
        optable = fopen("optab.txt", "r");
        //returning to start of optable
        fseek(optable, 0,SEEK_SET);
    }
    printf("\nE^00%s", start);
    fclose(input_prog);
    fclose(optable);
    fclose(symbol_table);
    fclose(prog_length);
    getch();
}