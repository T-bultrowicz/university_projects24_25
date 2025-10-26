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
    while(a->next != NULL && a->next != l) {
        res.push_back(a->val);
        a = a->next;
    }
    res.push_back(a->val);
    return res;
}

void cykliczna(lista a) {
    lista prv = a, much_prv = a, mid = a;
    mid = a->next;
    if(mid == NULL) {
        a->next = a;
        return;
    }
    a = mid->next;
    if(a == NULL) {
        mid->next = prv;
        return;
    }
    prv->next = NULL;
    while(a != NULL) {
        mid->next = prv;
        prv = mid;
        mid = a;
        a = a->next;
    }
    mid->next = prv;
    much_prv->next = mid;
    return;
}


int main() {
    int a;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    vector <int> b;
    int b_acc;
    for(int i = 0; i < a; i++) {
        if(scanf("%d", &b_acc) != 1) {
            return -1;
        }
        b.push_back(b_acc);
    }
    lista c = stworz_lista(b);
    cykliczna(c);
    b = zwroc_lista(c);
    for(int a: b) {
        printf("%d ",a);
    }
    lista ptr = c -> next;
    c->next = NULL;
    delete ptr;
    return 0;
}