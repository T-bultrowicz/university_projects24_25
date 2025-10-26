#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> Solve(vector <int>& t) {
    vector< vector <int>> res;
    sort(t.begin(), t.end());
    int s = t.size();
    for(int i = 0; i < s; i++) {
        int j = i - 1, k = i + 1;
        while(j >= 0 && k < s) {
            if(t[i] + t[j] + t[k] == 0) {
                res.push_back({t[i], t[j], t[k]});
                if(k + 1 < s) {
                    while(k + 1 == s || t[k + 1] == t[k]) {
                        k++;
                    }
                    k++;
                }
                else {
                    while(j - 1 == -1 || t[j - 1] == t[j]) {
                        j--;
                    }
                    j--;                 
                }
            } else if(t[i] + t[j] + t[k] < 0) {
                while(k + 1 == s || t[k + 1] == t[k]) {
                    k++;
                }
            } else {
                while(j - 1 == -1 || t[j - 1] == t[j]) {
                    j--;
                }
                j--;
            }
        }
    }
    return res;
}

int main() {
    int x;
    cin >> x;
    vector<int> tab(x);
    for(int i = 0; i < x; i++) {
        cin >> tab[i];
    }
    for(auto a : Solve(tab)) {
        for(int i : a) {
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}
