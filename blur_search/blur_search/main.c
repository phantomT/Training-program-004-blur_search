#pragma warning(disable:4996) //VS ����������

#include<functions.h>

int main()
{
	//��ʼģ���ֶ�
	char* src_str = NULL;
	//�ı���ַ
	char* tgt_str = NULL;
	printf("##### program initiating #####\n");

	input_info(&src_str, &tgt_str);
	printf("ģ���ֶ�:%s\n�ı���ַ:%s\n", src_str, tgt_str);
	
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
	printf("����ģ���ֶ�\n");
	*text_str = get_str();

	printf("�����ı���ַ\n"); 
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
	if (str1 == NULL)		//��ƥ���ַ���ָ��գ�����false
		return false;
	if (pattern == NULL)		//ģʽ�ַ���ָ��գ�����false
		return false;
	int len1 = strlen(str1);		//��ƥ���ַ����ĳ���
	int len2 = strlen(pattern);			//ģʽ�ַ����ĳ���
	int mark = 0;		//���ڷֶα��,'*'�ָ����ַ���
	int p1 = 0, p2 = 0;		//��ƥ��/ģʽ��ƫ����
	int flag_s = 0, flag_q = 0;			//�������* �ͣ����ʶ��λ

	while ((p1<len1) && (p2<len2))			//�ڳ��ȷ�Χ������
	{
		if (pattern[p2] == '?')			//���ģʽ���С�����ͨ�������ͬʱƫ��1����������һѭ��
		{
			flag_q = 1;
			p1++;
			p2++;
			continue;
		}
		if (pattern[p2] == '*')//�����ǰ��*�ţ���markǰ��һ�����Ѿ����ƥ�䣬//�ӵ�ǰ�㿪ʼ������һ�����ƥ��
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
				//��������ַ������⴦������ͬ��ƥ��ʧ��
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
		//�˴�������ȵ����
		p1++;
		p2++;
	}
	if (p2 == len2)
	{
		if (p1 == len1)
		{
			//�����ַ����������ˣ�˵��ģʽƥ��ɹ�
			return true;
		}
		if (pattern[p2 - 1] == '*')
		{
			//str1��û�н�������pattern�����һ���ַ���*������ƥ��ɹ�
			return true;
		}
		else
		{
			return false;
		}
	}
	while (p2<len2)
	{
		//pattern������ַ�ֻҪ��һ������*,ƥ��ʧ��
		if (pattern[p2] != '*')
			return false;
		p2++;
	}
	if ((len2 != len1) && (flag_s == 0))			//���û�г���*���ǳ��Ȳ�һ���򷵻�false
	{
		return false;
	}
	return true;
}