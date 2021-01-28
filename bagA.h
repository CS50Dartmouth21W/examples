/*
 * bag.h
 */

#include <stdbool.h>

/* the bag as a whole */
typedef struct bag bag_t;

bag_t * bag_new(void);
bool bag_insert(bag_t *bag, void *item);
void *bag_extract(bag_t *bag);
void bag_print(bag_t *bag, void (*printfunc)(void *item));
