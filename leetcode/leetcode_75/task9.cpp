#include<bits/stdc++.h>
using namespace std;

int ilosc_cyfr(int liczba) {
    if(liczba < 10) return 1;
    int x = 10;
    int i = 1;
    while(x * x <= liczba) {
        x *= x;
        i += i;
    }
    return i + ilosc_cyfr(liczba / x);
}

int main() {
    cout << ilosc_cyfr(100) << " " << ilosc_cyfr(1997234) << " " << ilosc_cyfr(12);
    string s;
    cin >> s;
    int streak = 1, kolj = 0;
    for(int i = 0; i < s.size() - 1; i++) {
        if(s[i + 1] == s[i]) {
            streak++;
        } else {
            if(streak == 1) {
                kolj++;
            } else {
                kolj += 1 + ilosc_cyfr(streak);
            }
            streak = 1;
        }
    }
    if(streak == 1) {
        kolj++;
    } else {
        kolj += 1 + ilosc_cyfr(streak);
    }
    cout << kolj;
    return 0;
}