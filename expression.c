#include "tools.h"
#include "stack.h"
#include "expression.h"
#include "trie_tree.h"
#include "string_division.h"
#include <stdio.h>
#include <stdlib.h>


void expression_calculate(char *_expression,Trie *_variable_tree)
{
	int cnt = 0;
	double result = 0;
	char **operator_item;
	char *expression_current;
	int cnt_se = count_symbol_num(_expression);
	Stack *operated_number_stack = initialize_stack();
	Stack *operator_stack = initialize_stack();

	delete_space(_expression);
	delete_se(_expression);
	expression_current = pretreatment_expression(_expression);
	operator_item=expression_division(expression_current);
	
	int i=0;
	while (*(operator_item + i) != NULL)
	{
		i++;
	}
	

	for (int j = 0; j< i; j++)
	{
		//运算符压栈与计算部分
		if (is_operator(**(operator_item + j)))
		{
			//单目运算处理，负号为~，正号为！.
			if ((j != 0 && **(operator_item + j) == '-'&&is_operator(**(operator_item + j - 1))
				&& **(operator_item + j) != ')') || j == 0 && **(operator_item + j) == '-')
			{
				**(operator_item+j) = '~';
				push(operator_stack, NULL, 0, 0, **(operator_item + j), OPERATOR);
			}
			else if ((j != 0 && **(operator_item + j) == '+'&&is_operator(**(operator_item + j - 1))
				&& **(operator_item + j) != ')') || j == 0 && **(operator_item + j) == '+')
			{
				**(operator_item + j) = '!';
				push(operator_stack, NULL, 0, 0, **(operator_item + j), OPERATOR);
			}
			else if (**(operator_item + j) == '@')   
			{
				push(operator_stack, NULL, 0, 0, **(operator_item + j), OPERATOR);
			}
			else
			{
				while(((operator_priority(**(operator_item + j)) < operator_priority(find_stack_top(operator_stack)->operator))
					&&find_stack_top(operator_stack)->operator!='(')
					||**(operator_item+j)==')'&&find_stack_top(operator_stack)->operator=='(')
				{
					if (**(operator_item + j) == ')')
					{

						if (**(operator_item + j - 2) == '(')
						{
							pop(operator_stack);
							j++;
						}
						else
						{

							while (find_stack_top(operator_stack)->operator != '(')
							{
								calculate_stack_top(pop(operated_number_stack), &operated_number_stack, pop(operator_stack)->operator);
							}
							pop(operator_stack);
							j++;
						}
					}
					else 
					{
						calculate_stack_top(pop(operated_number_stack), &operated_number_stack, pop(operator_stack)->operator);
					}
				}
				//表达式结束
				if (**(operator_item + j) == '#')
				{
					while (find_stack_top(operator_stack)->operator != '@')
					{
						calculate_stack_top(pop(operated_number_stack), &operated_number_stack, pop(operator_stack)->operator);
					}
					pop(operator_stack);
				}
				else
				{
					push(operator_stack, NULL, 0, 0, **(operator_item + j), OPERATOR);
				}
			}

		}
		//数字的压栈
		else if (is_number(*(operator_item + j)))
		{
			if (number_type(*(operator_item + j)))
			{
				
				push(operated_number_stack,NULL,0, atof(*(operator_item + j)),0,DOUBLE_CONST);
				
			}
			else
			{
				push(operated_number_stack, NULL,atoi(*(operator_item + j)),0,0,INT_CONST);
			}
		}
		//变量压栈
		else
		{
			push(operated_number_stack,find_variable(*(operator_item + j), _variable_tree),0,0,0,VARIABLE);
		
		}
	}
	
}

void print_value(char *_variable_name, Trie *_variable_tree)
{
	delete_space(_variable_name);
	
	if (is_number(_variable_name))
	{
		printf("%s\n", _variable_name);
	}
	else 
	{
		Trie *p_current = find_variable(_variable_name, _variable_tree); 
		if (p_current->type == INT)
		{
			printf("%d\n", p_current->int_value);
		}
		else
		{
			printf("%lf\n", p_current->double_value);
		}
	}
	
}

