#include<bits/stdc++.h>
using namespace std;

string znajdz_slowo(int& i, string& s) {
    string res = "";
    while(i < s.size() && s[i] != ' ') {
        res.push_back(s[i++]);
    }
    return res;
}

void przeskocz_spacje(int &i, string& s) {
    while(i < s.size() && s[i] == ' ') {
        i++;
    }
    return;
}

int main() {
    vector<string> words;
    string s = "  hello world ";
    int i = 0;
    przeskocz_spacje(i, s);
    while(i < s.size()) {
        words.push_back(znajdz_slowo(i, s));
        przeskocz_spacje(i, s);
    }
    s.clear();
    for(int i = words.size() - 1; i >= 0; i--) {
        s += words[i];
        s.push_back(' ');
    }
    s.resize(s.size() - 1);
    cout << s;
    return 0;
}