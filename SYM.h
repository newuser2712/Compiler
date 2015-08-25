/* T1 Group Number 25,
2011B4A7664P SAI VARUN ADDANKI
2011B3A7604P AVINASH KUMAR SINGH
*/




#ifndef SYM_H_
#define SYM_H_

#include <stdio.h>
#include<string.h>
#include<ctype.h>
#include "AST.h"

int isInt(char *s)
{

    int l=strlen(s);
    int flag=1;
    int dec=0;
    int i;
    for(i=0;i<l;i++)
    {
        if(s[i]=='.')
            dec++;
        else if(!isdigit(s[i]))
            flag=0;

    }
    if(flag==1 && dec<=1)
        return 1;
    else
        return 0;
}
int string2int(char *str)
{
    int len=strlen(str);
    int i,val=0;
    for(i=0;i<len;i++)
    {
        val=val*10+str[i]-'0';
    }
    return val;
}
FILE *fout2;
int scopes[100][2];
int scopesPoint=0;
int StartScopePointer=0,EndScopePointer=0;
int Stack[100];
char *variableList[200];
int variableScopes[200];

char collectionArray[100][20],*idenVals[200],*setstrings[200],*stringIDs[200];
int setstringpoint=0;
int idenValp=0;
int intrArray[200];
int intrpoint=0;
int collectionArrayPoint=0;
char *arraynames[200];
int arraynamesPoint=0;
int arraysizes[200];


int checkCollection(char *name)
{
    int i=0;
    //printf("Collection point at %d\n",collectionArrayPoint);
    for(i=0;i<collectionArrayPoint;i++)
    {
        //printf("Comparing %s with %s\n",name,collectionArray[i]);
        if(strcmp(collectionArray[i],name)==0)
        return 1;
    }
   // printf("\n");

    return 0;
}
int top=100;
void push(int val)
{
    top--;
    Stack[top]=val;
}
int head()
{
    return Stack[top];
}
void pop()
{
    Stack[top]=-1;
    top++;
}

int searchScope(int k)
{
    int i;

    for(i=0;i<scopesPoint;i++)
    {
        if(scopes[i][0]==k)
            return i+1;
    }
        return -1;

}
struct hashNode
{
	int declared;
	int fname;
	int arrayType;
	char *inputType;
	int arraySize;
	char *rhs[1000];
	int lineNumber[1000];
	int totalAssignment;
	int scope;
	int referred;
	int ReflineNumber[1000];
	char *type;
	int stringSize;
} hashNode;
char s[200][20],secondval[200][20],dummy[200];
typedef struct hashNode hashTable;
hashTable *array[1000][1000];

