#include <vector>
#include "prev.h"

std::vector<int> X;

void init(const std::vector<int> &x) {
    X = x;
}

int prevInRange(int i, int lo, int hi) {
    for(int idx = i; idx >= 0; idx--) {
        if(lo <= X[idx] && X[idx] <= hi) {
            return idx;
        }
    }
    
    return -1;
}

void pushBack(int v) {
    X.push_back(v);
}

void done() {
    X.clear();
}