#ifndef TOOLS_H
#define TOOLS_H

#include "stack.h"
#include <stdbool.h>

enum sentence_type{INT_DECLARATION_SENTENCE,DOUBLE_DECLARATION_SENTENCE,OUTPUT_SENTENCE, CALCULATE_SENTENCE, BLANK_SENTENCE};
//判断一个声明语句的数据类型 INT 为INT_DECLARATION_SENTENCE， DOUBLE 为DOUBLE_DECLARATION_SENTENCE， 运算语句返回 CALCULATE_SENTENCE，输出语句返回OUTPUT_SENTENCE,空行返回BLANK_SENTENCE
int declaration_variable_type(char *_declaration_sentence_sentence);

//传出声明语句的变量部分的开始位置
char *declaration_variable_start(char *_declaration_sentence);

//删掉不影响语义的空格
char *delete_space(char *_input_string);

//判断是语句的类型
int sentence_type_declaration(char *_sentence);

//判断是否为数字
bool is_number(char *_aword);

//判断数字的类型
int number_type(char *_aword);

//判断是否为操作符
bool is_operator(char _chararctor);

//预处理运算符连续出现的情况
char *pretreatment_expression(char *_expression);


//预处理过程中添加右括号
char *add_right_brace(char *_expression, int pointer);

//提出print语句中的变量名
char *find_name_in_print_sentence(char *_print_sentence);

//判断优先级
int operator_priority(char _operator);








#endif 

