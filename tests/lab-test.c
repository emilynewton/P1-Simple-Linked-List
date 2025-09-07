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



int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_list_create);
  RUN_TEST(test_list_append);
  RUN_TEST(test_list_insert);
  RUN_TEST(test_list_insert_and_remove);
  return UNITY_END();
}
