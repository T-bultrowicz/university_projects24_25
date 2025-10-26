#include "links.h"
#include <stdlib.h>
#include<assert.h>
#include<errno.h>
#include <stdio.h>
#include <string.h>
#define CEIL_DIV_64(x) ((((x) - 1) >> 6) + 1)

//usuwa wszystkie struktury z automatu, aby dzialala poprawnie
//automat a musi byc porozlaczany
void free_everything(moore_t *a) {
    free(a->con_in.index);
    free(a->con_in.conn);
    free(a->con_in.st);
    free(a->guard);
    free(a->state);
    free(a->output);
    free(a);
    return;
}


//wykonuje jeden krok funkcji f_out automatu a
void make_output_step(moore_t* a) {
    a->f_out(a->output, a->state, a->output_size, a->state_size);
    return;
}


//wykonuje jeden krok funkcji f_trans automatu a, umieszcze wynik w jego stanie
//musi dostac pointery p_st i p_in bedace w stanie przechowac stan wewnetrzny i syg. wejsciowe
void make_trans_step(uint64_t *p_st, uint64_t *p_in, moore_t *a) {
    calc_input(p_st, p_in, a);
    a->f_trans(p_st, p_in, a->state, a->input_size, a->state_size);
    memcpy(a->state, p_st, CEIL_DIV_64(a->state_size) * 8);
    return;
}


//funkcja wyjsciowa bedaca identycznoscia, uzywana przez ma_create_simple
void identity(uint64_t *output, uint64_t const *state, size_t, size_t s) {
    memcpy(output, state, CEIL_DIV_64(s) * 8);
    return;
}


moore_t * ma_create_full(size_t n, size_t m, size_t s, transition_function_t t, output_function_t y, uint64_t const *q) {
    if (!m || !s || t == NULL || y == NULL || q == NULL) {
        errno = EINVAL;
        return NULL;
    }

    moore_t* ma_new = malloc(sizeof(moore_t));
    if (ma_new == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    ma_new->input_size = n, ma_new->state_size = s, ma_new->output_size = m;
    ma_new->f_out = y, ma_new->f_trans = t;
    if (initialize(&ma_new->con_in, n) == -1) {
        free(ma_new);
        errno = ENOMEM;
        return NULL;
    }

    ma_new->guard = malloc(sizeof(link));
    ma_new->output = malloc(sizeof(uint64_t) * CEIL_DIV_64(s));
    ma_new->state = malloc(sizeof(uint64_t) * CEIL_DIV_64(m));
    if (ma_new->output == NULL || ma_new->state == NULL || ma_new->guard == NULL) {
        free_everything(ma_new);
        errno = ENOMEM;
        return NULL;
    }
    ma_new->guard->head = ma_new->guard;
    ma_new->guard->tail = ma_new->guard;  
    memcpy(ma_new->state, q, CEIL_DIV_64(ma_new->state_size) * 8);

    make_output_step(ma_new);
    return ma_new;
}


moore_t * ma_create_simple(size_t n, size_t s, transition_function_t t) {

    if (!s || t == NULL) {
        errno = EINVAL;
        return NULL;
    }

    uint64_t *q = malloc(sizeof(uint64_t) * CEIL_DIV_64(s));
    if (q == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    memset(q, 0, CEIL_DIV_64(s) * 8);

    moore_t* res = ma_create_full(n, s, s, t, identity, q);
    free(q);
    return res;
}


void ma_delete(moore_t *a) {
    if (a == NULL) return;
    if (a->input_size) ma_disconnect(a, 0, a->input_size);
    disconnect_every_output(a);
    free_everything(a);
    return;
}


int ma_connect(moore_t *a_in, size_t in, moore_t *a_out, size_t out, size_t num) {
    
    if(a_in == NULL || a_out == NULL || !num || 
        out + num > a_out->output_size || in + num > a_in->input_size
            || in + num < in || out + num < out) {
        errno = EINVAL;
        return -1;
    }
    link* l = create_link(a_in, a_out, num);
    if(l == NULL) {
        errno = ENOMEM;
        return -1;
    }

    for(size_t i = in; i < in + num; i++) {
        if(a_in->con_in.st[i] == LINKED) {
            disconnect_one(a_in->con_in.conn[i]);
        }
        a_in->con_in.st[i] = LINKED;
        a_in->con_in.conn[i] = l;
        a_in->con_in.index[i] = out + i - in;
    }
    return 0;
}


int ma_disconnect(moore_t *a_in, size_t in, size_t num) {

    if(a_in == NULL || !num || in + num > a_in->input_size
                                    || in + num < in) {
        errno = EINVAL;
        return -1;
    }

    ilink *l_in = &a_in->con_in;
    for(size_t i = in; i < in + num; i++) {
        if(l_in->st[i] == LINKED) {
            disconnect_one(l_in->conn[i]);
            l_in->st[i] = UNDEFINED;
        }
    }
    return 0;
}


int ma_set_input(moore_t *a, uint64_t const *input) {

    if(a == NULL || input == NULL || !a->input_size) {
        errno = EINVAL;
        return -1;
    }

    ilink *l_in = &a->con_in;
    for(size_t i = 0; i < a->input_size; i++) {
        if(l_in->st[i] != LINKED) {
            l_in->st[i] = UNLINKED;
            l_in->index[i] = get_bite(input, i);
        }
    }
    return 0;
}


int ma_set_state(moore_t *a, uint64_t const *state) {

    if(a == NULL || state == NULL) {
        errno = EINVAL;
        return -1;
    }

    memcpy(a->state, state, CEIL_DIV_64(a->state_size) * 8);
    make_output_step(a);
    return 0;
}


uint64_t const * ma_get_output(moore_t const *a) {
    if(a == NULL) {
        errno = EINVAL;
        return NULL;
    }

    return a->output;
}


int ma_step(moore_t *at[], size_t num) {
    
    size_t lngst_in = 0, lngst_st = 0;
    if(at == NULL || !num) {
        errno = EINVAL;
        return -1;
    }
    for(size_t i = 0; i < num; i++) {
        if(at[i] == NULL) {
            errno = EINVAL;
            return -1;
        }
        lngst_in = at[i]->input_size > lngst_in ? at[i]->input_size : lngst_in;
        lngst_st = at[i]->state_size > lngst_st ? at[i]->state_size : lngst_st;
    }

    uint64_t *new_input = malloc(sizeof(uint64_t) * CEIL_DIV_64(lngst_in));
    uint64_t *new_state = malloc(sizeof(uint64_t) * CEIL_DIV_64(lngst_st));
    if(new_input == NULL || new_state == NULL) {
        free(new_input);
        free(new_state);
        errno = ENOMEM;
        return -1;
    }
    for(size_t i = 0; i < num; i++) 
        make_trans_step(new_state, new_input, at[i]);
    for(size_t i = 0; i < num; i++)
        make_output_step(at[i]);
        
    free(new_input);
    free(new_state);
    return 0;
}
