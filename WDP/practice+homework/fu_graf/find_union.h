#ifndef FIND_UNION_H
#define FIND_UNION_H 1
#include<vector>

typedef struct node {
    int val;
    node *equal;
    std::vector<node*> childs;
} node;

typedef node* find_union;

find_union create_find_union(int v);
int find(find_union f);
bool equivalent(find_union f, find_union g);
void unite(find_union f, find_union g);
int size(find_union f);
std::vector<int> elems(find_union f); 
#endif 
