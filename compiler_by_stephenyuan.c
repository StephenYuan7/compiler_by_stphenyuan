#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#define BUFFER_LEN 2048

int skip_space(char buffer[],int char_count);//跳过空格和制表符
int judge_first_case0(char x);//判断第一个字符以转到后续状态
int main() {
	//打开读取测试用例与结果保存文件
	FILE* test, * file_result;
	char buffer[BUFFER_LEN];
	test = fopen("test1.txt", "r");
	file_result = fopen("compiler_result.txt", "w");
	char one_char;
	int char_count = 0;
	while ((one_char=fgetc(test))!=EOF)
	{
		buffer[char_count++] = one_char;
	}
	buffer[char_count] = '\0';
	printf("this is test.txt:\n%s", buffer);
	fprintf(file_result, "this is test.txt:\n%s", buffer);

	int state = 0;
	char_count = 0;
	do
	{
		switch (state)
		{
		case 0:
			char_count = skip_space(buffer, char_count);
			one_char = buffer[char_count];
			state = judge_first_case0(one_char);
			break;
		default:
			break;
		}
	} while (one_char!='\0');
	return 0;
}

int skip_space(char buffer[], int char_count)
{
	int temp_count = char_count;
	while (buffer[temp_count]==' ' || buffer[temp_count]=='\t')
	{
		temp_count++;
	}
	return temp_count;
}

int judge_first_case0(char x)
{
	int r;//返回值
	if ((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
	{
		r = 1;
	}
	else
	{
		if (x >= '0' && x <= '9')
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
			case ';':case '~':r = 24; break;
			default:
				r = 25;
				break;
			}
		}
	}
	return r;
}
