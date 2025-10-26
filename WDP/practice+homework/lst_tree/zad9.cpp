#include<bits/stdc++.h>
#include"bin_tree.h"
using namespace std;

void la_bomba(vector<int>& acc, bin_tree t, bool czy) {
    if(t == NULL) return;
    if(czy) {
        acc.push_back(t->val);
    }
    la_bomba(acc, t->left, !czy);
    la_bomba(acc, t->right, !czy);
    if(!czy) {
        acc.push_back(t->val);
    }
}

vector<int> obchodzenie_drzewa_skokami(const bin_tree root) {
    vector<int> res;
    la_bomba(res, root, false);
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
    vector <int> c = obchodzenie_drzewa_skokami(tree);
    for(int acc: c) {
        printf("%d  ", acc);
    }
    delete tree;
    return 0;
}