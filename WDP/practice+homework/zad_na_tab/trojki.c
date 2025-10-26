#include<stdio.h>
#include<stdlib.h>

int trojki(int* t, int s_t) {
    int res = 0;
    int k;
    for(int i = 0;i< s_t - 2;i++) {
        k = i + 2;
        for(int j = i + 1;j < s_t - 1;j++) {
            printf("%d  %d  %d  %d\n",i,j,k,res);
            while(k<=j) {
                k++;
            }
            while(k < s_t && t[k] < t[i] + t[j]) {
                k++;
            }
            res += k - j - 1;
        }
    }
    return res;
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
    printf("%d",trojki(tab,s));
    free(tab);
    return 0;
}
