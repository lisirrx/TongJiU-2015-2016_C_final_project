#include "stack.h"
#include <stdlib.h>

Stack *initialize_stack(void)
{
	Stack *p_newtree = (Stack *)malloc(sizeof(Stack));
	p_newtree->p_next = NULL;
	return p_newtree;
}

Stack *find_stack_top(Stack *_head)
{
	while (_head->p_next != NULL)
	{
		_head = _head->p_next;
	}
	
	return _head;
}

void push(Stack *_head,Trie *_item,int _int_value,double _double_value,char _operator,enum item_type _item_type) 
{
	Stack *temp = (Stack *)malloc(sizeof(Stack));
	while (_head->p_next != NULL)
	{
	_head = _head->p_next;
	}
	_head->p_next = temp;
	switch (_item_type)
	{
	case INT_CONST:temp->int_value = _int_value;
		break;
	case DOUBLE_CONST:temp->double_value = _double_value;
		break;
	case VARIABLE:temp->variable = _item;
		break;
	case OPERATOR:temp->operator=_operator;
		break;
	}
	
	temp->item_type = _item_type;
	temp->p_next=NULL;
}

Stack *pop(Stack *_head)
{	
	Stack *p_back;
	while (_head->p_next->p_next!= NULL)
	{
		_head = _head->p_next;
	}
	p_back = _head->p_next;
	
	_head->p_next = NULL;
	return p_back;
}