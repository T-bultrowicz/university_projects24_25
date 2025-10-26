#include<bits/stdc++.h>
using namespace std;

void r_combinationSum3(vector <vector <int>>& r, vector <int>& com, int n, int k, int least) {
    if(n < (2 * least + k  - 1) * k  / 2) return;
    if(n > (19 - k) * k / 2) return;
    if(!n && !k) {
        r.push_back(com);
        return;
    }
    for(int j = least; j < 10; j++) {
        if(j > n) break;
        com.push_back(j);
        r_combinationSum3(r, com, n - j, k - 1, j + 1);
        com.pop_back();
    }
    return;
}

vector<vector<int>> combinationSum3(int k, int n) {
    vector <vector <int>> res;
    vector <int> combination;
    r_combinationSum3(res, combination, n, k, 1);
    return res;
}

int main() {
    int k, n;
    cin >> k >> n;
    vector <vector <int>> res = combinationSum3(k, n);
    for(auto a : res) {
        for(int i : a) {
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}