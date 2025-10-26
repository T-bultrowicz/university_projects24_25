#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>


//przechowuje wspolrzedne punktu
typedef struct point{
    double x, y;
} point;

point lop, ata;

//przechowuje prostokat jako dwa punkty
typedef struct Rect {
    point lewy, prawy;
} Rect;

//przechowuje okrag jako punkt i radius
typedef struct Circ {
    point center;
    double radius;
} Circ;

//przechowuje dane o zgieciu
typedef struct Fold {
    int at;
    point p1, p2; 
} Fold;

//przechowuje typ kartki
typedef enum typ{
    RECT,
    CIRC,
    FOLD
} typ;

//przechowuje dane o kartce
typedef union Ksztalt {
    Rect rect;
    Circ circ;
    Fold fold;
} Ksztalt;

//przechowuje kartkę
typedef struct Kartka {
    typ r;
    Ksztalt k;
} Kartka;

//zwraca true, gdy dwa double sa dostatecznie blisko siebie
int rowne(double a, double b) {
    if(fabs(a - b) <= 0.00001) {
        return 1;
    } else {
        return 0;
    }
}
//sprawdza czy punkt lezy w prostokacie
int In_rect(Rect a, point b) {
    return (a.lewy.x <= b.x && b.x <= a.prawy.x && a.lewy.y <= b.y && b.y <= a.prawy.y);
}

//sprawdza czy punkt lezy w kole
int In_circ(Circ a, point b) {
    double dist = ((a.center.x - b.x) * (a.center.x - b.x)) + ((a.center.y - b.y) * (a.center.y - b.y));
    return(dist < a.radius * a.radius || rowne(dist, a.radius * a.radius));
}

//tworzy wzor funkcji liniowej laczacej punkty folda
//przechowuje w x wsp kierunkowy i w y wsp staly
//zwraca pusty point gdy funkcja nie istnieje
point tworz_prosta(Fold a) {
    point res;
    if(a.p1.x < a.p2.x) {
        res.x = (a.p2.y - a.p1.y) / (a.p2.x - a.p1.x);
        res.y = a.p1.y - (res.x * a.p1.x);
    } else if(a.p1.x > a.p2.x) {
        res.x = (a.p1.y - a.p2.y) / (a.p1.x - a.p2.x);
        res.y = a.p1.y - (res.x * a.p1.x);       
    }
    return res;
}

//sprawdza czy punkt znajduje się po dobrej stronie prostej zgiecia
int Po_zlej_stronie(Fold a, point b) {
    double kier, staly;
    point c = tworz_prosta(a);
    kier = c.x;
    staly = c.y;
    //przypadek pionowy - nie istnieje funkcja liniowa
    if(rowne(a.p1.x,a.p2.x)) {
        if(a.p1.y > a.p2.y) {
            if(b.x > a.p1.x || rowne(b.x,a.p1.x)) {
                return 0;
            } else {
                return 1;
            }
        } else {
            if(b.x < a.p1.x || rowne(b.x, a.p1.x)) {
                return 0;
            } else {
                return 1;
            }
        }
    } else if(a.p1.x < a.p2.x) {
        if(b.y > (b.x * kier) + staly || rowne(b.y, (b.x * kier) + staly)) {
            return 0;
        } else {
            return 1;
        }
    } else {
        if(b.y < (b.x * kier) + staly || rowne(b.y, (b.x * kier) + staly)) {
            return 0;
        } else {
            return 1;
        }
    }
}

//obraca punkt symetrią względem prostej Folda
point Obroc(Fold a, point b) {
    point res, c;
    //prosty przypadek - f.liniowa nie istnieje
    if(rowne(a.p1.x, a.p2.x)) {
        res.x = 2 * a.p1.x - b.x;
        res.y = b.y;
    } else if(rowne(a.p1.y, a.p2.y)) {
        res.x = b.x;
        res.y = 2 * a.p1.y - b.y;
    } else { //dla reszty
        //tworzymy druga funkcje prostopadla przechodzaca przez b (wektor symetrii), by dokonac obrotu
        //obsluguje ja -1/kier i n_staly
        double kier, staly, n_staly;
        point cross_prostych;
        c = tworz_prosta(a);
        kier = c.x;
        staly = c.y;
        n_staly = b.y + (b.x / kier);
        cross_prostych.x = kier * (n_staly - staly) / ((kier * kier) + 1);
        cross_prostych.y = (kier * cross_prostych.x) + staly;
        res.x = 2 * cross_prostych.x - b.x;
        res.y = 2 * cross_prostych.y - b.y;
    }
    return res;
}

