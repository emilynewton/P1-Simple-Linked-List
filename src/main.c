#include "lab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#ifdef TEST
#define main main_exclude
#endif

typedef struct ThreadArgs {
  List *list; 
  size_t start; 
  size_t end; 
  Compare cmp; 
} ThreadArgs;

// helper threadsafe function to call sort
void *threaded_sort(void *args) {
  ThreadArgs *targs = (ThreadArgs *)args; 
  sort(targs->list, targs->start, targs->end, targs->cmp); 
  return NULL; 
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <int|string> <length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *data_type = argv[1];
    size_t length = (size_t)atol(argv[2]);

    // populate list 
    List *list = list_create(LIST_LINKED_SENTINEL);
    generate_list(list, data_type, length);

    Compare cmp = (strcmp(data_type, "int") == 0) ? compare_int : compare_str;

    size_t mid = length / 2;

    pthread_t thread1, thread2;
    ThreadArgs args1 = {list, 0, mid, cmp};
    ThreadArgs args2 = {list, mid, length, cmp};

    pthread_create(&thread1, NULL, threaded_sort, &args1);
    pthread_create(&thread2, NULL, threaded_sort, &args2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    List *second_half = split(list, mid);
    List *merged = merge(list, second_half, cmp);
    // print sorted list
    for (size_t i = 0; i < list_size(merged); ++i) {
        void *data = list_get(merged, i);
        if (strcmp(data_type, "int") == 0) {
            printf("%d ", *(int *)data);
        } else {
            printf("%s ", (char *)data);
        }
    }
    printf("\n");

    list_destroy(merged, strcmp(data_type, "int") == 0 ? free : free);
    list_destroy(second_half, NULL); // already merged
}

    