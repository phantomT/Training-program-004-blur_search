#pragma once

#ifndef __NODE_H
#define	__NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct word_type
{
	char* word_store;				//指向动态字符串存储的指针
	int len;						//单词长度
	int cnt;					//第几个单词
	struct word_type* prev;		//上一个单词
	struct word_type* next;		//下一个单词
};

//建立单词节点
static struct word_type *create_node(void);
//插入节点
int insert_nodes(struct word_type *phead, struct word_type *pnew);
//删除链表
void destroy_link(struct word_type *phead);
//读取文本中单词
int read_words(FILE *fp, struct word_type *phead);
//输出所有单词(debug)
void print_words(struct word_type *phead);

#endif /* __NODE_H */