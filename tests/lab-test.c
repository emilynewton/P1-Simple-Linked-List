#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include "harness/unity.h"
#include "../src/lab.h"

void setUp(void) {
  printf("Setting up tests...\n");
}

void tearDown(void) {
  printf("Tearing down tests...\n");
}

void test_list_create(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_EQUAL(0, list_size(list));
  TEST_ASSERT_TRUE(list_is_empty(list));
  list_destroy(list, free);
}

void test_list_append(void) { 
  List *list = list_create(LIST_LINKED_SENTINEL);
  int *data1 = malloc(sizeof(int));
  int *data2 = malloc(sizeof(int));
  *data1 = 10;
  *data2 = 20;

  TEST_ASSERT_TRUE(list_append(list, data1));
  TEST_ASSERT_TRUE(list_append(list, data2));
  TEST_ASSERT_EQUAL(2, list_size(list));
  TEST_ASSERT_EQUAL_PTR(data1, list_get(list, 0));
  TEST_ASSERT_EQUAL_PTR(data2, list_get(list, 1));
  TEST_ASSERT_FALSE(list_is_empty(list));

  list_destroy(list, free);
}

void test_list_insert(void) {
    List *list = list_create(LIST_LINKED_SENTINEL);
    int *data1 = malloc(sizeof(int));
    int *data2 = malloc(sizeof(int));
    int *data3 = malloc(sizeof(int)); 
    *data1 = 5;
    *data2 = 10;
    *data3 = 15; 

    // Insert first element at index 0
    TEST_ASSERT_TRUE(list_insert(list, 0, data1));
    TEST_ASSERT_EQUAL_PTR(data1, list_get(list, 0));
    TEST_ASSERT_EQUAL(1, list_size(list));

    // Insert second element at index 1 (end)
    TEST_ASSERT_TRUE(list_insert(list, 1, data2));
    TEST_ASSERT_EQUAL_PTR(data2, list_get(list, 1));
    TEST_ASSERT_EQUAL(2, list_size(list));

    // Insert third element in the middle 
    TEST_ASSERT_TRUE(list_insert(list, 1, data3));
    TEST_ASSERT_EQUAL_PTR(data3, list_get(list, 1));
    TEST_ASSERT_EQUAL_PTR(data2, list_get(list, 2));
    TEST_ASSERT_EQUAL(3, list_size(list));

    list_destroy(list, free);
}

void test_list_insert_and_remove(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  int *data1 = malloc(sizeof(int));
  int *data2 = malloc(sizeof(int));
  int *data3 = malloc(sizeof(int));
  *data1 = 10;
  *data2 = 20;
  *data3 = 15;

  TEST_ASSERT_TRUE(list_append(list, data1));
  TEST_ASSERT_TRUE(list_append(list, data2));
  TEST_ASSERT_TRUE(list_insert(list, 1, data3)); // Insert in the middle

  TEST_ASSERT_EQUAL(3, list_size(list));
  TEST_ASSERT_EQUAL_PTR(data1, list_get(list, 0));
  TEST_ASSERT_EQUAL_PTR(data3, list_get(list, 1));
  TEST_ASSERT_EQUAL_PTR(data2, list_get(list, 2));

  int *removed_data = (int *)list_remove(list, 1); // Remove the middle element
  TEST_ASSERT_EQUAL_PTR(data3, removed_data);
  free(removed_data);

  TEST_ASSERT_EQUAL(2, list_size(list));
  TEST_ASSERT_EQUAL_PTR(data1, list_get(list, 0));
  TEST_ASSERT_EQUAL_PTR(data2, list_get(list, 1));

  list_destroy(list, free);
}

void test_list_size_null(void) {
  TEST_ASSERT_EQUAL(0, list_size(NULL));
}

void test_list_is_empty_null(void) {
  TEST_ASSERT_TRUE(list_is_empty(NULL));
}

void test_list_get_error(void) {
  TEST_ASSERT_NULL(list_get(NULL, 0)); 
  TEST_ASSERT_NULL(list_get(NULL, 1000)); 
}

