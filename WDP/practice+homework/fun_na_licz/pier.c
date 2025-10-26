#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


int pier(int n) {
    assert(n>0);
    int res = 0;
    int l = 0;
    while(l<=n) {
        res++;
        l += 2*res;
        l -= 1;
    }
    return res-1;
}
int main() {
    int x;
    if(scanf("%d",&x)!=1) {
        return -1;
    }
    printf("%d",pier(x));
    return 0;
}
