#include<bits/stdc++.h>
#include"bin_tree.h"
using namespace std;


void przyciecie(bin_tree t) {
    if(t == NULL) return;
    przyciecie(t->left);
    przyciecie(t->right);
    if(!t->left || !t->right) {
        if(!t->left && !t->right) {
            return;
        } else if(!t->left) {
            delete t->right;
            t->right = NULL;
        } else {
            delete t->left;
            t->left = NULL;
        }
    }
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
    przyciecie(tree);
    l = wartosci_infiks(tree);
    for(auto k: l) {
        printf("%d ", k);
    }
    delete tree;
    return 0;
}