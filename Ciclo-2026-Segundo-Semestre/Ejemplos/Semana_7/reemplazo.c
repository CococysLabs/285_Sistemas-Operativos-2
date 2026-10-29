#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MARCOS 16

static int contiene(const int *marco, int m, int pagina)
{
    for (int i = 0; i < m; i++)
        if (marco[i] == pagina)
            return i;
    return -1;
}

static int fifo(const int *ref, int n, int m)
{
    int marco[MAX_MARCOS], fallos = 0, siguiente = 0;
    for (int i = 0; i < m; i++)
        marco[i] = -1;
    for (int i = 0; i < n; i++) {
        if (contiene(marco, m, ref[i]) < 0) {
            marco[siguiente] = ref[i];
            siguiente = (siguiente + 1) % m;
            fallos++;
        }
    }
    return fallos;
}

static int lru(const int *ref, int n, int m)
{
    int marco[MAX_MARCOS], uso[MAX_MARCOS], fallos = 0;
    for (int i = 0; i < m; i++)
        marco[i] = -1, uso[i] = -1;
    for (int i = 0; i < n; i++) {
        int pos = contiene(marco, m, ref[i]);
        if (pos < 0) {
            pos = 0;
            for (int j = 1; j < m; j++)
                if (uso[j] < uso[pos])
                    pos = j;
            marco[pos] = ref[i];
            fallos++;
        }
        uso[pos] = i;
    }
    return fallos;
}

static int optimo(const int *ref, int n, int m)
{
    int marco[MAX_MARCOS], usados = 0, fallos = 0;
    for (int i = 0; i < n; i++) {
        if (contiene(marco, usados, ref[i]) >= 0)
            continue;
        fallos++;
        if (usados < m) {
            marco[usados++] = ref[i];
            continue;
        }
        int victima = 0, mas_lejos = -1;
        for (int j = 0; j < m; j++) {
            int k = i + 1;
            while (k < n && ref[k] != marco[j])
                k++;
            if (k > mas_lejos)
                mas_lejos = k, victima = j;
        }
        marco[victima] = ref[i];
    }
    return fallos;
}

static void imprimir(const int *ref, int n, int m, int verbose)
{
    printf("Cadena:");
    for (int i = 0; i < n; i++)
        printf(" %d", ref[i]);
    printf("  marcos=%d\n", m);
    printf("FIFO=%d  LRU=%d  OPT=%d\n", fifo(ref, n, m), lru(ref, n, m),
           optimo(ref, n, m));
    (void)verbose;
}

static int entero(const char *texto, int *valor)
{
    char *fin;
    long v = strtol(texto, &fin, 10);
    if (*texto == '\0' || *fin != '\0' || v < 0 || v > 2147483647L)
        return -1;
    *valor = (int)v;
    return 0;
}

int main(int argc, char **argv)
{
    static const int predeterminada[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    static const int belady[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int ref[1024], n, m, verbose = 0;

    if (argc == 1) {
        n = (int)(sizeof(predeterminada) / sizeof(predeterminada[0]));
        memcpy(ref, predeterminada, sizeof(predeterminada));
        m = 3;
    } else {
        int inicio = 1;
        if (strcmp(argv[1], "-v") == 0)
            verbose = 1, inicio++;
        if (argc - inicio < 2 || entero(argv[inicio], &m) < 0 ||
            m < 1 || m > MAX_MARCOS || argc - inicio - 1 > 1024) {
            fprintf(stderr, "Uso: %s [-v] <marcos> <ref1> <ref2> ...\n", argv[0]);
            return EXIT_FAILURE;
        }
        n = argc - inicio - 1;
        for (int i = 0; i < n; i++)
            if (entero(argv[inicio + 1 + i], &ref[i]) < 0) {
                fprintf(stderr, "Referencia invalida: %s\n", argv[inicio + 1 + i]);
                return EXIT_FAILURE;
            }
    }
    imprimir(ref, n, m, verbose);
    if (argc == 1)
        printf("Belady FIFO: 3 marcos=%d  4 marcos=%d\n",
               fifo(belady, 12, 3), fifo(belady, 12, 4));
    return EXIT_SUCCESS;
}
