#ifndef VARIABLE_H
#define VARIABLE_H

#include "trie_tree.h"
//在处理声明语句时，把每个变量名存入链表
void store_variable_in_tree(Trie* _variable, char *_declaration_sentence);

#endif
