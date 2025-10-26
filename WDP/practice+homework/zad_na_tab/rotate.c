#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int NWD(int n1, int n2) {
    while(n1!=n2) {
        if(n1>n2) {
            n1 -= n2;
        } else {
            n2 -= n1;
        }
    }
    return n1;
}

void Rotuj(int n, int* t,int k) {
    assert(n>0&&k>0);
    int l = NWD(n,k);
    int copy, paste, ind;
    for(int i=0;i<l;i++) {
        paste = t[i];
        ind = i+k;
        ind %= n;
        while(ind!=i) {
            copy = t[ind];
            t[ind] = paste;
            paste = copy;
            ind += k;
            ind %= n;
        }
        t[i] = paste;
    }
}

int main() {
    int a, b;
    if(scanf("%d %d",&a,&b)!=2) {
        return -1;
    }
    assert(a>0);
    int* tab = malloc((unsigned int) a * sizeof(int));
    for(int j=0;j<a;j++) {
        if(scanf("%d",tab+j)!=1) {
            return -1;
        }
    }
    Rotuj(a,tab,b);
    for(int i=0;i<a;i++) {
        printf("%d ",tab[i]);
    }
    free(tab);
    return 0;
}
