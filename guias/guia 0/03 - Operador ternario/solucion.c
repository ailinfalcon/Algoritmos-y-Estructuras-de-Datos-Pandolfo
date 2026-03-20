#include <stdlib.h>

int solucion(size_t valor){
        return (valor%2 == 0) ? valor/2 : valor*3 + 1;
}