void test_insert_error(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  TEST_ASSERT_NOT_NULL(list);
  int value = 5;
  TEST_ASSERT_FALSE(list_insert(NULL, 0, &value));  // list is NULL
  TEST_ASSERT_FALSE(list_insert(list, 0, NULL));    // data is NULL
  TEST_ASSERT_FALSE(list_insert(list, 999, &value)); // index too large
  TEST_ASSERT_TRUE(list_insert(list, 0, &value));
  TEST_ASSERT_EQUAL_PTR(&value, list_get(list, 0));
  TEST_ASSERT_EQUAL(1, list_size(list));

  list_destroy(list, NULL);
}

void test_append_error(void) {
    List *list = list_create(LIST_LINKED_SENTINEL);
    TEST_ASSERT_NOT_NULL(list);

    int value = 10;

    TEST_ASSERT_FALSE(list_append(NULL, &value));

    TEST_ASSERT_FALSE(list_append(list, NULL));

    TEST_ASSERT_TRUE(list_append(list, &value));
    TEST_ASSERT_EQUAL_PTR(&value, list_get(list, 0));
    TEST_ASSERT_EQUAL(1, list_size(list));

    list_destroy(list, NULL);
}

void test_list_remove_error(void) {
    List *list = list_create(LIST_LINKED_SENTINEL);
    TEST_ASSERT_NOT_NULL(list);

    int value = 42;

    TEST_ASSERT_NULL(list_remove(NULL, 0));

    TEST_ASSERT_NULL(list_remove(list, 999));

    TEST_ASSERT_TRUE(list_append(list, &value));
    TEST_ASSERT_EQUAL(1, list_size(list));

    void *removed = list_remove(list, 0);
    TEST_ASSERT_EQUAL_PTR(&value, removed);
    TEST_ASSERT_EQUAL(0, list_size(list));

    list_destroy(list, NULL);
}

void test_compare_int(void) {
  int a = 10, b = 5, c = 10;
  TEST_ASSERT_TRUE(compare_int(&a, &b) > 0);  // 10 > 5 → descending
  TEST_ASSERT_TRUE(compare_int(&b, &a) < 0);  // 5 < 10
  TEST_ASSERT_EQUAL(0, compare_int(&a, &c));  // equal
}

void test_compare_str(void) {
  char* a = "apple";
  char* b = "banana";
  char* c = "apple";
  TEST_ASSERT_TRUE(compare_str(a, b) > 0);    // "apple" < "banana"
  TEST_ASSERT_TRUE(compare_str(b, a) < 0);    // "banana" > "apple"
  TEST_ASSERT_EQUAL(0, compare_str(a, c));    // equal
}

void test_sort_int(void) {
  List* list = list_create(LIST_LINKED_SENTINEL);
  int* a = malloc(sizeof(int)); *a = 5;
  int* b = malloc(sizeof(int)); *b = 10;
  int* c = malloc(sizeof(int)); *c = 7;
  list_append(list, a);
  list_append(list, b);
  list_append(list, c);

  sort(list, 0, list_size(list), compare_int);
  TEST_ASSERT_TRUE(is_sorted(list, compare_int));

  list_destroy(list, free);
}

void test_sort_str(void) {
  List* list = list_create(LIST_LINKED_SENTINEL);
  list_append(list, strdup("banana"));
  list_append(list, strdup("apple"));
  list_append(list, strdup("cherry"));

  sort(list, 0, list_size(list), compare_str);
  TEST_ASSERT_TRUE(is_sorted(list, compare_str));

  list_destroy(list, free);
}

void test_merge_int(void) {
  List* list1 = list_create(LIST_LINKED_SENTINEL);
  List* list2 = list_create(LIST_LINKED_SENTINEL);

int* a = malloc(sizeof(int)); *a = 10;
int* b = malloc(sizeof(int)); *b = 8;
int* c = malloc(sizeof(int)); *c = 9;
int* d = malloc(sizeof(int)); *d = 7;

list_append(list1, a);
list_append(list1, b);
list_append(list2, c);
list_append(list2, d);

sort(list1, 0, list_size(list1), compare_int);
sort(list2, 0, list_size(list2), compare_int);

List* merged = merge(list1, list2, compare_int);
  size_t msize = list_size(merged);
  for (size_t i = 0; i < msize; ++i) {
    int *val = (int *)list_get(merged, i);
    printf("merged[%zu] = %d\n", i, val ? *val : 0);
  }
  TEST_ASSERT_EQUAL(4, list_size(merged));

  TEST_ASSERT_TRUE(is_sorted(merged, compare_int));

  list_destroy(list1, free);
  list_destroy(list2, free);
  list_destroy(merged, free);
}

