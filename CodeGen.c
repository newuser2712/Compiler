/* T1 Group Number 25,
2011B4A7664P SAI VARUN ADDANKI
2011B3A7604P AVINASH KUMAR SINGH
*/
#include "AST.h"
#include "SYM.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int tally=0;
int tally2=0;
int check_String(char *s)
{
    int i;
    for(i=0;i<setstringpoint;i++)
    {
       // printf("Checking with %s\n",stringIDs[i]);
        if(strcmp(stringIDs[i],s)==0)
            return i;
    }
    return -1;
}
int check_Array(char *s)
{
    int i;
    for(i=0;i<arraynamesPoint;i++)
    {
       // printf("Checking with %s\n",stringIDs[i]);
        if(strcmp(arraynames[i],s)==0)
            return i;
    }
    return -1;
}

void write_code(tree *root)
{
         //           printf("Entered\n");

int i=0,j,k;
    for(i=0;i<100;++i)
    {

        if(root->nod[i]!=NULL && root->nod[i]->term>=0)
        {
           // printf("%d\n",root->nod[i]->term);

            if(root->nod[i]->term==49)
            {
  //              printf("Entered scan\n");
                fprintf(fout,"mov eax, 3\n");
                fprintf(fout,"mov ebx, 2\n");
                fprintf(fout,"mov ecx, %s\n",idenVals[(root->nod[i]->nod[2]->term)-300]);
                fprintf(fout,"mov edx, 5\n");
                fprintf(fout,"int 80h\n");
                fprintf(fout,"mov eax,48\n");
                fprintf(fout,"sub [%s],eax\n",idenVals[(root->nod[i]->nod[2]->term)-300]);
            }
             else if(root->nod[i]->term==50)
            {
                printf("Entered print\n");
                if(root->nod[i]->nod[2]!=NULL)
                {
                    printf("Is NULL: %d\n",(root->nod[i]->nod[2]->term));
                }
                  if(check_String(idenVals[(root->nod[i]->nod[2]->term)-300])==-1)
                {
                    //printf("Check call is -1 for %s\n",idenVals[(root->nod[i]->nod[2]->term)-300]);
                    fprintf(fout,"mov eax, 48\n");
                    fprintf(fout,"add [%s], eax\n",idenVals[(root->nod[i]->nod[2]->term)-300]);
                    fprintf(fout,"mov eax, 4\n");
                    fprintf(fout,"mov ebx, 1\n");
                    fprintf(fout,"mov ecx, %s\n",idenVals[(root->nod[i]->nod[2]->term)-300]);
                    fprintf(fout,"mov edx, 5\n");
                    fprintf(fout,"int 80h\n");
                    fprintf(fout,"mov eax, 48\n");
                    fprintf(fout,"sub [%s], eax\n",idenVals[(root->nod[i]->nod[2]->term)-300]);

                }
                else
                {
                   // printf("Check call is 1 for %s\n",idenVals[(root->nod[i]->nod[2]->term)-300]);
                    fprintf(fout,"mov eax, 4\n");
                    fprintf(fout,"mov ebx, 1\n");
                    fprintf(fout,"mov ecx, %s\n",idenVals[(root->nod[i]->nod[2]->term)-300]);
                    fprintf(fout,"mov edx, len%d\n",check_String(idenVals[(root->nod[i]->nod[2]->term)-300]));
                    fprintf(fout,"int 80h\n");
                }

            }
            else if(root->nod[i]->term==19)
            {

        //        printf("Entered Assign\n");
          //      printf("%d %d %d\n",root->nod[i]->term,root->nod[i]->nod[3]->term,root->nod[i]->nod[1]->term);
                if(root->nod[i]->nod[1]->term>=300 && root->nod[i]->nod[3]->term>=400)
                {
            //        printf("SAT");
                    fprintf(fout,"mov eax,%d\n",intrArray[root->nod[i]->nod[3]->term-400]);
                    fprintf(fout,"mov [%s], eax\n",idenVals[(root->nod[i]->nod[1]->term)-300]);
                }
                else if(root->nod[i]->nod[3]->term==133 && root->nod[i]->nod[1]->term==120)
                {
              //      printf("Entered 2nd assign\n");
                    j=0;
                    k=0;
                    while(j<=100)
                    {
                        if(root->nod[i]->nod[1]->nod[j]!=NULL)
                        {
                                if(j==1)
                                    k++;
                                    fprintf(fout,"mov eax,%d\n",intrArray[root->nod[i]->nod[3]->nod[1]->nod[k]->term-400]);
                                    fprintf(fout,"mov [%s],eax\n",idenVals[(root->nod[i]->nod[1]->nod[j]->term)-300]);
                        }
                        j++;
                        k++;
                    }

                }
                else if(root->nod[i]->nod[3]->term==131 && root->nod[i]->nod[1]->term==120)
                {
                    //printf("YES...........\n");
                    fprintf(fout,"mov eax,%d\n",intrArray[(root->nod[i]->nod[3]->nod[1]->nod[1]->nod[0]->term)-400]);
                    fprintf(fout,"mov ebx,%d\n",intrArray[(root->nod[i]->nod[3]->nod[1]->nod[1]->nod[1]->nod[1]->term)-400]);
                    fprintf(fout,"mov edx,%d\n",intrArray[root->nod[i]->nod[1]->nod[1]->nod[1]->nod[0]->term-400]);

                    fprintf(fout,"cmp eax,ebx\n");
                    fprintf(fout,"jge h1\n");

                    fprintf(fout,"mov [high],ebx\n");

                    fprintf(fout,"mov [low],eax\n");

                    fprintf(fout,"mov eax,[high]\n");
                    fprintf(fout,"mov ecx,[low]\n");

                    fprintf(fout,"less1:\n");

                    fprintf(fout,"mov ebx,[%s+(4*ecx)]\n",idenVals[root->nod[i]->nod[1]->nod[0]->term-300]);
                    fprintf(fout,"mov [%s+(4*edx)],ebx\n",idenVals[root->nod[i]->nod[3]->nod[0]->term-300]);
                    fprintf(fout,"inc ecx\n");
                    fprintf(fout,"inc edx\n");

                    fprintf(fout,"cmp ecx,eax\n");
                    fprintf(fout,"jl less1\n");
                    fprintf(fout,"jmp h2\n");

                    fprintf(fout,"h1:\n");
                    fprintf(fout,"mov [high],eax\n");
                    fprintf(fout,"mov [low],ebx\n");

                    fprintf(fout,"mov ecx,[high]\n");
                    fprintf(fout,"mov eax,[low]\n");

                    fprintf(fout,"less2:\n");

                    fprintf(fout,"mov ebx,[%s + (4*ecx)]\n",idenVals[root->nod[i]->nod[1]->nod[0]->term-300]);
                    fprintf(fout,"mov [%s+(4*edx)],ebx\n",idenVals[root->nod[i]->nod[3]->nod[0]->term-300]);
                    fprintf(fout,"dec ecx\n");
                    fprintf(fout,"inc edx\n");

                    fprintf(fout,"add ax,1\n");

                    fprintf(fout,"cmp eax,ecx\n");
                    fprintf(fout,"jl less2\n");

                    fprintf(fout,"h2:\n");

                }
                else if(root->nod[i]->nod[3]->term>=300 && root->nod[i]->nod[1]->term==120)
                {
                  //  printf("YES...........\n");
                    fprintf(fout,"mov ebx,[%s]\n",idenVals[root->nod[i]->nod[3]->term-300]);
                    fprintf(fout,"mov ecx,[%s]\n",idenVals[root->nod[i]->nod[1]->nod[1]->term-300]);
                    fprintf(fout,"mov [%s+4*ecx],ebx\n",idenVals[root->nod[i]->nod[1]->nod[0]->term-300]);

                }
                else if(root->nod[i]->nod[3]->term==131 && root->nod[i]->nod[1]->term>=300)
                {
                    if(root->nod[i]->nod[3]->nod[2]->nod[0]->term==42)
                    {
                        if(root->nod[i]->nod[3]->nod[2]->nod[1]->term>=300 && root->nod[i]->nod[3]->nod[2]->nod[1]->term<400)
                        fprintf(fout,"mov eax,[%s];%d\n",idenVals[root->nod[i]->nod[3]->nod[2]->nod[1]->term-300],root->nod[i]->nod[3]->nod[2]->nod[1]->term-300);
                        else if(root->nod[i]->nod[3]->nod[2]->nod[1]->term>=400)
                        fprintf(fout,"mov eax,%d\n",intrArray[root->nod[i]->nod[3]->nod[2]->nod[1]->term-400]);

                        fprintf(fout,"add [%s],eax\n",idenVals[root->nod[i]->nod[3]->nod[0]->term-300]);
                        fprintf(fout,"mov eax,[%s]\n",idenVals[root->nod[i]->nod[3]->nod[0]->term-300]);
                        fprintf(fout,"mov [%s], eax\n",idenVals[root->nod[i]->nod[1]->term-300]);
                    }

                    else if(root->nod[i]->nod[3]->nod[2]->nod[0]->term==35)
                    {
                      //  printf("YES\n");
                       fprintf(fout,"mov ecx,0\n");
                       fprintf(fout,"mov edx,0\n");
                       fprintf(fout,"b7:\n");
                       fprintf(fout,"mov al,[%s+(1*ecx)]\n",idenVals[root->nod[i]->nod[3]->nod[0]->term-300]);
                       fprintf(fout,"mov bl,[%s+(1*edx)]\n",idenVals[root->nod[i]->nod[3]->nod[2]->nod[1]->term-300]);


                       //fprintf(fout,"lea si,[%s]\n",idenVals[root->nod[i]->nod[3]->nod[0]->term-300]);
                       //fprintf(fout,"lea di,[%s]\n",idenVals[root->nod[i]->nod[3]->nod[2]->nod[1]->term-300]);
                       fprintf(fout,"inc ecx\n");
                       fprintf(fout,"inc edx\n");
                       fprintf(fout,"cmp bl, al\n");
                       fprintf(fout,"jg NotEqual\n");
                       fprintf(fout,"cmp al, 0\n");
                       fprintf(fout,"jne b7\n");
                       fprintf(fout,"mov eax,0\n");
                       fprintf(fout,"mov [%s], eax\n",idenVals[root->nod[i]->nod[1]->term-300]);

                       fprintf(fout,"jmp final\n");


                        fprintf(fout,"NotEqual:\n");

                        fprintf(fout,"mov eax,1\n");
                       fprintf(fout,"mov [%s], eax\n",idenVals[root->nod[i]->nod[1]->term-300]);



                        fprintf(fout,"final:\n");


                    }
                }
            }
            else if(root->nod[i]->term==24)
            {

                if(root->nod[i]->nod[2]->term==41)
                {
                   //  printf("YES\n");

                    fprintf(fout,"mov eax,%d\n",intrArray[root->nod[i]->nod[2]->nod[2]->term-400]);
                    fprintf(fout,"cmp [%s],eax\n",idenVals[root->nod[i]->nod[2]->nod[0]->term-300]);
                    fprintf(fout,"JNE L7\n");
                }
            }
            else if(root->nod[i]->term==28)
            {
                fprintf(fout,"L7:\t");
            }
            else if(root->nod[i]->term==130)
            {
                fprintf(fout,"mov ecx,%d\nL%d:\n",intrArray[root->nod[i]->nod[2]->nod[2]->term-400],root->nod[i]->nod[2]->nod[2]->term-400);
            }
            else if(root->nod[i]->term==31)
            {
                fprintf(fout,"mov ecx,%d\n",intrArray[root->nod[2]->nod[2]->term-400]);
                //printf("Endloop %d\n",root->term);
                fprintf(fout,"mov edx,[%s]\n",idenVals[root->nod[2]->nod[0]->term-300]);
                fprintf(fout,"cmp edx,ecx\n");
                if(root->nod[2]->term==40)
                    fprintf(fout,"JNE L%d\n",root->nod[2]->nod[2]->term-400);
                else if(root->nod[2]->term==36)
                    fprintf(fout,"JL L%d\n",root->nod[2]->nod[2]->term-400);
                 else if(root->nod[2]->term==38)
                    fprintf(fout,"JG L%d\n",root->nod[2]->nod[2]->term-400);
                else if(root->nod[2]->term==41)
                    fprintf(fout,"JE L%d\n",root->nod[2]->nod[2]->term-400);
            }

                write_code(root->nod[i]);
        }
    }
}

