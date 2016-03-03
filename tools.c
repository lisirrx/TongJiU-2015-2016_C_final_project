
#include "stack.h"
#include "tools.h"
#include "string_division.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int declaration_variable_type(char *_declaration_sentence)
{
	unsigned int lens = strlen(_declaration_sentence);
	for (unsigned int i = 0; i <lens ; i++)
	{
		if (*(_declaration_sentence + i) == 'i'
			&&*(_declaration_sentence + i + 1) == 'n'
			 &&*(_declaration_sentence + i + 2) == 't'
			  &&*(_declaration_sentence + i + 3) == ' ')
		{
			return INT_DECLARATION_SENTENCE;
		}
		else if (*(_declaration_sentence + i) == 'd'
			 &&*(_declaration_sentence + i + 1) == 'o'
			  &&*(_declaration_sentence + i + 2) == 'u'
			   &&*(_declaration_sentence + i + 3) == 'b'
			    &&*(_declaration_sentence + i + 4) == 'l'
			     &&*(_declaration_sentence + i + 5) == 'e'
			      &&*(_declaration_sentence + i + 6) == ' ')
		{
			return DOUBLE_DECLARATION_SENTENCE;
		}
		else if ((*(_declaration_sentence + i) == 'p'
			&&*(_declaration_sentence + i + 1) == 'r'
			 &&*(_declaration_sentence + i + 2) == 'i'
			  &&*(_declaration_sentence + i + 3) == 'n'
			   &&*(_declaration_sentence + i + 4) == 't'
			     &&*(_declaration_sentence + i + 5) == '(')
			|| (*(_declaration_sentence + i) == 'p'
				&&*(_declaration_sentence + i + 1) == 'r'
				 &&*(_declaration_sentence + i + 2) == 'i'
				  &&*(_declaration_sentence + i + 3) == 'n'
				   &&*(_declaration_sentence + i + 4) == 't'
				    &&*(_declaration_sentence + i + 5) == ' '))
		{
			return OUTPUT_SENTENCE;
		}
		else if (i == lens - 1)
		{
			return CALCULATE_SENTENCE;
		}
		
		
	}
	return BLANK_SENTENCE;
}

char *declaration_variable_start(char *_declaration_sentence)
{
	for (unsigned int i = 0; i < strlen(_declaration_sentence); i++)
	{
		if (*(_declaration_sentence + i) == 'i'&&*(_declaration_sentence + i + 1) == 'n'
			&&*(_declaration_sentence + i + 2) == 't'&&*(_declaration_sentence + i + 3) == ' ')
		{
			return _declaration_sentence+i+4;
		}
		else if (*(_declaration_sentence + i) == 'd'&&*(_declaration_sentence + i + 1) == 'o'
			&&*(_declaration_sentence + i + 2) == 'u'&&*(_declaration_sentence + i + 3) == 'b'
			&&*(_declaration_sentence + i + 4) == 'l'&&*(_declaration_sentence + i + 5) == 'e'&&*(_declaration_sentence + i + 6) == ' ')
		{
			return _declaration_sentence+i+7;
		}
	}
}

char *delete_space(char *_input_string)
{
	int i, j;
	for (i=j=0; _input_string[i]; i++)
	{
		if (_input_string[i] != ' ')
		{
			_input_string[j++] = _input_string[i]; 
		}
	}
	_input_string[j] = '\0';
	return _input_string;
}

int sentence_type_declaration(char *_sentence)
{
	if (declaration_variable_type(_sentence) ==3 )
		return 0;
	else if (declaration_variable_type(_sentence) == 4)
		return 2;
	else
		return 1;
}

bool is_number(char *_aword)
{
	char  *poniter;
	
	strtod(_aword, &poniter);
	if (*poniter == NULL)
		return true;
	else 
		return false;
}

int number_type(char *_aword)
{
	int type = 0;
	unsigned int cnt = strlen(_aword);
	for (unsigned int i = 0; i < cnt; i++)
	{
		if (_aword[i] == '.' || _aword[i] == 'e')
			type = 1;
	}
	return type;
}

bool is_operator(char _chararctor)
{
	if (_chararctor == '(' || _chararctor == ')' || _chararctor == '+' || 
		_chararctor == '-' || _chararctor == '*' || _chararctor == '/'|| _chararctor == '='||
		_chararctor == '#'|| _chararctor == '@'|| _chararctor == '~'|| _chararctor == '!')
		return true;
	else
		return false;
}

