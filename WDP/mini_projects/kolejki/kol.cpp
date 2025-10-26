#include<bits/stdc++.h>
#include "kol.h"
using namespace std;

//przechowuje numerek do wydania
int _NOWY_NUMEREK;

//przechowują indeksy na początki i końce kolejek do poszcz. okienek
vector <interesant*> _KOL_START;
vector <interesant*> _KOL_KONIEC;

//tworzy początkowe, puste listy do okienek
void otwarcie_urzedu(int m) {
    _NOWY_NUMEREK = 0;
    for(int i = 0; i < m; i++) {
        interesant* a = (interesant*) malloc(sizeof(interesant));
        a->numerek = -1;
        a->second = NULL;
        interesant* b = (interesant*) malloc(sizeof(interesant));
        b->numerek = -1;
        b->first = a;
        a->first = b;
        b->second = NULL;
        _KOL_START.push_back(a);
        _KOL_KONIEC.push_back(b);
    }
    return;
}

//funkcja pomocnicza, odpina blok interesantow z i1 do i2 z kolejki
//aby dzialala poprawnie pop1 i pop2 sa odpowiednio sasiadami i1 i i2 tż pop1, pop2 w przedziale (i1; i2)
//ALTER WYWOLANIE: przepnij_inter(i,i,i->first,i->second) wypina i z kolejki
void przepnij_inter(interesant* i1, interesant* i2, interesant* pop1, interesant* pop2) {
    interesant *a, *b;
    if(i1->first == pop1) {
        a = i1->second;
        i1->second = NULL;
    } else {
        a = i1->first;
        i1->first = NULL;
    }
    if(i2->first == pop2 || i2->first == NULL) {
        b = i2->second;
        i2->second = NULL;
    } else {
        b = i2->first;
        i2->first = NULL;
    }
    if(a->first == i1) {
        a->first = b;
    } else {
        a->second = b;
    }
    if(b->first == i2) {
        b->first = a;
    } else {
        b->second = a;
    }
    return;
}

//wpina interesanta między podanych lft i rgt, oba musza byc sasiednie
void wepnij_miedzy(interesant* i, interesant* i_lft, interesant* i_rgt) {
    i->first = i_lft;
    i->second = i_rgt;
    if(i_lft->first == i_rgt) {
        i_lft->first = i;
    } else {
        i_lft->second = i;
    }
    if(i_rgt->first == i_lft) {
        i_rgt->first = i;
    } else {
        i_rgt->second = i;
    }
    return;
}

//tworzy nowego interesenta, ustawia na końcu kolejki k
interesant *nowy_interesant(int k) {
    interesant* nowy = (interesant*) malloc(sizeof(interesant));
    nowy->numerek = _NOWY_NUMEREK++;
    wepnij_miedzy(nowy, _KOL_KONIEC[k], _KOL_KONIEC[k]->first);
    return nowy;
}

//zwraca numerek interesanta
int numerek(interesant *i) {
    return i->numerek;
}

//zwraca wskaźnik na pierwszego interesenta w kolejkce nr k
//przepina wskaźniki tak, by opuścił on kolejkę, wpp NULL
interesant *obsluz(int k) {
    interesant* obsl = _KOL_START[k]->first;
    if(obsl->numerek == -1) {
        return NULL;
    } else {
        przepnij_inter(obsl, obsl, obsl->first, obsl->second);
        return obsl;
    }
}

//przepina interesanta i z akt miejsca na koniec kolejki k
void zmiana_okienka(interesant *i, int k) {
    //wypinamy i z kolejki
    przepnij_inter(i, i, i->first, i->second);
    //przepinamy i na koniec k
    wepnij_miedzy(i, _KOL_KONIEC[k], _KOL_KONIEC[k]->first);
    return;
}

//zamyka okienko k1, przerzuca wszystkich interesantów na koniec kolejki k2
void zamkniecie_okienka(int k1, int k2) {
    interesant *pierwszy = _KOL_START[k1]->first, *ostatni = _KOL_KONIEC[k1]->first;
    if(pierwszy->numerek == -1) { //czy kolejka k1 jest pusta
        return;
    }
    //opróżniamy kolejkę k1
    interesant *a = (pierwszy->first == _KOL_START[k1]) ? pierwszy->second : pierwszy->first;
    interesant *b = (ostatni->first == _KOL_KONIEC[k1]) ? ostatni->second : ostatni->first;
    przepnij_inter(pierwszy, ostatni, a, b);

    //wpinamy k1 do kolejki k2
    wepnij_miedzy(pierwszy, _KOL_KONIEC[k2], _KOL_KONIEC[k2]->first);
    if(ostatni != pierwszy) {
        wepnij_miedzy(ostatni, _KOL_KONIEC[k2], pierwszy);
        if(ostatni->first == pierwszy) {
            ostatni->first = b;
        } else {
            ostatni->second = b;
        }
        if(pierwszy->first == ostatni) {
            pierwszy->first = a;
        } else {
            pierwszy->second = a;
        }
    }
    return;
}

