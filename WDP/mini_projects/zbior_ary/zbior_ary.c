#include "zbior_ary.h"
#include<stdlib.h>
#include<stdio.h>
#include<math.h>

int ROZNICA_CIAGU;

//zwraca min
int mini(int a, int b) {
    return (a > b) ? b : a;
}

//zwraca max
int maxi(int a, int b) {
    return (a > b) ? a : b;
}


// Tworzy zbior_ary, o jednym podciagu, nadaje globalna wartosc ROZNICA_CIAGU
zbior_ary ciag_arytmetyczny(int a, int q, int b) {
    zbior_ary res;
    ROZNICA_CIAGU = q;
    res.il_podciagow = 1;
    res.podciagi = (pciag_ary*) malloc(1 * sizeof(pciag_ary));
    res.podciagi[0].el_poczatkowy = a;
    res.podciagi[0].el_koncowy = b;
    res.podciagi[0].modul = a % ROZNICA_CIAGU;
    if(res.podciagi[0].modul < 0) {
        res.podciagi[0].modul = ROZNICA_CIAGU + res.podciagi[0].modul;
    }
    return res;
}


// Tworzy zbior o jednym podciagu {a}
zbior_ary singleton(int a) {
    zbior_ary res;
    res.il_podciagow = 1;
    res.podciagi = (pciag_ary*) malloc(1 * sizeof(pciag_ary));
    res.podciagi[0].el_poczatkowy = a;
    res.podciagi[0].el_koncowy = a;
    res.podciagi[0].modul = a % ROZNICA_CIAGU;
    if(res.podciagi[0].modul < 0) {
        res.podciagi[0].modul = ROZNICA_CIAGU + res.podciagi[0].modul;
    }
    return res;
}

//sprawdza czy iloczyn zbiorow jest niepusty
bool czy_iloczyn(pciag_ary a, pciag_ary b) {
    return (a.modul == b.modul && maxi(a.el_poczatkowy, b.el_poczatkowy) <= mini(a.el_koncowy, b.el_koncowy));
}


// Sprawdza czy dwa podciagi nie sa po sobie (true gdy modul ten sam i el_koncowy jednego = el_poczatkowy_drugiego + q)
bool po_sobie(pciag_ary a, pciag_ary b) {
    return (a.el_poczatkowy == b.el_koncowy + ROZNICA_CIAGU || b.el_poczatkowy == a.el_koncowy + ROZNICA_CIAGU);
}


//zwraca sume podciagow a i b, zaklada ze sa po sobie lub laczne
pciag_ary scal(pciag_ary a, pciag_ary b) {
    pciag_ary scalony;
    scalony.el_poczatkowy = mini(a.el_poczatkowy, b.el_poczatkowy);
    scalony.el_koncowy = maxi(a.el_koncowy, b.el_koncowy);
    scalony.modul = a.modul;
    return scalony;
}


//zwraca iloczyn a i b, zaklada ze nie sa rozlaczne
pciag_ary czesc_wspolna(pciag_ary a, pciag_ary b) {
    pciag_ary wspolna;
    wspolna.el_poczatkowy = maxi(a.el_poczatkowy, b.el_poczatkowy);
    wspolna.el_koncowy = mini(a.el_koncowy, b.el_koncowy);
    wspolna.modul = a.modul;
    return wspolna;
}

//zwraca true gdy a jest mniejszy wg naszego porzadku od b
bool mniejszy(pciag_ary a, pciag_ary b) {
    return (a.modul < b.modul) || ((a.modul == b.modul) && (a.el_poczatkowy < b.el_poczatkowy));
}

