#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define BUFFER_LEN 2048
//�ؼ���
char keywords[32][32] = { "auto","break","case","char","const","continue",
"default","do","double","else","enum","extern","float","for","goto",
"if","int","long ","register","return","short","signed","static",
"sizeof","struct","switch","typedef","unionunsigned","void","volatile","while "};

int skip_space(char buffer[], int char_count);//�����ո���Ʊ��
int judge_first_case0(char x);//�жϵ�һ���ַ���ת������״̬
int letter(char x);//�ж��Ƿ�Ϊ�ַ�
int digit(char x);//�ж��Ƿ�Ϊ����
int my_reserve(char buffer[]);//�ж��Ƿ�Ϊ������


int main() {
	//�򿪶�ȡ�����������������ļ�
	FILE* test, * file_result;
	char buffer[BUFFER_LEN];
	test = fopen("test1.txt", "r");
	file_result = fopen("compiler_result.txt", "w");
	char one_char;
	int char_count = 0;
	while ((one_char = fgetc(test)) != EOF)
	{
		buffer[char_count++] = one_char;
	}
	buffer[char_count] = '\0';
	printf("this is test.txt:\n%s", buffer);
	fprintf(file_result, "this is test.txt:\n%s", buffer);

	int state = 0;
	int lexemebegin = 0,forword = 0;//��ʼָ������ǰָ��
	char strtoken[100];//�ݴ浥��
	int token_count = 0;//�ݴ���ָ��
	char str_buffer[BUFFER_LEN];
	strcpy(str_buffer, buffer);
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
			if (digit(one_char)||letter(one_char))
			{
				state = 1;
			}
			else
			{
				strtoken[token_count] = '\0';//�ַ���������ֹ��
				token_count = 0;
				forword--;
				state = 0;
				int iskey = my_reserve(strtoken);
				if (iskey)//�ǹؼ���
				{
					lexemebegin = forword + 1;
					printf("%s  %d\n", strtoken,iskey);
				}
				lexemebegin = forword + 1;
			}
			break;
		default:
			state = 0;
			lexemebegin++;
			break;
		}
	} while (one_char != '\0');
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
	int r;//����ֵ
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
			case ';':case '~':r = 24; break;
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

int my_reserve(char buffer[])
{
	for (int i = 0; i < 32; i++)
	{
		if (strcmp(keywords[i], buffer) == 0) {
			return i + 1;     //���Ǳ����֣��򷵻���������� 
		}
	}
	return 0;
}
