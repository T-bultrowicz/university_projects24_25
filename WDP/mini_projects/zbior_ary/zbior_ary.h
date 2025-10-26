#ifndef _ZBIOR_ARY_H_
#define _ZBIOR_ARY_H_

#include <stdbool.h>


//STRUKTURY


// pciag_ary zawiera 3 inty bedace el_poczatkowym, koncowym oraz wartoscia el_poczatkowy mod q, dla podciagu.
typedef struct pciag_ary {
    int el_poczatkowy;
    int el_koncowy;
    int modul;
} pciag_ary;



// zbior_ary jest definiowany jako tablica podciagow (struct pciag_ary) o il. elementow Ary
//pciag_ary sa posortowane wpierw wg modulu, potem wg el. pocz rosnaco

typedef struct zbior_ary {
    long int il_podciagow;
    pciag_ary* podciagi;
  /* do uzupelnienia */
} zbior_ary;


//STRULTURY


//FUNKCJE POMOCNICZE


int mini(int a, int b);

int maxi(int a, int b);


//sprawdza czy iloczyn zbiorow jest nie pusty
bool czy_iloczyn(pciag_ary a, pciag_ary b);


// Sprawdza czy dwa podciagi nie sa po sobie (true gdy modul ten sam i el_koncowy jednego = el_poczatkowy_drugiego + q)
bool po_sobie(pciag_ary a, pciag_ary b);

//zwraca sume podciagow a i b, zaklada ze sa po sobie lub laczne
pciag_ary scal(pciag_ary a, pciag_ary b);

//zwraca iloczyn a i b, zaklada ze nie sa rozlaczne
pciag_ary czesc_wspolna(pciag_ary a, pciag_ary b);

//zwraca true gdy a jest mniejszy wg naszego porzadku od b
bool mniejszy(pciag_ary a, pciag_ary b);

//Printuje zawartosc zbioru_ary A
void Wyczytaj(zbior_ary A);

//FUNKCJE POMOCNICZE



/* Najlepiej nie modyfikowac nic ponizej. */

// Funkcja daje w wyniku zbior reprezentujacy ciag arytmetyczny o elemencie poczatkowym a, końcowym b i roznicy q>0, tj. {a,a+q,...,b}.
// Mozesz zalozyc, ze we wszystkich zapytaniach w danym tescie wartosc q bedzie taka sama.
// Mozesz zalozyc, ze ta funkcja zostanie wywolana jako pierwsza.
zbior_ary ciag_arytmetyczny(int a, int q, int b);

// Daje w wyniku zbior zlozony z samego elementu a, tj. {a}.
zbior_ary singleton(int a);

// Daje w wyniku zbior reprezentujacy teoriomnogosciowa sume zbiorow A i B.
zbior_ary suma(zbior_ary A, zbior_ary B);

// Daje w wyniku zbior reprezentujacy czesc wspolna zbiorow A i B.
zbior_ary iloczyn(zbior_ary A, zbior_ary B);

// Daje w wyniku zbior A \ B.
zbior_ary roznica(zbior_ary A, zbior_ary B);

// Daje w wyniku true wtw. gdy liczba b nalezy do zbioru A.
bool nalezy(zbior_ary A, int b);

// Wynikiem funkcji jest liczba elementow w zbiorze A.
unsigned moc(zbior_ary A);

// Wynikiem funkcji jest Ary_q(A), czyli minimalna liczba parami rozlacznych ciagow arytmetycznych o roznicy q, ktorych suma jest zbior A.
unsigned ary(zbior_ary A);


#endif
