#include<bits/stdc++.h>
using namespace std;

int slupki(const vector <int> s) {
    vector <int> operand = s;
    sort(operand.begin(), operand.end());
    int mediana, res = 0;
    if(operand.size() % 2 == 0) {
        mediana = (operand[(operand.size() / 2) - 1] + operand[operand.size() / 2]) / 2;
    } else {
        mediana = operand[operand.size() / 2];
    }
    for(int i = 0;i < operand.size(); i++) {
        res += abs(operand[i] - mediana);
    }
    return res;
}

int main() {
    int a;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    vector <int> b;
    int b_acc;
    for(int i = 0; i < a; i++) {
        if(scanf("%d", &b_acc) != 1) {
            return -1;
        }
        b.push_back(b_acc);
    }
    printf("%d", slupki(b));
    return 0;
}