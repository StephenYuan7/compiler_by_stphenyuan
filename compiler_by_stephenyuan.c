#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_LEN 2048
//关键字0-31
char keywords[32][20] = { "auto","break","case","char","const","continue",
"default","do","double","else","enum","extern","float","for","goto",
"if","int","long ","register","return","short","signed","static",
"sizeof","struct","switch","typedef","unionunsigned","void","volatile","while "};
//分割符40-79
char delimiters[40][5] = { "=","+","*","**",";","(",")","{","}","<",
"?","^","%",",",";","[","]",">","#",".","-","!",
"<=","<>",">=","==","++","+=","--",
"-=","*=","/=","//","!=", "||","&&"};
//标识符表80-109
char id[30][10] = { "" };
//整数表110-159
int digitals[50] = { 0 };
//小数表160-209
double my_double[50] = { 0 };
//记录各类单词数量
int my_count[300] = { 0 };
//记录行数
int line_count = 1;
//记录单词数量
int word_count = 0;

int skip_space(char buffer[], int char_count);//跳过空格和制表符
int judge_first_case0(char x);//判断第一个字符以转到后续状态
int letter(char x);//判断是否为字符
int digit(char x);//判断是否为数字
int my_id(char buffer[]);//判断是否为分割符
int my_reserve(char buffer[]);//判断是否为保留字
int my_table_insert(char buffer[]);//返回符号表入口
int my_digit_insert(char buffer[]);//返回整数表入口
int my_double_insert(char buffer[]);//返回小数表入口


