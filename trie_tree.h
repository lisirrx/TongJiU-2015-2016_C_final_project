#ifndef TRIE_TREE_H
#define TRIE_TREE_H
#include <stdbool.h>

enum Type { INT, DOUBLE };
typedef struct Node {
	int int_value;
	double double_value;
	enum Type type;
	struct Node *p_next[256];
	bool declaraed;
}Trie;

//
Trie *initialize_tree(void);

//
void add_variable(enum Type _variable_type, char *_variable_name, Trie *_trie_tree);

//
Trie *find_variable(char *_variable_name, Trie *_trie_tree);



extern int line_cnt;





#endif

