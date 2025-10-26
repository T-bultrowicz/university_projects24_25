#include<stdlib.h>
#include<stdio.h>


long int pwr(long long int a, int b) {
    long long int k = 2, l = a;
    while(b >= k) {
        k *= 2;
    }
    k /= 2;
    b = b - k;
    while(k > 1) {
        a *= a;
        k /= 2;
    }
    while(b > 0) {
        a *= l;
        b--;
    }
    return a;
}


long long int Hanoi_licz(int t[], int s) {
    long long int res = 0;
    int gdzie_my_teraz = 0;
    for(int i = s - 1; i >= 1; i--) {
        if(t[i] != gdzie_my_teraz) {
            res += pwr(2, i);
            gdzie_my_teraz = 3 - t[i] - gdzie_my_teraz;
        }
    }
    if(t[0] != gdzie_my_teraz) {
        res++;
    }
    return res;
}

int main() {
    int x, res = 0;
    if(scanf("%d", &x) != 1) {
        return -1;
    }
    int polozenia[x];
    for(int i = x - 1; i >= 0; i--) {
        if(scanf("%d", polozenia + i) != 1) {
            return -1;
        }
    }
    printf("%lld", Hanoi_licz(polozenia, x));
    return 0;
}
