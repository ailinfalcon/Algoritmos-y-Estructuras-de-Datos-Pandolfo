compilar:
	gcc src/split.c -Wall -Werror -std=c99 -o split
	
valgrind: compilar
	valgrind --leak-check=full  ./split