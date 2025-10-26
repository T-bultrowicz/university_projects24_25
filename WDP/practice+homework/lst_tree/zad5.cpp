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

lista ostatni(lista a) {
    lista save = a;
    while(save->next != NULL) {
        save = save->next;
    }
    return save;
}

int Policz_el(lista j) {
    int k = 1;
    lista c = j;
    while(j->next != NULL) {
        j = j->next;
        k++;
    }
    j = c;
    return k;
}

lista wsp_fragment(lista a, lista b) {
    lista save_a = a, save_b = b;
    int jed = Policz_el(a);
    int dwa = Policz_el(b);
    if(jed > dwa) {
        for(int i = 0; i < jed - dwa; i++) {
            a = a->next;
        }
    } else {
        for(int i = 0; i < dwa - jed; i++) {
            b = b->next;
        }
    }
    lista res;
    while(a != b) {
        a = a->next;
        b = b->next;
    }
    res = a;
    a = save_a;
    b = save_b;
    return res;
}

int main() {
    int a, b;
    srand(time(NULL));
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
    lista l3 = ostatni(l2);
    lista l4 = l1;
    int k = rand() % a;
    printf("%d\n", k);
    for(int l = 0;l < k;l++) {
        l4 = l4->next;
    }
    l3->next = l4;
    lista sex = wsp_fragment(l1, l2);
    if(sex != l4) {
        printf("gejuchu\n");
    } else {
        printf("sigma\n");
    }
    c = zwroc_lista(sex);
    for(int k: c) {
        printf("%d ",k);
    }
    delete l1;
    l3->next = NULL;
    delete l2;
    return 0;
}