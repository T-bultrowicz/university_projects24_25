#include <stdio.h>
#include <stdlib.h>

int Parzystosc(int n) {
    int res = 0;
    if(n==0) {
        return -1;
    } else if(n<0) {
        n *= -1;
    }
    while(n%2==0) {
        res++;
        n /= 2;
    }
    return res;
}

int main() {
    int x;
    scanf("%d",&x);
    printf("%d",Parzystosc(x));
    return 0;
}
