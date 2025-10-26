#include<stdlib.h>
#include<stdio.h>

long long int _MOD = 10000007;

char* hanoi_MD(unsigned l, char* s) {
    long long int res_cor = 0, act = 1;
    char* res = malloc(sizeof(char));
    int* moves = malloc(sizeof(int) * l);
    char prze_cel = 'A', ban = 'B', po_cel = 'C', mem;
    for(int i = 0; i < l; i++) {
        if(s[i] == prze_cel) {
            moves[i] = 0;
            mem = po_cel;
            po_cel = ban;
            ban = mem;
        } else if(s[i] == ban) {
            res = realloc(res, sizeof(char) * 3);
            res[0] = 'N', res[1] = 'I', res[2] = 'E';
            return res;
        } else {
            moves[i] = 1;
            mem = prze_cel;
            prze_cel = ban;
            ban = mem;
        }
    }
    for(int k = l - 1; k >= 0; k--) {
        res_cor += act * moves[k];
        act <<= 1;
        act %= _MOD;
    }
    long long int dik = 10, times = 1, upp_time = 0;
    while(dik <= res_cor) {
        dik *= 10;
        times++;
    }
    res = realloc(res, sizeof(char) * (unsigned) times);
    while(dik > 1) {
        res[upp_time] = (char) 48 + ((res_cor % dik) / (dik / 10));
        dik /= 10;
        upp_time++;
    }
    free(moves);
    return res;
}

int main() {
    unsigned x;
    scanf("%d", &x);
    char* s = malloc(sizeof(char) * x);
    scanf("%c", s);
    for(int i = 0; i < x; i++) {
        scanf("%c", s + i);
    }
    char d = s[0], g = s[1];
    s = hanoi_MD(x, s);
    printf("%s", s);
    free(s);
    return 0;
}