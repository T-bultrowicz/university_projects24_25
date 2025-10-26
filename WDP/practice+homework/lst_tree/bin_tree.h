#ifndef BIN_TREE_H 
#define BIN_TREE_H 
#include<bits/stdc++.h>
using namespace std;


typedef struct node {
    int val;
    node *left, *right, *jump;
    ~node() {
        delete left;
        delete right;
    }
} node;

typedef node* bin_tree;

void nadaj_wartosci(const vector <pair<int, int>>& v, const bin_tree t);
bin_tree stworz_bin_tree(vector <pair <int, int>>& values);
void rek_infiks(vector <int>& r, bin_tree t);
void rek_postfiks(vector <int>& r, bin_tree t);
vector <int> wartosci_infiks(const bin_tree root);
vector <int> wartosci_postfiks(const bin_tree root);
void stworz_vector(vector <pair <int, int>>& b, int a);
void rek_sajz(bin_tree t, int& s);
int sajzof(const bin_tree root);
int rek_height(bin_tree t);
int heightof(const bin_tree root);
#endif 