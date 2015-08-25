/* T1 Group Number 25,
2011B4A7664P SAI VARUN ADDANKI
2011B3A7604P AVINASH KUMAR SINGH
*/
#ifndef AST_H_
#define AST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE *fout;
FILE *out;
typedef struct node tree;

char Tokens[200][20],secondVal[200][20],dummy[200];

int hashedTokens[300];
int Table[59][68];
int count;
int tokNo=0,grammarNo,p;

int Rules[300][100];

char Terms[300][40];

fill_terms(){
int i=0;

for(i=0;i<300;++i)
    memset(Terms[i],'\0',sizeof(Terms[i]));

FILE *in=fopen ("Terminals.txt","r+");
    	int lineNo=0;
		char temp[40];

		while (!feof(in)){
         //   memset(temp,'\0',sizeof(temp));
            fscanf(in,"%s",Terms[lineNo]);

            //strcpy(Terms[lineNo++],temp);
            lineNo++;

		}

    fclose(in);
in=fopen ("nonTerminalList.txt","r+");

     lineNo=0;
    while (!feof(in)){
            memset(temp,'\0',sizeof(temp));
            fscanf(in,"%s",Terms[lineNo+100]);

            //strcpy(Terms[lineNo+100],temp);
            lineNo++;

		}
fclose(in);
return;
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
/*
int get_tokens(){

FILE *ifp, *ofp;
ifp=fopen("Test_Case_7_Tokens.txt","r");

if(ifp==NULL)
    printf("not found");

int i=0;
int line[200],pos[200];

while(fscanf(ifp,"%s %[^\n]s",Tokens[i],dummy)!=EOF){

printf("%s\n",Tokens[i]);
 i++;
}
fclose(ifp);
return i-1;
}
*/

int get_tokens(char *filename){

int p=0;
for(p=0;p<200;p++)
memset(Tokens[p],'\0',sizeof(Tokens));

FILE *ifp, *ofp;
ifp=fopen(filename,"r");


int i=0;
int line[200],pos[200];

while(fscanf(ifp,"%s %s %[^\n]s",Tokens[i++],secondVal[i],dummy)!=EOF);
//while(fscanf(ifp,"%s %[^\n]s",Tokens[i],dummy)!=EOF){
//    i++;
//}
fclose(ifp);

return i-1;
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

struct node{
int count;
int term;
tree* nod[100];
};

tree* initialize_node(){
tree* root;
int i=0;

root=(tree*)malloc(sizeof(tree));
//memset(root->term,'\0',sizeof(root->term));
root->count=0;
root->term=-1;
for(i=0;i<100;++i)
    root->nod[i]=NULL;

return root;
}

tree* insert(tree* root,int temp){

 //root=initialize_node();
 root->term=temp;
 return root;

}

void dfs(tree* root)
{
    int p,i;
    if(root->term==1 && tokNo==count)
    {
        fprintf(fout,"complete parsetree generated");
        exit(0);
    }
    else if((root->term)==67)
         return;

    else if(root->term<100 && root->term>=0)
    {
        fprintf(fout,"Entered Terminal\n");
        if(root->term==hashedTokens[tokNo])
        {
            fprintf(fout,"Entered Terminal poping\n");

            tokNo++;
            return;
        }
        else
        {
            tokNo++;
            fprintf(fout,"Errror of Non matching token\n");
            return;
        }
    }

    else
    {

        fprintf(fout,"table value is %d where non terminal is %d and token is %d and token no is %d\n",Table[root->term-100][hashedTokens[tokNo]+1],root->term,hashedTokens[tokNo],tokNo);
        grammarNo=Table[root->term-100][hashedTokens[tokNo]+1]-1;

        p=0;

        while(Rules[grammarNo][p++]!=-1);
        p--;

        root->count=p-1;
        for(i=1;i<=p-1;i++)
        {
            fprintf(fout,"pushing %d\n",Rules[grammarNo][i]);
            root->nod[i-1]=initialize_node();
            root->nod[i-1]=insert(root->nod[i-1],Rules[grammarNo][i]);
        }

        for(i=1;i<=p-1;++i)
            dfs(root->nod[i-1]);

    }
}

void AST(tree* root)
{

    int i;
    for(i=0;i<10;++i)
        if(root->nod[i]!=NULL)
            AST(root->nod[i]);

    int j,p;

    for(j=0;j<10;++j)
    {
    if(root->nod[j]!=NULL)
        {
            if(root->nod[j]->count==1)
            {
                if(root->nod[j]->nod[0]->term==67)
                {
                    free(root->nod[j]->nod[0]);
                    free(root->nod[j]);
                    root->nod[j]=NULL;
                    root->count--;
                }


                else
                {
                    tree* temp=root->nod[j];
                    for(p=0;p<10;p++)
                    {
                        if(root->nod[j]->nod[p]!=NULL)
                        {
                               root->nod[j]=root->nod[j]->nod[p];
                               break;
                        }

                    }

                    free(temp);
                }
            }
        }

        //else if(root->nod[j]==NULL)
          //  break;
 }

return;
}

void prune(tree* root){

    int i;
    for(i=0;i<10;++i)
        if(root->nod[i]!=NULL)
            prune(root->nod[i]);

    int j;

    for(j=0;j<10;++j)
    {
    int x;
        if(root->nod[j]!=NULL)
        {
            x=root->nod[j]->term;
            if(x==0||x==1||x==4||x==5 || x==6 || x==7 || x==8 || x==9||x==10 || x==18||x==20||x==61 || x==55)
            {

                    free(root->nod[j]);
                    root->nod[j]=NULL;
                    root->count--;
            }
        }

        //else if(root->nod[j]==NULL)
          //  break;
    }
return;

}

int ID_count=0;
tree* func_def[100];
int count=0;

void getfunc_defs(tree *root){


int j;
for(j=0;j<100;++j){
    if(root->nod[j]!=NULL){
        if(root->term==113)
        return;

        else if(root->nod[j]->term==104){
            func_def[count]=root->nod[j];
            count++;
            return;
        }
    }
}
return;

int i;

for(i=0;i<100;++i){
    if(root->nod[i]!=NULL)
    {
    //    printf("Calling %d\n",i);
        getfunc_defs(root->nod[i]);
    }

}
}

void getcount_ID(tree *root){

int i;

for(i=0;i<100;++i){
    if(root->nod[i]!=NULL)
    {
    //    printf("Calling %d\n",i);
        getcount_ID(root->nod[i]);
    }

}

if(root->term==65){
    ID_count++;
    return;
}

return;
}

tree* prune_func_defs(tree *root){

    getfunc_defs(root);
    int i;
    for(i=0;i<100;++i)
        root->nod[i]==NULL;

    for(i=0;i<count;++i){
      root->nod[i]=func_def[i];
      root->nod[i]=insert(root->nod[i],104);
    }
return root;


}

tree* prune_ID(tree *root){

    getcount_ID(root);

    int i;
    for(i=0;i<100;++i)
        root->nod[i]==NULL;

    for(i=0;i<ID_count;++i){
      root->nod[i]=initialize_node();
      root->nod[i]=insert(root->nod[i],65);
    }
    root->count=ID_count;
return root;
}

tree* prune_dec(tree *root){

    getcount_ID(root);

    int i;
    for(i=1;i<100;++i)
        root->nod[i]==NULL;

    for(i=1;i<=ID_count;++i){
      root->nod[i]=initialize_node();
      root->nod[i]=insert(root->nod[i],65);
    }
    root->count=ID_count+1;
return root;
}


void ID_pruned(tree * root){

    if(root->term==102){

           root=prune_func_defs(root);
            count=0;
        return;
        }

    if(root->term==118){

            root=prune_dec(root);

            ID_count=0;
        return;

    }


    if( root->term==120 || root->term==11 || root->term==12 || root->term==13 || root->term==14 || root->term==15){

//    if(root->term==145){
            root=prune_ID(root);

            ID_count=0;
        return;
    }

    int i;
    for(i=0;i<100;++i){
        if(root->nod[i]!=NULL)
            ID_pruned(root->nod[i]);

    }
return;

}

void prune_All(tree* root){
 AST(root);
 prune(root);

return;

}

void prune_more(tree* root){

 int i;

    for(i=0;i<100;++i){
        if(root->nod[i]!=NULL)
            prune_more(root->nod[i]);
    }


    int j;

    for(j=0;j<100;++j){

        if(root->nod[j]!=NULL)
        {

           // printf("\n%s",Terms[root->nod[j]->term]);
            if(root->nod[j]->term==134)
                root->nod[j]->nod[1]=NULL;


            if( (root->nod[j]->term==114 ||root->nod[j]->term==135) && root->term!=130){
                //printf("ROOT IS %s %d\n",Terms[root->term],root->term);
                root->count=root->count + root->nod[j]->count-1;

                int ct=root->nod[j]->count;
                int k;//=root->count;

                tree *new=root->nod[j];
                tree *temp[100];

                for(k=0;k<100;++k)
                    temp[k]=NULL;

                int p=0;

               for(k=0;k<100;++k){
                        if(((root->nod[j])->nod[k])!=NULL)
                        {
                            temp[p]=((root->nod[j])->nod[k]);
                        //    printf("%s\n",Terms[((root->nod[j])->nod[k]->term)]);
                            p++;
                        }

                }
                p=0;


            if(new->term==114){
                    for(k=0; k<ct ;++k){
                            root->nod[k+1]=temp[k];

                    }
            }

                else if(new->term==135){
                    for(k=0; k<ct+1 ;++k){
                            root->nod[k+2]=temp[k];

                    }
                }
		int x;
		for(x=0;x<100;x++)
		{
			new->nod[x]=NULL;
		}
		new->term=-1;
                //free(new);

            }

            //else
             //   break;

        }
        //else
         //   break;
    }

return;
}


void print_tree(tree *root){

int i=0;
fprintf(fout,"%s",Terms[root->term]);
tree *tempo;
tempo=root;
for(i=0;i<100;++i)
    if(root->nod[i]!=NULL && root->nod[i]->term>=0)
        fprintf(fout," %d child %s ",i,Terms[root->nod[i]->term]);

fprintf(fout,"\n");

for(i=0;i<100;++i)
    if(root->nod[i]!=NULL)
        print_tree(root->nod[i]);
}

void post_pruning(tree *root)
{

    int i;
    for(i=0;i<10;++i)
        if(root->nod[i]!=NULL)
            post_pruning(root->nod[i]);

    int j,p;

    for(j=0;j<10;++j)
    {
    int x;
        if(root->count!=0)
        {
                    x=root->term;
                    if(x==105 && root->count==1)
                    {
                        if(root->nod[0]->term==65)
                        {
                          root->term=65;
                          free(root->nod[0]);
                          root->nod[0]=NULL;
                        }
                    }

                    else if(x==147)
                    {
                        root->term=root->nod[0]->term;
                        free(root->nod[0]);
                        root->nod[0]=NULL;
                        root->count--;
                    }

                   /* else if(x==118 && (root->nod[0]->term<100))
                    {
                        root->term=root->nod[0]->term;
                        free(root->nod[0]);
                        root->nod[0]=NULL;
                        root->count--;
                    }*/

                    else if(x==119)
                    {
                        root->term=root->nod[0]->term;
                        free(root->nod[0]);
                        root->nod[0]=NULL;
                        root->count--;
                    }

                 /*   else if(x==104 && root->nod[1]->term==65)
                    {
                        root->term=root->nod[1]->term;
                        free(root->nod[1]);
                        root->nod[1]=NULL;
                        root->count--;
                    }*/

                    else if(x==143)
                    {
                        root->term=root->nod[1]->term;
                        free(root->nod[1]);
                        root->nod[1]=NULL;
                        root->count--;

                    }
                    else if(x==127)
                    {
                        root->term=root->nod[0]->term;
                        free(root->nod[0]);
                        root->nod[0]=NULL;
                        root->count--;
                    }
                    else if(x==129)
                    {
                        root->term=root->nod[0]->term;
                        free(root->nod[0]);
                        root->nod[0]=NULL;
                        root->count--;
                    }
                      else if(x==151||x==155)
                    {
                        root->term=root->nod[1]->term;
                        free(root->nod[1]);
                        root->nod[1]=NULL;
                        root->count--;
                    }
                    else if(x==152||x==153||x==154)
                    {
                        root->term=root->nod[0]->term;
                        free(root->nod[0]);
                        root->nod[0]=NULL;
                        root->count--;
                    }



        }

        //else if(root->nod[j]==NULL)
          //  break;
    }
    return;
}

void final_pruning(tree *root)
{

    int i;
    for(i=0;i<10;++i)
        if(root->nod[i]!=NULL)
            final_pruning(root->nod[i]);

    int j,p;

    for(j=0;j<10;++j)
    {
    int x;
        if(root->nod[j]!=NULL)
        {
            x=root->nod[j]->term;
            if(x==25||x==26||x==16)
            {

                    free(root->nod[j]);
                    root->nod[j]=NULL;
                    root->count--;
            }
            x=root->term;
            if(x==104)
            {
                if(root->nod[1]->term==65)
                {
                    root->term=root->nod[1]->term;
                    free(root->nod[1]);
                    root->nod[1]=NULL;
                }
                /*else if(root->nod[1]->term==105)
                {
                    printf("Entered\n");
                    root->term=root->nod[1]->nod[0]->term;
                    free(root->nod[1]->nod[0]);
                    root->nod[1]->nod[0]=NULL;
                    root->nod[1]->count--;
                    if(root->nod[1]->count<=0)
                        root->nod[1]->term=-1;
                }*/

            }
         /*   if(x==23)
            {
                if(root->nod[1]==24)
                {
                    root->term=root->nod[1]->term;
                    free(root->nod[1]);
                    root->nod[1]=NULL;

                }
            }
            */
        }


        //else if(root->nod[j]==NULL)
          //  break;
    }
    return;
}


void main_AST(char *filename){

tree* root=NULL;
int count=get_tokens(filename);
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
dfs(root);

//print_tree(temp);
fclose(fout);
fout=fopen("AST13.txt","w+");
print_tree(temp);
//AST(temp,0);
prune_All(temp2);
i=0;
post_pruning(temp4);

ID_pruned(temp5);

prune_more(temp6);
final_pruning(temp7);
fclose(fout);

fout=fopen("BST131.txt","w+");

print_tree(temp3);
fclose(fout);

return;
}
#endif
