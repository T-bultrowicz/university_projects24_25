#ifndef LINKS_H 
#define LINKS_H 1

#include "ma.h"

//enum przechowujacy stany, w jakich znajdowac sie moze
//pojedynczy sygnal wejsciowy
typedef enum state {
    LINKED,
    UNLINKED,
    UNDEFINED
} state;


/* Struktura trzyma informacje o poj wywolaniu ma_connect przechowywane dla ma a:
 * ma_in - automat korzystajacy z wyjscia automatu ma_out
 * ma_out - ww.
 * value - rowne l. polaczen dalej aktywnych
 * # NIEZMIENNIK: gdy value osiaga zero struktura zwalnia swoja pamiec #
 * head, tail - wskazniki na inne elementy link, razem tworzace 
 * dwukierunkowa liste cykliczna podpiete pod a.guard
*/
typedef struct link {
    moore_t *ma_in, *ma_out;
    struct link *head, *tail;
    size_t value;
} link;


/* Struktura przechowujaca wszystkie dane o sygnalach wejsciowych automatu:
 * state[i] - stan wejscia i
 * conn[i] - wsk. na link z ktorego korzysta i, gdy jest linked
 * state[i] - wartosc 0/1 wejscia i gdy unlinked lub nr wyjscia z ktorego korzysta gdy linked
*/
typedef struct ilink {
    state *st;
    link** conn;
    size_t *index;
} ilink;

// Struktura reprezentujaca automat: przechowuje wszystkie dane o nim, jego
// polaczeniach, sgynalach i stanach za pomoca ww. struktur danych
struct moore {
    size_t input_size, state_size, output_size;
    transition_function_t f_trans;
    output_function_t f_out;
    uint64_t *state, *output;
    link *guard;
    ilink con_in;
};


void disconnect_one(link *l);
void disconnect_every_output(moore_t* a);
size_t get_bite(const uint64_t *ptr, size_t n);
int initialize(ilink *input, size_t input_size);
void calc_input(uint64_t* p_st, uint64_t* p_in, moore_t* a);
link * create_link(moore_t* a_in, moore_t* a_out, size_t value);

#endif 