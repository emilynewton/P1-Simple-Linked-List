#include "lab.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Represents a circular list with a sentinel node. 
 * AI Use: No AI 
 */
struct List { 
  struct Node* head; // sentinel node 
  int size; // size of linked list 
};

/**
 * Represents a node in the circular linked list. 
 * AI Use: No AI
 */
typedef struct Node {
  void *data; 

  // pointer to next node in list 
  struct Node* next; 

  // pointer to previous node in list 
  struct Node* prev; 
} Node;

/**
 * Creates a new circular linked list with a sentinel node. 
 * AI Use: Assisted by AI
 */
List *list_create(ListType type) {
  if (type != LIST_LINKED_SENTINEL) { // GCOVR_EXCL_START
    return NULL; 
  } // GCOVR_EXCL_STOP

  List *list = (List *)malloc(sizeof(List)); 

  if (list == NULL) { // GCOVR_EXCL_START
    return NULL; 
  } // GCOVR_EXCL_STOP

  Node *sentinel = (Node *)malloc(sizeof(Node)); 
  if (sentinel == NULL) { // GCOVR_EXCL_START
    free(list); 
    return NULL; 
  } // GCOVR_EXCL_STOP

  sentinel->data = 0; 
  sentinel->next = sentinel; // circular
  sentinel->prev = sentinel; // circular
  list->head = sentinel; 
  list->size = 0; 

  return list; 
}

/**
 * Destroys the circular linked list and frees all associated memory.
 * AI Use: Assisted by AI
 */
void list_destroy(List *list, FreeFunc free_func) {
  Node *curr = list->head->next;

  while (curr != list->head) {
    Node *next = curr->next;
    if (free_func != NULL && curr->data != NULL) {
      free_func(curr->data);
    }
    free(curr);
    curr = next;
  }
  free(list->head);
  free(list);
}

/**
 * Appends a new node with the given data to the end of the circular linked list.
 * AI Use: No AI 
 */
bool list_append(List *list, void *data) {
  if (!list || !data) { 
    return false; 
  } 

  Node *new = (Node *)malloc(sizeof(Node)); 

  new->data = data; 
  new->next = list->head; // circular list points back to sentinel node 
  new->prev = list->head->prev; // sentinel's previous node is the curr last node before appending
  list->head->prev->next = new; 
  list->head->prev = new; 
  list->size++; 
  return true; 
}

/**
 * Inserts a new node with the given data at the specified index in the circular linked list.
 * AI Use: Assisted by AI 
 */
bool list_insert(List *list, size_t index, void *data) {
  if (!list || !data || index > list->size) {  
    return false; 
  } 

  Node *new = (Node *)malloc(sizeof(Node)); 

  new->data = data; 

  Node *curr = list->head;

  for (size_t i = 0; i < index; i++) {
    curr = curr->next; 
  }

  new->next = curr->next;
  new->prev = curr;
  curr->next->prev = new;
  curr->next = new;
  list->size++;
  return true;
}

/**
 * Removes the node at the specified index from the circular linked list and returns its data.
 * AI Use: No AI 
 */
void *list_remove(List *list, size_t index) {
  if (!list || index >= list->size) { 
    return NULL; 
  }

  Node *curr = list->head->next; 
  for (size_t i = 0; i < index; i++) {
    curr = curr->next; 
  }

  if (!curr) return NULL;
  
  curr->prev->next = curr->next; 
  curr->next->prev = curr->prev;
  void *data = curr->data;
  free(curr);
  list->size--;
  return data;
}

/**
 * Retrieves the data at the specified index in the circular linked list.
 * AI Use: No AI 
 */
void *list_get(const List *list, size_t index) {
  if (!list || index >= list->size) { 
    return NULL; 
  } 

  Node *curr = list->head->next; 
  for (size_t i = 0; i < index; i++) {
    curr = curr->next; 
  }
  return curr->data; 
}

/**
 * Returns the number of elements in the circular linked list.
 * AI Use: No AI
 */
size_t list_size(const List *list) {
  if (!list) {
    return 0; 
  }
  return list->size;
}

/**
 * Checks if the circular linked list is empty.
 * AI Use: No AI
 */
bool list_is_empty(const List *list) {
  if (!list) {
    return true; 
  }
  return list->size == 0;
}


