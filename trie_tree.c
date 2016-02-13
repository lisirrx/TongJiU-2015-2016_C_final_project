#include "trie_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Trie *initialize_tree(void)
{
	Trie *new_node = (Trie *)malloc(sizeof(Trie));
	for (int i = 0; i < 256; i++)
	{
		new_node->p_next[i] = NULL;
	}
	
	return new_node;
}

void add_variable(enum Type _variable_type, char *_variable_name, Trie *_trie_tree)
{
	unsigned int len = strlen(_variable_name);
	for (unsigned int i = 0; i < len; i++)
	{
		if (_trie_tree->p_next[_variable_name[i]] == NULL)
		{
			_trie_tree->p_next[_variable_name[i]] = initialize_tree();
		}
		_trie_tree = _trie_tree->p_next[_variable_name[i]];
	}
	_trie_tree->type = _variable_type;
	_trie_tree->declaraed = true;
	_trie_tree->double_value = 0;
	_trie_tree->int_value = 0;
}

Trie *find_variable(char *_variable_name, Trie *_trie_tree)
{
	unsigned int len = strlen(_variable_name);
	for (unsigned int i = 0; i < len; i++)
	{

		if (_trie_tree->p_next[_variable_name[i]] == NULL)
		{
			printf("ERROR In Line %d : Can not find the variable.\n", line_cnt);
			exit(0);
		}
		_trie_tree = _trie_tree->p_next[_variable_name[i]];

	}
	if (_trie_tree->declaraed == true)
	{
		return _trie_tree;
	}
	else
	{
		printf("ERROR In Line %d : Can not find the variable\n", line_cnt);
		exit(0);
	}
}
