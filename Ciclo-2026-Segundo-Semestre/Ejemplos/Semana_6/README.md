# Semana 6: Condición de carrera, Mutex y Semáforos

Esta semana abordamos la demostración de una condición de carrera con hilos, su corrección utilizando exclusión mutua (`pthread_mutex`) y la coordinación del patrón productor-consumidor mediante el uso de semáforos.

## Requisitos

Para poder observar adecuadamente las condiciones de carrera, se recomienda ejecutar este programa en una máquina virtual (VM) Linux con al menos 2 núcleos asignados. 
Es necesario contar con el compilador `gcc` y enlazar la biblioteca de hilos utilizando la bandera `-pthread`.

---

## 1. Condición de carrera y Mutex (`carrera.c`)

El siguiente código muestra cómo cuatro hilos incrementan un contador global un millón de veces cada uno. Sin sincronización, el resultado es inconsistente (condición de carrera). Al descomentar el `lock` y `unlock`, se soluciona el problema usando un Mutex.

### Compilación y Ejecución

Guarda el código anterior en un archivo llamado `carrera.c` y ejecútalo varias veces:

```bash
gcc carrera.c -o carrera -pthread
time ./carrera
```
*Nota: La exclusión mutua corrige el resultado pero hace que el programa tarde más tiempo al serializar la sección crítica.*

---

## 2. Productor-Consumidor con Semáforos (`buffer.c`)

Este código implementa un búfer circular de 5 posiciones sincronizado mediante semáforos (para controlar los espacios vacíos y llenos) y un mutex (para proteger los índices del búfer).

### Compilación y Ejecución

Guarda el código anterior en un archivo llamado `buffer.c` y ejecútalo:

```bash
gcc buffer.c -o buffer -pthread
./buffer
```

---

## Resolución de Problemas (Errores Comunes)

| Falla / Mensaje de Error Común | Causa Raíz Frecuente | Solución Aplicada |
| :--- | :--- | :--- |
| **El programa se congela (no termina)** | Se olvidó `pthread_mutex_unlock` en algún camino o hay espera circular (Deadlock). | Revisar que cada `lock` tenga su `unlock`; usar un orden fijo de candados. |
| **sem_init: Function not implemented (macOS)** | Semáforos sin nombre no soportados nativamente fuera de Linux. | Ejecutar estrictamente dentro de la VM Linux. |
| **Resultado correcto pero muy lento** | Sección crítica demasiado grande o bloqueo en cada iteración de un ciclo extenso. | Acumular en una variable local y bloquear una sola vez al final (ej. `sumas parciales`). |
