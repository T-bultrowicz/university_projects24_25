#include<bits/stdc++.h>
#include"bin_tree.h"
using namespace std;


int r_srod(bin_tree t, bin_tree *res, int behind, int *cur_bst) {
    if(t == NULL) return 0;
    int l = r_srod(t->left, res, behind + 1, cur_bst);
    int r = r_srod(t->right, res, behind + 1, cur_bst);
    if(max(l, max(r, behind)) < *cur_bst) {
        *cur_bst = max(l, max(r, behind));
        *res = t;
    }
    return max(l, r) + 1;
}

int max_sciezka(bin_tree t) {
    if(t == NULL) return 0;
    return max(max_sciezka(t->left), max_sciezka(t->right)) + 1;
}

bin_tree srodek(bin_tree root) {
    bin_tree res = root;
    int l_dlug = max_sciezka(root->left) + 1;
    int r_dlug = max_sciezka(root->right) + 1;
    int cur_bst = max(l_dlug, r_dlug);
    r_srod(root->left, &res, r_dlug + 1, &cur_bst);
    r_srod(root->right, &res, l_dlug + 1, &cur_bst);
    return res;
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
    bin_tree midd = srodek(tree);
    printf("%d", midd->val);
    delete tree;
    return 0;
}