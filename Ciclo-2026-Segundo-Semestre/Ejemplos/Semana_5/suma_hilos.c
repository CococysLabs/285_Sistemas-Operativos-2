#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 200000000L

typedef struct { 
    int *a; 
    long ini, fin; 
    long long parcial; 
} tarea_t;

void *sumar(void *arg) {
    tarea_t *t = arg;
    long long s = 0;
    for (long i = t->ini; i < t->fin; i++) 
        s += t->a[i];
    t->parcial = s;
    return NULL;
}

int main(int argc, char **argv) {
    int k = argc > 1 ? atoi(argv[1]) : 4;
    int *a = malloc(N * sizeof(int));
    for (long i = 0; i < N; i++) 
        a[i] = 1;
        
    pthread_t th[k]; 
    tarea_t t[k];
    struct timespec t0, t1;
    
    clock_gettime(CLOCK_MONOTONIC, &t0);
    
    for (int i = 0; i < k; i++) {
        t[i] = (tarea_t){a, i * N / k, (i + 1) * N / k, 0};
        pthread_create(&th[i], NULL, sumar, &t[i]);
    }
    
    long long total = 0;
    for (int i = 0; i < k; i++) {
        pthread_join(th[i], NULL);
        total += t[i].parcial;
    }
    
    clock_gettime(CLOCK_MONOTONIC, &t1);
    printf("hilos=%d total=%lld tiempo=%.3f s\n", k, total,
           (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9);
           
    free(a);
    return 0;
}