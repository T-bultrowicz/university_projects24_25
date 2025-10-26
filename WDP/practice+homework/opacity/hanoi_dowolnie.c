#include<stdlib.h>
#include<stdio.h>


void Hanoi_def(int ile_krazkow, int start, int koniec) {
    if(ile_krazkow == 0) return;
    Hanoi_def(ile_krazkow - 1, start, 3 - start - koniec);
    printf("Przenosze krazek %d z miejsca %d na %d \n", ile_krazkow, start, koniec);
    Hanoi_def(ile_krazkow - 1, 3 - start - koniec, koniec);
}

void Hanoi(int rozmiar, int tab[], int start, int koniec) {
    if(rozmiar == 0) return;
    if(start == koniec) Hanoi(rozmiar - 1, tab, start, tab[rozmiar - 2]);
    else {
        Hanoi_def(rozmiar - 1, start, 3 - start - koniec);
        printf("Przenosze krazek %d z miejsca %d na %d \n", rozmiar, start, koniec);
        Hanoi(rozmiar - 1, tab, 3 - start - koniec, tab[rozmiar - 2]);
    }
}


int main() {
    int x;
    if(scanf("%d", &x) != 1) {
        return -1;
    }
    int polozenia[x];
    for(int i = x - 1; i >= 0; i--) {
        if(scanf("%d", polozenia + i) != 1) {
            return -1;
        }
    }
    Hanoi(x, polozenia, 0, polozenia[x - 1]);
    return 0;
}
