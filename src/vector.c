
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

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
		if ( vec.count >= vec.capacity ) { \
			if ( vec.capacity == 0 ) vec.capacity = 16; \
			else vec.capacity *= 2; \
			vec.items = realloc(vec.items, vec.capacity * sizeof(*vec.items)); \
			if ( vec.items == NULL ) exit(1); \
		} \
		vec.items[vec.count++] = item; \
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

	VEC_APPEND(fv, 1.5f);
	VEC_APPEND(fv, 2.5f);
	VEC_APPEND(fv, 3.5f);
	VEC_APPEND(fv, 4.5f);
	VEC_APPEND(fv, 5.5f);

	for ( i = 0; i < iv.count; i++ )
		printf("iv[%lu] = %d\n", i, iv.items[i]);

	for ( i = 0; i < fv.count; i++ )
		printf("fv[%lu] = %f\n", i, fv.items[i]);

	return EXIT_SUCCESS;

}