void test_merge_str(void) {
  List* list1 = list_create(LIST_LINKED_SENTINEL);
  List* list2 = list_create(LIST_LINKED_SENTINEL);
  list_append(list1, "apple");
  list_append(list1, "banana");
  list_append(list2, "avocado");
  list_append(list2, "blueberry");

  List* merged = merge(list1, list2, compare_str);
  TEST_ASSERT_EQUAL(4, list_size(merged));
  TEST_ASSERT_TRUE(is_sorted(merged, compare_str));

  list_destroy(list1, NULL);
  list_destroy(list2, NULL);
  list_destroy(merged, NULL);
}

void test_is_sorted_descending_int(void) {
  List* list = list_create(LIST_LINKED_SENTINEL);
  int* a = malloc(sizeof(int)); *a = 10;
  int* b = malloc(sizeof(int)); *b = 8;
  int* c = malloc(sizeof(int)); *c = 5;
  list_append(list, a);
  list_append(list, b);
  list_append(list, c);

  TEST_ASSERT_TRUE(is_sorted(list, compare_int)); 

  list_destroy(list, free);
}

void test_split(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  int* a = malloc(sizeof(int)); *a = 10;
  int* b = malloc(sizeof(int)); *b = 20;
  int* c = malloc(sizeof(int)); *c = 30;
  int* d = malloc(sizeof(int)); *d = 40;
  list_append(list, a);
  list_append(list, b);
  list_append(list, c);
  list_append(list, d);

  List* newList = split(list, 2);
  TEST_ASSERT_NOT_NULL(newList);
  TEST_ASSERT_EQUAL(2, list_size(list));
  TEST_ASSERT_EQUAL(2, list_size(newList));
  TEST_ASSERT_EQUAL_PTR(a, list_get(list, 0));
  TEST_ASSERT_EQUAL_PTR(b, list_get(list, 1));
  TEST_ASSERT_EQUAL_PTR(c, list_get(newList, 0));
  TEST_ASSERT_EQUAL_PTR(d, list_get(newList, 1));

  list_destroy(list, free);
  list_destroy(newList, free);
}

void test_split_sort_merge(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  int* a = malloc(sizeof(int)); *a = 30;
  int* b = malloc(sizeof(int)); *b = 10;
  int* c = malloc(sizeof(int)); *c = 40;
  int* d = malloc(sizeof(int)); *d = 20;
  list_append(list, a);
  list_append(list, b);
  list_append(list, c);
  list_append(list, d);

  List* newList = split(list, 2);
  TEST_ASSERT_NOT_NULL(newList);

  sort(list, 0, list_size(list), compare_int);
  sort(newList, 0, list_size(newList), compare_int);

  List* merged = merge(list, newList, compare_int);
  TEST_ASSERT_NOT_NULL(merged);
  TEST_ASSERT_EQUAL(4, list_size(merged));
  TEST_ASSERT_TRUE(is_sorted(merged, compare_int));

  list_destroy(list, free);
  list_destroy(newList, free);
  list_destroy(merged, free);
}

void test_sort_guard_conditions(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  int *x = malloc(sizeof(int)); *x = 1;
  TEST_ASSERT_TRUE(list_append(list, x));

  size_t before = list_size(list);

  /* should return immediately (no crash / no modification) */
  sort(NULL, 0, 1, compare_int);               // !list
  sort(list, 1, 1, compare_int);               // start >= end
  sort(list, 0, before + 1, compare_int);      // end > list->size
  sort(list, 0, before, NULL);                 // !cmp

  /* verify list unchanged */
  TEST_ASSERT_EQUAL(before, list_size(list));
  int *val = (int *)list_get(list, 0);
  TEST_ASSERT_NOT_NULL(val);
  TEST_ASSERT_EQUAL(1, *val);

  list_destroy(list, free);
}

