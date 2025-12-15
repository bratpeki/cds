
#include <stddef.h> /* `NULL`, `size_t` */
#include <stdlib.h> /* `realloc`, `free`, `exit` */
#include <stdio.h> /* `printf` */
#include <string.h> /* `memmove` */

/*
 * This is an example of an integer vector.
 */
typedef struct ivec {
	int *items;
	size_t count;
	size_t capacity;
} ivec_t;

/*
 * This is an example of a float vector.
 * Note how the only difference is in the type used for `items`
 */
typedef struct fvec {
	float *items;
	size_t count;
	size_t capacity;
} fvec_t;

/*
 * Appends `item` to vector `vec`.
 *
 * As long as the structure includes
 * - `ANYTYPE* items`
 * - `size_t count`
 * - `size_t capacity`
 * this macro should work for it.
 *
 * Set the initial `capacity` to taste, I put `16`.
 *
 * This also force-exits the program with an exit code of 1 if it can't reallocate memory.
 * You will probably want it to handle it differently.
 */
#define VEC_APPEND( vec, item ) \
	do { \
		if ( (vec).count >= (vec).capacity ) { \
			if ( (vec).capacity == 0 ) (vec).capacity = 16; \
			else (vec).capacity *= 2; \
			(vec).items = realloc((vec).items, (vec).capacity * sizeof(*(vec).items)); \
			if ( (vec).items == NULL ) exit(1); \
		} \
		(vec).items[(vec).count++] = (item); \
	} while (0)

/*
 * Removes an item from `vec` at the given `index`.
 *
 * Checks the upper bound (always the index of the last added item).
 *
 * Make sure `index` is an unsigned type, since this macro doesn't check the lower bound.
 * Preferably, `index` is a `size_t`.
 *
 * Some implementations call for shrinking the allocated memory
 * if the count goes below a certain threshold, usually capacity/2 or capacity/4.
 * That's not implemented here.
 */
#define VEC_REMOVE( vec, index ) \
	do { \
		if ( (index) < (vec).count ) { \
			memmove( \
				&(vec).items[(index)], \
				&(vec).items[(index) + 1], \
				sizeof(*(vec).items) * ((vec).count - 1 - (index)) \
			); \
			(vec).count--; \
		} \
	} while (0)

int main() {

	/* Preferred initiallization method is setting all zeros */
	ivec_t iv = { 0, 0, 0 };
	fvec_t fv = { 0, 0, 0 };

	size_t i;

	VEC_APPEND(iv, 1);
	VEC_APPEND(iv, 2);
	VEC_APPEND(iv, 3);
	VEC_APPEND(iv, 4);
	VEC_APPEND(iv, 5);

	/* (0:1), (1:2), (2:3), (3:4), (4:5) */
	for ( i = 0; i < iv.count; i++ )
		printf("(%lu:%d) ", i, iv.items[i]);
	printf("\n");

	VEC_REMOVE(iv, 0); /* Removes 1 */
	VEC_REMOVE(iv, 0); /* Removes 2 */
	VEC_REMOVE(iv, iv.count - 1); /* Removes 5 */

	/* (0:3) (1:4) */
	for ( i = 0; i < iv.count; i++ )
		printf("(%lu:%d) ", i, iv.items[i]);
	printf("\n");

	VEC_APPEND(fv, 1.5f);
	VEC_APPEND(fv, 2.5f);
	VEC_APPEND(fv, 3.5f);
	VEC_APPEND(fv, 4.5f);
	VEC_APPEND(fv, 5.5f);

	/* (0:1.5) (1:2.5) (2:3.5) (3:4.5) (4:5.5) */
	for ( i = 0; i < fv.count; i++ )
		printf("(%lu:%.1f) ", i, fv.items[i]);
	printf("\n");

	free(iv.items);
	free(fv.items);

	return EXIT_SUCCESS;

}

