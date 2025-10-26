#include<bits/stdc++.h>
using namespace std;

bool isVowel(char a) {
    return (a == 'a' || a == 'e' || a == 'o' || a == 'i' || a == 'u');
}

int maxVowels(string s, int k) {
    int res = 0, max_res;
    for(int i = 0; i < k; i++) {
        res += isVowel(s[i]);
    }
    max_res = res;
    for(int j = k; j < s.size(); j++) {
        res -= isVowel(s[j - k]);
        res += isVowel(s[j]);
        max_res = max(res, max_res);
    }
    return max_res;
}

int main() {
    string s;
    int k;
    cin >> s >> k;
    cout << maxVowels(s, k);
    return 0;
}