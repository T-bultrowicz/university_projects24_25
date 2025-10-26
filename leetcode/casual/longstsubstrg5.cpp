#include<bits/stdc++.h>
using namespace std;

string solve(string s) {
    if(!s.size()) return "";
    pair<int,int> bst_s;
    int begn = -1;
    int ind = 0;
    bool is_middle = true;
    while(ind < s.size()) {
        //check if can be added
        if(begn >= 0 && s[begn] == s[ind]) {
            is_middle = false;
            if(ind - begn + 1 > bst_s.second) {
                bst_s = make_pair(begn, ind - begn + 1);
            }
            begn--;
        } else {
            if(begn < 0) is_middle = true;
            if(!is_middle) ind--;
            begn = ind - 1;
            while(begn >= 0 && s[begn + 1] == s[begn]) {
                begn--;
            }
            if(begn == 0 && s[0] == s[ind]) begn--;
            while(ind + 1 < s.size() && s[ind + 1] == s[ind]) {
                ind++;
            }
            if(ind - begn > bst_s.second) {
                bst_s = make_pair(begn + 1, ind - begn);
            }    
            is_middle = true;
        }
        ind++;
    }
    return s.substr(bst_s.first, bst_s.second);
}

int main() {
    string s;
    cin >> s;
    cout << solve(s);
    return 0;
}