void test_split_guard_conditions(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  int *a = malloc(sizeof(int)); *a = 1;
  int *b = malloc(sizeof(int)); *b = 2;
  TEST_ASSERT_TRUE(list_append(list, a));
  TEST_ASSERT_TRUE(list_append(list, b));

  // NULL list should return NULL
  TEST_ASSERT_NULL(split(NULL, 0));

  // index == size (out of range) should return NULL
  TEST_ASSERT_NULL(split(list, list_size(list)));

  // index > size should return NULL
  TEST_ASSERT_NULL(split(list, list_size(list) + 1));

  // valid split for control: index within range should return a new list
  List *newList = split(list, 1);
  TEST_ASSERT_NOT_NULL(newList);
  TEST_ASSERT_EQUAL(1, list_size(list));
  TEST_ASSERT_EQUAL(1, list_size(newList));

  list_destroy(list, free);
  list_destroy(newList, free);
}

void test_split_internal_middle(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  int *a = malloc(sizeof(int)); *a = 1;
  int *b = malloc(sizeof(int)); *b = 2;
  int *c = malloc(sizeof(int)); *c = 3;
  int *d = malloc(sizeof(int)); *d = 4;

  list_append(list, a);
  list_append(list, b);
  list_append(list, c);
  list_append(list, d);

  /* split in the middle: index 2 -> newList gets elements 2..end (0-based) */
  List *newList = split(list, 2);
  TEST_ASSERT_NOT_NULL(newList);

  /* original should have first two elements */
  TEST_ASSERT_EQUAL(2, list_size(list));
  int *v0 = list_get(list, 0); TEST_ASSERT_NOT_NULL(v0); TEST_ASSERT_EQUAL(1, *v0);
  int *v1 = list_get(list, 1); TEST_ASSERT_NOT_NULL(v1); TEST_ASSERT_EQUAL(2, *v1);

  /* newList should have remaining elements in order */
  TEST_ASSERT_EQUAL(2, list_size(newList));
  int *n0 = list_get(newList, 0); TEST_ASSERT_NOT_NULL(n0); TEST_ASSERT_EQUAL(3, *n0);
  int *n1 = list_get(newList, 1); TEST_ASSERT_NOT_NULL(n1); TEST_ASSERT_EQUAL(4, *n1);

  list_destroy(list, free);
  list_destroy(newList, free);
}

void test_split_index_zero_moves_all_nodes(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  int *a = malloc(sizeof(int)); *a = 5;
  int *b = malloc(sizeof(int)); *b = 6;
  int *c = malloc(sizeof(int)); *c = 7;

  list_append(list, a);
  list_append(list, b);
  list_append(list, c);

  /* split at 0 should move all nodes to the new list, leaving original empty */
  List *newList = split(list, 0);
  TEST_ASSERT_NOT_NULL(newList);

  TEST_ASSERT_EQUAL(0, list_size(list));
  TEST_ASSERT_TRUE(list_is_empty(list));

  TEST_ASSERT_EQUAL(3, list_size(newList));
  int *n0 = list_get(newList, 0); TEST_ASSERT_NOT_NULL(n0); TEST_ASSERT_EQUAL(5, *n0);
  int *n1 = list_get(newList, 1); TEST_ASSERT_NOT_NULL(n1); TEST_ASSERT_EQUAL(6, *n1);
  int *n2 = list_get(newList, 2); TEST_ASSERT_NOT_NULL(n2); TEST_ASSERT_EQUAL(7, *n2);

  list_destroy(list, free);
  list_destroy(newList, free);
}

void test_is_sorted_guard_conditions(void) {
  /* NULL list -> should return true (guard) */
  TEST_ASSERT_TRUE(is_sorted(NULL, compare_int));

  /* empty list -> should return true */
  List *list = list_create(LIST_LINKED_SENTINEL);
  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_TRUE(is_sorted(list, compare_int));

  /* single-element list -> should return true */
  int *v = malloc(sizeof(int)); *v = 42;
  TEST_ASSERT_TRUE(list_append(list, v));
  TEST_ASSERT_EQUAL(1, list_size(list));
  TEST_ASSERT_TRUE(is_sorted(list, compare_int));

  list_destroy(list, free);
}

