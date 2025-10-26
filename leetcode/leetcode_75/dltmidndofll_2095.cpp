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
    vector <int> res;
    while(a->next != NULL) {
        res.push_back(a->val);
        a = a->next;
    }
    res.push_back(a->val);
    return res;
}

   
lista deleteMiddle(lista head) {
    if(head->next == NULL) {
        delete(head);
        return NULL;
    }
    if(head->next->next == NULL) {
        delete(head->next);
        head->next = NULL;
        return head;
    }
    lista res = head;
    lista fore_mid = head;
    while(head != NULL) {
        head = head->next;
        if(head == NULL) break;
        head = head->next;
        if(head == NULL) break;
        if(head->next == NULL) break;
        fore_mid = fore_mid->next;
    }
    lista pin_to = fore_mid->next->next;
    fore_mid->next->next = NULL;
    delete(fore_mid->next);
    fore_mid->next = pin_to;
    return res;
}

lista oddEvenList(lista head) {
    if(head->next == NULL) return head;
    if(head->next->next == NULL) return head;
    if(head->next->next->next == NULL) {
        head->next->next->next = head->next;
        head->next->next = NULL;
        return head;
    }
    lista mem = head->next;
    lista l1 = head, l2 = head->next;
    while(l2 != NULL) {
        l1->next = l2->next;
        if(l1->next == NULL) break;
        if(l1->next->next == NULL) {
            l2->next = NULL;
            l1->next->next = mem;
            break;
        }
        l2->next = l1->next->next;
        l1 = l1->next;
        l2 = l2->next;
    }
    l1->next = mem;
    return head;
}

lista reverseList(lista head) {
    if(head == NULL) return NULL;
    if(head->next == NULL) return head;
    lista l1 = head, l2 = head->next, l3;
    l1->next = NULL;
    while(l2 != NULL) {
        l3 = l2->next;
        l2->next = l1;
        l1 = l2;
        l2 = l3;
    }
    return l1;
}

int main() {
    int x;
    cin >> x;
    vector<int> t(x);
    for(int i = 0;i < x; i++) t[i] = i;
    lista a = stworz_lista(t);
    t = zwroc_lista(a);
    for(int i = 0; i < x - 1 ; i++) cout << t[i] << " ";
    lista b = reverseList(a);
    t = zwroc_lista(b);
    for(int i = 0; i < x - 1 ; i++) cout << t[i] << " ";
    delete(a);
    return 0;
}
