#include<bits/stdc++.h>
using namespace std;


int klocki[7][7];
bool pot_pocz[7][7];

void dodaj(int i, int j) {
    klocki[i][j]++;
    klocki[j][i]++;
}

bool zabierz(int i, int j) {
    if(klocki[i][j] > 0) {
        klocki[i][j]--;
        klocki[j][i]--;
        return true;
    }
    return false;
}

void wyzeruj() {
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 7; j++) {
            klocki[i][j] = 0;
            pot_pocz[i][j] = true;
        }
    }
}

void r_dom(int count, bool left, bool right, int lv, int rv, int& bst) {
    if(left) {
        for(int k = 0; k < 7; k++) {
            if(zabierz(lv, k)) {
                r_dom(count + 1, true, false, k ,lv, bst);
                if(!right) pot_pocz[lv][rv] = false; 
            }
        }
    }
    if(right) {
        for(int k = 0; k < 7; k++) {
            if(zabierz(rv, k)) {
                r_dom(count + 1, false, true, rv, k, bst);
                if(!left) pot_pocz[lv][rv] = false;
            }
        }
    }
    dodaj(lv, rv);
    bst = max(bst, count);
    return;
}

int domino(const vector<pair<int,int>>& k) {
    for(auto a : k) {
        dodaj(a.first, a.second);
    }
    int bst = INT_MIN;
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 7; j++) {
            if(zabierz(i,j) && pot_pocz[i][j]) {
                r_dom(1, true, true, i, j, bst);
            }
        }
    }
    return bst;
}

int main() {
    wyzeruj();
    int n, a, b;
    scanf("%d", &n);
    vector<pair<int,int>> klocki;
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &a, &b);
        klocki.push_back(make_pair(a,b));
    } 
    printf("%d ", domino(klocki));
    return 0;
}