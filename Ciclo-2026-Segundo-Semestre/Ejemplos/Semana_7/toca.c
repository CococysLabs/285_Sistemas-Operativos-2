#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    const size_t total = 200UL << 20;
    const long pagina = sysconf(_SC_PAGESIZE);
    char *memoria = malloc(total);
    if (memoria == NULL || pagina <= 0) {
        free(memoria);
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < total; i += (size_t)pagina)
        memoria[i] = 1;
    free(memoria);
    return EXIT_SUCCESS;
}
