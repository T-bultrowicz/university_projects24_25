#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"prior_queue.h"

int main() {
    clock_t start = clock();
    int a, b, c;
    scanf("%d", &a);
    pr_que abc = stworz_pr_que();
    for(int i = 0; i < a; i++) {
        scanf("%d", &b);
        if(b == 0) {
            front(abc);
        } else if(b == 1) {
            scanf("%d", &c);
            push(abc, c);
        } else {
            pop(abc);
        }
    }
    clock_t end = clock();
    printf("%.6f ", (double) (end - start) / 1000000);
    destroy(abc);
    return 0;
}