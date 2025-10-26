#include<stdio.h>
#include<stdlib.h>

int min(int a, int b) {
    if(a>b) {
        return b;
    } else {
        return a;
    }
}

int wrzucaj(int n_rurka, int rurka[], int n_krazki, int krazki[]) {
    int res = 0;
    int lejek[n_rurka];
    lejek[n_rurka-1] = rurka[n_rurka-1];
    for(int i = n_rurka - 2; i >= 0 ;i--) {
        lejek[i] = min(lejek[i + 1], rurka[i]);
    }
    int i_krazki = 0;
    for(int j = 0;j < n_rurka; j++) {
        if(i_krazki == n_krazki) {
            break;
        }
        if(lejek[j] >= krazki[j]) {
            res++;
            i_krazki++;
        }
    }
    return res;
}

int main() {
    int n_rurka, n_krazki;
    if(scanf("%d%d",&n_rurka,&n_krazki)!=2) {
        return -1;
    }
    int rurka[(unsigned int) n_rurka], krazki[(unsigned int) n_krazki];
    for(int i=0;i<n_rurka;i++) {
        if(scanf("%d",&rurka[i])!=1) {
            return -1;
        }
    }
    for(int j=0;j<n_krazki;j++) {
        if(scanf("%d",&krazki[j])!=1) {
            return -1;
        }
    }
    printf("%d",wrzucaj(n_rurka,rurka,n_krazki,krazki));
    return 0;
}

