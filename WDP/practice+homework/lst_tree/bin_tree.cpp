#include<bits/stdc++.h>
#include"bin_tree.h"
using namespace std;


void nadaj_wartosci(const vector <pair<int, int>>& v, const bin_tree t) {
    if(t == NULL) return;
    t->val = v[t->val - 1].second;
    nadaj_wartosci(v, t->left);
    nadaj_wartosci(v, t->right);
    return;
}


bin_tree stworz_bin_tree(vector <pair <int, int>>& values) {
    if(values.size() == 0) {
        return NULL;
    }
    assert(values[0].first == 1);
    queue <pair <bin_tree, int>> same_lvl;
    bin_tree root = new node;
    int acc = 1, always_acc = 1;
    root->val = acc;
    same_lvl.push({root, values[acc++ - 1].first});
    int i = 1;
    while(i < values.size()) {
        if(same_lvl.empty()) {
            delete root;
            return NULL;
        } else if(values[i].first == same_lvl.front().second * 2) {
            bin_tree a = new node;
            a->val = acc;
            same_lvl.front().first->left = a;
            same_lvl.push({a, values[acc++ - 1].first});
            i++;
        } else if(values[i].first == (same_lvl.front().second * 2) + 1) {
            bin_tree a = new node;
            same_lvl.front().first->right = a;
            a->val = acc;
            same_lvl.push({a, values[acc++ - 1].first});
            i++;
        } else{
            same_lvl.pop();
        }
    }
    nadaj_wartosci(values, root);
    return root;
}

void rek_infiks(vector <int>& r, bin_tree t) {
    if(t == NULL) return;
    rek_infiks(r, t->left);
    r.push_back(t->val);
    rek_infiks(r, t->right);
    return;
}

void rek_postfiks(vector <int>& r, bin_tree t) {
    if(t == NULL) return;
    rek_postfiks(r, t->left);
    rek_postfiks(r, t->right);
    r.push_back(t->val);
    return;
}

vector <int> wartosci_infiks(const bin_tree root) {
    vector<int> res;
    rek_infiks(res, root);
    return res;
}

vector <int> wartosci_postfiks(const bin_tree root) {
    vector<int> res;
    rek_postfiks(res, root);
    return res;
}


void stworz_vector(vector <pair <int, int>>& b, int a) {
    vector <int> b_f, b_s;
    int acc;
    for(int i = 0; i < a;i++) {
        if(scanf("%d", &acc) != 1) {
            return;
        }
        b_f.push_back(acc);
    }
     for(int i = 0; i < a;i++) {
        if(scanf("%d", &acc) != 1) {
            return;
        }
        b_s.push_back(acc);
    }
    for(int i = 0;i < a; i++) {
        b.push_back({b_s[i],b_f[i]});
    } 
}

void rek_sajz(bin_tree t, int& s) {
    if(t == NULL) return;
    s++;
    rek_sajz(t->left, s);
    rek_sajz(t->right, s);
}

int sajzof(const bin_tree root) {
    int l = 0;
    rek_sajz(root, l);
    return l;
}

int rek_height(bin_tree t) {
    if(t == NULL) return 0;
    return (max(rek_height(t->left), rek_height(t->right)) + 1);
}

int heightof(const bin_tree root) {
    int l = rek_height(root);
    return l;  
}