//funckja pomocnicza do fast track, znajduje grupę interesantow miedzy i1 do i2 wlacznie
vector <interesant*> znajdz_grupe(interesant* node, interesant* target) {
    //inicjalizacje
    interesant *mem1, *mem2;
    interesant *follow_one = node, *follow_two = node;
    interesant *search_one = node->first, *search_two = node->second;
    vector <interesant*> res_one, res_two;
    res_one.push_back(node), res_two.push_back(node);
    //petla przeszukiwan
    while(search_one != target && search_two != target) { //nie ma celu
        res_one.push_back(search_one);
        res_two.push_back(search_two);
        mem1 = search_one, mem2 = search_two;
        if(search_one->numerek == -1) { //dotarliśmy do brzegu
            mem1 = search_one;
        } else if(search_one->first == follow_one) {
            search_one = search_one->second;
        } else {
            search_one = search_one->first;
        }
        if(search_two->numerek == -1) { //dotarlimy do brzegu
            mem2 = search_two;
        } else if(search_two->first == follow_two) {
            search_two = search_two->second;
        } else {
            search_two = search_two->first;
        }
        follow_one = mem1, follow_two = mem2;
    }
    if(search_one == target) {
        res_one.push_back(search_one);
        return res_one;
    } else {
        res_two.push_back(search_two);
        return res_two;
    }
}

//sluzy szybkiemu obsluzeniu grupy interesantow od i1 do i2 w tej samej kolejce
vector<interesant *> fast_track(interesant *i1, interesant *i2) {
    vector <interesant *> res;
    if(i1 == i2) {
        res.push_back(i1);
        przepnij_inter(i1, i1, i1->first, i1->second);      
        return res;
    }
    res = znajdz_grupe(i1, i2);
    przepnij_inter(res[0], res[res.size()-1], res[1], res[res.size()-2]);
    return res;
}

//obraca kolejkę do okienka k kolejnością, zamienia strony
//w jakie obrócone są head i tail w interesantach w kolejce
void naczelnik(int k) {
    if(_KOL_START[k]->first->numerek == -1) {
        return;
    }
    //przepięcie pointerów startu i końca
    swap(_KOL_KONIEC[k]->first, _KOL_START[k]->first);

    //przepięcie interesantom brzegowym startu i końca
    if(_KOL_START[k]->first->first == _KOL_KONIEC[k]) {
        _KOL_START[k]->first->first = _KOL_START[k];
    } else {
        _KOL_START[k]->first->second = _KOL_START[k];
    }
    if(_KOL_KONIEC[k]->first->first == _KOL_START[k]) {
        _KOL_KONIEC[k]->first->first = _KOL_KONIEC[k];
    } else {
        _KOL_KONIEC[k]->first->second = _KOL_KONIEC[k];
    }
    return;
}

//dodaje wskaźniki na interesantów z kolejki
void dodaj_interesantow(long unsigned int nr, vector <interesant*>& res) {
    interesant *search = _KOL_START[nr]->first, *follow = _KOL_START[nr], *mem;
    while(search != _KOL_KONIEC[nr]) {
        res.push_back(search);
        mem = search;
        if(search->first == follow) {
            search = search->second;
        } else {
            search = search->first;
        }
        follow = mem;
    }
    return;
}

vector<interesant *> zamkniecie_urzedu() {
    vector <interesant*> res;
    for(long unsigned int i = 0; i < _KOL_START.size(); i++) {
        dodaj_interesantow(i, res);
    }
    for(long unsigned int j = 0; j < _KOL_START.size(); j++) {
        free(_KOL_START[j]);
        free(_KOL_KONIEC[j]);
    }    
    return res;    
}

void wywolaj() {
    for(long unsigned int i = 0; i < _KOL_START.size();i++) {
        interesant *nasz = _KOL_START[i]->first, *forr = _KOL_START[i], *mem;
        while(nasz != _KOL_KONIEC[i]) {
            printf("%d ", nasz->numerek);
            mem = nasz;
            if(nasz->first == forr) {
                nasz = nasz->second;
            } else {
                nasz = nasz->first;
            }
            forr = mem;
        }
        printf("\n");
    }
    printf("\n");
}

