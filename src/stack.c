
#include <stddef.h> /* `NULL`, `size_t` */
#include <stdlib.h> /* `realloc`, `free`, `exit` */
#include <stdio.h> /* `printf` */
#include <string.h> /* `memmove` */

/*
 * This is an example of a dynamic integer stack.
 */
typedef struct istk {
	int *items;
	signed long top; /* Has to be signed because it's initialized to `-1` */
	size_t capacity;
} istk_t;

/*
 * Pushes `item` onto the stack.
 *
 * The logic is almost identical to `VEC_APPEND` from `vector.c`.
 * The only notable change is the switch from `count` to `top`.
 */
#define STK_PUSH( st, item ) \
	do { \
		if ( (size_t)((st).top + 1) >= (st).capacity ) { \
			if ( (st).capacity == 0 ) (st).capacity = 16; \
			else (st).capacity *= 2; \
			(st).items = realloc((st).items, (st).capacity * sizeof(*(st).items)); \
			if ( (st).items == NULL ) exit(1); \
		} \
		(st).items[++(st).top] = (item); \
	} while (0)

/* Boolean, returns if the stack is empty */
#define STK_ISEMPTY( st ) \
	( (st).top == -1 )

/* Returns the topmost item of the stack */
#define STK_PEEK( st ) \
	( (st).items[(st).top] )

/* Pops and returns the topmost item of the stack */
#define STK_POP( st ) \
	( (st).items[(st).top--] )

int main() {

	istk_t is = { 0, -1, 0 };

	size_t i;

	STK_PUSH(is, 1);
	STK_PUSH(is, 10);
	STK_PUSH(is, 100);

	/* (0:1) (1:10) (2:100) */
	for ( i = 0; i < (size_t)(is.top + 1); i++ )
		printf("(%lu:%d) ", i, is.items[i]);
	printf("\n");

	printf("Top is %d\n", STK_PEEK(is)); /* 100 */

	/* Popping 100, 10 and then 1 */
	while (!STK_ISEMPTY(is))
		printf("Popped %d\n", STK_POP(is));

	free(is.items);

	return EXIT_SUCCESS;

}

