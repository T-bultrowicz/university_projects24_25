#include<bits/stdc++.h>
using namespace std;


typedef struct node {
    int val;
    node *left, *right, *next;
    ~node() {
        delete left;
        delete right;
    }
} node;

typedef node* bin_tree;

void nadaj_wartosci(const vector <pair<int, int>>& v, const bin_tree t) {
    if(t == NULL) return;
    t->val = v[t->val - 1].second;
    nadaj_wartosci(v, t->left);
    nadaj_wartosci(v, t->right);
    return;
}


bin_tree stworz_bin_tree(vector <pair <int, int>> values) {
    if(values.size() == 0) {
        return NULL;
    }
    assert(values[0].first == 1);
    queue <pair <bin_tree, int>> same_lvl;
    bin_tree root = new node;
    int acc = 1, always_acc = 1;
    root->val = acc;
    same_lvl.push({root, acc});
    acc++;
    always_acc++;
    int i = 1;
    while(i < values.size()) {
        if(same_lvl.empty()) {
            delete root;
            return NULL;
        } else if(values[i].first == same_lvl.front().second * 2) {
            bin_tree a = new node;
            a->val = acc;
            same_lvl.front().first->left = a;
            same_lvl.push({a, always_acc});
            always_acc++;
            acc++;
            i++;
        } else if(values[i].first == (same_lvl.front().second * 2) + 1) {
            bin_tree a = new node;
            same_lvl.front().first->right = a;
            a->val = acc;
            same_lvl.push({a, always_acc});
            always_acc++;
            acc++;
            i++;
        } else if(values[i].first > (same_lvl.front().second * 2) + 1) {
            if(same_lvl.front().first->left == NULL) {
                always_acc++;
            }
            if(same_lvl.front().first->right == NULL) {
                always_acc++;
            }
            same_lvl.pop();
        }      
    }
    nadaj_wartosci(values, root);
    return root;
}


void Stworz(vector <pair <int, int>>& b, int a) {
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

void rek_infiks(vector <pair <int, int>>& r, bin_tree t) {
    if(t == NULL) return;
    rek_infiks(r, t->left);
    if(t->next != NULL) {
        r.push_back({t->val, t->next->val});
    } else {
        r.push_back({t->val, -1});
    }
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

vector <pair <int, int>> wartosci_infiks(const bin_tree root) {
    vector<pair <int, int>> res;
    rek_infiks(res, root);
    return res;
}

vector <int> wartosci_postfiks(const bin_tree root) {
    vector<int> res;
    rek_postfiks(res, root);
    return res;
}

void Wyzeruj_next(bin_tree t) {
    if(t == NULL) return;
    Wyzeruj_next(t->left);
    t->next = NULL;
    Wyzeruj_next(t->right);
    return;
}

void Przepinanie(bin_tree t, bin_tree& pin_to, bin_tree& pin_from) {
    if(t == NULL) return;
    Przepinanie(t->right, pin_to, pin_from);
    bin_tree save = pin_from;
    if(pin_from != NULL) {
        if(pin_from->val != t->val) {
            while(pin_from != pin_to) {
                bin_tree l = pin_from->next;
                pin_from->next = pin_to;
                pin_from = l;
            }
            pin_to = save;
        }
    }
    t->next = save;
    pin_from = t;
    Przepinanie(t->left, pin_to, pin_from);
    return;
}


void fastryguj(const bin_tree root) {
    Wyzeruj_next(root);
    bin_tree pin_to = NULL, pin_from = NULL;
    Przepinanie(root, pin_to, pin_from);
    return;
}

int main() {
    int a;
    if(scanf("%d", &a) != 1){
        return -1;
    } 
    vector<pair <int, int>> b;
    vector <pair <int, int>> tree_reader;
    Stworz(b, a);
    bin_tree root = stworz_bin_tree(b);
    Wyzeruj_next(root);
    tree_reader = wartosci_infiks(root);
    bool i = true;
    for(pair <int, int> c: tree_reader) {
        printf("%d   %d\n", c.first, c.second);
    }
    printf("\n");
    fastryguj(root);
    i = true;
    tree_reader = wartosci_infiks(root);
    for(pair <int, int> c: tree_reader) {
        printf("%d   %d\n", c.first, c.second);
    }   
    delete root;
    return 0;
}