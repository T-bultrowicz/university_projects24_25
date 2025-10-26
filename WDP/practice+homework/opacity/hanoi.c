#include<stdlib.h>
#include<stdio.h>


void Hanoi(int ile_krazkow, int start, int koniec, int po_drodze) {
    if(ile_krazkow == 0) return;
    Hanoi(ile_krazkow - 1, start, po_drodze, koniec);
    printf("Przenosze krazek %d z miejsca %d na %d \n", ile_krazkow, start, koniec);
    Hanoi(ile_krazkow - 1, po_drodze, koniec, start);
}

int main() {
    int x;
    if(scanf("%d", &x) != 1) {
        return -1;
    }
    Hanoi(x, 0, 2, 1);
    return 0;
}
