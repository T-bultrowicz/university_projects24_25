#include<stdlib.h>
#include<stdio.h>

int Popraw(int a, int b) {
    int pom = a / (b * 2);
    a = a | (b * 2);
    a = a & (b * 2);
    a *= pom;
    a += b * 2;
    return a;
}

int next_rzadka(int n) {
    n ++;
    int maska = 1, poprzednia = 0;
    while(maska < n) {
        if(n & maska) {
            if(poprzednia) {
                n = Popraw(n, maska);
                poprzednia = 0;
            } else {
                poprzednia = 1;
            }
        } else {
            poprzednia = 0;
        }
        maska *= 2;
    }
    return n;
}


int main() {
    int x;
    if(scanf("%d", &x) != 1) {
        return -1;
    }
    printf("%d", next_rzadka(x));
    return 0;
}
