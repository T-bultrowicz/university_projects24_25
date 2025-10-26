#ifndef PRIOR_QUEUE_H
#define PRIOR_QUEUE_H 1

typedef struct elem {
    int _used_mem, _alloc_mem;
    int* _tab;
} elem;

typedef elem* pr_que;

pr_que stworz_pr_que();
int front(pr_que a);
int sajzof(pr_que a);
void push(pr_que a, int b);
void pop(pr_que a);
void destroy(pr_que a);
#endif 