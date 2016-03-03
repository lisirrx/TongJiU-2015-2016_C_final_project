#include "tools.h"
#include "string_division.h"
#include "variable_store.h"
#include <stdio.h>
#include <stdlib.h>

void store_variable_in_tree(Trie* _variable, char *_declaration_sentence)
{
	delete_se(_declaration_sentence);
	int cnt_se = count_symbol_num(_declaration_sentence);
	enum Type type = declaration_variable_type(_declaration_sentence);
	char **variable_name = (char **)malloc(sizeof(char*)*(cnt_se + 1));
	int flag = 0;
	char *variable_sentence = declaration_variable_start(_declaration_sentence);
	delete_space(variable_sentence);
	for (unsigned i = 0; i < strlen(variable_sentence); i++)
	{
		if (i == 0 && variable_sentence[i] == ',')
		{
			flag = 1;
		}
		else if(variable_sentence[i]==','&&variable_sentence[i+1]==',')
		{
			flag = 1;
		}
	}
	if (flag == 0)
	{
		variable_name = string_division(variable_sentence);

		for (int j = 0; j < cnt_se + 1; j++)
		{
			if (!strcmp(*(variable_name + j), "int") || !strcmp(*(variable_name + j), "double") || !strcmp(*(variable_name + j), "print"))
			{
				printf("ERROR In Line %d : The variable's name is illegal.\n",line_cnt);
				exit(1);
			}
			else
			{
				add_variable(type, *(variable_name + j), _variable);
			}
		}
	}
	else
	{
		printf("ERROR In Line %d : The variable's name is illegal.\n",line_cnt);
		exit(1);
	}
}