void  calculate_stack_top(Stack *_operated_number_top, Stack **_operated_number, char _operator)
{
	int int_value = 0;
	double double_value = 0;
	Stack *operated_number_now = find_stack_top(*_operated_number);
	//把已经弹出的栈顶值保留
	switch (_operated_number_top->item_type)
	{
	case(INT_CONST) : int_value = _operated_number_top->int_value;
		break;
	case(DOUBLE_CONST) : double_value = _operated_number_top->double_value;
		break;
	case(VARIABLE) :
		if ((_operated_number_top->variable)->type == INT)
		{
			int_value = (_operated_number_top->variable)->int_value;
		}
		else
		{
			double_value = (_operated_number_top->variable)->double_value;
		}
				   break;
	}
    //以下为已弹栈顶为DOUBLE
	if (_operated_number_top->item_type == DOUBLE_CONST || (_operated_number_top->item_type == VARIABLE 
		&& _operated_number_top->variable->type == DOUBLE))
	{
		switch (operated_number_now->item_type)
		{
			//现在栈顶为INT_CONST 压回DOUBLE值
		case (INT_CONST) :

			if (1)
			{
				int temp_int_value = operated_number_now->int_value;
				double temp_double_value = 0.0;

				switch (_operator)
				{
				case '!':
					push(*_operated_number, NULL, 0, double_value,0, DOUBLE_CONST);
					break;
				case '~':
					push(*_operated_number, NULL, 0, -double_value, 0, DOUBLE_CONST);
					break;
				case '+':
					temp_double_value = temp_int_value + double_value;
					operated_number_now->double_value = temp_double_value;
					operated_number_now->item_type = DOUBLE_CONST;
					break;
				case '-':
					temp_double_value = temp_int_value - double_value;
					operated_number_now->double_value = temp_double_value;
					operated_number_now->item_type = DOUBLE_CONST;
					break;
				case '*':
					temp_double_value = temp_int_value * double_value;
					operated_number_now->double_value = temp_double_value;
					operated_number_now->item_type = DOUBLE_CONST;
					break;
				case '/':
					if (double_value == 0)
					{
						printf("divided by ZERO\n");

						exit(0);
					}
					else
					{
						temp_double_value = temp_int_value / double_value;
						operated_number_now->double_value = temp_double_value;
						operated_number_now->item_type = DOUBLE_CONST;
					}
					break;
				case '=':
					break;
				}
			}
						 break;
		//现在栈顶为DOUBLE_CONST 压回 DOUBLE_CONST
		case (DOUBLE_CONST) :

			if (1)
			{
				int temp_int_value = 0;
				double temp_double_value = operated_number_now->double_value;

				switch (_operator)
				{
				case '!':
					push(*_operated_number, NULL, 0, double_value, 0, DOUBLE_CONST);
					break;
				case '~':
					push(*_operated_number, NULL, 0, -double_value, 0, DOUBLE_CONST);
					break;
				case '+':
					temp_double_value = temp_double_value + double_value;
					operated_number_now->double_value = temp_double_value;
					operated_number_now->item_type = DOUBLE_CONST;
					break;
				case '-':
					temp_double_value = temp_double_value - double_value;
					operated_number_now->double_value = temp_double_value;
					operated_number_now->item_type = DOUBLE_CONST;
					break;
				case '*':
					temp_double_value = temp_double_value * double_value;
					operated_number_now->double_value = temp_double_value;
					operated_number_now->item_type = DOUBLE_CONST;
					break;
				case '/':
					if (double_value == 0)
					{
						printf("divided by ZERO\n");
						exit(0);
					}
					else
					{
						temp_double_value = temp_double_value / double_value;
						operated_number_now->double_value = temp_double_value;
						operated_number_now->item_type = DOUBLE_CONST;
					}
					break;
				case '=':
					break;
				}
			}

							break;
		//现在栈顶为变量
		case (VARIABLE) : 
			//INT类型，返回DOUBLE_VARIABLE
			if (operated_number_now->variable->type == INT)
			{
				if (1)
				{
					int temp_int_value = operated_number_now->variable->int_value;
					double temp_double_value = 0.0;

					switch (_operator)
					{
					case '!':
						push(*_operated_number, NULL, 0, double_value, 0, DOUBLE_CONST);
						break;
					case '~':
						push(*_operated_number, NULL, 0, -double_value, 0, DOUBLE_CONST);
						break;
					case '+':
						temp_double_value = temp_double_value + double_value;
						operated_number_now->double_value = temp_double_value;
						operated_number_now->item_type = DOUBLE_CONST;
						break;
					case '-':
						temp_double_value = temp_int_value - double_value;
						operated_number_now->double_value = temp_double_value;
						operated_number_now->item_type = DOUBLE_CONST;
						break;
					case '*':
						temp_double_value = temp_int_value * double_value;
						operated_number_now->double_value = temp_double_value;
						operated_number_now->item_type = DOUBLE_CONST;
						break;
					case '/':
						if (double_value == 0)
						{
							printf("divided by ZERO\n");
							exit(0);
						}
						else
						{
							temp_double_value = temp_int_value / double_value;
							operated_number_now->double_value = temp_double_value;
							operated_number_now->item_type = DOUBLE_CONST;
						}
						break;
					case '=':
						temp_int_value = double_value;
						operated_number_now->variable->int_value = temp_int_value;
						operated_number_now->variable->type = INT;
						break;
					}
				}

			}
				//DOUBLE类型，返回DOUBLE_VARIABLE
			else if (operated_number_now->variable->type == DOUBLE)
			{
				if (1)
				{
					int temp_int_value = 0;
					double temp_double_value = operated_number_now->variable->double_value;

					switch (_operator)
					{
					case '!':
						push(*_operated_number, NULL, 0, double_value, 0, DOUBLE_CONST);
						break;
					case '~':
						push(*_operated_number, NULL, 0, -double_value, 0, DOUBLE_CONST);
						break;
					case '+':
						temp_double_value = temp_double_value + double_value;
						operated_number_now->double_value = temp_double_value;
						operated_number_now->item_type = DOUBLE_CONST;
						break;
					case '-':
						temp_double_value = temp_double_value - double_value;
						operated_number_now->double_value = temp_double_value;
						operated_number_now->item_type = DOUBLE_CONST;
						break;
					case '*':
						temp_double_value = temp_double_value * double_value;
						operated_number_now->double_value = temp_double_value;
						operated_number_now->item_type = DOUBLE_CONST;
						break;
					case '/':
						if (double_value == 0)
						{
							printf("divided by ZERO\n");
							exit(0);
						}
						else
						{
							temp_double_value = temp_double_value / double_value;
							operated_number_now->double_value = temp_double_value;
							operated_number_now->item_type = DOUBLE_CONST;
						}
						break;
					case '=':
						temp_double_value = double_value;
						operated_number_now->variable->double_value = temp_double_value;
						operated_number_now->variable->type = DOUBLE;
						break;
					}
				}
			}
			break;


		}

	}
	//已弹栈顶为INT
	else if (_operated_number_top->item_type == INT_CONST || (_operated_number_top->item_type == VARIABLE 
		&& _operated_number_top->variable->type == INT))
	{
		switch (operated_number_now->item_type)
		{
			//现在栈顶为INT_CONST,压回INT_CONST
		case (INT_CONST) :

			if (1)
			{
				int temp_int_value = operated_number_now->int_value;
				double temp_double_value = 0.0;

				switch (_operator)
				{
				case '!':
					push(*_operated_number, NULL, int_value, 0, 0, INT_CONST);
					break;
				case '~':
					push(*_operated_number, NULL, -int_value, 0,0, INT_CONST);
					break;
				case '+':
					temp_int_value = temp_int_value + int_value;
					operated_number_now->int_value = temp_int_value;
					operated_number_now->item_type = INT_CONST;
					break;
				case '-':
					temp_int_value = temp_int_value - int_value;
					operated_number_now->int_value = temp_int_value;
					operated_number_now->item_type = INT_CONST;
					break;
				case '*':
					temp_int_value = temp_int_value * int_value;
					operated_number_now->int_value = temp_int_value;
					operated_number_now->item_type = INT_CONST;
					break;
				case '/':
					if (int_value == 0)
					{
						printf("divided by ZERO\n");
						exit(0);
					}
					else
					{
						temp_int_value = temp_int_value / int_value;
						operated_number_now->int_value = temp_int_value;
						operated_number_now->item_type = INT_CONST;
					}
					break;
				case '=':
					break;
				}
			}
						break;
		//现在栈顶为DOUBLE_CONST,压回DOUBLE_CONST
		case (DOUBLE_CONST) :

			if (1)
			{
				int temp_int_value = 0;
				double temp_double_value = operated_number_now->double_value;

				switch (_operator)
				{
				case '!':
					push(*_operated_number, NULL, int_value, 0, 0, INT_CONST);
					break;
				case '~':
					push(*_operated_number, NULL, -int_value, 0, 0, INT_CONST);
					break;
				case '+':
					temp_double_value = temp_double_value + int_value;
					operated_number_now->double_value = temp_double_value;
					operated_number_now->item_type = DOUBLE_CONST;
					break;
				case '-':
					temp_double_value = temp_double_value - int_value;
					operated_number_now->double_value = temp_double_value;
					operated_number_now->item_type = DOUBLE_CONST;
					break;
				case '*':
					temp_double_value = temp_double_value * int_value;
					operated_number_now->double_value = temp_double_value;
					operated_number_now->item_type = DOUBLE_CONST;
					break;
				case '/':
					if (int_value == 0)
					{
						printf("divided by ZERO\n");
						exit(0);
					}
					else
					{
						temp_double_value = temp_double_value / int_value;
						operated_number_now->double_value = temp_double_value;
						operated_number_now->item_type = DOUBLE_CONST;
					}
					break;
				case '=':
					break;
				}
			}

							break;
		//现在栈顶为VARIABLE
		case (VARIABLE) :
			//压回INT
			if (operated_number_now->variable->type == INT)
			{
				if (1)
				{
					int temp_int_value = operated_number_now->variable->int_value;
					double temp_double_value = 0.0;

					switch (_operator)
					{
					case '!':
						push(*_operated_number, NULL, int_value, 0, 0, INT_CONST);
						break;
					case '~':
						push(*_operated_number, NULL, -int_value, 0, 0, INT_CONST);
						break;
					case '+':
						temp_int_value = temp_int_value + int_value;
						operated_number_now->int_value = temp_int_value;
						operated_number_now->item_type = INT_CONST;
						break;
					case '-':
						temp_int_value = temp_int_value - int_value;
						operated_number_now->int_value = temp_int_value;
						operated_number_now->item_type = INT_CONST;
						break;
					case '*':
						temp_int_value = temp_int_value * int_value;
						operated_number_now->int_value = temp_int_value;
						operated_number_now->item_type = INT_CONST;
						break;
					case '/':
						if (int_value == 0)
						{
							printf("divided by ZERO\n");
							exit(0);
						}
						else
						{
							temp_int_value = temp_int_value / int_value;
							operated_number_now->int_value = temp_int_value;
							operated_number_now->item_type = INT_CONST;
						}
						break;
					case '=':
						temp_int_value = int_value;
						operated_number_now->variable->int_value = temp_int_value;
						operated_number_now->variable->type = INT;
						break;
					}
				}

			}
						//压回DOUBLE
			else if (operated_number_now->variable->type == DOUBLE)
			{
				if (1)
				{
					int temp_int_value = 0;
					double temp_double_value = operated_number_now->variable->double_value;

					switch (_operator)
					{
					case '!':
						push(*_operated_number, NULL, int_value, 0, 0, INT_CONST);
						break;
					case '~':
						push(*_operated_number, NULL, -int_value, 0, 0, INT_CONST);
						break;
					case '+':
						temp_double_value = temp_double_value + int_value;
						operated_number_now->double_value = temp_double_value;
						operated_number_now->item_type = DOUBLE_CONST;
						break;
					case '-':
						temp_double_value = temp_double_value - int_value;
						operated_number_now->double_value = temp_double_value;
						operated_number_now->item_type = DOUBLE_CONST;
						break;
					case '*':
						temp_double_value = temp_double_value * int_value;
						operated_number_now->double_value = temp_double_value;
						operated_number_now->item_type = DOUBLE_CONST;
						break;
					case '/':
						if (int_value == 0)
						{
							printf("divided by ZERO\n");
							exit(0);
						}
						else
						{
							temp_double_value = temp_double_value / int_value;
							operated_number_now->double_value = temp_double_value;
							operated_number_now->item_type = DOUBLE_CONST;
						}
						break;
					case '=':
						temp_double_value = int_value;
						operated_number_now->variable->double_value = temp_double_value;
						operated_number_now->variable->type = DOUBLE;
						break;
					}
				}
			}
						break;
		}
	}
}




