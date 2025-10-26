#include<stdio.h>
#include<stdlib.h>

struct punkt {
        int x, y;
};

struct Prostokat {
    struct punkt a, b;
};
struct Prostokat przeciecie(struct Prostokat p_a, struct Prostokat p_b) {
    struct Prostokat res;
    if(p_a.a.x>p_b.a.x) {
        res.a.x=p_a.a.x;
    } else {
        res.a.x=p_b.a.x;
    }
    if(p_a.a.y>p_b.a.y) {
        res.a.y = p_a.a.y;
    } else {
        res.a.y = p_b.a.y;
    }
    if(p_a.b.x>p_b.b.x) {
        res.b.x = p_b.b.x;
    } else {
        res.b.x = p_a.b.x;
    }
    if(p_a.b.y>p_b.b.y) {
        res.b.y = p_b.b.y;
    } else {
        res.b.y = p_a.b.y;
    }
    return res;
}
int main() {
    struct Prostokat p1;
    struct Prostokat p2;
    scanf("%d",&p1.a.x);
    scanf("%d",&p1.a.y);
    scanf("%d",&p1.b.x);
    scanf("%d",&p1.b.y);
    scanf("%d",&p2.a.x);
    scanf("%d",&p2.a.y);
    scanf("%d",&p2.b.x);
    scanf("%d",&p2.b.y);
    p1 = przeciecie(p1, p2);
    if(p1.a.x>p1.b.x||p1.a.y>p1.b.y) {
        printf("non existing rectangle!\n");
    } else {
        printf("%d  %d  %d   %d",p1.a.x,p1.a.y,p1.b.x,p1.b.y);
    }
    return 0;
}
