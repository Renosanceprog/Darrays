#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct{
    int* head;
    int count;
    int capacity;
}darray;

darray init_d(){
    darray n;
    n.count = 0;
    n.capacity = 1;
    n.head = malloc(n.capacity * sizeof(int));
    return n;
}

void append_d(darray *n, int num){
    if (n->count >= n->capacity){
        n->capacity *= 2;
        n->head = realloc(n->head, n->capacity * sizeof(int));
    }

    n->head[n->count] = num;
    n->count++;
}

void pop_d(darray *n, int index){
    for (size_t i = index; i < n->count-1; i++) n->head[i] = n->head[i+1];
    n->count--;

    if ((n->capacity >= n->count * 2) && (n->capacity > 2)){
        n->capacity /= 2;
        n->head = realloc(n->head, n->capacity * sizeof(int));
    }
}

void debugprint(darray *n){
    printf("darray stats: count = %d, max capacity = %d, sizeof(head) = %3u bytes | {", n->count, n->capacity, n->capacity*sizeof(n->head));
    for (size_t i = 0; i < n->count; i++)
    {
        printf("%d", n->head[i]);
        if (i < n->count - 1) printf(", ");
    }
    printf("}\n");
}

int main(void) {
    darray nums = init_d();
    debugprint(&nums);
    append_d(&nums, 1);
    debugprint(&nums);
    pop_d(&nums, 0);
    debugprint(&nums);
    append_d(&nums, 80085);
    debugprint(&nums);
    return 0;
}
