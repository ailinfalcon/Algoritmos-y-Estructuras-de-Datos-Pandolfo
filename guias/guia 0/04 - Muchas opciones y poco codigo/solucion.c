#define ERROR -1

#define A_BATALLAS 20
#define R_BATALLAS 17
#define L_BATALLAS 15
#define G_BATALLAS 30
#define F_BATALLAS 8
#define O_BATALLAS 27
#define T_BATALLAS 5
#define C_BATALLAS 39
#define B_BATALLAS 10


/*
 * Se recibe una letra. Si ella se corresponde con alguna de las proveídas en el enunciado (A, R, L, G, F, O, T, C, R, B) se devuelve la cantidad de batallas ganadas por el pokemon respectivo.
 */

int batallas_ganadas(char letra){
        int batallas = 0;

        switch(letra){
        case 'A':
                batallas = A_BATALLAS;
                break;
        case 'R':
                batallas = R_BATALLAS;
                break;
        case 'L':
                batallas = L_BATALLAS;
                break;
        case 'G':
                batallas = G_BATALLAS;
                break;
        case 'F':
                batallas = F_BATALLAS;
                break;
        case 'O':
                batallas = O_BATALLAS;
                break;
        case 'T':
                batallas = T_BATALLAS;
                break;
        case 'C':
                batallas = C_BATALLAS;
                break;
        case 'B':
                batallas = B_BATALLAS;
                break;
        default:
                batallas = ERROR;
                break;
        }

        return batallas;
}