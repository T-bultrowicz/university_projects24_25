#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int wybory(int* t, int t_size) {
    int kandydat = t[0];
    int ilosc = 1;
    for(int i=1;i<t_size;i++) {
        if(t[i]==kandydat) {
            ilosc++;
        } else {
            ilosc--;
        }
        if(ilosc==0) {
            kandydat = t[i];
            ilosc = 1;
        }
    }
    printf("%d   ",kandydat);
    ilosc = 0;
    for(int j=0;j<t_size;j++) {
        if(t[j]==kandydat) {
            ilosc++;
        }
    }
    if(ilosc>t_size/2) {
        return kandydat;
    }
    return -1;
}

int main() {
    int a;
    if(scanf("%d",&a)!=1) {
        return -1;
    }
    int* tab = malloc((unsigned int) a * sizeof(int));
    for(int j=0;j<a;j++) {
        if(scanf("%d",tab+j)!=1) {
            return -1;
        }
    }
    printf("%d",wybory(tab,a));
    free(tab);
    return 0;
}
