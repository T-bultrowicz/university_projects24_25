#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int bity (unsigned int x) {
    int res=0;
    while(x>1) {
        res += x & 1;
        x = x >> 1;
    }
    return res+1;
}
int main() {
    int x;
    if(scanf("%d",&x)!=1) {
        return -1;
    }
    printf("%d",bity((unsigned int) x));
    return 0;
}
