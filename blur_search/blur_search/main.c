#pragma warning(disable:4996) //VS 编译声明？

#include<functions.h>

int main()
{
	//初始模糊字段
	char* src_str = NULL;
	//文本地址
	char* tgt_str = NULL;
	printf("##### program initiating #####\n");

	input_info(&src_str, &tgt_str);
	printf("模糊字段:%s\n文本地址:%s\n", src_str, tgt_str);
	
	FILE *fp;
	if ((fp = fopen(tgt_str, "r")) == NULL)
	{
		printf("Open failure....\n");
		exit(1);
	}

	read_word(fp, src_str);

	fclose(fp);

	printf("##### running complete #####\n");
	system("pause");
	return 0;
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

void read_word(FILE* fp,char* src_str)
{
	char *token;
	const char seps[9] = " ,.:\t\n\"\'";
	char temp[MAX_LINE+1];
	int i = 0;
	bool answer;

	while (fgets(temp, MAX_LINE, fp)!=NULL)
	{	
		//fgets(temp, MAX_LINE, fp);
		token = strtok(temp, seps);
		while (token != NULL)
		{
			//printf("%s\n", token);
			answer = match(token, src_str);
			if (answer == true)
				printf("true:%s\n", token);
			token = strtok(NULL, seps);
		}
	}
}

bool match(char* str1, char* pattern)
{
	if (str1 == NULL)		//待匹配字符串指向空，返回false
		return false;
	if (pattern == NULL)		//模式字符串指向空，返回false
		return false;
	int len1 = strlen(str1);		//待匹配字符串的长度
	int len2 = strlen(pattern);			//模式字符串的长度
	int mark = 0;		//用于分段标记,'*'分隔的字符串
	int p1 = 0, p2 = 0;		//待匹配/模式的偏移量
	int flag_s = 0, flag_q = 0;			//如果出现* 和？则标识置位

	while ((p1<len1) && (p2<len2))			//在长度范围内运行
	{
		if (pattern[p2] == '?')			//如果模式中有‘？’通配符，则：同时偏移1，并进入下一循环
		{
			flag_q = 1;
			p1++;
			p2++;
			continue;
		}
		if (pattern[p2] == '*')//如果当前是*号，则mark前面一部分已经获得匹配，//从当前点开始继续下一个块的匹配
		{
			flag_s = 1;
			p2++;
			mark = p2;
			continue;
		}
		if (str1[p1] != pattern[p2])
		{
			if (p1 == 0 && p2 == 0)
			{
				//如果是首字符，特殊处理，不相同即匹配失败
				return false;
			}
			if (flag_s == 1)
			{
				p1 -= p2 - mark - 1;
				p2 = mark;
				continue;
			}
			else
			{
				return false;
			}
			
		}
		//此处处理相等的情况
		p1++;
		p2++;
	}
	if (p2 == len2)
	{
		if (p1 == len1)
		{
			//两个字符串都结束了，说明模式匹配成功
			return true;
		}
		if (pattern[p2 - 1] == '*')
		{
			//str1还没有结束，但pattern的最后一个字符是*，所以匹配成功
			return true;
		}
		else
		{
			return false;
		}
	}
	while (p2<len2)
	{
		//pattern多出的字符只要有一个不是*,匹配失败
		if (pattern[p2] != '*')
			return false;
		p2++;
	}
	if ((len2 != len1) && (flag_s == 0))			//如果没有出现*但是长度不一致则返回false
	{
		return false;
	}
	return true;
}