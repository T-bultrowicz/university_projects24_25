#include<bits/stdc++.h>
using namespace std;

int do_search(unordered_set <int> *p, int l) {
    if(p->find(l - 1) != p->end() && p->find(l + 1) != p->end()) {
        p->insert(l);
        return -1;
    } else if(p->find(l - 1) == p->end() && p->find(l + 1) == p->end()) {
        p->insert(l);
        return 1;
    } else {
        p->insert(l);
        return 0;
    }
}

int wyspy(const vector <int> s) {
    vector <pair <int, int> > dane;
    unordered_set <int> zle;
    zle.insert(-1);
    zle.insert(s.size());
    int ilosc_wysp = 1, res = 1, ind = 0;
    for(int i = 0; i < s.size(); i++) {
        dane.push_back({s[i], i});
    }
    sort(dane.begin(), dane.end());
    while(ind < s.size() - 1) {
        while(dane[ind].first == dane[ind + 1].first) {
            ilosc_wysp += do_search(&zle, dane[ind++].second);
            if(ind == s.size() - 1) {
                break;
            }
        }
        ilosc_wysp += do_search(&zle, dane[ind++].second);         
        if(res < ilosc_wysp) {
            res = ilosc_wysp;
        }
    }
    ilosc_wysp += do_search(&zle, dane[ind++].second);             
    if(res < ilosc_wysp) {
        res = ilosc_wysp;
    }    
    return res;
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
    printf("%d", wyspy(b));
    return 0;
}