#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<assert.h>


float abss(float x) {
    if(x<0) {
        x *= -1;
    }
    return x;
}
struct punkt {
        int x, y;
};

struct odcinek {
    struct punkt a, b;
};
float sqrtt(float a) {
    assert(a>0);
    float num = a;
    int i=0;
    while((num*num)-a>0.0001) {
        i++;
        if(i==50) {
            break;
        }
        num = num + (a/num);
        num /= 2;
    }
    printf("%f  %f   %f\n",num,num*num,a);
    return num;
}
int distance(struct punkt pa, struct punkt pb) {
    int res = 0;
    res = (pb.x-pa.x)*(pb.x-pa.x);
    res += (pb.y-pa.y)*(pb.y-pa.y);
    if(res>=0) {
        return res;
    } else {
        return res*(-1);
    }
}
float spec_sinus(struct punkt p1, struct punkt p2) {
    float res;
    float f = (float) distance(p1,p2);
    if(p2.x>=p1.x&&p2.y>p1.y) {
        res = p2.y-p1.y;
        res /= sqrtt(f);
    } else if(p2.x<p1.x&&p2.y>=p1.y) {
        res = p2.y-p1.y;
        res /= sqrtt(f);
        res *= -1;
        res += 2;
    } else if(p2.x<=p1.x&&p2.y<p1.y) {
        res = p2.y-p1.y;
        res /= sqrtt(f);
        res *= -1;
        res += 2;
    } else {
        res = p2.y-p1.y;
        res /= sqrtt(f);
        res += 4;
    }
    return res;
}
int wewnatrz(struct odcinek o, struct punkt p) {
    if(o.a.x>o.b.x) {
        if(p.x>=o.b.x&&p.x<=o.a.x) {
            if(o.a.y>o.b.y) {
                if(p.y>=o.b.y&&p.y<=o.a.y) {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                if(p.y<=o.b.y&&p.y>=o.a.y) {
                    return 1;
                } else {
                    return 0;
                }
            }
        } else {
            return 0;
        }
    } else {
        if(p.x<=o.b.x&&p.x>=o.a.x) {
            if(o.a.y>o.b.y) {
                if(p.y>=o.b.y&&p.y<=o.a.y) {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                if(p.y<=o.b.y&&p.y>=o.a.y) {
                    return 1;
                } else {
                    return 0;
                }
            }
        } else {
            return 0;
        }
    }
}

int main() {
    struct odcinek odc1, odc2;
    scanf("%d",&odc1.a.x);
    scanf("%d",&odc1.a.y);
    scanf("%d",&odc1.b.x);
    scanf("%d",&odc1.b.y);
    scanf("%d",&odc2.a.x);
    scanf("%d",&odc2.a.y);
    scanf("%d",&odc2.b.x);
    scanf("%d",&odc2.b.y);
    float a,b,c;
    int var1, var2;
    a = spec_sinus(odc1.a,odc2.a);
    b = spec_sinus(odc1.a,odc2.b);
    c = spec_sinus(odc1.a,odc1.b);
    printf("\n%f  %f   %f\n",a,b,c);
    if(c<=2) {
        if(abss(c-b)<0.001||abss(c+2-b)<0.001) {
            b = 0;
        } else if(b>c&&b<(c+2)) {
            b = -1;
        } else {
            b = 1;
        }
        if(abss(c-a)<0.001||abss(c+2-a)<0.001) {
            a = 0;
        } else if(a>c&&a<(c+2)) {
            a = -1;
        } else {
            a = 1;
        }
    } else {
        if(abss(c-b)<0.001||abss(c-2-b)<0.001) {
            b = 0;
        } else if(b>(c-2)&&b<c) {
            b = -1;
        } else {
            b = 1;
        }
        if(abss(c-a)<0.001||abss(c-2-a)<0.001) {
            a = 0;
        } else if(a>(c-2)&&a<c) {
            a = -1;
        } else {
            a = 1;
        }
    }
    printf("%f  %f\n",a,b);
    var1 = (int)a*b;
    a = spec_sinus(odc2.a,odc1.a);
    b = spec_sinus(odc2.a,odc1.b);
    c = spec_sinus(odc2.a,odc2.b);
    printf("\n%f  %f   %f\n",a,b,c);
    if(c<=2) {
        if(c==b||b==(c+2)) {
            b = 0;
        } else if(b>c&&b<(c+2)) {
            b = -1;
        } else {
            b = 1;
        }
        if(c==a||a==(c+2)) {
            a = 0;
        } else if(a>c&&a<(c+2)) {
            a = -1;
        } else {
            a = 1;
        }
    } else {
        if(c==b||b==(c-2)) {
            b = 0;
        } else if(b>(c-2)&&b<c) {
            b = -1;
        } else {
            b = 1;
        }
        if(c==a||a==(c-2)) {
            a = 0;
        } else if(a>(c-2)&&a<c) {
            a = -1;
        } else {
            a = 1;
        }
    }
    printf("%f  %f\n",a,b);
    var2 = (int)a*b;
    if(var1==0&&var2==0) {
        if(wewnatrz(odc1,odc2.a)||wewnatrz(odc1,odc2.b)) {
            printf("przecinaja sie!\n");
        } else {
            printf("nie przecinaja sie!\n");
        }
        return 0;
    }
    if(var1<=0&&var2<=0) {
        printf("przecinaja sie!\n");
        return 0;
    }
    printf("nie przecinaja sie!\n");
    return 0;
}
