#include <stdlib.h>
#include <stdio.h>

typedef struct punkt
{
    double x, y;
}punkt;

typedef struct kartka
{
    char typ;
    int k; // poprzedni stan
    punkt A, B; //dla kola A -srodek Bx - promien
}kartka;

double ab(double x)
{
    if(x < 0)return -x;
    else return x;
}

int iloczyn_wektorowy(punkt P, punkt A, punkt B)
{
    double pom = (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
    if (ab(pom) < 0.000001) return 0;
    else if (pom < 0) return -1;
    else return 1;
}

punkt rzut(punkt P, punkt A, punkt B)
{

    // Wektor V (reprezentujacy prosta)
    double vx = B.x - A.x;
    double vy = B.y - A.y;

    // Wektor od poczatku wektora do punktu A
    double ax = P.x - A.x;
    double ay = P.y - A.y;

    double dl_v = vx * vx + vy * vy; //dl v do kwadratu
    double t = (ax * vx + ay * vy) / dl_v;

    punkt pom;
    pom.x = A.x + t * vx;
    pom.y = A.y + t * vy;

    punkt wyn;
    wyn.x = P.x + 2 * (pom.x - P.x);
    wyn.y = P.y + 2 * (pom.y - P.y);

    return wyn;
}

int orig(int K, punkt P, kartka kartki[])
{
    if(kartki[K].typ == 'Z')
    {
        int il = iloczyn_wektorowy(P, kartki[K].A, kartki[K].B);
        if(il > 0)
        {
            punkt P2 = rzut(P, kartki[K].A, kartki[K].B);
            return orig(kartki[K].k, P, kartki) + orig(kartki[K].k, P2, kartki);
        }
        else if (il == 0)
        {
            return orig(kartki[K].k, P, kartki);
        }
        else return 0;
    }
    else if(kartki[K].typ == 'P')
    {
        if(P.x >= kartki[K].A.x && P.x <= kartki[K].B.x && P.y >= kartki[K].A.y && P.y <= kartki[K].B.y)
        {
            return 1;
        }
        else return 0;
    }
    else
    {
        if(((kartki[K].A.x - P.x) * (kartki[K].A.x - P.x) + (kartki[K].A.y - P.y) * (kartki[K].A.y - P.y))
           <= kartki[K].B.x * kartki[K].B.x) return 1;
        else return 0;
    }
}

int main()
{
    int n, q;
    int l;
    l = scanf("%d %d",&n, &q);
    kartka *kartki = (kartka*) malloc((unsigned int)(n + 1) * sizeof(kartka));
    for(int i = 1; i <= n; i++)
    {
        kartka pom;
        l = scanf(" %c", &pom.typ);
        if(pom.typ == 'P')
        {
            l = scanf("%lf %lf %lf %lf", &pom.A.x, &pom.A.y, &pom.B.x, &pom.B.y);
        }
        else if(pom.typ == 'K')
        {
            l = scanf("%lf %lf %lf", &pom.A.x, &pom.A.y, &pom.B.x);
        }
        else
        {
            l = scanf("%d %lf %lf %lf %lf", &pom.k, &pom.A.x, &pom.A.y, &pom.B.x, &pom.B.y);
        }
        kartki[i] = pom;
    }

    int *odp = (int*) malloc((unsigned int)q * sizeof(int));
    for(int j = 0; j < q; j++)
    {
        int k;
        punkt P;
        l = scanf("%d %lf %lf", &k, &P.x, &P.y);
        odp[j] = orig(k, P, kartki);
    }

    for(int j = 0; j < q; j++)
    {
        printf("%d\n", odp[j]);
    }
    kartki[0].A.x = (double) l;
    free(odp);
    free(kartki);
}
