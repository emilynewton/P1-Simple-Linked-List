#include <stdlib.h>
#include <stdio.h>
#include "harness/unity.h"
#include "../src/lab.h"

/**
 * TODO: 
 * write unit tests to ensure list works, minimum of four? 
 */

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
  return UNITY_END();
}
