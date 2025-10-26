#include<bits/stdc++.h>
using namespace std;

bool is_vowel(char a) {
    if(a == 'a' || a == 'e' || a == 'o' || a == 'u' || a == 'i' || a == 'A' || a == 'E' ||
        a == 'O' || a == 'I' || a == 'U') return true;
    return false;
}

int main() {
    string s;
    cin >> s;
    int i = 0, j = s.size() - 1;
    while(i < j) {
        while(i < s.size() && !is_vowel(s[i])) i++;
        while(j >= 0 && !is_vowel(s[j])) j--;
        if(i < j) {
            char a = s[i];
            s[i] = s[j];
            s[j] = a;
        }
        i++;
        j--;
    }
    cout << s;
    return 0;
}