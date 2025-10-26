#include<bits/stdc++.h>
using namespace std;

int main() {
    string str1, str2;
    cin >> str1 >> str2;
    while(str1.size() != str2.size()) {
        size_t a = str1.size(), b = str2.size();
        if(a > b) {
            if(str1.substr(a - b, b) == str2) {
                str1 = str1.substr(0, a - b);
            } else {
                cout << "";
                return 0;
            }
        } else {
            if(str2.substr(b - a, a) == str1) {
                str2 = str2.substr(0, b - a);
            } else {
                cout << "";
                return 0;
            }
        }
    }
    if(str1 == str2) {
        cout << str1;
        return 0;
    }
    cout << "";
    return 0;
}