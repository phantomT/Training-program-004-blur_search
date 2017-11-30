#pragma once

#ifndef __NODE_H
#define	__NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct word_type
{
	char* word_store;				//ָ��̬�ַ����洢��ָ��
	int len;						//���ʳ���
	int cnt;					//�ڼ�������
	struct word_type* prev;		//��һ������
	struct word_type* next;		//��һ������
};

//�������ʽڵ�
static struct word_type *create_node(void);
//����ڵ�
int insert_nodes(struct word_type *phead, struct word_type *pnew);
//ɾ������
void destroy_link(struct word_type *phead);
//��ȡ�ı��е���
int read_words(FILE *fp, struct word_type *phead);
//������е���(debug)
void print_words(struct word_type *phead);

#endif /* __NODE_H */