#include<bits/stdc++.h>
using namespace std;

bool pierwsza(int n) {
    if(!n) return false;
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0) return false;
    }
    return true;
}

vector<int>pierwsze(int n) {
    vector<int> wynik;
    if(pierwsza(n)) {
        wynik.push_back(n);
        return wynik;
    } else if(n % 2 == 0) {
        for(int i = 2; i <= n / 2; i++) {
            if(pierwsza(i) && pierwsza(n - i)) {
                wynik.push_back(i);
                wynik.push_back(n - i);
                return wynik;
            }
        }
    } else {
        if(pierwsza(n - 2)) {
            wynik.push_back(2);
            wynik.push_back(n - 2);
            return wynik;
        }
        n -= 3;
        for(int i = 2; i <= n / 2; i++) {
            if(pierwsza(i) && pierwsza(n - i)) {
                wynik.push_back(3);
                wynik.push_back(i);
                wynik.push_back(n - i);
                return wynik;
            }
        }       
    }
    return wynik;
}

int main() {
    int n;
    scanf("%d", &n);
    vector<int> pierw = pierwsze(n);
    for(int i = 0; i < pierw.size(); i++) {
        printf(" %d ", pierw[i]);
    }
    return 0;
}