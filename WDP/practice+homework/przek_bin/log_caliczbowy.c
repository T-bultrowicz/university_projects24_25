#include<stdlib.h>
#include<stdio.h>
#include<assert.h>

int log_caliczbowy(long long int n) {
    int log = 0;
    if(n == 1) {
        return 0;
    }
    if(n >= (long long int) 1 << 32) {
        printf("%llb\n", n);
        n >>= 32;
        log += 32;
    }
    if(n >= (long long int) 1 << 16) {
        printf("%llb\n", n);
        n >>= 16;
        log += 16;
    }
    if(n >= 1 << 8) {
        printf("%llb\n", n);
        n >>= 8;
        log += 8;
    }
    if(n >= 1 << 4) {
        printf("%llb\n", n);
        n >>= 4;
        log += 4;
    }
    if(n >= 1 << 2) {
        printf("%llb\n", n);
        n >>= 2;
        log += 2;
    }
    if(n > 1) {
        printf("%llb\n", n);
        n >>= 1;
        log += 1;
    }
    return log;
}


int main() {
    long long int x;
    if(scanf("%lld", &x) != 1) {
        return -1;
    }
    printf("%d", log_caliczbowy(x));
    return 0;
}
