#include <stdio.h>
#include <pthread.h>

#define H 4
#define REP 1000000

long contador = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *inc(void *arg) {
    for (int i = 0; i < REP; i++) {
        /* Descomentar las siguientes líneas para corregir la condición de carrera: */
        /* pthread_mutex_lock(&m); */
        contador++;
        /* pthread_mutex_unlock(&m); */
    }
    return NULL;
}

int main(void) {
    pthread_t t[H];
    
    // Crear hilos
    for (int i = 0; i < H; i++) {
        pthread_create(&t[i], NULL, inc, NULL);
    }
    
    // Esperar hilos
    for (int i = 0; i < H; i++) {
        pthread_join(t[i], NULL);
    }
    
    printf("contador=%ld esperado=%d\n", contador, H * REP);
    return 0;
}