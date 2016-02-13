#include "string_division.h"
#include<stdio.h>
#include<stdlib.h>


char **string_division(char *input_string)
{
	int cnt_se;
	char** item_string;
	char *string_current = (char *)malloc(sizeof(char)*(strlen(input_string)+1));
	
	strcpy(string_current, input_string);
	cnt_se = count_symbol_num(string_current);
	item_string = (char**)malloc(sizeof(char*) * cnt_se+1);
	
	for (int j = 0; j < cnt_se+1; j++)
	{
		char *str_now = strtok(string_current, ",");
		*(item_string + j) = (char*)malloc(sizeof(char) * strlen(str_now));
		strcpy(*(item_string + j),str_now);
		string_current = NULL;
	}
	free(string_current);
	return item_string;
}

int count_symbol_num(char *_expression)
{
	int cnt = 0;
	for (unsigned int i = 0; i < strlen(_expression); i++)
	{
		if (*(_expression + i) == '+' || *(_expression + i) == '-' || *(_expression + i) == '*' 
			|| *(_expression + i) == '/' || *(_expression + i) == '='|| *(_expression + i) == '£¨'
			|| *(_expression + i) == '£©'|| *(_expression + i) == '#'|| *(_expression + i) == '@'|| *(_expression + i) == ',')
			cnt++;
	}
	
	return cnt;
}

char **expression_division(char *_expression)
{
	int cnt_space=0;
	
	char *string_current = (char *)malloc(sizeof(char)*(strlen(_expression) + 1));

	strcpy(string_current, _expression);
	for (int i=0; string_current[i] != '#'; i++)
	{
		if (string_current[i] == ' ')
			cnt_space++;
	}
	char **item_string = (char **)malloc(sizeof(char*) * (cnt_space + 2));
	int j;
	for ( j = 0; j < cnt_space+1 ; j++)
	{
		char *trimed_string = strtok(string_current, " ");
		unsigned int len = strlen(trimed_string);
		*(item_string + j) = (char *)malloc(sizeof(char) * (len+2));
		strcpy(*(item_string + j), trimed_string);
		string_current = NULL;
	}
	*(item_string + j) = NULL;
	
	return item_string;
}

char *delete_se(char *_string)
{
	int cnt = strlen(_string);
	for (int i = 0; i < cnt; i++)
	{
		if (_string[i] == ';')
		{
			_string[i] = '\0';
		}
		else if (i == cnt - 1 && _string[i] != ';')
		{
			printf("ERROR In Line %d : A Semicolon is excepted .\n",line_cnt);
			exit(0);
		}
	}

	return _string;
}