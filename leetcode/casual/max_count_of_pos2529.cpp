#include<bits/stdc++.h>
using namespace std;

int maximumCount(vector <int>& t) {
    int s = t.size();
    if(!s) return 0;
    if(s == 1) return t[0] ? 1 : 0;
    int left_0, right_0;
    int l = 0, r = s - 1, mid;
    while(l < r) {
        mid = (l + r) / 2;
        if(t[mid] >= 0) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    if(!l && t[l] >= 0) l--;
    if(l == s - 1 && t[l] < 0) l++;
    left_0 = l;
    l = 0, r = s - 1;
    while(l < r) {
        mid = (l + r) / 2;
        if(t[mid] <= 0) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    if(l == s - 1 && t[l] <= 0) l++; 
    right_0 = l;
    return max(left_0,(int) s - right_0);
}


int main() {
    int x;
    cin >> x;
    vector <int> t(x);
    for(int i = 0; i < x; i++) {
        cin >> t[i];
    }
    cout << maximumCount(t);
    return 0;
}