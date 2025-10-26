#include<bits/stdc++.h>
using namespace std;

int longestNiceSubarray(vector<int>& t) {
    int s = t.size();
    int i = 0, j = 1, best = 1, l;
    int b_or_i = t[i];
    while(j < s) {
        l = t[j] & b_or_i;
        if(i == j) {
            b_or_i = t[i];
            j++;
        } else if(!l) {
            b_or_i = b_or_i | t[j++];
            best = max(best, j - i);
        } else {
            b_or_i = b_or_i ^ t[i++];
        }
    }
    l = t[s - 1] &  b_or_i;
    if(!l) best = max(best, s - i);
    return best;
}

int main() {
    int x;
    int d[] = {84139415,693324769,614626365,497710833,615598711,264,65552,50331652,1,1048576,16384,544,270532608,151813349,221976871,678178917,845710321,751376227,331656525,739558112,267703680};
    cin >> x;
    vector <int> t(x), tl;
    for(int i = 0; i < x; i++) {
        cin >> t[i];
    }
    for(int i = 0; i < 22; i++) {
        tl.push_back(d[i]);
    }
    cout << longestNiceSubarray(t);
    return 0;
}