void test_is_sorted_detects_unsorted_pair(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  int *a = malloc(sizeof(int)); *a = 8;
  int *b = malloc(sizeof(int)); *b = 10;

  TEST_ASSERT_TRUE(list_append(list, a));
  TEST_ASSERT_TRUE(list_append(list, b));

  /* cmp(a,b) = 8 - 10 = -2 < 0 -> should trigger the branch and return false */
  TEST_ASSERT_FALSE(is_sorted(list, compare_int));

  list_destroy(list, free);
}

void test_generate_random_string_chars_and_length(void) {
  for (int iter = 0; iter < 50; ++iter) {
    char *s = generate_random_string();
    TEST_ASSERT_NOT_NULL(s);

    size_t len = strlen(s);
    TEST_ASSERT_TRUE(len >= 5 && len <= 15);

    for (size_t i = 0; i < len; ++i) {
      TEST_ASSERT_TRUE(s[i] >= 'a' && s[i] <= 'z');
    }
    TEST_ASSERT_EQUAL_CHAR('\0', s[len]);

    free(s);
  }
}

void test_generate_list_ints(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  TEST_ASSERT_NOT_NULL(list);

  /* generate 10 integer entries */
  generate_list(list, "int", 10);
  TEST_ASSERT_EQUAL(10, list_size(list));

  for (size_t i = 0; i < list_size(list); ++i) {
    int *v = (int *)list_get(list, i);
    TEST_ASSERT_NOT_NULL(v);
    /* basic sanity: dereference must be a valid int (no further range assumptions) */
    (void)*v;
  }

  list_destroy(list, free);
}

void test_generate_list_uses_random_string(void) {
  List *list = list_create(LIST_LINKED_SENTINEL);
  TEST_ASSERT_NOT_NULL(list);

  /* generate 8 random strings (non-"int" branch) */
  generate_list(list, "str", 8);
  TEST_ASSERT_EQUAL(8, list_size(list));

  for (size_t i = 0; i < list_size(list); ++i) {
    char *s = (char *)list_get(list, i);
    TEST_ASSERT_NOT_NULL(s);

    size_t len = strlen(s);
    TEST_ASSERT_TRUE(len >= 5 && len <= 15);

    for (size_t j = 0; j < len; ++j) {
      TEST_ASSERT_TRUE(s[j] >= 'a' && s[j] <= 'z');
    }
  }

  list_destroy(list, free);
}



int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_list_create);
  RUN_TEST(test_list_append);
  RUN_TEST(test_list_insert);
  RUN_TEST(test_list_insert_and_remove);
  RUN_TEST(test_list_size_null);
  RUN_TEST(test_list_is_empty_null);
  RUN_TEST(test_list_get_error);
  RUN_TEST(test_insert_error);
  RUN_TEST(test_append_error);
  RUN_TEST(test_list_remove_error);
  RUN_TEST(test_compare_int);
  RUN_TEST(test_compare_str);
  RUN_TEST(test_sort_int);
  RUN_TEST(test_sort_str);
  RUN_TEST(test_merge_int);
  RUN_TEST(test_merge_str);
  RUN_TEST(test_is_sorted_descending_int);
  RUN_TEST(test_split);
  RUN_TEST(test_split_sort_merge);
  RUN_TEST(test_sort_guard_conditions);
  RUN_TEST(test_split_guard_conditions);
  RUN_TEST(test_split_internal_middle);
  RUN_TEST(test_split_index_zero_moves_all_nodes);
  RUN_TEST(test_is_sorted_guard_conditions);
  RUN_TEST(test_is_sorted_detects_unsorted_pair);
  RUN_TEST(test_generate_random_string_chars_and_length);
  RUN_TEST(test_generate_list_ints);
  RUN_TEST(test_generate_list_uses_random_string);
  return UNITY_END();
}