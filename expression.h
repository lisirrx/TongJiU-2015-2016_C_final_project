#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "trie_tree.h"

//表达式计算
void expression_calculate(char *_expression,Trie *_variable_tree);

//输出某个变量
void print_value(char *_variable_name,Trie *_variable_tree);

//对栈顶进行操作
void calculate_stack_top(Stack *_operator_number_top, Stack **_operator_number, char _operator);

#endif

