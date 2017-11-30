#pragma warning(disable:4996) //VS 编译声明？

#include<functions.h>

int main()
{
	//初始模糊字段
	char* src_str = NULL;
	//文本地址
	char* tgt_str = NULL;
	//模糊类型 0->* 1->? -1->no blur
	int stat = 0;
	printf("##### program initiating #####\n");

	input_info(&src_str, &tgt_str);
	str_stat(src_str, &stat);
	printf("模糊字段:%s\n文本地址:%s\n模糊类型:%d\n", src_str, tgt_str,stat);
	
	FILE* fp;
	fp = open_file(tgt_str);

	read_word(fp, src_str,stat);

	fclose(fp);

	printf("##### running complete #####\n");
	system("pause");
	return 0;
}

FILE *open_file(char *filename)
{
	FILE *fp;
	if ((fp = fopen(filename, "r")) == NULL)
	{
		printf("Open failure....\n");
		exit(1);
	}
	return fp;
}

void input_info(char** text_str, char** addr_str)
{
	printf("输入模糊字段\n");
	*text_str = get_str();

	printf("输入文本地址\n"); 
	*addr_str = get_str();
}

void str_stat(char* src_str,int* stat)
{
	int i = 0;
	for (i = 0; src_str[i] != '\0'; i++)
	{
		if (src_str[i] == '*')
		{
			*stat = 0;
			break;
		}
		else if (src_str[i] == '?')
		{
			*stat = 1;
			break;
		}
		else
			*stat = -1;
	}
}

char* get_str(void)											
{
	char *str=NULL;
	int j = 1;

	str = (char*)malloc(sizeof(char)*(j + 1));
	if (NULL == str)
	{
		exit(1);
	}

	while ((str[j-1] = getchar()) != '\n')
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

void read_word(FILE* fp,char* src_str,int stat)
{
	char *token;
	char ch;
	char seps = " ,.:\t\n\"\'";
	char temp[MAX_LINE+1];
	int i = 0;

	while (ch=fgetc(fp)!= EOF)
	{	
		fp--;
		fgets(temp, MAX_LINE, fp);					//报错！！！！！
		token = strtok(temp, seps);
		while (token != NULL)
		{
			printf("%s\n", token);

			if (stat == 1)
			{
				for (i = 0; src_str[i] != '?'; i++);
				ch = token[i];
				token[i] = '?';
				if (strcmp(src_str, token))
				{
					token[i] = ch;
					printf("positive:%s\n", token);
				}
			}
			else if (stat == -1)
			{
				if (strcmp(src_str, token))
				{
					printf("positive:%s\n", token);
				}
			}
			else if (stat == 0)
			{

			}
			token = strtok(NULL, seps);
		}
	}
}