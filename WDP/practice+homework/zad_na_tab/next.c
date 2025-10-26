#include<stdio.h>
#include<stdlib.h>

void reverse(int* tab, int i_a, int i_b) {
    int copy;
    for(int i = i_a;i <= ((i_b - i_a) / 2) + i_a ;i++) {
        copy = tab[i];
        tab[i] = tab[i_b + i_a - i];
        tab[i_b + i_a - i] = copy;
    }
}

int next(int* t, int s_t) {
    int copy, ind_zmiana = 0;
    for(int i = s_t - 1; i >= 1; i--) {
        if(t[i-1] < t[i]) {
            ind_zmiana = s_t-1;
            for(int j = i; j < s_t ; j++) {
                if(t[j] < t[i-1]) {
                    ind_zmiana = j - 1;
                    break;
                }
            }
            copy = t[ind_zmiana];
            t[ind_zmiana] = t[i-1];
            t[i-1] = copy;
            reverse(t,i,s_t-1);
            return 1;
        }
    }
    reverse(t,0,s_t-1);
    return 0;
}

int main() {
    int s;
    if(scanf("%d",&s)!=1) {
        return -1;
    }
    int* tab = malloc((unsigned int) s * sizeof(int));
    for(int i=0;i<s;i++) {
        if(scanf("%d",tab+i)!=1) {
            return -1;
        }
    }
    printf("%d ",next(tab,s));
    free(tab);
    return 0;
}
