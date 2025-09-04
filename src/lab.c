#include "lab.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * TODO: 
 * Implement all functions declared in lab.h 
 * Remove all useless junk in this file 
 * Delete main.c, understand that this is unit test based. 
 * Code annotations, try try try to think through it and not go to AI!!! 
 */

struct List { 
  struct Node* head; // sentinel node 
  int size; // size of linked list 
};

typedef struct Node {
  int data; 

  // pointer to next node in list 
  struct Node* next; 

  // pointer to previous node in list 
  struct Node* prev; 
} Node;

List *list_create(ListType type) {
  if (type != LIST_LINKED_SENTINEL) {
    return NULL; 
  }

  List *list = (List *)malloc(sizeof(List)); 

  if (list == NULL) {
    return NULL; 
  }

  Node *sentinel = (Node *)malloc(sizeof(Node)); 
  if (sentinel == NULL) {
    free(list); 
    return NULL; 
  }

  sentinel->data = 0; 
  sentinel->next = sentinel; // circular
  list->head = sentinel; 
  list->size = 0; 

  return list; 
}

void *list_destroy(List *list, FreeFunc free_func) {
  if (!list->head) {
    return; 
  }

  Node *curr = list->head;
  Node *next;

  while (curr) {
    next = curr->next;
    free_func(curr->data);
    free(curr);
    curr = next;
  }

  free(list);
}

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

bool list_insert(List *list, size_t index, void *data) {
  if (!list || !data || index > list->size) { 
    return false; 
  }

  Node *new = (Node *)malloc(sizeof(Node)); 

  new->data = data; 

  Node *curr = list->head->next; // node right after sentinel 
  for (size_t i = 0; i < index; i++) {
    curr = curr->next; 
  }

  new->next = curr;
  new->prev = curr->prev;
  curr->prev->next = new;
  curr->prev = new; 
  list->size++;
  return true;
}

void *list_remove(List *list, size_t index) {
  if (!list || index > list->size) {
    return NULL; 
  }

  Node *curr = list->head->next; 
  for (size_t i = 0; i < index; i++) {
    curr = curr->next; 
  }

  curr->prev->next = curr->next; 
  curr->next->prev = curr->prev;
  list->size--;
  return true; 
}

void *list_get(const List *list, size_t index) {
  if (!list || index > list->size) {
    return NULL; 
  }

  Node *curr = list->head->next; 
  for (size_t i = 0; i < index; i++) {
    curr = curr->next; 
  }

  return curr->data;
}

size_t list_size(const List *list) {
  if (!list) {
    return 0; 
  }
  return list->size;
}

bool list_is_empty(const List *list) {
  if (!list) {
    return true; 
  }
  return list->size == 0;
}


