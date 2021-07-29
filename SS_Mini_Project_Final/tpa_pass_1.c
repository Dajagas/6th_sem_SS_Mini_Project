#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/* The printf("hello there") statements are for debugging,don't focus on them,we'll remove them in the final version */
//pass 1 complete,need to add pass 2
int main()
{
    FILE *inpt,*optable,*symboltable,*total_length,*nice_input;
    int locctr,start,operand,opcode,len;
    char directives[20],label[20],op[20],opname[20];

    //program code in input file
    inpt = fopen("input.txt","r");
    //file to keep track of symbols in the source code
    symboltable = fopen("symboltab.txt","w");
    //file to store with location
    nice_input = fopen("nice_input.txt","w");
    //checking for start of program
    fscanf(inpt,"%s %s %d",label,directives,&operand);
    if(strcmp(directives,"START") == 0)
    {   
        //starting location of program is the first operand encountered
        start = operand;
        //location pointer,points towards starting location
        locctr = start;
        fprintf(nice_input,"-\t%s\t%s\t%d\n",label,directives,operand);
    }
    else
    {
        //location assumed to start at location 0 
        locctr = 0;
    }
    fscanf(inpt,"%s %s",label,directives);
    //printf("hello there outside \n");
    while(!feof(inpt))
    {
        //printf("hello there inside \n");
        fscanf(inpt,"%s",op);
        //printing the input code with current location
        fprintf(nice_input,"\n%d\t%s\t%s\t%s\n",locctr,label,directives,op);
        
        //inputting detected symbols into the code
        if(strcmp(label,"-")!=0)
        {
            fprintf(symboltable,"\n%d\t%s\n",locctr,label);
            //fprintf(symboltable,"\n%s\t%d\n",label,locctr);
        }
        //file to open opcode table
        optable = fopen("optab.txt","r");
        //read opcode from optable
        fscanf(optable,"%s %d",opname,&opcode);
        //printf("hello there");
        while(!feof(optable))
        {
            if(strcmp(directives,opname) == 0)
            {
                //printf("hello there");
                //location updated by 3 bytes due to size of instruction
                locctr += 3;
                break;
            }
            fscanf(optable,"%s %d",opname,&opcode);
        }
        fclose(optable);

        if(strcmp(directives,"WORD") == 0)
        {
            //one word = 3 bytes,hence location + 3  
            locctr += 3;
        }

        else if(strcmp(directives,"RESW") == 0)
        {
            operand = atoi(op);
            locctr += 3*operand;
        }

        else if(strcmp(directives,"BYTE") == 0)
        {
            if(op[0] == 'X')
            {
                locctr += 1;
            }
            else
            {
                len = strlen(op);
                locctr += len;
            }
        }

        else if(strcmp(directives,"RESB") == 0)
        {
            operand = atoi(op);
            locctr += operand;
        }
        
        fscanf(inpt, "%s %s",label,directives);
    }
    if(strcmp(directives,"END") == 0)
    {
        printf("Total program length = %d\n",(locctr-start));
    }
    //file to keep track of program length,due to two different programs
    total_length =  fopen("length.txt","w");
    fprintf(total_length,"%d",(locctr-start));
    //closing all files
    fclose(inpt);
    fclose(symboltable);
    fclose(total_length);
}




