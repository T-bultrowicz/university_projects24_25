#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int mini(int a, int b) {
    return (a < b) ? a : b;
}
int maxi(int a, int b) {
    return (a > b) ? a : b;
}

int brut_mala(int s, int* siec, int* odl) {
    int mala = INT_MAX;
    for(int i = 0; i < s ; i++) {
        for(int j = i + 1; j < s; j++) {
            for(int k = j + 1; k < s; k++) {
                if(siec[i] != siec [j] && siec[j] != siec[k] && siec[k] != siec[i]) {
                    mala = mini(mala, maxi(odl[k] - odl[j], odl[j] - odl[i]));
                }
            }
        }
    }
    if(mala == INT_MAX) {
        mala = 0;
    }
    return mala;
}

int brut_duza(int s, int* siec, int* odl) {
    int duza = 0;
    for(int i = 0; i < s ; i++) {
        for(int j = i + 1; j < s; j++) {
            for(int k = j + 1; k < s; k++) {
                if(siec[i] != siec [j] && siec[j] != siec[k] && siec[k] != siec[i]) {
                    duza = maxi(duza, mini(odl[k] - odl[j], odl[j] - odl[i]));
                }
            }
        }
    }
    return duza;
}


int main() {
    int a;
    if(scanf("%d", &a) != 1) {
        return -1;
    }
    int *siec = malloc((unsigned)a * sizeof(int));
    int *odl = malloc((unsigned)a * sizeof(int));
    for(int i = 0;i < a; i++) {
        if(scanf("%d%d",siec + i, odl + i) != 2) {
            return -1;
        }
    }
    printf("%d %d",brut_mala(a, siec, odl), brut_duza(a, siec, odl));
    free(siec);
    free(odl);
    return 0;
}
