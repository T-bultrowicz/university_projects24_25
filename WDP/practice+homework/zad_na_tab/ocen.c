#include<stdio.h>
#include<stdlib.h>
#include "gra.h"

int main() {
    int a, b;
    int choice, NWD_res;
    if(scanf("%d%d\n",&a,&b)!=2) {
        return -1;
    }
    while(1) {
        if(a == 1 && b == 1) {
            printf("Player lost!\n");
            return 0;
        }
        scanf("%d",&choice);
        if(choice == 1) {
             a -= 1;
             NWD_res = NWD(a, b);
             a /= NWD_res;
             b /= NWD_res;
        } else {
             b -= 1;
             NWD_res = NWD(a, b);
             a /= NWD_res;
             b /= NWD_res;
        }
        printf("%d  %d\n",a,b);
        if(graj(a,b) == 1) {
             a -= 1;
             NWD_res = NWD(a, b);
             a /= NWD_res;
             b /= NWD_res;
        } else if(graj(a, b) == 2) {
             b -= 1;
             NWD_res = NWD(a, b);
             a /= NWD_res;
             b /= NWD_res;
        } else {
            printf("Computer player lost!\n");
            return 0;
        }
        printf("%d  %d\n",a,b);
    }
    return 0;
}
