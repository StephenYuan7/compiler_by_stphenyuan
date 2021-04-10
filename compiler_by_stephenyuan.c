#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#define BUFFER_LEN 2048

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
	return 0;
}