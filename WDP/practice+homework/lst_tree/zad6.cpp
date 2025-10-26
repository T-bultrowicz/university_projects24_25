#include<bits/stdc++.h>
using namespace std;

typedef struct elem {
    int val;
    elem *next;
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

lista check_cykl(const lista l) {
    lista slow = l, fast = l;
    if(slow->next == NULL || slow->next->next == NULL) {
        return NULL;
    }
    while(true) {
        if(slow->next == NULL || fast->next == NULL || fast->next->next == NULL) {
            return NULL;
        } else {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) {
                return slow;
            }
        }
    }
    return NULL;
}

void dodaj_los_cykl(const lista l, int d) {
    if(rand() % 2 == 0) {
        printf("nie dodano\n");
        return;
    } else {
        lista g = l, h = l;
        int k = rand() % d;
        printf("Jest na miejscu:%d\n", k);
        while(g->next != NULL) {
            g = g->next;
        }
        for(int j = 0; j < k; j++) {
            h = h->next;
        }
        g->next = h;
        return;
    }
}

int rozmiar_petli(const lista a) {
    lista b = a;
    int k = 1;
    b = b->next;
    while(a != b) {
        b = b->next;
        k++;
    }
    return k;
}


int main() {
    int a;
    srand(time(NULL));
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    vector <int> c;
    int acc;
    for(int i = 0; i < a; i++) {
        if(scanf("%d", &acc) != 1) {
            return -1;
        }
        c.push_back(acc);
    }
    lista l = stworz_lista(c);
    dodaj_los_cykl(l, a);
    lista check = check_cykl(l);
    if(check) {
        printf("sigma balls%d", rozmiar_petli(check));
        lista hwdp = check->next;
        check->next = NULL;
        delete hwdp;
    } else {
        printf("nigger");
    }
    delete l;
    return 0;
}