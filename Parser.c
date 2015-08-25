#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int No_of_Nonterminals=59;
int No_of_Terminals=66;
char Tokens[200][20],dummy[200];
int hashedTokens[300];
int Table[59][68];
int count;

int Rules[300][100];


int Stack[1001];
int top=1001;
FILE *fout;

void printStack()
{
    int l=top;
    while(l<1001)
    {
        fprintf(fout,"%d ",Stack[l++]);
    }
    fprintf(fout,"\n");
}
void readRules()
{

    FILE * in=fopen("RULES.txt","r+");
    int i,j,k,id;
    i=0;
    j=0;
    while(!feof(in)){

    fscanf(in,"%d",&id);
    if(id==-1){
        Rules[i][j]=id;
    ++i;
    j=0;
    }

    else{
        Rules[i][j]=id;
    ++j;
    }

}
int p=i;
for(i=0;i<p;i++)
{
    for(j=0;j<20;j++)
    {
        if(Rules[i][j]==-1)
            break;
     //   printf("%d ",Rules[i][j]);
    }
    //printf("\n");

}
return ;
}
int fill_line(char temp[][30],int grammarNo){

int i,j,k;
FILE *in=fopen ("grammar.txt","r+");
FILE *fout=fopen("RULES.txt","a");
    int lineNo=0;
    char grammarRule[200];

    while(!feof(in)){

            memset(grammarRule,'\0',sizeof(grammarRule));

            fscanf(in," %[^\n]s",grammarRule);

                if(lineNo==grammarNo){
                    break;
                }

                else
                    lineNo++;
    }

  //  printf("%s\n",grammarRule);

i=0;
j=0;

	for(k=0;k<strlen(grammarRule);k++)
    {
            if(grammarRule[k]==' '||grammarRule[k]=='-'||grammarRule[k]==','||grammarRule[k]=='$')
            {
                temp[i][j]='\0';
                i++;
                j=0;

            }
            else
           temp[i][j++]=grammarRule[k];

	}
	temp[i][j+1]='\0';
	int p=0;

	printf("Start of RULE %d\n",grammarNo);
	for(p=0;p<i;p++)
    {
        printf("%s\n",temp[p]);
        if(hash_tokens(temp[p])>0)
        Rules[grammarNo][p]=hash_tokens(temp[p]);


        else
            Rules[grammarNo][p]=hash_nonterm(temp[p]);
        fprintf(fout,"%d ",Rules[grammarNo][p]);

    }
    fprintf(fout,"$\n");
    fclose(fout);


    printf("End of RULE\n");


return 0;

}
void push(int a)
{
    top--;
    Stack[top]=a;
}
void pop()
{
    Stack[top]=-1;
    top++;
}
int head()
{
    return Stack[top];
}
char nonTerm[30];
char token[30];



int get_tokens(){

int p=0;
for(p=0;p<200;p++)
memset(Tokens[p],'\0',sizeof(Tokens));

FILE *ifp, *ofp;
ifp=fopen("Test_Case_6_Tokens.txt","r");


int i=0;
int line[200],pos[200];

while(fscanf(ifp,"%s %[^\n]s",Tokens[i++],dummy)!=EOF);

fclose(ifp);

return i-1;
}

int hash_nonterm(char str[]){

    FILE *in=fopen ("nonTerminalList.txt","r+");

		int lineNo=0;
		char temp[40];

		while (!feof(in)){
            memset(temp,'\0',sizeof(temp));
            fscanf(in,"%s",temp);

            if(strcmp(temp,str)==0)
                return lineNo+=100;

            else
                lineNo++;

		}
    fclose(in);

return -1;
}

int hash_tokens(char *str){

    FILE *in=fopen ("Terminals.txt","r+");

		int lineNo=0;
		char temp[40];

		while (!feof(in)){
            memset(temp,'\0',sizeof(temp));
            fscanf(in,"%s",temp);

            if(strcmp(temp,str)==0)
                return lineNo;

            else
                lineNo++;

		}
    fclose(in);
return -1;
}



void generate_table(){

 int i,j;
 FILE *in=fopen ("table.txt","r+");

 while(!feof(in)){

    for(i=0;i<59;i++)
        for(j=0;j<68;++j)
            fscanf(in,"%d ",&Table[i][j]);

 }

 for(i=0;i<59;i++)
        for(j=0;j<68;++j)
            if(Table[i][j]==129 || Table[i][j]==130 || Table[i][j]==0)
                Table[i][j]=-1;


}


int main()
{
    //generate_table();
    //count = get_tokens();
    //int j=0,i;
    int i=0,j;
    memset(Stack,'0',sizeof(Stack));

 //   for(i=0;i<300;i++)
  //      memset(Rules[i],0,sizeof(Rules[i]));
    //char temp[200][30];
//char temp[200][30];
    //for(i=0;i<200;i++)
     //   memset(temp[i],'\0',sizeof(temp[i]));
   //for(i=100;i<127;i++)
   // j=fill_line(temp,127);

    //printf("%d",hash_nonterm("variables"));
    //j=fill_line(temp,108);
   // j=fill_line(temp,109);
   // for(i=100;i<128;i++)
    //j=fill_line(temp,i);


int x,y;
int count=get_tokens();

for(i=0;i<count;i++)
{
    hashedTokens[i]=hash_tokens(Tokens[i]);
 //   printf("%s %d\n",Tokens[i],hashedTokens[i]);
}
fout=fopen("Checkfile.txt","w+");
generate_table();
fclose(fout);

/*for(i=0;i<59;i++)
{
    for(j=0;j<68;j++)
        fprintf(fout,"%d ",Table[i][j]);
    fprintf(fout,"\n");
}*/

readRules();
fout=fopen("Output.txt","w+");
int tokNo=0,grammarNo,p;
push(100);
int loopcount=0,currentHash;
while(top<1001)
{
  loopcount++;
  if(top==1001 && tokNo==count)
    return 0;
  else if(top==1001 && tokNo!=count)
    return -1;
  else if(top!=1001 && tokNo==count)
    return -1;

  printStack();

  fprintf(fout,"table value is %d where non terminal is %d and token is %d and token no is %d\n",Table[head()-100][hashedTokens[tokNo]+1],head(),hashedTokens[tokNo]+1,tokNo);

  grammarNo=Table[head()-100][hashedTokens[tokNo]+1]-1;
  //PUSHING
  //pop()

  p=0;

  while(Rules[grammarNo][p++]!=-1);
  p--;

  pop();

  for(i=p-1;i>0;i--)
  {
     fprintf(fout,"pushing %d\n",Rules[grammarNo][i]);
    push(Rules[grammarNo][i]);
  }
  if(head()==67)
    {
        fprintf(fout,"Popping Ebsilon\n");
        pop();
    }

  while(1 && tokNo<count && top<1001)
  {
      if(head()<100 && head()>=0)
      {
          fprintf(fout,"head inside small loop is %d and token is %d\n",head(),hashedTokens[tokNo]);
          if(head()==hashedTokens[tokNo])
          {
              fprintf(fout,"Poppping %d\n",head());
              pop();
              tokNo++;
          }
          else
          {
              fprintf(fout,"Wrong Terminal \n");
              pop();
              tokNo++;
          }
      }
      else
        break;

  }

}
return 0;
}

