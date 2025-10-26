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

void podwoj_lista(lista a) {
    while(a != NULL) {
        lista n = new elem;
        n->val = a->val;
        n->next = a->next;
        a->next = n;
        a = n->next;
    }
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
    podwoj_lista(c);
    b = zwroc_lista(c);
    for(int a: b) {
        printf("%d ",a);
    }
    delete c;
    return 0;
}