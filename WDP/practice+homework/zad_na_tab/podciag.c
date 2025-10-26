#include<stdio.h>
#include<stdlib.h>

int podciag(int s_t_main, int t_main[], int s_t_pod, int t_pod[]) {
    int ind_pod = 0;
    for(int i = 0;i < s_t_main; i++) {
        if(s_t_main - i < s_t_pod - ind_pod) {
            return 0;
        }
        if(t_main[i] == t_pod[ind_pod]) {
            ind_pod++;
        }
        if(ind_pod >= s_t_pod) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int a, b;
    if(scanf("%d%d", &a, &b) != 2) {
        return -1;
    }
    int tab_a[(unsigned int) a], tab_b[(unsigned int) b];
    for(int i = 0;i < a; i++) {
        if(scanf("%d", &tab_a[i]) != 1) {
            return -1;
        }
    }
    for(int j = 0;j < b; j++) {
        if(scanf("%d", &tab_b[j]) != 1) {
            return -1;
        }
    }
    printf("%d",podciag(a ,tab_a ,b ,tab_b));
    return 0;
}

