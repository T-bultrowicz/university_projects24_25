#include<stdio.h>
#include<float.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>


float sqrtt(float a) {
    assert(a>0);
    float num = a;
    while((num*num)-a>0.000001) {
        num = num + (a/num);
        num /= 2;
    }
    return num;
}
long long int code(long long int x, long long int y) {
    return ((x+y)*(x+y))+y;
}
long long int encode1(long long int kd) {
    assert(kd>0);
    long long int helper = (int) sqrtt((double) kd);
    long long int res = kd - (helper*helper);
    return helper - res;
}
long long int encode2(long long int kd) {
    assert(kd>0);
    long long int helper = (int) sqrtt((double) kd);
    return kd - (helper*helper);
}


int main() {
    long long int x,y;
    scanf("%lld%lld",&x,&y);
    printf("\n%lld\n%lld    %lld",code(x,y),encode1(code(x,y)),encode2(code(x,y)));
    return 0;
}
