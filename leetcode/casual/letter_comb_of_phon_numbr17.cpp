#include<bits/stdc++.h>
using namespace std;

vector<char> possible(char num) {
    int x = (int) num;
    if(x == 55) return {'p', 'q', 'r', 's'};
    if(x == 56) return {'t', 'u', 'v'};
    if(x == 57) return {'w', 'x', 'y', 'z'};
    return {(char) (int) (3 * num - 53), (char) (int) (3 * num - 52), (char) (int) (3 * num - 51)};
}

void recursiveCombinations(const string& a, vector<string>& r, int what, string& l) {
    if(what == a.size()) {
        r.push_back(l);
        return;
    }
    for(auto c : possible(a[what])) {
        l.push_back(c);
        recursiveCombinations(a, r, what + 1, l);
        l.pop_back();
    }
    return;
}


vector<string> letterCombinations(string digits) { 
    string a = digits, l;
    vector<string> res;
    if(!digits.size()) return res; 
    recursiveCombinations(a, res, 0, l);
    return res;
}

int main() {
    string s = "23";
    vector <string> ss;
    ss = letterCombinations(s);
    for(auto a : ss) {
        cout << a << endl;
    }
    return 0;
}