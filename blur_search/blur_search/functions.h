#pragma once

#ifndef __FUNCTIONS_H
#define	__FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>

//搜索函数
void blur_search(char* src_str, char* tgt_str);

//不定长输入
char* get_str(void);

//输入函数
void input_info(char** text_str, char** addr_str);
#endif /* __FUNCTIONS_H */
