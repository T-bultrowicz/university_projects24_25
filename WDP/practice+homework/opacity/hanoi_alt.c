#include<stdlib.h>
#include<stdio.h>


void Hanoi(int ile_krazkow, int start, int koniec) {
    if(ile_krazkow == 0) return;
    Hanoi(ile_krazkow - 1, start, 3 - start - koniec);
    printf("Przenosze krazek %d z miejsca %d na %d \n", ile_krazkow, start, koniec);
    Hanoi(ile_krazkow - 1, 3 - start - koniec, koniec);
}

int main() {
    int x;
    if(scanf("%d", &x) != 1) {
        return -1;
    }
    Hanoi(x, 0, 2);
    return 0;
}
