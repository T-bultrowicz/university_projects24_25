#include "links.h"
#include <stdlib.h>
#include <string.h>

#ifndef CEIL_DIV_64
#define CEIL_DIV_64(x) ((((x) - 1) >> 6) + 1)
#endif 

//dba o usuwanie struktur link
void disconnect_one(link *l) {
    l->value--;
    if(!l->value) {
        l->head->tail = l->tail;
        l->tail->head = l->head;
        free(l);
    }
    return;
}


//wywolywane przy usuwaniu automatu, zapewnie nie korzystanie
//z usunietego wyjscia, usuniecie wszystkich polaczen
void disconnect_every_output(moore_t* a) {
    link *l = a->guard->head;
    while(l != a->guard) {
        for(size_t i = 0; i < l->ma_in->input_size; i++) {
            if(l->ma_in->con_in.st[i] == LINKED) {
                if(l->ma_in->con_in.conn[i] == l) {
                    l->ma_in->con_in.st[i] = UNDEFINED;
                }
            }
        }
        l = l->head;
        free(l->tail);
    }
    return;
}


//wydobywa bit ze ciagu ptr bedacy na n-tej pozycji
size_t get_bite(const uint64_t *ptr, size_t n) {
    size_t rest = n & 63;
    return ptr[n >> 6] & (1ULL << rest) ? 1 : 0;
}


//inicjuje strukture ilink dla tworzonego automatu
int initialize(ilink *input, size_t input_size) {
    if(input_size * 4 < input_size || input_size * 8 < input_size)
        return -1;
    input->index = malloc(input_size * sizeof(size_t));
    input->conn = malloc(input_size * sizeof(link*));
    input->st = malloc(input_size * sizeof(state));
    if(input->st == NULL || input->index == NULL || input->conn == NULL) {
        free(input->st);
        free(input->conn);
        free(input->index);
        return -1;
    }

    for(size_t i = 0; i < input_size; i++) input->st[i] = UNDEFINED;
    return 0;
}


//przelicza wartosc sygnalow wejsciowych automatu a
void calc_input(uint64_t* p_st, uint64_t* p_in, moore_t* a) {
    if (a->input_size == 0) return;
    memset(p_in, 0, CEIL_DIV_64(a->input_size) * 8);
    memset(p_st, 0, CEIL_DIV_64(a->state_size) * 8);
    size_t j = -1; //miejsce w tabeli

    ilink *l_in = &a->con_in;
    for(size_t i = 0; i < a->input_size; i++) {
        if((i & 63) == 0) j++;
        if(l_in->st[i] == LINKED) {
            p_in[j] |= get_bite(l_in->conn[i]->ma_out->output, l_in->index[i])
                        << (i & 63);
        } else if(l_in->st[i] == UNLINKED) {
            p_in[j] |= (l_in->index[i] << (i & 63));
        }
    }
}


//tworzy nowa strukture link o zadanych parametrach
link * create_link(moore_t* a_in, moore_t* a_out, size_t value) {
    link* p = malloc(sizeof(link));
    if(p == NULL) return NULL;
    p->ma_in = a_in;
    p->ma_out = a_out;
    p->head = a_out->guard->head;
    p->tail = a_out->guard;
    p->head->tail = p;
    p->tail->head = p;
    p->value = value;
    return p;
}



