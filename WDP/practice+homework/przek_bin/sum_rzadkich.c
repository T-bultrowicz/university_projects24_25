#include<stdlib.h>
#include<stdio.h>

struct suma {
    long int pierwsza;
    long int druga;
};
typedef struct suma sum;

sum sum_rzadkich(long int n) {
    long int i = 0, j = 1;
    int skb = 0;
    sum ret;
    ret.pierwsza = 0;
    ret.druga = 0;
    if(n < 0) {
        n *= -1;
        skb = 1;
    }
    while(n > 0) {
        if(n & 1 == 1) {
            if(i % 2 == 0) {
                ret.pierwsza += j;
            } else {
                ret.druga += j;
            }
        }
        i++;
        j *= 2;
        n >>= 1;
    }
    if(skb) {
        ret.druga *= -1;
        ret.pierwsza *= -1;
    }
    return ret;
}

int main() {
    long int x;
    if(scanf("%ld", &x) != 1) {
        return -1;
    }
    sum res = sum_rzadkich(x);
    printf("%ld %ld",res.pierwsza, res.druga);
    return 0;
}
