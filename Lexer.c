/* T1 Group Number 25,
2011B4A7664P SAI VARUN ADDANKI
2011B3A7604P AVINASH KUMAR SINGH
*/
#include <stdio.h>
#include<string.h>
int pos=0;
char temp[100];
FILE *fout;
struct node
{
	char *lex;
	char *token;
	char *sym;
} node;

struct token
{
	char *lexeme;
	char *tokenVal;
	int line;
	int pos;
}token;
typedef struct token Token;
typedef struct node Node;

Node *bin[3000];

long hash(char *name)
{
	long h = 0, g;

	while ( *name ) {
		h = ( h << 4 ) + *name++;
		if ( g = h & 0xF0000000 )
		h ^= g >> 24;
		h &= ~g;
	}

	return h%2999;
}
void initiateValue(char s[],char k[])
{
	long i=hash(s);
	bin[i] = (Node *)malloc(sizeof(node));
	bin[i]->lex = (char *)malloc(strlen(s)+1);
	bin[i]->token = (char *)malloc(strlen(k)+1);
	strcpy(bin[i]->lex, s);
	strcpy(bin[i]->token, k);
}
char getNextChar(char *s)
{
	return s[pos++];
}
char getNextNonBlank(char *s)
{
	while(s[pos]==' ')
	pos++;
	return s[pos++];
}
void lookup(char *s,int line,int pos)
{
	if(strcmp(bin[hash(s)]->lex,s)==0)
	{
		Token *to=(Token*)malloc(sizeof(Token));
		to->lexeme=(char*)malloc(sizeof(s));
		to->tokenVal=(char*)malloc(sizeof(bin[hash(s)]->token));
		to->line=line;
		to->pos=pos-strlen(s);

		strcpy(to->lexeme,s);
		strcpy(to->tokenVal,bin[hash(s)]->token);
		fprintf(fout,"%s %d %d\n",to->tokenVal,to->line,to->pos);
	}
}
int main(void) {
initiateValue("Prog","PROG");
initiateValue("EndProg","ENDPROG");
initiateValue("Global","GLOBAL");
initiateValue("%","FUNC_START");
initiateValue("EndGlobal","ENDGLOBAL");
initiateValue("Integer","INTEGER");
initiateValue("Decimal","DECIMAL");
initiateValue("Boolean","BOOLEAN");

initiateValue("(","O_PAR");
initiateValue(")","C_PAR");
initiateValue("[","LSB");
initiateValue("]","RSB");

initiateValue(":","COLON");
initiateValue(",","COMMA");
initiateValue(";","SEMICOLON");
initiateValue("if","IF");
initiateValue("else","ELSE");
initiateValue("elseif","ELSEIF");

initiateValue("Begin","BEGIN");
initiateValue("End","END");
initiateValue("Endif","ENDIF");
initiateValue("print","PRINT");
initiateValue("scan","SCAN");
initiateValue("Collection","COLLECTION");
initiateValue("includes","INCLUDES");
initiateValue("endincludes","ENDINCLUDES");

initiateValue("#","REPEAT");
initiateValue("?","LEXICOGRAPHIC");

initiateValue("<","LT");
initiateValue("<=","LTE");
initiateValue(">","GT");
initiateValue(">=","GTE");
initiateValue("=","EQ");
initiateValue("<>","NEQ");

initiateValue("&","AND");
initiateValue("|","OR");
initiateValue("!","NOT");

initiateValue("+","PLUS");
initiateValue("-","MINUS");
initiateValue("/","DIV");
initiateValue("*","MULT");
initiateValue("@","COMM_START");
initiateValue("_","UNDERSCORE");
initiateValue("Character","CHARACTER");
initiateValue("return","RETURN");
initiateValue("\"","DOUBLE_QUOTE");
initiateValue("'","QUOTE");

initiateValue("TRUE","TRUE");
initiateValue("FALSE","FALSE");

initiateValue("FALSE","FALSE");
initiateValue("FALSE","FALSE");

initiateValue("while","WHILE");
initiateValue("Loop","LOOP");
initiateValue("EndLoop","ENDLOOP");

initiateValue("Call","CALL");
initiateValue("SubProg","SUBPROG");
initiateValue("EndSubProg","ENDSUBPROG");
initiateValue("assign","ASSIGN");
initiateValue("as","AS");

initiateValue("multiple","MULTIPLE");
initiateValue("NAME_EQU","Name_Equ");
initiateValue("STRUCT_EQU","Struct_Equ");

char s[44][1001];
int i,j;
char tc;
fout=fopen("Test_Case_14.txt","r");
for(i=0;i<44;i++)
{
	for(j=0;j<1001;j++)
	{
		fscanf(fout,"%c",&s[i][j]);
		if(s[i][j]=='\n')
			break;
	}
	if(strcmp(s[i],"EndProg")==0)
		break;
}
fclose(fout);
fout=fopen("Test_Case_14_Tokens.txt","w+");
int k=i;
int flag=0;
char lexeme[100];
int line=0;
int linlen=0;
int lexlen=0;
char c;
int state=0;
for(i=0;i<=k;i++)
{
	line++;
	pos=0;
	while(s[i][pos]==' ')
		pos++;
	while(pos<strlen(s[i]))
	{

		c=getNextChar(s[i]);
	//	fprintf(fout,"%c",c);
	//	fprintf(fout," %d\n",state);
		switch(state)
		{
			case 0:
			{
				if(c=='P')
				state=1;
				else if(c=='s')
				state=104;
				else if(c=='N')
				state=147;
				else if(c=='E')
				state=2;
				else if(c=='e')
				state=65;
				else if(c=='p')
				state=94;
				else if(c==' ')
				state=0;
				else if(c=='S')
				state=161;
				else if(c=='I')
				state=191;
				else if(c=='B')
				state=198;
				else if(c=='D')
				state=184;
				else if(c=='T')
				state=118;
				else if(c=='w')
				state=131;
				else if(c=='m')
				state=136;
				else if(c=='F')
				state=122;
				else if(c=='a')
				state=155;
				else if(c=='i')
				state=63;
				else if(c=='L')
				state=127;
				else if(c=='G')
				state=3;
				else if(c=='C')
				state=108;
				else if(c=='%')
				{
					lookup("%",line,pos);
					state=0;
				}
				else if(c=='(')
				{
					lookup("(",line,pos);
					state=0;
				}
				else if(c==')')
				{
					lookup(")",line,pos);
					state=0;
				}
				else if(c=='[')
				{
					lookup("[",line,pos);
					state=0;
				}
				else if(c==']')
				{
					lookup("]",line,pos);
					state=0;
				}
				else if(c==':')
				{
					lookup(":",line,pos);
					state=0;
				}
				else if(c==',')
				{
					lookup(",",line,pos);
					state=0;
				}
				else if(c==';')
				{
					lookup(";",line,pos);
					state=0;
				}
				else if(c=='+')
				{
					lookup("+",line,pos);
					state=0;
				}
				else if(c=='-')
				{
					lookup("-",line,pos);
					state=0;
				}
				else if(c=='/')
				{
					lookup("/",line,pos);
					state=0;
				}
				else if(c=='*')
				{
					lookup("*",line,pos);
					state=0;
				}
				else if(c=='&')
				{
					lookup("&",line,pos);
					state=0;
				}
				else if(c=='|')
				{
					lookup("|",line,pos);
					state=0;
				}
				else if(c=='!')
				{
					lookup("!",line,pos);
					state=0;
				}
				else if(c=='#')
				{
					lookup("#",line,pos);
					state=0;
				}
				else if(c=='?')
				{
					lookup("?",line,pos);
					state=0;
				}
				else if(c=='=')
				{
					lookup("=",line,pos);
					state=0;
				}
				else if(c=='>')
					state=401;
				else if(c=='<')
					state=403;

				else if(c==' ')
				state=0;
				else if(c=='"')
				{
					lookup("\"",line,pos);
					state=303;
				}
				else if(c=='r')
				state=99;
				else if(isalpha(c))
				state=301;
				else if(isdigit(c))
				state=300;
				break;
			}
			case 401:
			{
				if(c=='=')
				{
					lookup(">=",line,pos);
					state=0;
				}
				else
				{
					lookup(">",line,pos);
					state=0;

				}
				break;
			}

			case 403:
			{
				if(c=='=')
				{
					lookup("<=",line,pos);
					state=0;
				}
				else
				{
					lookup("<",line,pos);
					state=0;

				}
				break;
			}
			case 303:
			{

				pos--;
				int k=pos;
				fprintf(fout,"STR ");
				while(s[i][pos]!='"')
				fprintf(fout,"%c",s[i][pos++]);
				fprintf(fout," %d %d\n",line,k);
				lookup("\"",line,pos);
				pos++;
				state=0;
				break;

			}
			case 300:
			{
				pos-=2;
				//fprintf(fout,"300 int is%c\n",s[i][pos++]);
				char s2[5];
				int p=0,flag=0,flagalph=0,count=0;
				while(isalpha(s[i][pos])||isdigit(s[i][pos])|| s[i][pos]=='.')
				{

					if(isalpha(s[i][pos]))
					{
						flagalph=1;
						break;
					}
					if(s[i][pos]=='.')
					{
					//	fprintf(fout,"Read decimal\n");
						flag=1;
						count++;
					}
					s2[p++]=s[i][pos++];
				}
				if(count>1)
				fprintf(fout,"Error %s at %d %d Number cannot have more than 1 decimal\n",s2,line,pos);
				else if(flag==0 && !flagalph)
					fprintf(fout,"INTR %s %d %d\n",s2,line,pos);
				else if(!flagalph)
					fprintf(fout,"DEC %s %d %d\n",s2,line,pos);
				memset(s2,'\0',strlen(s2));
				state=0;
				break;
			}

			case 301:
			{
				int j=pos-1;
				if(s[i][j-1]==' '||s[i][j-1]==',')
				j--;
				if(j==0)
				{
					i--;
					j=strlen(s[i])-2;
					line--;
				}
				while(!isalpha(s[i][j]))
				j--;
				while(s[i][j]-'0'>=0 && s[i][j]-'0'<=9)
				j--;

			//	fprintf(fout,"%c isdig=%d\n",s[i][j-1],isdigit(s[i][j-1]));
		//		fprintf(fout,"found at %c %d\n",s[i][pos-1],j);
				while(j!=-1 && s[i][j]!=' ' && (isalpha(s[i][j])||isdigit(s[i][j])))
				j--;
				pos=++j;
		//		fprintf(fout,"j=%d pos=%d\n",j,pos);
				//fprintf(fout,"Entered at %c\n",s[i][j]);
				char s2[30];
				int p=0;
				while(isalpha(s[i][j])||isdigit (s[i][j]))
				s2[p++]=s[i][j++];
				if(p>30)
				fprintf(fout,"Bad identifier at %d %d\n",line,pos);
				else if(s2[0]-'0'>=0 && s2[0]-'0'<=9)
				fprintf(fout,"Identifiers cannot start with integer %s\n",s2);
				else
				fprintf(fout,"IDEN %s %d %d\n",s2,line,pos);
				pos=j;
				memset(s2,'\0',sizeof(s2));
				state=0;
				break;
			}
			case 1:
			{
				if(c=='r')
				state=5;
				else
				state=301;
				break;
			}
			case 5:
			{
				if(c=='o')
				state=8;
				else
				state=301;
				break;
			}
			case 8:
			{
				if(c=='g')
				{
					//fprintf(fout,"%d %d\n",strlen(s[i]),pos);
					if(pos-1<strlen(s[i])-1 && s[i][pos]=='\n')
					{
						lookup("Prog",line,pos);
					state=0;
					}
					else
					state=301;
				}

				else
				state=301;
				break;
			}
			case 3:
			{
				if(c=='l')
				state=7;

				else
				state=301;
				break;
			}
			case 7:
			{
				if(c=='o')
				state=10;
				else
				state=301;
				break;
			}
			case 10:
			{
				if(c=='b')
				state=14;
				else
				state=301;
				break;
			}
			case 14:
			{
				if(c=='a')
				state=17;
				else
				state=301;
				break;

			}
			case 17:
			{
				if(c=='l')
				{
					if(pos-1<strlen(s[i])-1 && s[i][pos]=='\n')
					{
						lookup("Global",line,pos);
						state=0;
					}
					else
					state=301;

				}

				else
				state=301;
				break;
			}
			case 2:
			{
				if(c=='n')
				state=6;
				else
				state=301;
				break;
			}
			case 6:
			{
				if(c=='d')
				{
					if(s[i][pos]=='\n')
					{
						lookup("End",line,pos);
						state=0;
					}
					else
					state=9;
				}
				else
				state=301;
				break;
			}
			case 9:
			{
				if(c=='S')
				state=25;
				else if(c=='P')
				state=12;
				else if(c=='G')
				state=13;
				else if(c=='L')
				state=32;


				else
				state=301;
				break;
			}
			case 25:
			{
				if(c=='u')
				state=26;
				else
				state=301;
				break;
			}
			case 26:
			{
				if(c=='b')
				state=27;
				else
				state=301;
				break;
			}
			case 27:
			{
				if(c=='P')
				state=28;
				else
				state=301;
				break;
			}
			case 28:
			{
				if(c=='r')
				state=29;
				else
				state=301;
				break;
			}
			case 29:
			{
				if(c=='o')
				state=30;
				else
				state=301;
				break;
			}
			case 30:
			{
				if(c=='g')
				{
					if(s[i][pos]=='\n')
					{
						lookup("EndSubProg",line,pos);
						state=0;
					}
					else
					state=301;//Throw to ID
				}
				else
				state=301;
				break;
			}
			case 12:
			{
				if(c=='r')
				state=15;
				else
				state=301;
				break;
			}
			case 15:
			{
				if(c=='o')
				state=18;
				else
				state=301;
				break;
			}
			case 18:
			{
				if(c=='g')
				{
					if(pos==strlen(s[i])||pos==strlen(s[i])-1)
					{
						lookup("EndProg",line,pos);
						state=0;
					}
					else
					state=301; //throw to ID
				}
				else
				state=301;
				break;
			}
			case 13:
			{
				if(c=='l')
				state=16;
				else
				state=301;
				break;
			}
			case 16:
			{
				if(c=='o')
				state=19;
				else
				state=301;
				break;
			}
			case 19:
			{
				if(c=='b')
				state=22;
				else
				state=301;
				break;
			}
			case 22:
			{
				if(c=='a')
				state=23;
				else
				state=301;
				break;
			}
			case 23:
			{
				if(c=='l')
				{
					if(s[i][pos]=='\n')
					{
						lookup("EndGlobal",line,pos);
						state=0;
					}
					else
					state=301; //throw to id
				}
				else
				state=301;
				break;
			}
			case 136:
			{
				if(c=='u')
				state=137;
				else
				state=301;
				break;
			}
			case 137:
			{
				if(c=='l')
				state=138;
				else
				state=301;
				break;
			}
			case 138:
			{
				if(c=='t')
				state=139;
				else
				state=301;
				break;
			}
			case 139:
			{
				if(c=='i')
				state=140;
				else
				state=301;
				break;
			}
			case 140:
			{
				if(c=='p')
				state=141;
				else
				state=301;
				break;
			}
			case 141:
			{
				if(c=='l')
				state=142;
				else
				state=301;
				break;
			}
			case 142:
			{
				if(c=='e')
				{
					if(!isalpha(s[i][pos]) && !isdigit(s[i][pos]))
					{
						lookup("multiple",line,pos);
						state=0;
					}
					else
					state=301;
				}

				else
				state=301;
				break;
			}
			case 127:
			{
				if(c=='o')
				state=128;
				else
				state=301;
				break;
			}
			case 128:
			{
				if(c=='o')
				state=129;
				else
				state=301;
				break;
			}
			case 129:
			{
				if(c=='p')
				{
					//if(pos==strlen(s[i])-2)
					//{
						lookup("Loop",line,pos);
						state=0;
					//}
					//else
					//state=301;
				}
				else
				state=301;
				break;
			}
			case 131:
			{
				if(c=='h')
				state=132;
				else
				state=301;
				break;
			}
			case 132:
			{
				if(c=='i')
				state=133;
				else
				state=301;
				break;
			}
			case 133:
			{
				if(c=='l')
				state=134;
				else
				state=301;
				break;
			}
			case 134:
			{
				if(c=='e')
				{
					if(!isalpha(s[i][pos]))
					{
						lookup("while",line,pos);
						state=0;
					}
					else
					state=301;
				}
				else
				state=301;
				break;
			}
			case 65:
			{
				if(c=='l')
				state=66;
				else if(c=='n')
				state=71;
				else
				state=301;
				break;
			}
			case 66:
			{
				if(c=='s')
				state=67;
				else
				state=301;
				break;
			}
			case 67:
			{
				if(c=='e')
				{
					if(!isalpha(s[i][pos]))
					{
						lookup("else",line,pos);
						state=0;
					}
					else
					state=301;//throw to ID
				}
				else if (c=='i')
				state=69;
				else
				state=301;
				break;
			}
			case 147:
			{
				if(c=='a')
				state=148;
				else
				state=301;
				break;
			}
			case 148:
			{
				if(c=='m')
				state=149;
				else
				state=301;
				break;
			}
			case 149:
			{
				if(c=='e')
				state=150;
				else
				state=301;
				break;
			}
			case 150:
			{
				if(c=='_')
				state=151;
				else
				state=301;
				break;
			}
			case 151:
			{
				if(c=='E')
				state=152;
				else
				state=301;
				break;
			}
			case 152:
			{
				if(c=='q')
				state=153;
				else
				state=301;
				break;
			}
			case 153:
			{
				if(c=='u')
				{
					if(!isalpha(s[i][pos]))
					{
						fprintf(fout,"NAME_EQU %d %d\n",line,pos);
						state=0;
					}
					else
					state=301;
				}
				else
				state=301;
				break;

			}
			case 71:
			{
				if(c=='d')
				state=72;
				else
				state=301;
				break;
			}
			case 72:
			{
				if(c=='i')
				state=73;
				else
				state=301;
				break;
			}


			case 108:
			{
				if(c=='a')
				state=144;
				else if(c=='o')
				state=109;
				else if(c=='h')
				state=501;
				else
				state=301;
				break;
			}
			case 501:
			{
				if(c=='a')
				state=502;
				else
				state=301;
				break;
			}
			case 502:
			{
				if(c=='r')
				state=503;
				else
				state=301;
				break;
			}
			case 503:
			{
				if(c=='a')
				state=504;
				else
				state=301;
				break;
			}
			case 504:
			{
				if(c=='c')
				state=505;
				else
				state=301;
				break;
			}
			case 505:
			{
				if(c=='t')
				state=506;
				else
				state=301;
				break;
			}
			case 506:
			{
				if(c=='e')
				state=507;
				else
				state=301;
				break;
			}
			case 507:
			{
				if(c=='r')
				{
					if(s[i][pos]==' ')
					{
						lookup("Character",line,pos);
						state=0;
					}
					else
					state=301;
				}
				else
				state=301;
				break;
			}
			case 144:
			{
				if(c=='l')
				state=145;
				else
				state=301;
				break;
			}

			case 145:
			{
				if(c=='l')
				{
					if(s[i][pos]==' ')
					{
						lookup("Call",line,pos);
						state=0;
					}
					else
					state=301;
				}
				else
				state=301;
				break;
			}
			case 109:
			{
				if(c=='l')
				state=110;
				else
				state=301;
				break;
			}
			case 110:
			{
				if(c=='l')
				state=111;
				else
				state=301;
				break;
			}
			case 111:
			{
				if(c=='e')
				state=112;
				else
				state=301;
				break;
			}
			case 112:
			{
				if(c=='c')
				state=113;
				else
				state=301;
				break;
			}
			case 113:
			{
				if(c=='t')
				state=114;
				else
				state=301;
				break;
			}
			case 114:
			{
				if(c=='i')
				state=115;
				else
				state=301;
				break;
			}
			case 115:
			{
				if(c=='o')
				state=116;
				else
				state=301;
				break;
			}
			case 116:
			{
				if(c=='n')
				{
					if(s[i][pos]==' ')
					{
						lookup("Collection",line,pos);
						state=0;
					}
					else
					state=301;
				}
				else
				state=301;
				break;
			}
			case 69:
			{
				if(c=='f')
				{
					if(!isalpha(s[i][pos]))
					{
						lookup("elseif",line,pos);
						state=0;
					}
					else
					state=301;//throw to ID
				}
				else
				state=301;
				break;
			}
			case 73:
			{
				if(c=='f')
				{
					if(s[i][pos]=='\n')
					{
						lookup("Endif",line,pos);
						state=0;
					}
					else
					state=301; //throw to id
				}
				else if(c=='n')
				state=75;
				else
				state=301;
				break;
			}
			case 75:
			{
				if(c=='c')
				state=76;
				else
				state=301;
				break;
			}
			case 76:
			{
				if(c=='l')
				state=77;
				else
				state=301;
				break;
			}
			case 77:
			{
				if(c=='u')
				state=78;
				else
				state=301;
				break;
			}
			case 78:
			{
				if(c=='d')
				state=79;
				else
				state=301;
				break;
			}

			case 79:
			{
				if(c=='e')
				state=80;
				else
				state=301;
				break;
			}

			case 80:
			{
				if(c=='s')
				{
					if(pos==strlen(s[i])-2 || !isalpha(s[i][pos]))
					{
						lookup("endincludes",line,pos);
						state=0;
					}
					else
					state=301;
				}
				else
				state=301;
				break;
			}
			case 32:
			{
				if(c=='o')
				state=33;
				else
				state=301;
				break;
			}
			case 33:
			{
				if(c=='o')
				state=34;
				else
				state=301;
				break;
			}
			case 34:
			{
				if(c=='p')
				{
					if(s[i][pos]=='\n')
					{
						lookup("EndLoop",line,pos);
						state=0;
					}
					else
					state=301;//throw to ID
				}
				else
				state=301;
				break;
			}
			case 63:
			{
				if(c=='n')
				state=87;
				else if(c=='f')
				{
					if(!isalpha(s[i][pos]))
					{
						lookup("if",line,pos);
						state=0;
					}
					else
					state=301;
				}
				else
				state=301;
				break;
			}
			case 94:
			{
				if(c=='r')
				state=95;
				else
				state=301;
				break;
			}
			case 95:
			{
				if(c=='i')
				state=96;
				else
				state=301;
				break;
			}
			case 96:
			{
				if(c=='n')
				state=97;
				else
				state=301;
				break;
			}
			case 97:
			{
				if(c=='t')
				{
					if(!isalpha(s[i][pos]))
					{
						lookup("print",line,pos);
						state=0;
					}
					else
					state=301;//throw to Id
				}
				else
				state=301;
				break;
			}
			case 99:
			{
				if(c=='e')
				state=100;
				else
				state=301;
				break;
			}
			case 100:
			{
				if(c=='t')
				state=101;
				else
				state=301;
				break;
			}
			case 101:
			{
				if(c=='u')
				state=102;
				else
				state=301;
				break;
			}
			case 102:
			{
				if(c=='r')
				state=103;
				else
				state=301;
				break;
			}
			case 103:
			{
				if(c=='n')
				{
					if(!isalpha(s[i][pos]))
					{
						lookup("return",line,pos);
						state=0;
					}

					else
					state=301;
				}
				else
				state=301;
				break;
			}

			case 87:
			{
				if(c=='c')
				state=88;
				else
				state=301;
				break;
			}
			case 88:
			{
				if(c=='l')
				state=89;
				else
				state=301;
				break;
			}
			case 89:
			{
				if(c=='u')
				state=90;
				else
				state=301;
				break;
			}
			case 90:
			{
				if(c=='d')
				state=91;
				else
				state=301;
				break;
			}
			case 91:
			{
				if(c=='e')
				state=92;
				else
				state=301;
				break;
			}
			case 92:
			{
				if(c=='s')
				{
					if(s[i][pos]=='\n')
					{
						lookup("includes",line,pos);
						state=0;
					}
					else
					state=301;
				}
				else
				state=301;
				break;
			}
			case 104:
			{
				if(c=='c')
				state=105;
				else
				state=301;
				break;
			}
			case 105:
			{
				if(c=='a')
				state=106;
				else
				state=301;
				break;
			}
			case 106:
			{
				if(c=='n')
				{
					if(!isalpha(s[i][pos]))
					{
						lookup("scan",line,pos);
						state=0;
					}
					else
					state=0;
				}
				else
				state=301;
				break;
			}
			case 161:
			{
				if(c=='u')
				state=162;
				else if(c=='t')
				state=167;
				else
				state=301;
				break;
			}
			case 167:
			{
				if(c=='r')
				state=168;
				else
				state=301;
				break;
			}
			case 168:
			{
				if(c=='u')
				state=169;
				else if(c=='i')
				state=181;
				else
				state=301;
				break;
			}
			case 169:
			{
				if(c=='c')
				state=170;
				else
				state=301;
				break;
			}
			case 170:
			{
				if(c=='t')
				state=171;
				else
				state=301;
				break;
			}
			case 171:
			{
				if(c=='_')
				state=172;
				else
				state=301;
				break;
			}
			case 172:
			{
				if(c=='E')
				state=173;
				else
				state=301;
				break;
			}
			case 173:
			{
				if(c=='q')
				state=174;
				else
				state=301;
				break;
			}
			case 174:
			{
				if(c=='u')
				{
					if(!isalpha(s[i][pos]))
					{
						fprintf(fout,"STRUCT_EQU %d %d\n",line,pos);
						state=0;
					}
					else
					state=301;
				}
				else
				state=301;
				break;
			}
			case 181:
			{
				if(c=='n')
				state=182;
				else
				state=301;
				break;
			}
			case 182:
			{
				if(c=='g')
				{
					if(!isalpha(s[i][pos]))
					{
						fprintf(fout,"STRING %d %d\n",line,pos);
						state=0;
					}
					else
					state=301;
				}
				else
				state=301;
				break;
			}

			case 162:
			{
				if(c=='b')
				state=163;
				else
				state=301;
				break;
			}
			case 163:
			{
				if(c=='P')
				state=164;
				else
				state=301;
				break;
			}
			case 164:
			{
				if(c=='r')
				state=165;
				else
				state=301;
				break;
			}
			case 165:
			{
				if(c=='o')
				state=166;
				else
				state=301;
				break;
			}
			case 166:
			{
				if(c=='g')
				{
					if(s[i][pos]=='\n' || s[i][pos]==' ')
					{
						lookup("SubProg",line,pos);
						state=0;
					}
					else
					state=301; //throw to ID
				}
				else
				state=301;
				break;
			}
			case 184:
			{
				if(c=='e')
				state=185;
				else

				state=301;
				break;
			}
			case 185:
			{
				if(c=='c')
				state=186;
				else

				state=301;
				break;
			}
			case 186:
			{
				if(c=='i')
				state=187;
				else

				state=301;
				break;
			}
			case 187:
			{
				if(c=='m')
				state=188;
				else

				state=301;
				break;
			}
			case 188:
			{
				if(c=='a')
				state=189;
				else

				state=301;
				break;
			}
			case 189:
			{
				if(c=='l')
				{
					if(s[i][pos]==' ')
					{
						lookup("Decimal",line,pos);
						state=0;
					}
					else
					state=301; //Throw to ID'
				}
				else
				state=301;
				break;
			}
			case 191:
			{
				if(c=='n')
				state=192;
				else

				state=301;
				break;
			}
			case 192:
			{
				if(c=='t')
				state=193;
				else

				state=301;
				break;
			}
			case 193:
			{
				if(c=='e')
				state=194;
				else

				state=301;
				break;
			}
			case 194:
			{
				if(c=='g')
				state=195;
				else

				state=301;
				break;
			}
			case 195:
			{
				if(c=='e')
				state=196;
				else

				state=301;
				break;
			}
			case 196:
			{
				if(c=='r')
				{
					if(s[i][pos]==' '||!isalpha(s[i][pos]))
					{
						lookup("Integer",line,pos);
						state=0;
					}
					else
					state=301; //Throw to ID'
				}
				else
				state=301;
				break;
			}
			case 198:
			{
				if(c=='o')
				state=199;
				else if(c=='e')
				state=83;
				else

				state=301;
				break;
			}
			case 199:
			{
				if(c=='o')
				state=200;
				else

				state=301;
				break;
			}
			case 200:
			{
				if(c=='l')
				state=201;
				else

				state=301;
				break;
			}
			case 201:
			{
				if(c=='e')
				state=202;
				else

				state=301;
				break;
			}
			case 202:
			{
				if(c=='a')
				state=203;
				else

				state=301;
				break;
			}
			case 203:
			{
				if(c=='n')
				{
					if(s[i][pos]==' ')
					{
						lookup("Boolean",line,pos);
						state=0;
					}
					else
					state=301; //Throw to ID'
				}
				else
				state=301;
				break;
			}
			case 118:
			{
				if(c=='R')
				state=119;
				else
				state=301;
				break;
			}
			case 119:
			{
				if(c=='U')
				state=120;
				else
				state=301;
				break;
			}
			case 120:
			{
				if(c=='E')
				{
					//fprintf(fout,"%d %d\n",strlen(s[i]),pos);
					if(!isalpha(s[i][pos]))
					lookup("TRUE",line,pos);
					state=0;
				}

				else
				state=301;
				break;
			}
			case 122:
			{
				if(c=='A')
				state=123;
				else
				state=301;
				break;
			}
			case 123:
			{
				if(c=='L')
				state=124;
				else
				state=301;
				break;
			}
			case 124:
			{
				if(c=='S')
				state=125;
				else
				state=301;
				break;
			}
			case 125:
			{
				if(c=='E')
				{
					//fprintf(fout,"%d %d\n",strlen(s[i]),pos);
					if(!isalpha(s[i][pos]))
					lookup("FALSE",line,pos);
					state=0;
				}

				else
				state=301;
				break;
			}
			case 155:
			{
				if(c=='s')
				{
					if(s[i][pos]==' ')
					{
						state=0;
						lookup("as",line,pos);
					}
					else
					state=156;
				}

				else
				state=301;
				break;
			}
			case 156:
			{
				if(c=='s')
				state=157;
				else

				state=301;
				break;
			}
			case 157:
			{
				if(c=='i')
				state=158;
				else

				state=301;
				break;
			}
			case 158:
			{
				if(c=='g')
				state=159;
				else

				state=301;
				break;
			}

			case 159:
			{
				if(c=='n')
				{
					if(s[i][pos]==' ')
					{
						lookup("assign",line,pos);
						state=0;
					}
					else
					state=301; //Throw to ID'
				}
				else
				state=301;
				break;
			}
			case 83:
			{
				if(c=='g')
				state=84;
				else
				state=301;
				break;
			}
			case 84:
			{
				if(c=='i')
				state=85;
				else
				state=301;
				break;
			}
			case 85:
			{
				if(c=='n')
				{
					//fprintf(fout,"%d %d\n",strlen(s[i]),pos);
					if(s[i][pos]==' '||s[i][pos]=='\n')
					lookup("Begin",line,pos);
					state=0;
				}

				else
				state=301;
				break;
			}
		}

	}
}
fclose(fout);
return 0;
}