int main() {
	//打开读取测试用例与结果保存文件
	FILE* test;
	char buffer[BUFFER_LEN];
	test = fopen("test5.txt", "r");

	char one_char;
	int char_count = 0;
	while ((one_char = fgetc(test)) != EOF)
	{
		buffer[char_count++] = one_char;
	}
	buffer[char_count] = '\0';
	printf("this is test.txt:\n%s", buffer);


	int state = 0;
	int lexemebegin = 0,forword = 0;//开始指针与向前指针
	char strtoken[100];//暂存单词
	int token_count = 0;//暂存区指针
	char str_buffer[BUFFER_LEN];
	strcpy(str_buffer, buffer);
	printf("\n\nthis is line %d:\n", line_count);
	do
	{
		switch (state)
		{
		case 0:
			lexemebegin = skip_space(buffer, lexemebegin);
			forword = lexemebegin;
			one_char = str_buffer[lexemebegin];
			state = judge_first_case0(one_char);
			break;
		case 1:
			strtoken[token_count++] = one_char;
			forword ++;
			one_char = str_buffer[forword];
			if (digit(one_char)||letter(one_char)||one_char=='_')
			{
				state = 1;
			}
			else
			{
				strtoken[token_count] = '\0';//字符串加上终止符
				token_count = 0;
				forword--;
				state = 0;
				int iskey = my_reserve(strtoken);
				if (iskey)//是关键字
				{
					lexemebegin = forword + 1;
					printf("%s  %d\n", strtoken,iskey);
					my_count[iskey]++;
					word_count++;
				}
				else
				{
					int identity = my_table_insert(strtoken);
					printf("%s  %d\n", strtoken, identity);
					my_count[identity]++;
					word_count++;
					lexemebegin = forword + 1;
				}
			}
			break;
		case 2:
			strtoken[token_count++] = one_char;
			forword++;
			one_char = str_buffer[forword];
			if (digit(one_char))
			{
				state = 2;
			}
			else
			{
				switch (one_char)
				{
				case '.':state = 3; break;
				case 'E':state = 5; break;
				default:
					strtoken[token_count] = '\0';//字符串加上终止符
					token_count = 0;
					forword--;
					state = 0;
					int identity = my_digit_insert(strtoken);
					printf("%s  %d\n", strtoken, identity);
					my_count[identity]++;
					word_count++;
					lexemebegin = forword + 1;
					break;
				}
			}
			break;
		case 3:
			strtoken[token_count++] = one_char;
			forword++;
			one_char = str_buffer[forword];
			if (digit(one_char))
			{
				state = 4;
			}
			else
			{
				lexemebegin = forword + 1;
				state = 0;
				printf("error in line %d:\n", line_count);
			}
			break;
		case 4:
			strtoken[token_count++] = one_char;
			forword++;
			one_char = str_buffer[forword];
			if (digit(one_char))
			{
				state = 4;
			}
			else
			{
				if (one_char == 'E')
				{
					state = 5;
				}
				else
				{
					strtoken[token_count] = '\0';//字符串加上终止符
					token_count = 0;
					forword--;
					state = 0;
					int identity = my_double_insert(strtoken);
					printf("%s  %d\n", strtoken, identity);
					my_count[identity]++;
					word_count++;
					lexemebegin = forword + 1;
					break;
				}
			}
			break;
		case 5:
			strtoken[token_count++] = one_char;
			forword++;
			one_char = str_buffer[forword];
			if (digit(one_char))
			{
				state = 7;
			}
			else
			{
				if (one_char == '+' || one_char == '-')
				{
					state = 6;
				}
				else
				{
					lexemebegin = forword + 1;
					state = 0;
					printf("error in line %d:\n", line_count);
				}
				break;
			}
		case 6:
			strtoken[token_count++] = one_char;
			forword++;
			one_char = str_buffer[forword];
			if (digit(one_char))
			{
				state = 7;
			}
			else
			{
				lexemebegin = forword + 1;
				state = 0;
				printf("error in line %d:\n", line_count);
			}
			break;
		case 7:
			strtoken[token_count++] = one_char;
			forword++;
			one_char = str_buffer[forword];
			if (digit(one_char))
			{
				state = 7;
			}
			else
			{
				strtoken[token_count] = '\0';//字符串加上终止符
				token_count = 0;
				forword--;
				state = 0;
				int identity = my_table_insert(strtoken);
				printf("%s  %d\n", strtoken, identity);
				my_count[identity]++;
				word_count++;
				lexemebegin = forword + 1;
				break;
			}
			break;
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 17:
		case 20:
		case 21:
		case 22:
		case 24:
			strtoken[token_count++] = one_char;
			forword++;
			one_char = str_buffer[forword];
			strtoken[token_count++] = one_char;
			strtoken[token_count] = '\0';//字符串加上终止符
			token_count = 0;
			state = 0;
			int isid = my_id(strtoken);
			if (isid)//是双分割符
			{
				lexemebegin = forword + 1;
				printf("%s  %d\n", strtoken, isid);
				my_count[isid]++;
				word_count++;
			}
			else
			{
				//单分割符
				strtoken[1] = '\0';
				isid = my_id(strtoken);
				if (isid)
				{
					lexemebegin = forword;
					printf("%s  %d\n", strtoken, isid);
					my_count[isid]++;
					word_count++;
				}
				else
				{
					lexemebegin = forword + 1;
					state = 0;
					printf("error in line %d:\n", line_count);
				}
			}
			break;
		case 14:
			strtoken[token_count++] = one_char;
			forword++;
			one_char = str_buffer[forword];
			if (one_char == '=')
			{
				strtoken[token_count] = '\0';//字符串加上终止符
				token_count = 0;
				state = 0;
				int isid = my_id(strtoken);
				if (isid)//是分割符
				{
					lexemebegin = forword + 1;
					printf("%s  %d\n", strtoken, isid);
					my_count[isid]++;
					word_count++;
				}
			}
			else
			{
				if (one_char == '/')
				{
					state = 15;
					break;
				}
				else
				{
					if (one_char == '*')
					{
						state = 16;
						break;
					}
					else //仅为除号
					{
						strtoken[1] = '\0';
						int isid = my_id(strtoken);
						token_count = 0;
						state = 0;
						if (isid)
						{
							lexemebegin = forword;
							printf("%s  %d\n", strtoken, isid);
							my_count[isid]++;
							word_count++;
						}
					}
				}
			}
		// 判断//注释
		case 15:
			strtoken[token_count++] = one_char;
			forword++;
			one_char = str_buffer[forword];
			while (one_char!='\n')
			{
				strtoken[token_count++] = one_char;
				forword++;
				one_char = str_buffer[forword];
			}
			strtoken[token_count] = '\0';//字符串加上终止符
			printf("annotation:  %s\n", strtoken);
			token_count = 0;
			state = 0;
			lexemebegin = forword;
			break;
		// 判断/*注释
		case 16:
			strtoken[token_count++] = one_char;
			forword++;
			one_char = str_buffer[forword];
			while (one_char != '\0')
			{
				if (one_char=='*')
				{
					strtoken[token_count++] = one_char;
					forword++;
					one_char = str_buffer[forword];
					if (one_char=='/')
					{
						strtoken[token_count++] = one_char;
						break;
					}
				}
				else
				{
					if (one_char == '\n')
					{
						line_count++;
						printf("\n\nthis is line %d:\n", line_count);
					}
					strtoken[token_count++] = one_char;
					forword++;
					one_char = str_buffer[forword];
				}
			}
			strtoken[token_count] = '\0';//字符串加上终止符
			printf("annotation:  %s\n", strtoken);
			token_count = 0;
			state = 0;
			lexemebegin = forword + 1;
			break;
		//判断双引号
		case 19:
			strtoken[token_count++] = one_char;
			forword++;
			one_char = str_buffer[forword];
			while (one_char != '"')
			{
				strtoken[token_count++] = one_char;
				forword++;
				one_char = str_buffer[forword];
			}
			strtoken[token_count++] = one_char;
			strtoken[token_count] = '\0';//字符串加上终止符
			token_count = 0;
			state = 0;
			int identity = my_table_insert(strtoken);
			printf("%s  %d\n", strtoken, identity);
			my_count[identity]++;
			word_count++;
			lexemebegin = forword + 1;
			break;
		case 23:
			strtoken[token_count++] = one_char;
			forword++;
			one_char = str_buffer[forword];
			while (one_char != '\'')
			{
				strtoken[token_count++] = one_char;
				forword++;
				one_char = str_buffer[forword];
			}
			strtoken[token_count++] = one_char;
			strtoken[token_count] = '\0';//字符串加上终止符
			token_count = 0;
			state = 0;
			identity = my_table_insert(strtoken);
			printf("%s  %d\n", strtoken, identity);
			my_count[identity]++;
			word_count++;
			lexemebegin = forword + 1;
			break;
		default:
			if (one_char != '\n')
			{
				printf("error in line %d:\n", line_count);
			}			
			state = 0;
			lexemebegin++;
			break;
		}
	} while (one_char != '\0');
	printf("\nthis is statistics:\nword   count\n\n\n");
	word_count = 0;
	for (int i = 0; i < 32; i++)
	{
		if (my_count[i + 1] > 0)
		{
			printf("%s    %d\n", keywords[i], my_count[i + 1]);
			word_count = word_count + my_count[i + 1];
		}
	}
	for (int i = 0; i < 40; i++)
	{
		if (my_count[i + 40] > 0)
		{
			printf("%s    %d\n", delimiters[i], my_count[i + 40]);
			word_count = word_count + my_count[i + 40];
		}
	}
	for (int i = 0; i < 30; i++)
	{
		if (my_count[i + 80] > 0)
		{
			printf("%s    %d\n", id[i], my_count[i + 80]);
			word_count = word_count + my_count[i + 80];
		}
	}
	for (int i = 0; i < 50; i++)
	{
		if (my_count[i + 110] > 0)
		{
			printf("%d    %d\n", digitals[i], my_count[i + 110]);
			word_count = word_count + my_count[i + 110];
		}
	}
	for (int i = 0; i < 50; i++)
	{
		if (my_count[i + 160] > 0)
		{
			printf("%llf    %d\n", my_double[i], my_count[i + 160]);
			word_count = word_count + my_count[i + 160];
		}
	}
	printf("total:%d", word_count);
	return 0;
}