// Tworzy zbior_ary bedacy suma teoriomnogosciowa zbiorow A i B
//Przyjmuje posortowane zbiory i zwraca posortowane wg opisu w headerze
zbior_ary suma(zbior_ary A, zbior_ary B) {
    //res akumuluje wynik
    zbior_ary res;
    res.il_podciagow = A.il_podciagow + B.il_podciagow;
    res.podciagi = (pciag_ary*) malloc((unsigned) res.il_podciagow * sizeof(pciag_ary));

    int i = 0, j = 0;
    int ile_el_res = 0; // Sledzi ilosc elementow w res
    pciag_ary kp_A = A.podciagi[0], kp_B = B.podciagi[0]; //kop akt podciag w A i B, by nie naruszyc tabel

    //petla przelatuje po kolei po indeksach dwoch tabel, reagujac w zaleznosci jakie warunki so spelnione:
    // 1. - jedna z tabel sie skonczyla, wtedy wypisuje druga do konca
    // 2. - zbiory sa rozlaczne - patrzy ktory mniejszy i jako ze jest on na pewno rozlaczny z wszystkim wrzuca go do res
    // 3. - zbiory na siebie nachodza - scalamy i poruwnujemy co zlaczylismy z nast. wg war sortowania elementem

    while(i < A.il_podciagow || j < B.il_podciagow) {
        //warunki konca tabel
        if(i >= A.il_podciagow) {
            res.podciagi[ile_el_res++] = kp_B;
            kp_B = B.podciagi[++j];
        } else if(j >= B.il_podciagow) {
            res.podciagi[ile_el_res++] = kp_A;
            kp_A = A.podciagi[++i];
        }

        //rozlaczne podzbiory i nie po sobie, wrzucamy na res
        else if(!czy_iloczyn(kp_A, kp_B) && !po_sobie(kp_A, kp_B)) {
            if(mniejszy(kp_A, kp_B)) {
                res.podciagi[ile_el_res++] = kp_A;
                kp_A = A.podciagi[++i];
            } else {
                res.podciagi[ile_el_res++] = kp_B;
                kp_B = B.podciagi[++j];
            }
        }

        //podzbiory o niepustym iloczynie lub po sobie
        else {
            //warunki gdy trafiamy na brzeg tablicy
            if(i == A.il_podciagow - 1 && j == B.il_podciagow - 1) {
                res.podciagi[ile_el_res++] = scal(kp_A, kp_B);
                i++;
                j++;
            } else if(j == B.il_podciagow - 1) {
                kp_B = scal(kp_A, kp_B);
                kp_A = A.podciagi[++i];
            } else if(i == A.il_podciagow - 1) {
                kp_A = scal(kp_A, kp_B);
                kp_B = B.podciagi[++j];
            }
            //zwykle porownanie
            else if(mniejszy(A.podciagi[i + 1], B.podciagi[j + 1])) {
                kp_B = scal(kp_A, kp_B);
                kp_A = A.podciagi[++i];
            } else {
                kp_A = scal(kp_A, kp_B);
                kp_B = B.podciagi[++j];
            }
        }
    }
    res.il_podciagow = ile_el_res;
    res.podciagi = (pciag_ary*) realloc(res.podciagi, (unsigned) res.il_podciagow * sizeof(pciag_ary));
    return res;
}


// Tworzy zbior_ary bedacy iloczynem teoriomnogosciowym zbiorow A i B
zbior_ary iloczyn(zbior_ary A, zbior_ary B) {
    //res akumuluje wynik
    zbior_ary res;
    res.il_podciagow = A.il_podciagow + B.il_podciagow;
    res.podciagi = (pciag_ary*) malloc((unsigned) res.il_podciagow * sizeof(pciag_ary));

    int i = 0, j = 0, ile_el_res = 0; //indeksy do tabel podciagów

    //petla przelatuje po kolei po indeksach dwoch tabel, reagujac w zaleznosci jakie warunki so spelnione:
    // 1. - jedna z tabel sie skonczyla, mozna opuscic petle
    // 2. - iloczyn elementow niepusty - akumulowany na res
    // 3. - przesuwamy nast indeks na mniejszy el.

    while(i < A.il_podciagow && j < B.il_podciagow)  {
        if(czy_iloczyn(A.podciagi[i], B.podciagi[j])) {
            res.podciagi[ile_el_res++] = czesc_wspolna(A.podciagi[i], B.podciagi[j]);
        }
        if(i == A.il_podciagow - 1) {
            j++;
        } else if(j == B.il_podciagow - 1) {
            i++;
        } else if(mniejszy(A.podciagi[i + 1], B.podciagi[j + 1])) {
            i++;
        } else {
            j++;
        }
    }
    res.il_podciagow = ile_el_res;
    res.podciagi = (pciag_ary*) realloc(res.podciagi, (unsigned) res.il_podciagow * sizeof(pciag_ary));
    return res;
}


