#include<bits/stdc++.h>
#include"bin_tree.h"
using namespace std;


void r_symtr(bin_tree t1, bin_tree t2, bool* res) {
    printf("%d %d\n", t1 ? t1->val : -1, t2 ? t2->val : -1);
    if(!t1 || !t2) {
        if(!t1 && !t2) {
            return;
        } else {
            *res = false;
            return;
        }
    }
    if(t1->val != t2->val) {
        *res = false;
        return;
    }
    r_symtr(t1->left, t2->right, res);
    r_symtr(t1->right, t2->left, res);
    return;
} 

bool symetryczne(bin_tree root) {
    bool res = true;
    r_symtr(root->left, root->right, &res);
    return res;
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
    if(symetryczne(tree)) {
        printf("symetryczne");
    } else {
        printf("niesymetryczne");
    }
    delete tree;
    return 0;
}