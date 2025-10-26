#include<bits/stdc++.h>
#include"bin_tree.h"
using namespace std;

int main() {
    int a, acc, acc_dwa;
    vector<pair <int, int>> b;
    vector <int> c;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    stworz_vector(b, a);
    bin_tree tree = stworz_bin_tree(b);
    c = wartosci_infiks(tree);
    for(int acc: c) {
        printf("%d ", acc);
    }
    printf("\n");
    c = wartosci_postfiks(tree);
    for(int acc: c) {
        printf("%d ", acc);
    }
    printf("\n%d %d", sajzof(tree), heightof(tree));
    delete tree;
    return 0;
}