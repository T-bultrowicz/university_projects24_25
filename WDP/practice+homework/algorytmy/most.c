#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

int mini(int a, int b) {
    return (a > b) ? b : a;
}

bool possible(int *t, int s, int k, int c, int dystans) {
    int i = 0, j = 0;
    int minimum = INT_MAX;
    while(j < s) {
        minimum = mini(minimum, t[j]);
        if((j - i + dystans) / dystans * c > minimum) {
            if(k == 0) {
                return false;
            } else {
                k--;
                minimum = t[j];
                i = j;
            }
        } else {
            j++;
        }
    }
    return true;
}


int most(int *t, int s, int k) {
    int c = INT_MAX, dystans_l = 1, dystans_p = (s + k) / (k + 1); //do bin searcha
    int mid;
    for(int i = 0; i < s; i++) { //szukanie wartosci c;
        c = mini(c, t[i]);
    }
    while(dystans_l < dystans_p) { //bin search po wyniku
        mid = (dystans_l + dystans_p) / 2;
        if(possible(t, s, k, c, mid)) { //sprawdzenie mozliwosci rozlozenia podpor
            dystans_p = mid;
        } else {
            dystans_l = mid + 1;
        }
    }
    return dystans_l;
}

int main() {
    int a, b;
    if(scanf("%d%d",&a, &b) != 2) {
        return -1;
    }
    int *tab = malloc((unsigned) a * sizeof(int));
    for(int i = 0;i < a; i++) {
        if(scanf("%d", tab + i) != 1) {
            return -1;
        }
    }
    printf("%d", most(tab, a, b));
    free(tab);
    return 0;
}
