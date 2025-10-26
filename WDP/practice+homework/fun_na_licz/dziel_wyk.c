#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int dziel_wyk(int n, int m) {
    assert(n>0&&m>0);
    int res = 0;
    int reminder = m;
    while(m<=n) {
        res += n/m;
        m *= reminder;
    }
    return res;
}
int main() {
    int x, y;
    if(scanf("%d  %d",&x,&y)!=2) {
        return -1;
    }
    printf("%d",dziel_wyk(x,y));
    return 0;
}
