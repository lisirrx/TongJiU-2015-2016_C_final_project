#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "trie_tree.h"

//���ʽ����
void expression_calculate(char *_expression,Trie *_variable_tree);

//���ĳ������
void print_value(char *_variable_name,Trie *_variable_tree);

//��ջ�����в���
void calculate_stack_top(Stack *_operator_number_top, Stack **_operator_number, char _operator);

#endif

