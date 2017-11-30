#pragma warning(disable:4996) //VS 编译声明？
#include<node.h>

static struct word_type *create_node(void)
{
	struct word_type *pnew;

	pnew = (struct word_type *)malloc(sizeof(struct word_type));
	if (!pnew)
	{
		printf("creating failure\n");
		return NULL;
	}
	pnew->cnt = 0;
	pnew->len = 0;
	pnew->next = NULL;
	pnew->prev = NULL;

	return pnew;
}

int insert_nodes(struct word_type *phead, struct word_type *pnew)
{
	struct word_type *pcur;
	pcur = phead;

	if (!(phead))
	{
		phead = pnew;
		return 0;
	}

	pnew->prev = pcur;
	pcur->next = pnew;

	return 0;
}

void destroy_link(struct word_type *phead)
{
	struct word_type *pcur = phead, *ptmp;

	while (pcur)
	{
		ptmp = pcur->next;
		free(pcur->word_store);
		free(pcur);
		pcur = ptmp;
	}
}

int read_words(FILE *fp, struct word_type *phead)
{
	struct word_type *pnew;
	struct word_type *pcur;
	int ch, i = 0, flag = 0;
	char* word;

	pnew = create_node();
	if (!pnew)
	{
		return -1;
	}
	pcur = phead;

	while ((ch = fgetc(fp)) != EOF)
	{
		word = (char*)malloc(sizeof(char)*(i + 1));
		if (NULL == word)
		{
			exit(1);
		}

		if (isalpha(ch))
		{
			word[i++] = ch;
			flag = 0;
			word = (char*)realloc(word, i);
			if (NULL == word)
			{
				exit(1);
			}
		}
		else if (isblank(ch) || isdigit(ch) || isspace(ch) || ispunct(ch) && (!('-')) && !flag)
		{
			word[i] = '\0';
			strcpy(pnew->word_store, word);
			insert_nodes(pcur, pnew);							//链接现在的节点和刚填充的新节点
			pcur = pnew;										//将刚完成的节点作为现在的节点
			pnew = create_node();								//再建立下一个节点

			i = 0;
			flag = 1;
			free(word);
		}
	}
	if (i == 0)
		free(pnew);

	return 0;
}

void print_words(struct word_type *phead)
{
	struct word_type *pcur = phead;

	while (pcur)
	{
		printf("%12s\n", pcur->word_store);
		pcur = pcur->next;
	}
}