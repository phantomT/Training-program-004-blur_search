#pragma warning(disable:4996) //VS 编译声明？

#include<functions.h>

int main()
{
	char* src_str = NULL;
	char* tgt_str = NULL;
	printf("##### program initiating #####\n");

	input_info(&src_str, &tgt_str);
	printf("模糊字段:%s\n文本地址:%s\n", src_str, tgt_str);

	

	return 0;
}

void blur_search(char* src_str,char* tgt_str)
{

}

void input_info(char** text_str, char** addr_str)
{
	printf("输入模糊字段\n");
	*text_str = get_str();

	printf("输入文本地址\n"); 
	*addr_str = get_str();
}

char* get_str(void)											
{
	char *str;
	int j = 1;

	str = (char*)malloc(sizeof(char)*(j + 1));
	if (NULL == str)
	{
		exit(1);
	}

	while ((str[j - 1] = getchar()) != '\n')
	{
		j++;
		str = (char*)realloc(str, j);
		if (NULL == str)
		{
			exit(1);
		}
	}
	str[j - 1] = '\0';

	return(str);
}