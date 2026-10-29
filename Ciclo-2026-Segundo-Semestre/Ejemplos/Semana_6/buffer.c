#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

int buf[N], in = 0, out = 0;
sem_t vacios, llenos;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *productor(void *a) {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&vacios); // Esperar si no hay espacios vacíos
        
        pthread_mutex_lock(&m); 
        buf[in] = i; 
        in = (in + 1) % N; 
        pthread_mutex_unlock(&m);
        
        sem_post(&llenos); // Señalar que hay un nuevo elemento
    }
    return NULL;
}

void *consumidor(void *a) {
    for (int i = 1; i <= 10; i++) {
        sem_wait(&llenos); // Esperar si no hay elementos llenos
        
        pthread_mutex_lock(&m); 
        int x = buf[out]; 
        out = (out + 1) % N;
        pthread_mutex_unlock(&m);
        
        sem_post(&vacios); // Señalar que se liberó un espacio
        
        printf("consumido %d\n", x);
    }
    return NULL;
}

int main(void) {
    pthread_t prod, cons;
    
    // Inicializar semáforos: (N espacios vacíos, 0 elementos llenos)
    sem_init(&vacios, 0, N);
    sem_init(&llenos, 0, 0);
    
    pthread_create(&prod, NULL, productor, NULL);
    pthread_create(&cons, NULL, consumidor, NULL);
    
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    
    sem_destroy(&vacios);
    sem_destroy(&llenos);
    
    return 0;
}