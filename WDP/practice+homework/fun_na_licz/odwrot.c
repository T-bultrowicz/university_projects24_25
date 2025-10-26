#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int odwrot(int n) {
    assert(n>=0);
    int res = 0;
    while(n>0) {
        res *= 10;
        res += n%10;
        n /= 10;
    }
    return res;
}

int main() {
    int n;
    scanf("%d",&n);
    printf("%d",odwrot(n));
    return 0;
}
