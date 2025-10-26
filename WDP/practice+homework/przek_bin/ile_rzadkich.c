#include<stdlib.h>
#include<stdio.h>

double sqrt_5 = 2.2360679775;


typedef struct matryca_2na2 {
    int l_gorny;
    int l_dolny;
    int p_gorny;
    int p_dolny;
} matryca_2na2;


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
   // printf("%d   ", n);
    return n;
}


double pwr(double a, int b) {
    if(b == 0) {
        return 1;
    }
    double l = a;
    while(b > 1) {
        if(b % 2 == 1) {
            a *= l;
            b --;
        } else {
            a *= a;
            b /= 2;
        }
    }
    return a;
}

// Implementuje mnozenie matryc 2 na 2
matryca_2na2 M_mat(matryca_2na2 a, matryca_2na2 b) {
    matryca_2na2 c = a;
    c.l_gorny = a.l_gorny * b.l_gorny + a.p_gorny * b.l_dolny;
    c.l_dolny = a.l_dolny * b.l_gorny + a.p_dolny * b.l_dolny;
    c.p_dolny = a.l_dolny * b.p_gorny + a.p_dolny * b.p_dolny;
    c.p_gorny = a.l_gorny * b.p_gorny + a.p_gorny * b.p_dolny;
    return c;
}

// Implementuje potegowanie matryc 2 na 2, ok 3 * log n
matryca_2na2 P_mat(matryca_2na2 a, int n) {
    matryca_2na2 pot = a;
    int l = 0, b = 1;
    while(n >= b) {
        b *= 2;
        l ++;
    }
    b /= 2;
    n -= b;
    l --;
    while(l > 0) {
        a = M_mat(a, a);
        l --;

    }
    while(n > 0) {
        a = M_mat(a, pot);
        n--;
    }
    return a;
}


int fib(int x) {
    x += 1;
    matryca_2na2 mat;
    mat.l_dolny = 1;
    mat.l_gorny = 1;
    mat.p_dolny = 0;
    mat.p_gorny = 1;
    mat = P_mat(mat, x);
    return mat.l_gorny;
}


int ile_rzadkich(int n) {
    int i = 0, j = 1;
    int res = 0;
    if(n != next_rzadka(n - 1)) {
        res --;
    }
    n = next_rzadka(n - 1);
    while(j <= n) {
        if(n & j) {
            res += fib(i);
        }
        j *= 2;
        i ++;
    }
    return res;
}
// Zlozonosc Memory O(1)  , Time O( n * log n) ) = GOATED BEST POSSIBLE

int main() {
    int x;
    if(scanf("%d", &x) != 1) {
        return -1;
    }
    printf("%d", ile_rzadkich(x));
    return 0;
}
