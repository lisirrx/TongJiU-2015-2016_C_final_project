#ifndef STRINGDIVISION_H
#define STRINGDIVISION_H

#include <string.h>
extern int line_cnt;

//按照某种符号分词
char **string_division(char *input_string);

//计算运算符个数
int count_symbol_num(char *_expression);

//将表达式按照空格分出来
char **expression_division(char *_expression);

//删除分号
char *delete_se(char *string);


#endif
