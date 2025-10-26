#include <bits/stdc++.h>
#include "bin_tree.h"


bin_tree r_bstfy(bin_tree t, bin_tree prv) {
    if(t == NULL) return t;
    r_bstfy(t->left, t);
    r_bstfy(t->right, t);
    // printf("dotarlem do: %d, nad to: %d\n", t->val, prv ? prv->val : -1);
    bin_tree mem = t->left, mem2 = t->right;
    int l_val = (t->left == NULL) ? INT_MIN : t->left->val;
    int r_val = (t->right == NULL) ? INT_MAX : t->right->val;
    if(l_val > t->val) {
        if(l_val > r_val) {
            swap(t->left, t->right);
            swap(mem, mem2);
        }

        if(prv != NULL) {
            if(prv->left == t) {
                prv->left = t->left;
            } else {
                prv->right = t->left;
            }
        }

        t->right = t->left->right;
        t->left = t->left->left;
        mem->left = t;
        mem->right = mem2;
        if(prv == NULL) {
            return mem;
        }
    } else {
        if(l_val > r_val) {
            swap(t->left, t->right);
        } else if(r_val < t->val) {
            if(prv != NULL) {
                if(prv->left == t) {
                    prv->left = t->right;
                } else {
                    prv->right = t->right;
                }
            }

            t->left = t->right->left;
            t->right = t->right->right;
            mem2->left = mem;
            mem2->right = t;

            if(prv == NULL) {
                return mem2;
            }
        }
    }
    // printf("skonczylem: %d, nad to: %d\n", t->val, prv ? prv->val : -1);
    return t;
}

bin_tree bestify(bin_tree root) {
    return r_bstfy(root, (bin_tree) NULL);
}


int main() {
    int a, acc, acc_dwa;
    vector<pair <int, int>> b;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    stworz_vector(b, a);
    bin_tree tree = stworz_bin_tree(b);
    vector <int> c = wartosci_infiks(tree);
    for(int llama: c) {
        printf("%d ", llama);
    } 
    printf("\n");
    tree = bestify(tree);
    c = wartosci_infiks(tree);
    for(int llama: c) {
        printf("%d ", llama);
    }   
    delete tree;
    return 0;
}