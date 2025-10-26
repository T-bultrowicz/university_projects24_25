#include "prev.h"
#include<cstdlib>
#include<cstdio>
#include<climits>
#include<memory>

typedef struct node {
    int val;
    std::shared_ptr<node> left, right;
} node;

typedef std::shared_ptr<node> bin_tree;

//przechowuje pamiec dotyczaca poszczegolnych zapytan o wystepowanie wartosci
std::vector<bin_tree> _ALL_NODES;


//sprawdza czy przedzial [l_rng, r_rng] zawiera sie calkowicie w przedziale [l, r]
bool totally_in(long long int l_rng, long long int r_rng, long long int l, long long int r) {
    return (l_rng >= l) && (r_rng <= r);
}

//sprawdza czy przedzial [l_rng, r_rng] zawiera sie czesciowo w przedziale [l, r]
bool partially_in(long long int l_rng, long long int r_rng, long long int l, long long int r) {
    return (l_rng <= l && r_rng >= l) || (r_rng >= r && l_rng <= r);
}

long long int dziel(long long int l, long long int r) {
    return ((l & 1) ^ (r & 1)) ? (l + r - 1) / 2 : (l + r) / 2;
}

//funkcja rekurencyjna pomocnicza uzywana w funkcji pushBack,
//aktualizuje historie drzewa
void r_update(bin_tree t, bin_tree pin_to, long long int l, long long int r, const int result, const long long int v) {
    if(l == r) return;
    long long int mid = dziel(l, r);
    if((v >= l) && (v <= mid)) {
        t->left = std::make_shared<node>();
        t->left->val = result;
        if(pin_to) {
            t->right = pin_to->right;
            r_update(t->left, pin_to->left, l, mid, result, v);
        } else {
            r_update(t->left, NULL, l, mid, result, v);
        }
    } else {
        t->right = std::make_shared<node>();
        t->right->val = result;
        if(pin_to) {
            t->left = pin_to->left;
            r_update(t->right, pin_to->right, mid + 1, r, result, v);
        } else {
            r_update(t->right, NULL, mid + 1, r, result, v);
        }
    }
}


//dodaje wartosc value do struktury drzew interwalowych _ALL_NODES
void pushBack(int value) {
    bin_tree t = std::make_shared<node>();
    bin_tree prev = (_ALL_NODES.size() > 0) ? _ALL_NODES[_ALL_NODES.size() - 1] : (std::shared_ptr<node>) NULL;
    t->val = (int) _ALL_NODES.size();
    _ALL_NODES.push_back(t);
    r_update(t, prev, INT_MIN, INT_MAX, t->val, (long long int) value);
    return;
}

//inicjuje strukture drzew interwalowych _ALL_NODES dla wektora seq
void init(const std::vector<int>& seq) {
    for(int v: seq) {
        pushBack(v);
    }
    return;
}

//zwalnia pamiec struktury _ALL_NODES pod koniec zapytan
void done() {
    _ALL_NODES.clear();
    return;
}

//funkcja rekurencyjna pomocnicza dla prevInRange, znajduje ostatnie wyst. liczby z przedzialu [lo, hi]
//wsrod dzieci danego wierzcholka t obslugujacego wyniki z przedzialu [l, r]
int r_find_prev(bin_tree t, long long int lo, long long int hi, long long int l, long long int r) {
    if(!t) return -1;
    if(totally_in(l, r, lo, hi)) return t->val;
    long long int mid = dziel(l,r);
    int l_res = -1, r_res = -1;
    if(partially_in(l, mid, lo, hi)) {
        l_res = r_find_prev(t->left, lo, (hi > mid) ? mid : hi, l ,mid);
    }
    if(partially_in(mid + 1, r, lo, hi)) {
        r_res = r_find_prev(t->right, (lo < mid + 1) ? mid + 1: lo, hi, mid + 1, r);
    }
    return (l_res > r_res) ? l_res : r_res;
}


//zwraca ostatnie wystapienie liczby z przedzialu [lo, hi]
//na miejscach [0, i] wektora obsl. przez ALL_NODES
int prevInRange(int i, int lo, int hi) {
    return r_find_prev(_ALL_NODES[i], (long long int) lo, (long long int) hi, INT_MIN, INT_MAX);
}

