#pragma once

#ifndef __FUNCTIONS_H
#define	__FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE 1023

//���ʽṹ��
struct word_type
{
	char* word_store;				//ָ��̬�ַ����洢��ָ��
	int len;						//���ʳ���
};

//����������
char* get_str(void);
//���뺯��
void input_info(char** text_str, char** addr_str);
//���ļ�
FILE *open_file(char *filename);
//��ȡһ������
void read_word(FILE* fp, char* src_str);

bool match(char* str1, char* pattern);

#endif /* __FUNCTIONS_H */
