#include<bits/stdc++.h>
using namespace std;

typedef struct elem {
    int val;
    elem *next, *prev;
    ~elem() {
        delete next;
    }
} elem;

typedef elem* lista;

lista stworz_lista(vector <int> values) {
    lista backer = new elem;
    backer->val = values[0];
    lista joiner = backer;
    for(int i = 1; i < values.size(); i++) {
        lista a = new elem;
        a->val = values[i];
        a->next = backer;
        backer->prev = a;
        backer = a; 
    } 
    joiner->next = backer;
    backer->prev = joiner;
    return joiner;
}

vector <int> zwroc_lista(lista a) {
    lista l = a;
    vector <int> res;
    while(a->next != NULL && a-> next != l) {
        res.push_back(a->val);
        a = a->next;
    }
    res.push_back(a->val);
    a = l;
    return res;
}

int main() {
    int a;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    vector <int> c, d;
    int acc;
    for(int i = 0; i < a; i++) {
        if(scanf("%d", &acc) != 1) {
            return -1;
        }
        c.push_back(acc);
    }
    lista l1 = stworz_lista(c);
    d = zwroc_lista(l1);
    for(int a: d) {
        printf("%d ", a);
    }
    lista l3 = l1->next;
    l1->next = NULL;
    delete l3;
    return 0;
}