int skip_space(char buffer[], int char_count)
{
	int temp_count = char_count;
	while (buffer[temp_count] == ' ' || buffer[temp_count] == '\t')
	{
		temp_count++;
	}
	return temp_count;
}

int judge_first_case0(char x)
{
	if (x == '\n')
	{
		line_count++;
		printf("\n\nthis is line %d:\n", line_count);
	}
	int r;//返回值
	if (letter(x))
	{
		r = 1;
	}
	else
	{
		if (digit(x))
		{
			r = 2;
		}
		else
		{
			switch (x)
			{
			case '<':r = 8; break;
			case '>':r = 9; break;
			case '=':r = 10; break;
			case '+':r = 11; break;
			case '-':r = 12; break;
			case '*':r = 13; break;
			case '/':r = 14; break;
			case '!':r = 17; break;
			case '"':r = 19; break;
			case '|':r = 20; break;
			case '&':r = 21; break;
			case '#':r = 22; break;
			case '\'':r = 23; break;
			case '?':case '^':case '%':case '(':case ')':
			case '[':case ']':case '{':case '}':case ',':
			case ';':case '~':case '.':r = 24; break;
			default:
				r = 25;
				break;
			}
		}
	}
	return r;
}

int letter(char x)
{
	int r = 0;
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
	{
		r = 1;
	}
	return r;
}

int digit(char x)
{
	int r = 0;
	if (x >= '0' && x <= '9')
	{
		r = 1;
	}
	return r;
}

int my_id(char buffer[])
{
	for (int i = 0; i < 40; i++)
	{
		if (strcmp(delimiters[i], buffer) == 0) {
			return i + 40;     //若是分割符字，则返回它的类别码 
		}
	}
	return 0;
}

int my_reserve(char buffer[])
{
	for (int i = 0; i < 32; i++)
	{
		if (strcmp(keywords[i], buffer) == 0) {
			return i + 1;     //若是保留字，则返回它的类别码 
		}
	}
	return 0;
}

int my_table_insert(char buffer[])
{
	for (int  i = 0; i < 30; i++)
	{
		if (strcmp(id[i], buffer) == 0) {
			return i + 80;     //若在符号表中，则返回它的类别码 
		}
		else
		{
			if (strlen(id[i]) == 0)
			{
				for (int j = 0; j < strlen(buffer); j++)
				{
					id[i][j] = buffer[j];
				}
				return i + 80;
			}
		}
	}
	return 0;
}

int my_digit_insert(char buffer[])
{
	int x = atoi(buffer);
	if (x == 0)
	{
		return 110;
	}
	for (int i = 1; i < 50; i++)
	{
		if (x == digitals[i]) {
			return i + 110;     //若在整数表中，则返回它的类别码 
		}
		else
		{
			if (digitals[i] == 0)
			{
				digitals[i] = x; //添加到整数表
				return i + 110;     
			}
		}
	}
	return 0;
}

int my_double_insert(char buffer[])
{
	double x = atof(buffer);
	for (int i = 0; i < 50; i++)
	{
		if (x == my_double[i]) {
			return i + 160;     //若在小数表中，则返回它的类别码 
		}
		else
		{
			if (my_double[i] == 0)
			{
				my_double[i] = x; //添加到小数表
				return i + 160;
			}
		}
	}
	return -1;
}
