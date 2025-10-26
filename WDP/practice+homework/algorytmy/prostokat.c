#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>


int** Preprocess(int ** tab, int x, int y) {
    int** res = (int **) malloc((unsigned) x * sizeof(int*));
    for(int j = 0;j < x; j++) {
        res[j] = malloc((unsigned) y * sizeof(int));
        for(int k = 0; k < y; k++) {
            if(j == 0 && k == 0) {
                res[0][0] = tab[0][0];
            } else if(j == 0) {
                res[0][k] = res[0][k - 1] + tab[0][k];
            } else if(k == 0) {
                res[j][0] = res[j - 1][0] + tab[j][0];
            } else {
                res[j][k] = res[j - 1][k] + res[j][k - 1] - res[j - 1][k - 1] + tab[j][k];
            }
        }
    }
    return res;
}

bool Znaleziono(int** pom, int x, int y, int cel, int akt_x, int akt_y) {
    int l;
    for(int i = akt_x - 1; i < x; i++) {
        for(int j = akt_y - 1; j < y; j++) {
            l = 0;
            l += pom[i][j];
            if(i - akt_x >= 0 && j - akt_y >= 0) {
                l += pom[i - akt_x][j - akt_y];
            }
            if(i - akt_x >= 0) {
                l -= pom[i - akt_x][j];
            }
            if(j - akt_y >= 0) {
                l -= pom[i][j - akt_y];
            }
            if(l >= cel) {
                return true;
            }
        }
    }
    return false;
}

bool Istnieje(int** pom, int x, int y, int cel, int akt_obwod) {
    for(int i = 1; i < akt_obwod / 2; i++) {
        if((akt_obwod - (2 * i)) % 2 == 0 && i <= x && (akt_obwod - (2 * i)) / 2 <= y) {
            if(Znaleziono(pom, x, y, cel, i, (akt_obwod - (2 * i)) / 2)) {
                return true;
            }
        }
    }
    return false;
}

int prostokat(int** tab, int x, int y, int f) {
    int** prefiks = Preprocess(tab, x, y);
    int lewo = 4, prawo = 2 * (x + y), s;
    int check_even;
    while(lewo < prawo && x < 100) {
        check_even = 0;
        s = lewo + prawo;
        s /= 2;
        if(s % 2 != 0) {
            s--;
            check_even = 1;
        }
        if(Istnieje(prefiks, x, y, f, s)) {
            prawo = s - 1 + check_even;
        } else {
            lewo = s + 1 + check_even;
        }
        if(!check_even) {
            s++;
        }
    }
    for(int k = 0; k < x; k++) {
        free(prefiks[k]);
    }
    free(prefiks);
    return lewo;
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
    printf("\n%d", prostokat(t, a, b, v));
    for(int l = 0; l < a; l++) {
        free(t[l]);
    }
    free(t);
    return 0;
}
