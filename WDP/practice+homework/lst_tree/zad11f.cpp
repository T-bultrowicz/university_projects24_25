#include<bits/stdc++.h>
#include"bin_tree.h"
using namespace std;


int r_odch(bin_tree t) {
    if(t == NULL) return 0;
    int lval = r_odch(t->left), rval = r_odch(t->right);
    if(lval < 0) {
        delete t->left;
        t->left = NULL;
    }
    if(rval < 0) {
        delete t->right;
        t->right = NULL;
    }
    return lval + rval + t->val;
}

bin_tree odchudzanie(bin_tree root) {
    r_odch(root);
    return root;
}

int main() {
    int a, acc, acc_dwa;
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
    odchudzanie(tree);
    l = wartosci_infiks(tree);
    for(auto k : l) {
        printf("%d ", k);
    }
    delete tree;
    return 0;
}