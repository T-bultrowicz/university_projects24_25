#include<bits/stdc++.h>
#include"bin_tree.h"
using namespace std;

void rek_lew(bin_tree t, bool& res) {
    if(t ==NULL) return; 
    if(t->right != NULL && t->left == NULL) {
        res = false;
    }
    rek_lew(t->left, res);
    rek_lew(t->right, res);
}


bool ultralewicowe(const bin_tree root) {
    bool res = true;
    rek_lew(root, res);
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
    printf("%d", ultralewicowe(tree) ? 69 : 420);
    delete tree;
    return 0;
}