long hash(char *name)
{
	long h = 0, g;

	while ( *name ) {
		h = ( h << 4 ) + *name++;
		if ( g = h & 0xF0000000 )
		h ^= g >> 24;
		h &= ~g;
	}

	return h%1000;
}
int variablesCount=0;
int insertIntoTable(char *name,int scopeVal,char *type,int DecPos,int arraySize)
{
    variableList[variablesCount]=(char *)malloc(sizeof(name));
    strcpy(variableList[variablesCount++],name);
    int scope=scopeVal;
   // printf("%s %d DecPos is %d with scope %d and type %s\n",name,hash(name),DecPos,scope,type);

    long i=hash(name);
    if(array[scope][i]==NULL)
	array[scope][i] = (hashTable *)malloc(sizeof(hashTable));
	else
    printf("Variable Can't be Declared twice\n");
	array[scope][i]->declared = DecPos;
	array[scope][i]->scope= scope;
	array[scope][i]->fname =0;
	array[scope][i]->referred =0;
	array[scope][i]->totalAssignment=0;
	array[scope][i]->type=(char*)malloc(strlen(type)+1);
	if(strcmp("STRING",type)==0)
        array[scope][i]->stringSize=20;
	if(arraySize==0)
    {
        array[scope][i]->arrayType=0;
        array[scope][i]->arraySize=0;
    }
    else
    {
        arraynames[arraynamesPoint]=(char *)malloc(sizeof(name));
        arraysizes[arraynamesPoint]=arraySize;
        strcpy(arraynames[arraynamesPoint++],name);

        array[scope][i]->arrayType=1;
        array[scope][i]->arraySize=arraySize;
    }
	strcpy(array[scope][i]->type,type);
	return i;
}
void addRef(char *name,int lineNumber,int scope)
{
    //printf("adding ref for %s at %d\n",name,lineNumber);
    if(array[scope][hash(name)]!=NULL)
    {
      array[scope][hash(name)]->ReflineNumber[array[scope][hash(name)]->referred++]=lineNumber;
    }
    else if(array[0][hash(name)]!=NULL)
    {
      array[0][hash(name)]->ReflineNumber[array[0][hash(name)]->referred++]=lineNumber;
    }
    return ;
}
void lookup(char *name,int line)
{
    int matchScopes[8];
    int point=0;
    int i;

    for(i=0;i<scopesPoint;i++)
    {
        if(scopes[i][0]<=line && scopes[i][1]>line)
            matchScopes[point++]=i;
    }
    int j,temp;

    for(i=0;i<point-1;i++)
    {
        for(j=0;j<point;j++)
        {
            if((line-scopes[matchScopes[i]][0])<(line-scopes[matchScopes[i+1]][0]))
            {
                temp=matchScopes[i];
                matchScopes[i]=matchScopes[i+1];
                matchScopes[i+1]=temp;
            }
        }
    }
    int scope;
    for(i=0;i<point;i++)
    {
       // printf("%d\n",scopes[matchScopes[i]][0]);
        scope=searchScope(scopes[matchScopes[i]][0]);
        if(array[scope][hash(name)]!=NULL)
        {
            printHashVal(name,scope);
            return;
        }
    }
    if(array[0][hash(name)]!=NULL)
        {
            printHashVal(name,0);
            return;
        }
    printf("Symbol Not Found\n");
    return;

}
void printHashVal(char *name,int scope)
{
    long i=hash(name);
    int p;
    if(array[scope][i]!=NULL)
    {
        fprintf(fout2,"%s declaration %d scope %d fname %d assignments %d array type=%d referred=%d\n",name,array[scope][i]->declared,array[scope][i]->scope,array[scope][i]->fname,array[scope][i]->totalAssignment,array[scope][i]->arrayType,array[scope][i]->referred);
        //if(array[scope][i]->fname!=1)
        fprintf(fout2,"type is %s\n",array[scope][i]->type);
        if(array[scope][i]->fname==1)
        fprintf(fout2,"inputtype is %s\n",array[scope][i]->inputType);

        if(array[scope][i]->totalAssignment!=0)
        {

            for(p=0;p<array[scope][i]->totalAssignment;p++)
                fprintf(fout2,"rhs=%s at line %d\n",array[scope][i]->rhs[p],array[scope][i]->lineNumber[p]);

       // for(p=0;p<array[scope][i]->referred;p++)
        //    fprintf(fout2,"referred at line\n"/,array[scope][i]->ReflineNumber[p]);

        }

    }
    else
        printf("Symbol not found\n");


}
void fill_as(int i,int line,char *expression,int scopeVal)
{

    int scope=scopeVal;
    if(array[scope][i]==NULL)
    {
        if(array[0][i]!=NULL)
            scope=0;
        else
        {
            printf("Undeclared Variable assigned %d\n",i);
            array[scope][i] = (hashTable *)malloc(sizeof(hashTable));
            array[scope][i]->declared = -1;
            array[scope][i]->fname=0;
            array[scope][i]->totalAssignment=0;

        }

    }
   // printf("fill called with %d %s\n",line,expression);

    array[scope][i]->rhs[array[scope][i]->totalAssignment]=(char *)malloc(strlen(expression)+1);
    strcpy(array[scope][i]->rhs[array[scope][i]->totalAssignment],expression);
    array[scope][i]->lineNumber[array[scope][i]->totalAssignment]=line;
    array[scope][i]->totalAssignment++;
    return;

}
int get_tokens1(char *filename1){

FILE *ifp, *ofp;
ifp=fopen(filename1,"r");

if(ifp==NULL)
    printf("not found");

int i=0;
int line[200],pos[200];

while(fscanf(ifp,"%s %s %[^\n]s",s[i],secondval[i],dummy)!=EOF){
    if(strcmp(s[i],"IDEN")==0)
    {
//        printf("Adding as ID %s\n",secondval[i]);
        idenVals[idenValp]=(char *)malloc(sizeof(secondval[i]));
        strcpy(idenVals[idenValp++],secondval[i]);
    }
    else if(strcmp(s[i],"STR")==0)
    {
        setstrings[setstringpoint]=(char *)malloc(sizeof(secondval[i]));
        stringIDs[setstringpoint]=(char *)malloc(sizeof(idenVals[idenValp-1]));
        strcpy(stringIDs[setstringpoint],idenVals[idenValp-1]);

        strcpy(setstrings[setstringpoint++],secondval[i]);


        //printf("string =%s %s\n",secondval[i],idenVals[idenValp-1]);
        //idenValp--;
    }
    else if(strcmp(s[i],"INTR")==0)
        intrArray[intrpoint++]=string2int(secondval[i]);
    i++;
}

fclose(ifp);
return i-1;
}
int checkCall(int i)
{
    int p=i;
    while(strcmp(s[i++],"SEMICOLON")!=0)
    {

        if(strcmp(s[i],"CALL")==0)
            return 1;
    }
    return 0;
}
int checkBoolean(int i)
{
    int p=i;
    while(strcmp(s[i++],"C_PAR")!=0)
    {
        if(strcmp(s[i],"LEXICOGRAPHIC")==0||strcmp(s[i],"LT")==0||strcmp(s[i],"LTE")==0||strcmp(s[i],"GT")==0||strcmp(s[i],"GTE")==0||strcmp(s[i],"NEQ")==0||strcmp(s[i],"EQ")==0)
            return 1;
    }
    return 0;
}
void main_Sym(char *filename1)
{
int i,j,previous;
int startScope[20],endScope[20];
int k=get_tokens1(filename1);
memset(Stack,'-1',sizeof(Stack));
//printf("%d %d\n",string2int("2"),string2int("17"));
int structCount=-1;
for(i=0;i<k;i++)
{
    if(strcmp(s[i],"SUBPROG")==0)
        push(string2int(secondval[i]));
    else if(strcmp(s[i],"INCLUDES")==0)
        push(string2int(secondval[i]));
    else if(strcmp(s[i],"ENDINCLUDES")==0)
    {
        scopes[scopesPoint][0]=head();
        scopes[scopesPoint++][1]=string2int(secondval[i]);
        pop();
    }

    else if(strcmp(s[i],"ENDSUBPROG")==0)
    {

        scopes[scopesPoint][0]=head();
        scopes[scopesPoint++][1]=string2int(secondval[i]);
        pop();
    }
    //printf("end %s\n",secondval[i]);
}
//for(i=0;i<scopesPoint;i++)
  // printf("scopes %d %d\n",scopes[i][0],scopes[i][1]);


char inhashval[1000][20];
char tempstr[100];
char tempstr2[30];
int tempstrpoint=0;
int tempstr2point=0;
int inhasvalpoint=0;
int line=0;
int start,end;
char typeChar[30];
int p,c,z;
int currentSub=0;

for(i=0;i<k;++i)
{
  //  printf("%s\n",s[i]);
    if(strcmp(s[i],"COLLECTION")==0)
    {
        strcpy(collectionArray[collectionArrayPoint++],secondval[i+1]);
        i+=2;
    }
    if(strcmp(s[i],"SUBPROG")==0||strcmp(s[i],"INCLUDES")==0)
    {
    //    printf("scope change\n");
        currentSub=searchScope(string2int(secondval[i]));
    }
    if(strcmp(s[i],"IF")==0)
    {
        if(checkBoolean(i)==0)
            printf("IF statement should have expression of Boolean Type\n");
    }
    if(strcmp(s[i],"IDEN")==0)
        addRef(secondval[i],string2int(secondval[i-1]),currentSub);
    if(strcmp(s[i],"RETURN")==0)
    {
        i+=2;
        if(array[currentSub][hash(secondval[i])]->totalAssignment==0)
            printf("Return variable not assigned %d\n",line);
    }

    if(strcmp(s[i],"LEXICOGRAPHIC")==0)
    {
        line=string2int(secondval[i]);
        previous=i;
        printf("BoolOP\n");
        if(strcmp(s[i-1],"IDEN")!=0 || strcmp(s[i+1],"IDEN")!=0)
        {
            printf("Wrong operands to lexicographic Operator\n");
        }
        if(strcmp(array[currentSub][hash(secondval[i-1])]->type,"STRING")!=0 || strcmp(array[currentSub][hash(secondval[i+1])]->type,"STRING")!=0)
        {
            printf("Wrong operands to lexicographic Operator\n");
        }

        while(strcmp(s[i],"AS")!=0)
            i--;
        i--;
        if(strcmp(s[i],"IDEN")==0)
        {
            p=hash(secondval[i]);
            if(strcmp(array[currentSub][p]->type,"BOOLEAN")!=0)
                printf("Wrong types at %d\n",line);
        }
        i=previous+1;
    }
    if(strcmp(s[i],"LT")==0 || strcmp(s[i],"LTE")==0|| strcmp(s[i],"GT")==0|| strcmp(s[i],"GTE")==0)
    {
        line=string2int(secondval[i]);
        previous=i;
        printf("BoolOP\n");\
        if(strcmp(s[i-1],"IDEN")!=0  || isInt(secondval[i+1])==0)
        {
            printf("Wrong operands to Boolean Comparision Operator\n");
        }
        if(strcmp(s[i-1],"IDEN")==0)
        {
             if(strcmp(array[currentSub][hash(secondval[i-1])]->type,"BOOLEAN")!=0 && strcmp(array[currentSub][p]->type,"INTEGER")!=0 && strcmp(array[currentSub][p]->type,"DECIMAL")!=0)
                {
                    printf("Operands Should be boolean at %d\n",line);
                }

        }


        while(strcmp(s[i],"AS")!=0 && strcmp(s[i],"WHILE")!=0 && strcmp(s[i],"IF")!=0)
            i--;
        i--;
        if(strcmp(s[i],"IDEN")==0)
        {
            p=hash(secondval[i]);
            if(strcmp(array[currentSub][p]->type,"BOOLEAN")!=0 && strcmp(array[currentSub][p]->type,"INTEGER")!=0 && strcmp(array[currentSub][p]->type,"DECIMAL")!=0)
                printf("Wrong types at %d %s\n",line,array[currentSub][p]->type);
        }
        i=previous+1;
    }
    if(strcmp(s[i],"AND")==0|| strcmp(s[i],"OR")==0|| strcmp(s[i],"NOT")==0)
    {
        line=string2int(secondval[i]);
        previous=i;
        printf("BoolOP\n");
        if(strcmp(s[i-1],"IDEN")!=0 || (strcmp(s[i+1],"IDEN")!=0 && strcmp(s[i+1],"TRUE")!=0) && strcmp(s[i+1],"FALSE")!=0)
        {
            printf("Wrong operands to Boolean Operator\n");
        }
        if(strcmp(s[i-1],"IDEN")==0 && strcmp(s[i+1],"IDEN")==0)
        {
             if(strcmp(array[currentSub][hash(secondval[i-1])]->type,"BOOLEAN")!=0 || strcmp(array[currentSub][hash(secondval[i+1])]->type,"BOOLEAN")!=0)
                {
                    printf("Operands Should be boolean at this%d\n",line);
                }

        }
        else if(strcmp(s[i-1],"IDEN")==0 && (strcmp(s[i+1],"TRUE")==0 || strcmp(s[i+1],"FALSE")==0))
        {
                if(strcmp(array[currentSub][hash(secondval[i-1])]->type,"BOOLEAN")!=0 )
                {
                    printf("Operands Should be boolean at this %d\n",line);
                }

        }
        while(strcmp(s[i],"AS")!=0 && strcmp(s[i],"WHILE")!=0)
            i--;
        i--;
        if(strcmp(s[i],"IDEN")==0)
        {
            p=hash(secondval[i]);
            if(strcmp(array[currentSub][p]->type,"BOOLEAN")!=0)
                printf("Wrong types at %d\n",line);
        }
        i=previous+1;
    }

    if(strcmp(s[i],"PLUS")==0 || strcmp(s[i],"MINUS")==0|| strcmp(s[i],"MULT")==0|| strcmp(s[i],"DIV")==0||strcmp(s[i],"NEQ")==0|| strcmp(s[i],"EQ")==0)
    {
        line=string2int(secondval[i]);
        previous=i;
        printf("ArithmeticOP\n");
        if(strcmp(s[i-1],"IDEN")!=0)
        {
            if(isInt(secondval[i-1])==0)
                printf("Wrong 1st operand to Arithmetic Operator\n");
        }
        if(strcmp(s[i+1],"IDEN")!=0)
        {
            if(isInt(secondval[i+1])==0)
                printf("Wrong 2nd operand to Arithmetic Operator\n");
        }
        if(strcmp(s[i-1],"IDEN")==0 && strcmp(s[i+1],"IDEN")==0)
        {
            if((strcmp(array[currentSub][hash(secondval[i-1])]->type,"INTEGER")!=0 && strcmp(array[currentSub][hash(secondval[i-1])]->type,"DECIMAL")!=0) || (strcmp(array[currentSub][hash(secondval[i+1])]->type,"INTEGER")!=0 && strcmp(array[currentSub][hash(secondval[i+1])]->type,"DECIMAL")!=0))
        //{
            printf("Wrong operands to Arithmetic Operator %s %s\n",secondval[i-1],secondval[i+1]);
        //}


        }
         while(strcmp(s[i],"AS")!=0 && strcmp(s[i],"IF")!=0 && strcmp(s[i],"WHILE")!=0)
            i--;
        i--;
        if(strcmp(s[i],"IDEN")==0)
        {
            p=hash(secondval[i]);
            if(strcmp(array[currentSub][p]->type,"INTEGER")!=0 && strcmp(array[currentSub][p]->type,"DECIMAL")!=0)
                printf("Wrong types at this %d\n",line);
        }
        i=previous+1;
    }
    if(strcmp(s[i],"COLON")==0 && strcmp(s[i+1],"LSB")!=0)
    {
        if(strcmp(s[i-1],"INTR")==0 && strcmp(s[i+1],"INTR")==0)
        {
            int l1=string2int(secondval[i-1]);
            int l2=string2int(secondval[i+1]);
       //     printf("l1 and l2 is %s %s\n",secondval[i-1],secondval[i+1]);
            int k3=i;
            while(strcmp(s[k3],"IDEN")!=0)
                k3--;
            p=hash(secondval[k3]);
            printf("l1 l2 %d %d\n",l1,l2);
            if(l1>=array[currentSub][p]->arraySize || l2>=array[currentSub][p]->arraySize)
            {
                printf("index cannot exceed array size at %d\n",line);
            }

        }
        else
            printf("indexes should be integers at %d\n",line);


    }
    if(strcmp(s[i],"NAME_EQU")==0 || strcmp(s[i],"STRUCT_EQU")==0)
    {
       // printf("%s %s\n",array[currentSub][hash(secondval[i+2])]->type,secondval[i+4]);
       // if((strcmp(array[currentSub][hash(secondval[i+2])]->type,"A")!=0 || (strcmp(array[currentSub][hash(secondval[i+4])]->type,"B")!=0)))
        printf("Wrong Operands to collection operator at %d\n",line);
        if(strcmp(s[i],"STRUCT_EQU")==0)
        exit(0);

    }
  //  printf("%s %s\n",s[i],secondval[i]);
    if((strcmp(s[i],"INTEGER")==0||strcmp(s[i],"STRING")==0||strcmp(s[i],"DECIMAL")==0||strcmp(s[i],"CHARACTER")==0||strcmp(s[i],"BOOLEAN")==0 || checkCollection(secondval[i]))&& strcmp(s[i+1],"RSB")!=0)
    {
        line=string2int(secondval[i]);
        if(checkCollection(secondval[i]))
        strcpy(typeChar,secondval[i]);
        else
        strcpy(typeChar,s[i]);

        if(strcmp(s[i+1],"LSB")==0)
        {
            i+=2;
            c=string2int(secondval[i]);
            printf("size =%d\n",string2int(secondval[i]));
            while(strcmp(s[i],"IDEN")!=0)
                i++;
            p=insertIntoTable(secondval[i],currentSub,typeChar,string2int(secondval[i-1]),c);

            //printf("array name=%s %d\n",secondval[i],string2int(secondval[i-1]));
        }
        else
        {
            strcpy(inhashval[inhasvalpoint++],secondval[i+1]);
            p=insertIntoTable(secondval[i+1],currentSub,typeChar,string2int(secondval[i]),0);
            i+=2;
            while(strcmp(s[i],"COMMA")==0)
            {
                strcpy(inhashval[inhasvalpoint++],secondval[i+1]);
                p=insertIntoTable(secondval[i+1],currentSub,typeChar,string2int(secondval[i]),0);
                i+=2;
            }
            memset(typeChar,'\0',sizeof(typeChar));

        }
    }
    else if(strcmp(s[i],"FUNC_START")==0)
    {
        previous=i;
        line=string2int(secondval[i]);
        strcpy(inhashval[inhasvalpoint++],secondval[i+1]);


        p=insertIntoTable(secondval[i+1],0,"fname",string2int(secondval[i]),0);
        array[0][p]->fname=1;
        while(strcmp(s[i],"SUBPROG")!=0)
        {
            if(strcmp(s[i],"O_PAR")==0)
                break;
            i++;
        }
        i++;
        if(strcmp(s[i],"C_PAR")!=0)
        {
            array[0][p]->inputType=(char*)malloc(sizeof(s[i])+1);
            strcpy(array[0][p]->inputType,s[i]);
        }
        while(strcmp(s[i],"SUBPROG")!=0)
        {
            if(strcmp(s[i],"LSB")==0)
                break;
            i++;
        }
        i++;
        if(strcmp(s[i],"RSB")!=0)
        {
            array[0][p]->type=(char *)malloc(sizeof(s[i]));
            //printf("Copyting %s %d\n",s[i],i);
            strcpy(array[0][p]->type,s[i]);
        }
        else
        {
            array[0][p]->type=(char *)malloc(sizeof("Void"));
            //printf("Copyting %s %d\n","Void",i);
            strcpy(array[0][p]->type,"Void");
        }
        array[0][p]->fname=1;
        i=previous+1;
    }
    else if(strcmp(s[i],"ASSIGN")==0)
    {
        previous=i+1;
        line=string2int(secondval[i]);
        if(strcmp(s[i+1],"MULTIPLE")==0)
        {
           // printf("Entered")
            i+=3;
            p=hash(secondval[i]);
            c=checkCall(i);
            if(c==1)
            {
                z=i+4;
                if(strcmp(array[0][hash(secondval[z])]->type,array[currentSub][hash(secondval[previous+2])]->type)!=0)
               printf("Wrong type does not match with return is %s\n",array[0][hash(secondval[z])]->type);

                if(array[0][hash(secondval[z])]->inputType!=NULL)
                {
                    if(array[currentSub][hash(secondval[previous+8])]!=NULL)
                    {
                        if(strcmp(array[0][hash(secondval[z])]->inputType,array[currentSub][hash(secondval[previous+8])]->type)!=0)
                        printf("Wrong type does not match with input is %s\n",array[0][hash(secondval[z])]->inputType);
                //        printf("%s inputted\n",array[currentSub][hash(secondval[previous+8])]->type);

                    }
                    else
                    {
                        if(strcmp(array[0][hash(secondval[z])]->inputType,array[0][hash(secondval[previous+8])]->type)!=0)
                        printf("Wrong type does not match with input is %s\n",array[0][hash(secondval[z])]->inputType);
                        //printf("%s inputted\n",array[currentSub][hash(secondval[previous+8])]->type);

                    }

                }

                //printf("ftype is %s\n",array[0][hash(secondval[z])]->type);

                while(strcmp(s[z],"SEMICOLON")!=0 && strcmp(s[z],"C_PAR")!=0)
                {
                    if(strcmp(s[z],"IDEN")==0)
                    {
                        // addRef(secondval[z],line,currentSub);
                        for(j=0;j<strlen(secondval[z]);j++)
                        {
                            tempstr[tempstrpoint++]=secondval[z][j];
                        }

                        tempstr[tempstrpoint++]=' ';
                    }
                z+=2;
                }
                i=z;


                //printf("%s\n",tempstr);
                fill_as(p,line,tempstr,currentSub);
                memset(tempstr,'\0',sizeof(tempstr));
                tempstrpoint=0;
            }
            else
            {
               // printf("%s\n",s[i]);
                start=i;
                while(strcmp(s[i],"LSB")!=0)
                    i++;
                i++;
                end=i;
                p=hash(secondval[start]);
                fill_as(p,line,secondval[end],currentSub);
                while(strcmp(s[start+1],"COMMA")==0)
                {
                   start+=2;
                   end+=2;
                   p=hash(secondval[start]);
                   fill_as(p,line,secondval[end],currentSub);
                 //  printf("first and sec %s %s %d\n",secondval[start],secondval[end],line);
                }
                while(strcmp(s[i],"SEMICOLON")!=0)
                    i++;
            }
        }
        else if(strcmp(s[i+1],"LSB"))
        {
            memset(tempstr,'\0',sizeof(tempstr));
            p=hash(secondval[i+1]);
            i+=3;
            z=i;
        //memset(tempstr,'\0',sizeof(tempstr));
            if(strcmp(s[i-1],"LSB")==0)
            {
                printf("%s has ",secondval[i-2]);
                p=hash(secondval[i-2]);
                while(strcmp(s[i],"AS")!=0)
                    i++;
                i++;
                z=i;
                while(strcmp(s[z],"SEMICOLON")!=0)
                {
                    if(strcmp(s[z],"DEC")==0||strcmp(s[z],"INTR")==0||strcmp(s[z],"STR")==0||strcmp(s[z],"IDEN")==0)
                    {
                        if(strcmp(s[z],"IDEN")==0)
                        //addRef(secondval[z],line,currentSub);

                        for(j=0;j<strlen(secondval[z]);j++)
                        {
                            tempstr[tempstrpoint++]=secondval[z][j];
                           // printf("%c",secondval[z][j]);
                        }
                        //printf("\n");

                    }
                    else
                    {
                        for(j=0;j<strlen(s[z]);j++)
                        {
                            tempstr[tempstrpoint++]=s[z][j];
                        }
                    }

                    tempstr[tempstrpoint++]=' ';
                    z++;
                }

             //   printf("rhs=%s\n",tempstr,strlen(tempstr));
                fill_as(p,line,tempstr,currentSub);
                memset(tempstr,'\0',sizeof(tempstr));
                i=z;
                tempstrpoint=0;
            }
            else
            {
                while(strcmp(s[z],"SEMICOLON")!=0)
                {
                    if(strcmp(s[z],"DEC")==0||strcmp(s[z],"INTR")==0||strcmp(s[z],"STR")==0||strcmp(s[z],"IDEN")==0)
                    {
                        if(strcmp(s[z],"IDEN")==0)
                        //addRef(secondval[z],line,currentSub);

                        for(j=0;j<strlen(secondval[z]);j++)
                        {
                            tempstr[tempstrpoint++]=secondval[z][j];
                           // printf("%c",secondval[z][j]);
                        }

                    }
                    else
                    {
                        for(j=0;j<strlen(s[z]);j++)
                        {
                            tempstr[tempstrpoint++]=s[z][j];
                        }
                    }

                    tempstr[tempstrpoint++]=' ';
                z++;
                }

                i=z;
              //  printf("\nrhs=%s\n",tempstr,strlen(tempstr));
                fill_as(p,line,tempstr,currentSub);
                memset(tempstr,'\0',sizeof(tempstr));
                tempstrpoint=0;


            }

        }

    i=previous+1;
    }

}
lookup("D",25);
//printf("curr=%d\n",currentSub);
int l;
//TEST CASE 1
/*
fout=fopen("SymbolTable1.txt","w");
printHashVal("a1",1);
printHashVal("a2",1);
printHashVal("b1",1);
printHashVal("b2",1);
printHashVal("avar",1);
printHashVal("bvar",1);
fclose(fout);

*/
//TEST CASE 2
/*
fout=fopen("SymbolTable2.txt","w");

printHashVal("a",0);
printHashVal("first",0);
printHashVal("y",0);
printHashVal("b",1);
printHashVal("second",0);
printHashVal("z",1);
printHashVal("a",2);
printHashVal("b",2);
printHashVal("",0);
printHashVal("c",3);
fclose(fout);
*/
//Test Case 3
/*
fout=fopen("SymbolTable3.txt","w");
printHashVal("main",0);
printHashVal("arr",1);
printHashVal("i",1);
printHashVal("revarr",1);
fclose(fout);
*/
//Test Case 4
/*
fout=fopen("SymbolTable4.txt","w");
printHashVal("taxCalculation",0);
printHashVal("income",0);
printHashVal("adjustVal",2);
printHashVal("taxUtil",0);
printHashVal("y",1);
printHashVal("finalVal",1);
printHashVal("main",0);
printHashVal("d",3);
printHashVal("tax",3);
fclose(fout);
*/
//Test Case 5
/*
fout=fopen("SymbolTable5.txt","w");
printHashVal("a",1);
printHashVal("b",1);
printHashVal("c",1);
printHashVal("a",2);
printHashVal("b",2);
printHashVal("c",2);
printHashVal("main",0);
printHashVal("a1",3);
printHashVal("b1",3);
printHashVal("C",3);
printHashVal("D",3);
fclose(fout);
*/
//Test Case 6
/*
fout=fopen("SymbolTable6.txt","w");
printHashVal("main",0);
printHashVal("S1",1);
printHashVal("S2",1);
printHashVal("b1",1);
fclose(fout);
*/

/*
tree* root=NULL;

int count=get_tokens();
//int i;

    for(i=0;i<count;i++)
        hashedTokens[i]=hash_tokens(Tokens[i]);

generate_table();
//int j;
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
fout=fopen("AST7.txt","w+");
//AST(temp,0);
prune_All(temp2);
i=0;
post_pruning(temp4);

ID_pruned(temp5);

prune_more(temp6);
final_pruning(temp7);
fclose(fout);

fout=fopen("BST7.txt","w+");

//print_tree(temp3);
fclose(fout);
*/
//main_AST();


return;
}
#endif
