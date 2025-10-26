#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

int maxi(int a, int b) {
    return (a > b) ? a : b;
}

int kwadrat(int** t, int a, int b, int p) {
    int maximum = 0;
    int x_d, y_d; //dolne el gasienicy
    int x_g, y_g; //gorne el gasienicy
    int suma;
    for(int i = 0; i < b; i++) {
        x_d = x_g = a - 1;
        y_d = y_g = i;
        suma = 0;
        while(x_g >= 0 && y_g >= 0 && x_d >= 0 && y_d >= 0) {
            if(suma < p) {
                for(int ii = x_d; ii >= x_g; ii--) {
                    suma += t[ii][y_g];
                }
                for(int iii = y_d; iii > y_g; iii--) {
                    suma += t[x_g][iii];
                }
                maximum = maxi(maximum, x_d - x_g);
                x_g--;
                y_g--;
            } else {
                for(int ii = x_g + 1; ii <= x_d; ii++) {
                    suma -= t[ii][y_d];
                }
                for(int iii = y_g + 1; iii < y_d; iii++) {
                    suma -= t[x_d][iii];
                }
                x_d--;
                y_d--;
            }
            printf("%d %d    %d %d     %d\n", x_d, y_d, x_g, y_g, suma);
        }
        if(suma < p) {
            maximum = maxi(maximum, x_d - x_g);
        }
    }
    for(int j = 0;j < a - 1; j++) {
        x_d = x_g = j;
        y_d = y_g = b - 1;
        suma = 0;
        while(x_g >= 0 && y_g >= 0 && x_d >= 0 && y_d >= 0) {
            if(suma < p) {
                for(int ii = x_d; ii >= x_g; ii--) {
                    suma += t[ii][y_g];
                }
                for(int iii = y_d; iii > y_g; iii--) {
                    suma += t[x_g][iii];
                }
                maximum = maxi(maximum, x_d - x_g);
                x_g--;
                y_g--;
            } else {
                //x_d = 3, y_d = 2, x_g = 2, y_g = 1
                for(int ii = x_g + 1; ii <= x_d; ii++) {
                    suma -= t[ii][y_d];
                }
                for(int iii = y_g + 1; iii < y_d; iii++) {
                    suma -= t[x_d][iii];
                }
                x_d--;
                y_d--;
            }
        }
        if(suma < p) {
            maximum = maxi(maximum, x_d - x_g);
        }
    }
    return maximum;
}

int main() {
    int a, b, v;
    if(scanf("%d %d %d", &a, &b, &v) != 3) {
        return -1;
    }
    int** t = (int**) malloc((unsigned) a * sizeof(int*));
    for(int j = 0;j < a; j++) {
        t[j] = malloc((unsigned) b * sizeof(int));
        for(int k = 0;k < b; k++) {
            if(scanf("%d", &t[j][k]) != 1) {
                return -1;
            }
        }
    }
    printf("\n%d", kwadrat(t, a, b, v));
    for(int l = 0; l < a; l++) {
        free(t[l]);
    }
    free(t);
    return 0;
}
