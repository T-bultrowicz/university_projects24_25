#include<bits/stdc++.h>
#include"bin_tree.h"
using namespace std;

void r_w_lw(bin_tree t, int acc, vector <bin_tree>& same) {
    if(!t) return;
    if(acc > same.size()) {
        t->jump = NULL;
        same.push_back(t);
    } else {
        t->jump = same[acc - 1];
        same[acc - 1] = t;
    }
    r_w_lw(t->left, acc + 1, same);
    r_w_lw(t->right, acc + 1, same);
}

void w_lewo(bin_tree root) {
    vector <bin_tree> same;
    r_w_lw(root, 1, same);
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
    w_lewo(tree);
    printf("%d %d %d", tree->right->jump->val, tree->right->right->jump->val, tree->left->right->jump->val);
    delete tree;
    return 0;
}