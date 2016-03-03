#ifndef STACK_H
#define STACK_H

#include "trie_tree.h"

enum item_type {INT_CONST, DOUBLE_CONST,VARIABLE,OPERATOR};
typedef struct stack
	{
		Trie *variable;
		int int_value;
		double double_value;
		char operator;
		enum item_type item_type;
		struct stack *p_next;
	}Stack;

//新建一个栈
Stack *initialize_stack(void);

//找到栈顶，返回栈顶指针
Stack *find_stack_top(Stack *_head);

//压栈
void push(Stack *_head, Trie *_item, int _int_value, double _double_value,char _operator, enum item_type _item_type);

//弹栈
Stack *pop(Stack *head);

#endif