// Tworzy zbior_ary bedacy roznica zbiorow A i B
zbior_ary roznica(zbior_ary A, zbior_ary B) {
    //res akumuluje wynik
    zbior_ary res;
    res.il_podciagow = A.il_podciagow + B.il_podciagow;
    res.podciagi = (pciag_ary*) malloc((unsigned) res.il_podciagow * sizeof(pciag_ary));

    int i = 0, j = 0, ile_el_res = 0; //indeksy do tabel podciagow
    pciag_ary kp_A = A.podciagi[0]; //w petli rowny A.podciagi[i]

    //petla przelatuje po kolei po indeksach dwoch tabel, reagujac w zaleznosci jakie warunki so spelnione:
    // 1. - koniec A wyjdz, koniec B wypisz wszystko z A
    // 2. - iloczyn el niepusty, to dolny element a-b na res, gorny do dalszego porownywania. Gdy nie istnieja pomija
    // 3. - iloczyn pusty - przesuwa indeks na kolejny element, porzadkiem by nic nie ominac
    //      jesli ma pewnosc dzieki cechom sortowania, ze dany pciag a w A nalezy do A-B to wypisuje go na res

    while(i < A.il_podciagow) {
        if(j >= B.il_podciagow) { //koniec elementow w B
            res.podciagi[ile_el_res++] = kp_A;
            kp_A = A.podciagi[++i];
        } else if(czy_iloczyn(kp_A, B.podciagi[j])) {
            if(B.podciagi[j].el_poczatkowy > kp_A.el_poczatkowy) { //istnieje dolna czesc w A[i] - B[j]
                res.podciagi[ile_el_res].el_poczatkowy = kp_A.el_poczatkowy;
                res.podciagi[ile_el_res].el_koncowy = B.podciagi[j].el_poczatkowy - ROZNICA_CIAGU;
                res.podciagi[ile_el_res].modul = kp_A.modul;
                ile_el_res++;
            }
            if(B.podciagi[j].el_koncowy < kp_A.el_koncowy) { // istnieje gorna czesc w A[i] - B[j]
                kp_A.el_poczatkowy = B.podciagi[j++].el_koncowy + ROZNICA_CIAGU;
            } else { //nie istnieje gorna - mozna przesunac indeks
                kp_A = A.podciagi[++i];
            }
        } else if(((kp_A.el_poczatkowy > B.podciagi[j].el_koncowy) && (kp_A.modul == B.podciagi[j].modul)) || kp_A.modul > B.podciagi[j].modul) { //A[i] zbyt duze na porownywanie z B[j]
            j++;
        } else { // A[i] zbyt male na porownywanie z B[j]
            res.podciagi[ile_el_res++] = kp_A;
            kp_A = A.podciagi[++i];
        }
    }
    res.il_podciagow = ile_el_res;
    res.podciagi = (pciag_ary*) realloc(res.podciagi, (unsigned) res.il_podciagow * sizeof(pciag_ary));
    return res;
}


//sprawdza czy element nalezy do ktoregos z podciagow, bin_searchem
bool nalezy(zbior_ary A, int b) {
    int modul_b = abs(b % ROZNICA_CIAGU);
    long int l = 0, p = A.il_podciagow - 1, s;
    while(l <= p) {
        s = (l + p) / 2;
        if(A.podciagi[s].modul > modul_b) {
            p = s - 1;
        } else if(A.podciagi[s].modul < modul_b) {
            l = s + 1;
        } else {
            if(A.podciagi[s].el_koncowy < b) {
                l = s + 1;
            } else if(A.podciagi[s].el_poczatkowy > b) {
                p = s - 1;
            } else {
                return true;
            }
        }
    }
    return false;
}


//zwraca il_elementow zbioru_ary
unsigned ary(zbior_ary A) {
    return (unsigned) A.il_podciagow;
}


//zwraca moc zbioru_ary
unsigned moc(zbior_ary A) {
    unsigned wynik = 0;
    for(int i = 0; i < A.il_podciagow; i++) {
        wynik += (unsigned) ( (long unsigned) (A.podciagi[i].el_koncowy - A.podciagi[i].el_poczatkowy) / (unsigned) ROZNICA_CIAGU);
    }
    wynik += (unsigned) A.il_podciagow;
    return wynik;
}

void Wyczytaj(zbior_ary A) {
    for(int i = 0; i < A.il_podciagow; i++) {
        if(i != 0) {
            if(A.podciagi[i].modul != A.podciagi[i - 1].modul) {
                printf("\n");
            }
        }
        for(int j = A.podciagi[i].el_poczatkowy; j <= A.podciagi[i].el_koncowy; j += ROZNICA_CIAGU) {
            printf("%d ",j);
        }
        printf("\n");
    }
    printf("\n\n");
}


