#include<bits/stdc++.h>
#include"bin_tree.h"
using namespace std;

typedef struct walk {
    bin_tree curr;
    stack<bin_tree> prv; 
} walk;

walk make_walk(bin_tree t) {
    walk res;
    res.curr = t;
    return res;
}

void go(walk &w, int direction) {
    if(direction == 0) {
        if(w.curr->left != NULL) {
            w.prv.push(w.curr);
            w.curr = w.curr->left;
        }
    } else if(direction == 1) {
        if(w.curr->right != NULL) {
            w.prv.push(w.curr);
            w.curr = w.curr->right;
        }
    } else if(direction == 2) {
        if(!w.prv.empty()) {
            w.curr = w.prv.top();
            w.prv.pop();
        }
    }
}

int lookup(const walk w) {
    return w.curr->val;
}


int main() {
    int a;
    vector<pair <int, int>> b;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    stworz_vector(b, a);
    bin_tree tree = stworz_bin_tree(b);
    walk w = make_walk(tree);
    printf("%d ", lookup(w));
    go(w, 0);
    printf("%d ", lookup(w));
    go(w, 1);
    printf("%d ", lookup(w));
    go(w, 2);
    printf("%d ", lookup(w));
    delete tree;
    return 0;
}