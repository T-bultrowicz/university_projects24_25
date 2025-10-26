#include<bits/stdc++.h>
#include"bin_tree.h"
using namespace std;


void r_bst_cut(bin_tree t) {
    if(t == NULL) return;
    r_bst_cut(t->left);
    r_bst_cut(t->right);
    if(t->left) {
        if(t->left->val > t->val) {
            delete t->left;
            t->left = NULL;
        } 
    }
    if(t->right) {
        if(t->right->val < t->val) {
            delete t->right;
            t->right = NULL;
        }
    }
    return;
}

void bestify_cut(bin_tree root) {
    r_bst_cut(root);
    return;
}

int main() {
    int a;
    vector<pair <int, int>> b;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    stworz_vector(b, a);
    bin_tree tree = stworz_bin_tree(b);
    auto l = wartosci_infiks(tree);
    for(auto k : l) {
        printf("%d ", k);
    }
    printf("\n");
    bestify_cut(tree);
    l = wartosci_infiks(tree);
    for(auto k : l) {
        printf("%d ", k);
    }
    delete tree;
    return 0;
}