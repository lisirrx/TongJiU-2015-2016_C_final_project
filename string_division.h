#ifndef STRINGDIVISION_H
#define STRINGDIVISION_H

#include <string.h>
extern int line_cnt;

//����ĳ�ַ��ŷִ�
char **string_division(char *input_string);

//�������������
int count_symbol_num(char *_expression);

//�����ʽ���տո�ֳ���
char **expression_division(char *_expression);

//ɾ���ֺ�
char *delete_se(char *string);


#endif
