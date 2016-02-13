#ifndef TOOLS_H
#define TOOLS_H

#include "stack.h"
#include <stdbool.h>

enum sentence_type{INT_DECLARATION_SENTENCE,DOUBLE_DECLARATION_SENTENCE,OUTPUT_SENTENCE, CALCULATE_SENTENCE, BLANK_SENTENCE};
//�ж�һ������������������ INT ΪINT_DECLARATION_SENTENCE�� DOUBLE ΪDOUBLE_DECLARATION_SENTENCE�� ������䷵�� CALCULATE_SENTENCE�������䷵��OUTPUT_SENTENCE,���з���BLANK_SENTENCE
int declaration_variable_type(char *_declaration_sentence_sentence);

//�����������ı������ֵĿ�ʼλ��
char *declaration_variable_start(char *_declaration_sentence);

//ɾ����Ӱ������Ŀո�
char *delete_space(char *_input_string);

//�ж�����������
int sentence_type_declaration(char *_sentence);

//�ж��Ƿ�Ϊ����
bool is_number(char *_aword);

//�ж����ֵ�����
int number_type(char *_aword);

//�ж��Ƿ�Ϊ������
bool is_operator(char _chararctor);

//Ԥ����������������ֵ����
char *pretreatment_expression(char *_expression);


//Ԥ������������������
char *add_right_brace(char *_expression, int pointer);

//���print����еı�����
char *find_name_in_print_sentence(char *_print_sentence);

//�ж����ȼ�
int operator_priority(char _operator);








#endif 

