all:
	make vec

vec:
	gcc -Wall -Wextra -Wpedantic -Werror src/vector.c -o vector.out
