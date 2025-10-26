#include<bits/stdc++.h>
#include"bin_tree.h"
using namespace std;


void r_jed(bin_tree t, bin_tree prv, bool singl) {
    if(!t->left || !t->right) {
        if(!t->left && !t->right) {
            return;
        } else if(!t->left) {
            r_jed(t->right, t, true);
            if(singl && !t->left) {
                if(prv->left == t) {
                    prv->right = t->right;
                } else {
                    prv->left = t->right;
                }
                t->right = NULL;
            }
        } else {
            r_jed(t->left, t, true);
            if(singl && !t->right) {
                if(prv->left == t) {
                    prv->right = t->left;
                } else {
                    prv->left = t->left;
                }
                t->left = NULL;                
            }
        }
    } else {
        r_jed(t->left, t, false);
        r_jed(t->right, t, false);
    }
    return;
}

void jedynaki(bin_tree root) {
    if(!root) return;
    r_jed(root, (bin_tree) NULL, false);
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
    jedynaki(tree);
    l = wartosci_infiks(tree);
    for(auto k: l) {
        printf("%d ", k);
    }
    delete tree;
    return 0;
}