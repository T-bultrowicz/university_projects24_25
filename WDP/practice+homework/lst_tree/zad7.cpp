#include<bits/stdc++.h>
using namespace std;

typedef struct elem {
    int val;
    elem *next, *other;
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
    while(l->next != NULL && l-> next != a) {
        res.push_back(l->val);
        l = l->next;
    }
    res.push_back(l->val);
    return res;
}

lista stworz_zapetlone(vector <int> a, vector <int> b) {
    lista l1 = stworz_lista(a), l2 = stworz_lista(b);
    lista opr = l1;
    stack <lista> pointers;
    while(opr!= NULL) {
        pointers.push(opr);
        if(opr->next == NULL) {
            opr->next = l1;
            break;
        }
        opr = opr->next;    
    }
    opr = l2;
    while(opr != NULL) {
        opr->other = pointers.top();
        pointers.top()->other = opr;
        if(opr->next == NULL) {
            opr->next = l2;
            break;
        }
        opr = opr->next;
        pointers.pop();
    }
    return l1;
}

void rotate(lista lis) {
    lista zap = lis, zap_inna = lis->other;
    lista inna = lis->next->other;
    while(lis->next != zap) {
        inna->other = lis;
        lis->other = inna;
        lis = lis->next;
        inna = lis->next->other;
    }
    lis->other = zap_inna;
    zap_inna->other = lis;
    lis = zap;
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
    for(int i = 0; i < a; i++) {
        if(scanf("%d", &acc) != 1) {
            return -1;
        }
        d.push_back(acc);
    }
    lista l1 = stworz_zapetlone(c,d);
    c = zwroc_lista(l1);
    d = zwroc_lista(l1->other);
    for(int i = 0; i < c.size(); i++) {
        printf("%d  %d\n", c[i], d[i]);
    }
    rotate(l1);
    c = zwroc_lista(l1);
    d = zwroc_lista(l1->other);
    for(int i = 0; i < c.size(); i++) {
        printf("%d  %d\n", c[i], d[i]);
    }
    lista del = l1->other;
    lista del_next = del->next;
    del->next = NULL;
    delete del_next;
    del = l1->next;
    l1->next = NULL;
    delete del;
    return 0;
}