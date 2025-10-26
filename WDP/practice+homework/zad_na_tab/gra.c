#include<stdio.h>
int NWD(int a, int b) {
    if(a==0||b==0) {
        return -1;
    }
    while(a!=b) {
        if(a>b) {
            a -= b;
        } else {
            b -= a;
        }
    }
    return a;
}
int graj(int a, int b) {
    if(a > 1 && b > 1) {
        if(a % 2 == 0) {
            return 1;
        } else {
            return 2;
        }
    } else if(a > 1) {
        return 1;
    } else if(b > 1) {
        return 2;
    } else {
        return 0;
    }
}
