#pragma once

#ifndef __FUNCTIONS_H
#define	__FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

//��������
void blur_search(char* src_str, char* tgt_str);

//����������
char* get_str(void);

//���뺯��
void input_info(char** text_str, char** addr_str);
#endif /* __FUNCTIONS_H */
