#include<stdio.h>
#include<stdlib.h>

int maxi(int a, int b) {
    return(a > b) ? a : b;
}

int cheops(int *t, int s) {
    int res = 0;
    int i = 0, j = 1, k; // dwa indeksy przesuwne i k - tymczasowe
    int equal_counter = 1; //gdy sa rownej wysokosci
    while(j < s) {
        if(t[j] > t[j - 1]) { //podnosimy rozmiar pot. piramidy
            j++;
            equal_counter = 1;
        } else if(t[j] == t[j - 1]) { //nabijamy rowne elementy
            j++;
            equal_counter++;
        } else {
            if(j - i > 1) { //tylko wyzsze sprawdzamy
                if(equal_counter > 0) { //korekta j, i przez rowne el.
                    if(equal_counter % 2 == 0) {
                        i = j - 1;
                    } else {
                        j -= equal_counter / 2;
                    }
                }
                k = j;
                while(k < 2 * j - i - 1) {
                    if(k == s) {
                        break;
                    } else if(t[k] != t[2 * j - 2 - k]) {
                        break;
                    }
                    k++;
                }
                res = maxi(res, t[j - 1] - t [k - 1]);
                j = k;
                i = j - 1;
            } else {
                i++;
                j++;
            }
        }
    }
    return res;
}


int main() {
    int a, b;
    if(scanf("%d",&a) != 1) {
        return -1;
    }
    int *tab = malloc((unsigned) a * sizeof(int));
    for(int i = 0;i < a; i++) {
        if(scanf("%d", tab + i) != 1) {
            return -1;
        }
    }
    printf("%d", cheops(tab, a));
    free(tab);
    return 0;
}
