#include<bits/stdc++.h>
using namespace std;

int calc_area(int x, int y, int d) {
    return min(x, y) * d;
}

int maxArea(vector<int>& t) {
    int x = t.size();
    int i = 0, j = x - 1, k;
    int max_area = calc_area(t[i], t[j], j - i);
    while(i < j) {
        if(t[i] < t[j]) {
            k = i + 1;
            while(k < j && t[k] <= t[i]) {
                k++;
            }
            max_area = max(max_area, max(calc_area(t[i], t[k], k - i), calc_area(t[k], t[j], j - k)));
            i = k;
        } else {
            k = j - 1;
            while(k > i && t[k] <= t[j]) {
                k--;
            }
            max_area = max(max_area, max(calc_area(t[i], t[k], k - i), calc_area(t[k], t[j], j - k)));
            j = k;
        }
    }
    return max_area;
}

int main() {
    int x;
    cin >> x;
    vector<int> tab(x);
    for(int i = 0; i < x; i++) {
        cin >> tab[i];
    }
    cout << maxArea(tab);
    return 0;
}