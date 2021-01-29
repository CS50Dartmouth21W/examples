/* 
 * bag.c - CS50 'bag' module WITH A UNIT_TEST
 *
 * see bag.h for more information.
 *
 * David Kotz, April 2016, 2017, 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bag.h"
#include "memory.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct bagnode {
  void *item;         // pointer to data for this item
  struct bagnode *next;       // link to next node
} bagnode_t;

/**************** global types ****************/
typedef struct bag {
  struct bagnode *head;       // head of the list of items in bag
} bag_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see bag.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static bagnode_t *bagnode_new(void *item);

/**************** bag_new() ****************/
/* see bag.h for description */
bag_t *
bag_new(void)
{
  bag_t *bag = count_malloc(sizeof(bag_t));

  if (bag == NULL) {
    return NULL; // error allocating bag
  } else {
    // initialize contents of bag structure
    bag->head = NULL;
    return bag;
  }
}

/**************** bag_insert() ****************/
/* see bag.h for description */
void
bag_insert(bag_t *bag, void *item)
{
  if (bag != NULL && item != NULL) {
    // allocate a new node to be added to the list
    bagnode_t *new = bagnode_new(item);
    if (new != NULL) {
      // add it to the head of the list
      new->next = bag->head;
      bag->head = new;
    }
  }

#ifdef MEMTEST
  count_report(stdout, "After bag_insert");
#endif
}


/**************** bagnode_new ****************/
/* Allocate and initialize a bagnode */
static bagnode_t * // not visible outside this file
bagnode_new(void *item)
{
  bagnode_t *node = count_malloc(sizeof(bagnode_t));

  if (node == NULL) {
    // error allocating memory for node; return error
    return NULL;
  } else {
    node->item = item;
    node->next = NULL;
    return node;
  }
}

/**************** bag_extract() ****************/
/* see bag.h for description */
void *
bag_extract(bag_t *bag)
{
  if (bag == NULL) {
    return NULL; // bad bag
  } else if (bag->head == NULL) {
    return NULL; // bag is empty
  } else {
    bagnode_t *out = bag->head; // the node to take out
    void *item = out->item; // the item to return
    bag->head = out->next;  // hop over the node to remove
    count_free(out);
    return item;
  }
}

/**************** bag_print() ****************/
/* see bag.h for description */
void
bag_print(bag_t *bag, FILE *fp, void (*itemprint)(FILE *fp, void *item) )
{
  if (fp != NULL) {
    if (bag != NULL) {
      fputc('{', fp);
      for (bagnode_t *node = bag->head; node != NULL; node = node->next) {
	// print this node
	if (itemprint != NULL) {  // print the node's item 
	  (*itemprint)(fp, node->item); 
	  fputc(',', fp);
	}
      }
      fputc('}', fp);
    } else {
      fputs("(null)", fp);
    }
  }
}

/**************** bag_iterate() ****************/
/* see bag.h for description */
void
bag_iterate(bag_t *bag, void *arg, void (*itemfunc)(void *arg, void *item) )
{
  if (bag != NULL && itemfunc != NULL) {
    // call itemfunc with arg, on each item
    for (bagnode_t *node = bag->head; node != NULL; node = node->next) {
      (*itemfunc)(arg, node->item); 
    }
  }
}

/**************** bag_delete() ****************/
/* see bag.h for description */
void 
bag_delete(bag_t *bag, void (*itemdelete)(void *item) )
{
  if (bag != NULL) {
    for (bagnode_t *node = bag->head; node != NULL; ) {
      if (itemdelete != NULL) {       // if possible...
        (*itemdelete)(node->item);      // delete node's item
      }
      bagnode_t *next = node->next;     // remember what comes next
      count_free(node);         // free the node
      node = next;          // and move on to next
    }

    count_free(bag);
  }

#ifdef MEMTEST
  count_report(stdout, "End of bag_delete");
#endif
}

/* *********************************************************** */
/* Unit test: glass-box test of the bag module.
 * Create a bag, work with it, and verify its innards. 
 */
#ifdef UNIT_TEST
#include <stdbool.h>

// file-local global variables
static int unit_tested = 0;     // number of test cases run
static int unit_failed = 0;     // number of test cases failed

// a macro for shorthand calls to expect()
#define EXPECT(cond) { unit_expect((cond), __LINE__); }

// Checks 'condition', increments unit_tested, prints FAIL or PASS
void unit_expect(bool condition, int linenum)
{
  unit_tested++;
  if (condition) {
    printf("PASS test %03d at line %d\n", unit_tested, linenum);
  } else {
    printf("FAIL test %03d at line %d\n", unit_tested, linenum);
    unit_failed++;
  }
}

int main()
{
  // make a bag to work with
  bag_t *bag1 = bag_new();
  EXPECT(bag1 != NULL);
  EXPECT(bag1->head == NULL);

  // put five things into the bag  
  int a=1, b=2, c=3, d=4, e=5;
  bag_insert(bag1, &a);
  bag_insert(bag1, &b);
  bag_insert(bag1, &c);
  bag_insert(bag1, &d);
  bag_insert(bag1, &e);

  // check the head of the bag, and remove it
  EXPECT(bag1->head->item == &e);
  EXPECT(bag1->head->next->item == &d);
  EXPECT(bag_extract(bag1) == &e);
  EXPECT(bag1->head->item == &d);

  // pull the others out and then expect bag is empty
  EXPECT(bag_extract(bag1) == &d);
  EXPECT(bag_extract(bag1) == &c);
  EXPECT(bag_extract(bag1) == &b);
  EXPECT(bag_extract(bag1) == &a);
  EXPECT(bag1->head == NULL);
  EXPECT(bag_extract(bag1) == NULL);

  // mix insert and extract
  bag_insert(bag1, &a);
  bag_insert(bag1, &b);
  EXPECT(bag_extract(bag1) == &b);
  bag_insert(bag1, &c);
  bag_insert(bag1, &d);
  bag_insert(bag1, &e);

  // ensure we can work with another bag too
  bag_t *bag2 = bag_new();
  EXPECT(bag2 != NULL);

  // move all items from bag1 to the bag2
  for (int *x; (x = bag_extract(bag1)) != NULL; ) {
    bag_insert(bag2, x);
  }
  EXPECT(bag_extract(bag1) == NULL);
  // and pull them out
  EXPECT(bag_extract(bag2) == &a);
  EXPECT(bag_extract(bag2) == &c);
  EXPECT(bag_extract(bag2) == &d);
  EXPECT(bag_extract(bag2) == &e);
  EXPECT(bag_extract(bag2) == NULL);

  // There should be more tests, notably, of bag_iterate, bag_print, bag_delete
  // ...

  // print a summary
  if (unit_failed > 0) {
    printf("FAILED %d of %d tests\n", unit_failed, unit_tested);
    return unit_failed;
  } else {
    printf("PASSED all of %d tests\n", unit_tested);
    return 0;
  }
}
#endif // UNIT_TEST