void ID_put(tree *root)
{
    int i=0;
    //printf("checking %d\n",root->term);
    for(i=0;i<100;++i)
    {
        if(root->nod[i]!=NULL && root->nod[i]->term>=0)
        {
      //      printf("checking Inside now %d\n",root->nod[i]->term);
            if(root->nod[i]->term==65)
            {
                root->nod[i]->term=300+tally++;
        //        printf("Taking 1 now %d\n",root->nod[i]->term);
            }
                ID_put(root->nod[i]);
        }

    }

}

void INTR_put(tree *root)
{
    int i=0;
   // printf("checking %d\n",root->term);
    for(i=0;i<100;++i)
    {
        if(root->nod[i]!=NULL && root->nod[i]->term>=0)
        {
     //       printf("checking Inside now %d\n",root->nod[i]->term);
            if(root->nod[i]->term==57)
            {
                root->nod[i]->term=400+tally2++;
       //         printf("Taking 1 now %d\n",root->nod[i]->term);
            }
                INTR_put(root->nod[i]);
        }

    }

}
int main()
{
main_Sym("Test_Case_13_Tokens.txt");

tree* root=NULL;

int count=get_tokens("Test_Case_13_Tokens.txt");
int i;

    for(i=0;i<count;i++)
        hashedTokens[i]=hash_tokens(Tokens[i]);

generate_table();
int j;
readRules();

fill_terms();
fout=fopen("Output.txt","w+");
//fout=fopen("AST.txt","w+");
root=initialize_node();
root=insert(root,100);
tree* temp=root;
tree* temp2=root;

tree* temp3=root;
tree* temp4=root;
tree* temp5=root;
tree* temp6=root;
tree* temp7=root;
tree* temp8=root;
tree* temp9=root;
tree* temp10=root;
tree* temp11=root;
dfs(root);

//print_tree(temp);
fclose(fout);
//fout=fopen("AST13.txt","w+");

//AST(temp,0);
prune_All(temp2);

i=0;

post_pruning(temp4);

ID_pruned(temp5);

prune_more(temp6);
print_tree(temp);
final_pruning(temp7);
//fclose(fout);

fout=fopen("BST13.txt","w+");

print_tree(temp3);

fclose(fout);


//for(i=0;i<idenValp;i++)
//printf("%s\n",idenVals[i]);

fout=fopen("Code13.txt","w+");

ID_put(temp8);

INTR_put(temp11);
print_tree(temp9);
fclose(fout);
for(i=0;i<idenValp;i++)
    //printf("%s %d\n",idenVals[i],i);
fout=fopen("MASMnew13.asm","w+");
fprintf(fout,"\tsection .bss\n");
for(i=0;i<variablesCount;i++)
{
    if(check_String(variableList[i])==-1 && check_Array(variableList[i])==-1)
    fprintf(fout,"%s resd 1\n",variableList[i]);
}
for(i=0;i<variablesCount;i++)
{
 //   if(check_String(variableList[i])==-1)
    //printf("%s\n",variableList[i]);
}

fprintf(fout,"section .text\n");
fprintf(fout,"\t\tglobal _start\n");
fprintf(fout,"_start:\n");

write_code(temp10);
fprintf(fout,"mov eax, 1\n");
fprintf(fout," mov ebx, 0\n");
fprintf(fout,"int 80h\n");
if(setstringpoint>0 || arraynamesPoint>0)
{
    fprintf(fout,"section .data\n");
    for(i=0;i<setstringpoint;i++)
    {
        fprintf(fout,"%s db '%s$', 0xa\n",stringIDs[i],setstrings[i]);
        fprintf(fout,"len%d equ $ - %s\n",i,stringIDs[i]);
    }
    for(i=0;i<arraynamesPoint;i++)
    {
 //   if(check_String(variableList[i])==-1)
    fprintf(fout,"%s TIMES %d dd 0\n",arraynames[i],arraysizes[i]);
    }
    fprintf(fout,"high TIMES 1 dd 0\n");
    fprintf(fout,"low TIMES 1 dd 0\n");

}
fclose(fout);
return 0;
}
