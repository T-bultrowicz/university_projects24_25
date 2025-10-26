#include<stdlib.h>
#include<stdio.h>

int maks(int a, int b) {
    return(a > b) ? a : b;
}
int mini(int a, int b) {
    return(a <= b) ? a : b;
}

int main() {
    int seed, questions;
    int a1, a2, a3, a4, a5, c_convert, sign;
    scanf("%d %d", &seed, &questions);
    srand(seed);
    printf("1000 %d\n", questions);
    for(int i = 0;i < 1000; i++) {
        a1 = rand()%200;
        sign = rand()%2;
        if(sign == 1) {
            a1 *= -1;
        }
        a2 = rand()%200;
        sign = rand()%2;
        if(sign == 1) {
            a2 *= -1;
        }
        a3 = rand()%200;
        sign = rand()%2;
        if(sign == 1) {
            a3 *= -1;
        }
        a4 = rand()%200;
        sign = rand()%2;
        if(sign == 1) {
            a4 *= -1;
        }
        if(i > 0) {
            a5 = rand()%i;
            a5++;
            c_convert = rand()%5;
            switch (c_convert)
            {
            case 0:
                printf("P %d %d %d %d", mini(a1, a2), mini(a3, a4), maks(a1, a2), maks(a3, a4));
                break;
            case 1:
                if(a3 < 0) {
                    a3 *= -1;
                }
                if(!a3) {
                    a3++;
                }
                printf("K %d %d %d", a1, a2, a3);
                break;
            case 2:
                if(a1 == a3 && a2 == a4) {
                    a1 += 1;
                }
                printf("Z %d %d %d %d %d", a5, a1, a2, a3, a4);
                break;
            case 3:
                if(a1 == a3 && a2 == a4) {
                    a1 += 1;
                }
                printf("Z %d %d %d %d %d", a5, a1, a2, a3, a4);
                break;
            case 4:
                if(a1 == a3 && a2 == a4) {
                    a1 += 1;
                }
                printf("Z %d %d %d %d %d", a5, a1, a2, a3, a4);
                break;                                        
            default:
                break;
            }
        } else {
            printf("P %d %d %d %d", mini(a1, a2), mini(a3, a4), maks(a1, a2), maks(a3, a4));
        }
        printf("\n");
    }
    for(int j = 0; j < questions; j++) {
        a1 = rand()%200;
        sign = rand()%2;
        if(sign == 1) {
            a1 *= -1;
        }
        a2 = rand()%200;
        sign = rand()%2;
        if(sign == 1) {
            a1 *= -1;
        }
        a3 = rand()%1000;
        a3++;
        printf("%d %d %d\n", a3, a1, a2);
    }
    return 0;
}