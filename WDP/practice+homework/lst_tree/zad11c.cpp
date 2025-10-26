#include<bits/stdc++.h>
#include"bin_tree.h"
using namespace std;

int ilosc_w(bin_tree t) {
    return t ? ilosc_w(t->left) + ilosc_w(t->right) + 1 : 0;
}

int r_rozc(bin_tree t, int ilosc, int* roznica, bin_tree* cut, bin_tree* blw_cut) {
    if(t == NULL) return 0;
    int l = r_rozc(t->left, ilosc, roznica, cut, blw_cut);
    int r = r_rozc(t->right, ilosc, roznica, cut, blw_cut);
    if(ilosc - l < *roznica) {
        *roznica = ilosc - l;
        *cut = t;
        *blw_cut = t->left;
    } else if(ilosc - r < *roznica) {
        *roznica = ilosc - r;
        *cut = t;
        *blw_cut = t->right;
    }
    return l + r + 1;
}

bin_tree rozciecie(bin_tree root) {
    int res = INT_MAX;
    bin_tree cut = NULL, blw_cut;
    r_rozc(root, ilosc_w(root), &res, &cut, &blw_cut);
    if(cut) {
        if(cut->left == blw_cut) {
            cut->left = NULL;
        } else if(cut->right == blw_cut) {
            cut->right = NULL;
        }
    }
    return blw_cut;
}

int main() {
    int a;
    vector <pair <int,int>> b;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    stworz_vector(b, a);
    bin_tree tree = stworz_bin_tree(b), sml_tree;
    vector <int> vals;
    vals = wartosci_infiks(tree);
    for(int c: vals) {
        printf("%d ", c);
    }
    printf("\n");
    sml_tree = rozciecie(tree);
    vals = wartosci_infiks(tree);
    for(int c: vals) {
        printf("%d ", c);
    }
    printf("\n");    
    delete tree;
    delete sml_tree;
    return 0;
}