//funckja rekurencyjna ilosc_zlozen, zwraca ilosc warstw kartki w punkcie
//przyjmuje strukture, indeks na zapytanie i punkt pinezki
int Ilosc_zlozen(Kartka* kartki, int ind, point que) {
    int a = 0;
    if(kartki[ind].r == RECT) {
        return In_rect(kartki[ind].k.rect, que);
    } else if(kartki[ind].r == CIRC) {
        return In_circ(kartki[ind].k.circ, que);
    } else {
        Fold f = kartki[ind].k.fold;
        if(Po_zlej_stronie(f, que)) {
            //na pewno punkt jest po zlej stronie, wiec zlozenia to 0
            return 0;
        } else {
            //zaczyna rekurencje by obliczyc ilosc zlozen, badajac "od konca"
            a = Ilosc_zlozen(kartki, f.at, que);
            if(!rowne(que.x, Obroc(f, que).x) || !rowne(que.y, Obroc(f,que).y)) {
                a += Ilosc_zlozen(kartki, f.at, Obroc(f, que));
            }
            return a;
        }
    }
}

int main() {
    //wczytuja ilosci struktur i zapytan
    int a, b;
    if(scanf("%d %d", &a, &b) != 2) {
        return -1;
    }
    //sluza wczytaniu struktur
    double p1, p2, p3, p4;
    char c;
    Kartka* kartki = (Kartka*) malloc((unsigned) a * sizeof(Kartka));
    point zapytanie;
    int ind;
    int* wyniki = (int*) malloc((unsigned) b * sizeof(int));
    //Wczytujemy struktury
    for(int i = 0; i < a; i++) {
        if(scanf("%c", &c) != 1) { //ten zawsze wczytuje newline
            return -1;
        }
        if(scanf("%c", &c) != 1) {
            return -1;
        }
        switch(c) {
            case 'P':
                if(scanf("%lf %lf %lf %lf",&p1, &p2, &p3, &p4) != 4) {
                    return -1;
                }
                kartki[i].r = RECT;
                kartki[i].k.rect.lewy.x = p1;
                kartki[i].k.rect.lewy.y = p2;
                kartki[i].k.rect.prawy.x = p3;
                kartki[i].k.rect.prawy.y = p4;
                break;
            case 'K':
                if(scanf("%lf %lf %lf", &p1, &p2, &p3) != 3) {
                    return -1;
                }
                kartki[i].r = CIRC;
                kartki[i].k.circ.center.x = p1;
                kartki[i].k.circ.center.y = p2;
                kartki[i].k.circ.radius = p3;
                break;
            case 'Z':
                if(scanf("%d %lf %lf %lf %lf",&ind, &p1, &p2, &p3, &p4) != 5) {
                    return -1;
                }
                kartki[i].r = FOLD;
                kartki[i].k.fold.at = ind - 1;
                kartki[i].k.fold.p1.x = p1;
                kartki[i].k.fold.p1.y = p2;
                kartki[i].k.fold.p2.x = p3;
                kartki[i].k.fold.p2.y = p4;
                break;
            default:
                break;                        
        }
    }
    //Zaczynamy zapytania
    for(int j = 0; j < b; j++) {
        //wczytanie zapytania
        if(scanf("%d %lf %lf", &ind, &p1, &p2) != 3) {
            return -1;
        }
        zapytanie.x = p1;
        zapytanie.y = p2;
        //wywolanie rekurencyjne by uzyskac wynik
        wyniki[j] = Ilosc_zlozen(kartki, ind - 1, zapytanie);
    }
    //wypis wyniku
    for(int k = 0; k < b; k++) {
        printf("%d\n", wyniki[k]);
    }
    free(wyniki);
    free(kartki);
    return 0;
}