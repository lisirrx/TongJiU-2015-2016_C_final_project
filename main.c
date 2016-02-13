#include "tools.h"
#include "stack.h"
#include "expression.h"
#include "trie_tree.h"
#include "variable_store.h"
#include "string_division.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int line_cnt = 1;
int main(int argc, char *argv[])
{
	
	FILE *file_input=NULL;
	

	file_input = stdin;


	if (!file_input) {
		printf("ERROR:File open error.\n");
		exit(1);
	}
	Trie *variable_tree = initialize_tree();
	char *sentence = (char *)malloc(sizeof(char) * 1010);
	while (!feof(file_input)) {
		sentence = memset(sentence, 0, 1010);
		fgets(sentence, 1010, file_input);

		int len = strlen(sentence);
		int sentence_type = declaration_variable_type(sentence);

		if (len <= 0)
		{
			break;
		}
		if (sentence[len - 2] == '\r')
		{
			sentence[len - 2] = '\0';
		}
		if (sentence[len - 1] == '\n') 
		{
			sentence[len - 1] = '\0';
		}
		if (sentence_type == INT_DECLARATION_SENTENCE
			|| sentence_type == DOUBLE_DECLARATION_SENTENCE)
		{
			store_variable_in_tree(variable_tree, sentence);
		}
		else if (sentence_type == CALCULATE_SENTENCE)
		{
			expression_calculate(sentence, variable_tree);
		}
		else if(sentence_type ==OUTPUT_SENTENCE)
		{
			print_value(find_name_in_print_sentence(sentence), variable_tree);
		}
		else if (sentence_type == BLANK_SENTENCE)
		{
			continue;
		}
		line_cnt++;
	}
	
	free(variable_tree);
	free(sentence);
	sentence = NULL;
	variable_tree = NULL;
	
	return 0;
}
