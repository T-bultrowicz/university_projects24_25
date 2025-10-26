#include<bits/stdc++.h>
using namespace std;

typedef struct elem {
    int val;
    elem* next;
    ~elem() {
        delete next;
    }
} elem;

typedef elem* lista;

lista stworz_lista(vector <int> values) {
    lista joiner = NULL;
    for(int i = values.size() - 1; i >= 0; i--) {
        lista a = new elem;
        a->val = values[i];
        a->next = joiner;
        joiner = a;
    }
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
    return res;
}

lista zlacz_listy(lista a, lista b) {
    lista at_end = a;
    if(!a || !b) {return a;}
    lista a_front = a->next, b_front = b-> next;  
    if(!a_front && !b_front) {a->next = b; b = a; return a;}
    while(a_front && b_front) {
        a->next = b;
        b->next = a_front;
        a = a_front;
        b = b_front;
        a_front = a_front->next;
        b_front = b_front->next;
    }
    a->next = b;
    if(a_front) {
       b->next = a_front;
    }
    return at_end;
}

int main() {
    int a, b;
    if(scanf("%d %d", &a, &b) != 2) {
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
    for(int j = 0; j < b; j++) {
        if(scanf("%d", &acc) != 1) {
            return -1;
        }
        d.push_back(acc);
    };
    lista l1 = stworz_lista(c);
    lista l2 = stworz_lista(d);
    lista l3 = zlacz_listy(l1, l2);
    c = zwroc_lista(l3);
    for(int k: c) {
        printf("%d ",k);
    }
    delete l3;
    return 0;
}