char *pretreatment_expression(char *_expression)
{
	char *expression_new = (char *)malloc(sizeof(char)*(strlen(_expression) + 2));
	strcpy(expression_new, _expression);

	for (unsigned int i = 0; i < strlen(expression_new); i++)
	{
		if (is_operator(expression_new[i]) &&i != 0&& expression_new[i - 1] != ' ')
		{
			expression_new = (char *)realloc(expression_new, sizeof(char)*(strlen(expression_new) + 4));
			expression_new[strlen(expression_new) + 1] = 0;
			expression_new[strlen(expression_new) + 2] = 0;
			for (unsigned int j = strlen(expression_new) + 1; j > i; --j)
			{
				expression_new[j] = expression_new[j - 2];
			}
			expression_new[i + 1] = expression_new[i];
			expression_new[i] = expression_new[i + 2] = ' ';
			i += 2;
		}
		else if (is_operator(expression_new[i]) && i == 0)
		{
			expression_new = (char *)realloc(expression_new, sizeof(char)*(strlen(expression_new) + 3));
			expression_new[strlen(expression_new) + 1] = 0;
			for (unsigned int j = strlen(expression_new); j > i + 1; --j)
			{
				expression_new[j] = expression_new[j - 1];
			}
			expression_new[i + 1] = ' ';
			i++;
		}
		else if (is_operator(expression_new[i]) && expression_new[i - 1] == ' ')
		{
			expression_new = (char *)realloc(expression_new, sizeof(char)*(strlen(expression_new) + 3));
			expression_new[strlen(expression_new) + 1] = 0;
			for (unsigned int j = strlen(expression_new); j > i; --j)
			{
				expression_new[j] = expression_new[j - 1];
			}
			expression_new[i + 1] = ' ';
			i++;
		}
	}
	expression_new = (char *)realloc(expression_new, sizeof(char)*(strlen(expression_new) + 5));
	int len = strlen(expression_new);
	expression_new[len + 1] = 0;
	expression_new[len + 2] = 0;
	expression_new[len + 3] = 0;
	expression_new[len + 4] = 0;

	for (unsigned int j = len + 1; j > 1; j--)
	{
		expression_new[j] = expression_new[j - 2];
	}
	expression_new[0] = '@';
	expression_new[1] = ' ';


	if (expression_new[len + 1] == ' ')
	{
		expression_new[len + 2] = '#';
		expression_new[len + 3] = ' ';
	}
	else
	{
		expression_new[len + 2] = ' ';
		expression_new[len + 3] = '#';
		expression_new[len + 4] = ' ';
	}
	
	return expression_new;
}

char *add_right_brace(char *_expression, int pointer)
{
	unsigned int len = strlen(_expression);
	char *expression_new = (char *)realloc(_expression, sizeof(char)*(len + 2));
	
	expression_new[len + 1] = 0;
	
	for (unsigned j = strlen(_expression); j >pointer + 1; --j)
	{
		expression_new[j] = expression_new[j - 1];
	}
	*(expression_new + pointer +2) = ')';
	
	return expression_new;
}


char *find_name_in_print_sentence(char *_print_sentence)
{
	int flag = 0;
	for (unsigned int i = 0; i < strlen(_print_sentence); i++)
	{
		if (_print_sentence[i] == ')')
		{
			flag = 1;
		}
	}
	if (flag)
	{
		_print_sentence = delete_se(_print_sentence);
		_print_sentence = delete_space(_print_sentence);
		int left_pa = 0, right_pa = 0;

		while (_print_sentence[left_pa] != '(' || _print_sentence[left_pa + 1] == '(')
		{
			left_pa++;
		}
		while (_print_sentence[right_pa] != ')'&&_print_sentence[right_pa + 1] != ')')
		{
			right_pa++;
		}
		_print_sentence[right_pa + 1] = '\0';

		return _print_sentence + left_pa + 1;
	}
	else
	{
		printf("ERROR In Line %d :A right-parenthese is excepted.\n",line_cnt);
		exit(1);
	}
}

int operator_priority(char _operator)
{
	switch (_operator)
	{
	case '@':
		return 0;
		break;
	case ')':
		return 1;
		break;
	case '=':
		return 2;
		break;
	case '+':
		return 3;
		break;
	case '-':
		return 3;
		break;
	case '*':
		return 4;
		break;
	case '/':
		return 4;
		break;
	case '!':
		return 5;
		break;
	case '~':
		return 5;
		break;
	case '(':
		return 6;
		break;
	}
}
