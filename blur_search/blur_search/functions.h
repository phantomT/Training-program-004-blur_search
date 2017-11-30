#pragma once

#ifndef __FUNCTIONS_H
#define	__FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 1023

//单词结构体
struct word_type
{
	char* word_store;				//指向动态字符串存储的指针
	int len;						//单词长度
};

//不定长输入
char* get_str(void);
//输入函数
void input_info(char** text_str, char** addr_str);
//打开文件
FILE *open_file(char *filename);
//读取一个单词
void read_word(FILE* fp, char* src_str);

bool match(char* str1, char* pattern);

#endif /* __FUNCTIONS_H */
