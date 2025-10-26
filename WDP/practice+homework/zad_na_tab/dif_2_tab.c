#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int next(int i, int* table, int table_s) {
    for(int l = i+1;l<table_s;l++) {
        if(table[l]!=table[i]) {
            return l;
        }
    }
    return table_s;
}

int dif_2_tab(int* t_l, int* t_r, int l_size, int r_size) {
    int l_ind = 0, r_ind = 0;
    int res = 0;
    while(l_ind<l_size&&r_ind<r_size) {
        res++;
        if(t_l[l_ind]<t_r[r_ind]) {
            l_ind = next(l_ind,t_l,l_size);
        } else if(t_l[l_ind]>t_r[r_ind]) {
            r_ind = next(r_ind,t_r,r_size);
        } else {
            l_ind = next(l_ind,t_l,l_size);
            r_ind = next(r_ind,t_r,r_size);
        }
    }
    while(l_ind<l_size) {
        res++;
        l_ind = next(l_ind,t_l,l_size);
    }
    while(r_ind<r_size) {
        res++;
        r_ind = next(r_ind,t_r,r_size);
    }
    return res;
}


int main() {
    int a, b;
    if(scanf("%d%d",&a,&b)!=2) {
        return -1;
    }
    int* tab1 = malloc((unsigned int) a * sizeof(int));
    int* tab2 = malloc((unsigned int) b * sizeof(int));
    for(int i=0;i<a;i++) {
        if(scanf("%d",tab1+i)!=1) {
            return -1;
        }
    }
    for(int i=0;i<b;i++) {
        if(scanf("%d",tab2+i)!=1) {
            return -1;
        }
    }
    printf("%d",dif_2_tab(tab1,tab2,a,b));
    free(tab1);
    free(tab2);
    return 0;
}

