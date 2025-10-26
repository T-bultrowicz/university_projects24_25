#include<stdlib.h>
#include<stdio.h>

int czy_rzadka(int n) {
    int poprzednia = 0;
    while(n > 0) {
        if(n & 1 == 1) {
            if(poprzednia) {
                return 0;
            } else {
                poprzednia = 1;
            }
        } else {
            poprzednia = 0;
        }
        n >>= 1;
    }
    return 1;
}


int main() {
    int x;
    if(scanf("%d", &x) != 1) {
        return -1;
    }
    if(czy_rzadka(x)) {
        printf("TAK");
    } else {
        printf("NIE");
    }
    return 0;
}
