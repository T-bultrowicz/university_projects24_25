#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int zer_jeden(int n) {
    assert(n>0);
    int res=0;
    int k=5;
    while(k<=n) {
        res += n/k;
        k *= 5;
    }
    return res;
}
int main() {
    int x;
    if(scanf("%d",&x)!=1) {
        return -1;
    }
    printf("%d",zer_jeden(x));
    return 0;
}
