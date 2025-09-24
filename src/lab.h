#ifndef LAB_H
#define LAB_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @file lab.h
 * @brief Header file for a generic list data structure supporting multiple implementations.
 */
typedef struct List List;

/**
 * @enum ListType
 * @brief Enumeration for selecting the list implementation type.
 */
typedef enum {
    LIST_LINKED_SENTINEL
} ListType;

/**
 * @typedef FreeFunc
 * @brief Function pointer type for freeing elements. If NULL, no action is taken.
 * Must be provided by the user when destroying the list or removing elements.
 *
 */
typedef void (*FreeFunc)(void *);

/**
 * @typedef Compare 
 * @brief. Function pointer type for comparing two elements in a list. If a < b, 
 * a negative integer is returned and vice versa. 
 */
typedef int (*Compare)(void* a, void* b); 


/**
 * @brief Create a new list of the specified type.
 * @param type The type of list to create (e.g., LIST_LINKED_SENTINEL).
 * @return Pointer to the newly created list, or NULL on failure.
 */
List *list_create(ListType type);

/**
 * @brief Destroy the list and free all associated memory.
 * @param list Pointer to the list to destroy.
 * @param free_func Function to free individual elements. If NULL, elements are not freed.
 */
void list_destroy(List *list, FreeFunc free_func);

/**
 * @brief Append an element to the end of the list.
 * @param list Pointer to the list.
 * @param data Pointer to the data to append.
 * @return true on success, false on failure.
 */
bool list_append(List *list, void *data);

/**
 * @brief Insert an element at a specific index.
 * @param list Pointer to the list.
 * @param index Index at which to insert the element.
 * @param data Pointer to the data to insert.
 * @return true on success, false on failure (e.g., index out of bounds).
 */
bool list_insert(List *list, size_t index, void *data);

/**
 * @brief Remove an element at a specific index.
 * @param list Pointer to the list.
 * @param index Index of the element to remove.
 * @return Pointer to the element, or NULL if index is out of bounds.
 */
void *list_remove(List *list, size_t index);

/**
 * @brief Get a pointer the element at a specific index.
 * @param list Pointer to the list.
 * @param index Index of the element to retrieve.
 * @return Pointer to the element, or NULL if index is out of bounds.
 */
void *list_get(const List *list, size_t index);

/**
 * @brief Get the current size of the list.
 * @param list Pointer to the list.
 * @return The number of elements in the list.
 */
size_t list_size(const List *list);

/**
 * @brief Check if the list is empty.
 * @param list Pointer to the list.
 * @return true if the list is empty, false otherwise.
 */
bool list_is_empty(const List *list);

/**
 * @brief Sorts the list. 
 * @param list Pointer to the list.
 * @param start Starting index of the list. 
 * @param end Ending index of the list. 
 * @param cmp Pointer to the Compare function. 
 */
void sort(const List *list, size_t start, size_t end, Compare cmp);

/**
 * @brief Merges two lists.
 * @param list1 Pointer to the first list. 
 * @param list2 Pointer to the second list. 
 * @param cmp Pointer to the Compare function.
 */
void merge(const List *list1, const List *list2, Compare cmp); 

/**
 * @brief Sorts integers in descending order.
 * @param a Integer to be compared. 
 * @param b Integer to be compared. 
 */
int compare_int(void *a, void *b); 

/**
 * @brief Sorts strings in lexicographical order.
 * @param a String to be compared. 
 * @param b String to be compared. 
 */
int compare_str(void *a, void *b); 

/**
 * @brief Returns if the list is sorted or not.
 * @return true is the list is sorted, false otherwise. 
 */
bool is_sorted(List* list, Compare cmp); 

#endif // LAB_H