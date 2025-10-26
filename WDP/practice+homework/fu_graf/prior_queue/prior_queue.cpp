#include<stdio.h>
#include<stdlib.h>
#include "prior_queue.h"

pr_que stworz_pr_que() {
    pr_que a = (pr_que) malloc(sizeof(elem));
    a->_tab = (int*) malloc(sizeof(int));
    a->_alloc_mem = 1;
    a->_used_mem = 1;
    return a;
}

void add_mem(pr_que a) {
    a->_alloc_mem *= 2;
    a->_tab = (int*) realloc(a->_tab, a->_alloc_mem * sizeof(int));
}


int front(const pr_que a) {
    return (a->_used_mem == 1) ? -1 : a->_tab[0];
}
int sajzof(pr_que a) {
    return a->_used_mem - 1;
}

void push(pr_que a, int b) {
    if(a->_alloc_mem < a->_used_mem) add_mem(a);
    int i = a->_used_mem;
    a->_tab[i - 1] = b;
    while(i > 1) {
        if(a->_tab[(i / 2) - 1] > a->_tab[i - 1]) {
            int c = a->_tab[(i / 2) - 1];
            a->_tab[(i / 2) - 1] = a->_tab[i - 1];
            a->_tab[i - 1] = c;
        } else {
            break;
        }
        i /= 2;
    }
    a->_used_mem++;
    return;
}
void pop(pr_que a) {
    if(a->_used_mem == 1) return;
    int i = 1;
    while(i < a->_used_mem) {
        if(2 * i + 1 < a->_used_mem) {
            if(a->_tab[2 * i] < a->_tab[2 * i - 1]) {
                a->_tab[i - 1] = a->_tab[2 * i];
                i = 2 * i + 1;
            } else {
                a->_tab[i - 1] = a->_tab[2 * i - 1];
                i *= 2;
            }
        } else if(2 * i < a->_used_mem) {
            a->_tab[i - 1] = a->_tab[2 * i - 1];
            i *= 2;   
        } else {
            a->_tab[i - 1] = a->_tab[a->_used_mem - 2];
            while(i > 1) {
                if(a->_tab[(i / 2) - 1] > a->_tab[i - 1]) {
                    int c = a->_tab[(i / 2) - 1];
                    a->_tab[(i / 2) - 1] = a->_tab[i - 1];
                    a->_tab[i - 1] = c;
                } else {
                    break;
                }
                i /= 2;                
            }
            break;
        }
    }
    a->_used_mem--;
    return;
}

void destroy(pr_que a) {
    free(a->_tab);
    free(a);
}
