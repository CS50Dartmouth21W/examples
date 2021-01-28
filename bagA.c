/*
 * this is bag.c 
 * 
 * really need a better header comment.
 */

#include <stdio.h>
#include <stdlib.h>
#include "bagA.h"

/* the items in a bag */
typedef struct bagnode {
  void *item;
  struct bagnode *next;
} bagnode_t;

bagnode_t *bagnode_new(void *item);

/* the bag as a whole */
typedef struct bag {
  bagnode_t *head;
} bag_t;


/* ********************* bag_new ************************* */
/* bag_new: create a new bag.
 *
 * We return:
 *   a pointer if success, NULL if failure.
 * We guarantee:
 *   the bag is initialized as empty.
 * Caller is responsible for:
 *   eventually calling bag_delete()
 * Notes:
 *   
 */
bag_t * 
bag_new(void)
{
  bag_t *bag = malloc(sizeof(bag_t));

  if (bag != NULL) {
    bag->head = NULL;
  }
  return bag;
}


/* ********************* bag_insert ************************* */
/* bag_insert: insert the given name into the bag.
 *
 * We assume:
 *   caller provides a valid bag pointer valid item pointer.
 * We return:
 *   true if success, false if failure.
 * We guarantee:
 *   item pointer will be retained in bag; item itself is not copied.
 * Caller is responsible for:
 *   later pulling the item out of the bag and free'ing it if appropriate.
 * Notes:
 *   Note the bag stores a copy of the item pointer - but not the item itself.
 */
bool bag_insert(bag_t *bag, void *item) 
{
  if (bag == NULL) {
    return false;
  }

  bagnode_t *node = bagnode_new(item);
  if (node == NULL) {
    return false;
  }

  // insert the new node at head of the list
  node->next = bag->head;
  bag->head = node;

  return true;
}

/* ********************* bagnode_new ************************* */
/* bagnode_new: create a new node to store the given name.
 * We assume:
 *   the pointer 'name' is a unique pointer - not good to store repeat pointer in bag.
 * We return:
 *   pointer to new node, if successful, else returns NULL.
 * We guarantee:
 *   item pointer will be retained in node; item itself is not copied.
 * Caller is responsible for:
 *   later deleting 'name'.
 * Notes:
 *   Note the node stores a copy of the item pointer - but not the item itself.
 */
bagnode_t *bagnode_new(void *item) 
{
  // allocate memory for the new node
  bagnode_t *node = malloc(sizeof(bagnode_t));
  
  if (node == NULL) {
    return NULL;
  }

  // initialize node contents
  node->next = NULL;
  node->item = item;

  return node;
}

/* ********************* bag_extract ************************* */
/* bag_extract: extract an item (any item) from the bag.
 * We assume:
 *   caller provides a valid bag pointer.
 * We return:
 *   an item pointer, or NULL if bag is empty or if some failure.
 * We guarantee:
 *   return of an item from the bag, if bag is not empty.
 * Caller is responsible for:
 *   freeing the item if that is appropriate.
 */
void *bag_extract(bag_t *bag) 
{
  if (bag == NULL) {
    return NULL;
  } else if (bag->head == NULL) {
    return NULL;
  } else {
    // pull off the node at head of the list
    bagnode_t *node = bag->head;
    void *item = bag->head->item;
    bag->head = node->next;
    free(node);
    return item;
  }
}


/* ********************* bag_print ************************* */
/* bag_print: print a bag, calling the func on each item.
 * We assume:
 *   caller provides a valid bag;
 *   caller provides a valid print-function pointer.
 *   output should go to stdout.
 * We return:
 *   nothing.
 * We print:
 *   the list of items, separated by comma-space, surrounded by {curly brackets}.
 * Caller is responsible for:
 *   printing a following newline if desired.
 * Notes:
 *   All our output is to stdout so printfunc should also print to stdout.
 *   We print nothing if bag==NULL; we print empty strings if printfunc==NULL.
 */
/* *************************************************
 * 
 */
void bag_print(bag_t *bag, void (*printfunc)(void *item)) 
{
  if (bag == NULL) {
    return;
  } else {
    printf("{");
    for (bagnode_t *node = bag->head; node != NULL; node = node->next) {
      if (printfunc != NULL)
	(*printfunc)(node->item);
      printf(", ");
    }
    printf("}");
  }
}
