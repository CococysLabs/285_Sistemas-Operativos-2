# Semana 5: Suma paralela de un arreglo con PThreads

Esta semana contiene un ejercicio de creación, paso de argumentos y unión de hilos POSIX (PThreads). 

- `suma_hilos.c` es un programa que suma 200 millones de enteros dividiendo el arreglo en partes para que cada hilo realice el cálculo de su segmento en paralelo. El hilo principal se encarga de combinar los resultados y medir la aceleración del tiempo de ejecución.

## Requisitos

Para observar los beneficios del paralelismo, se recomienda ejecutar este programa en una máquina virtual (VM) con al menos 2 núcleos asignados. Es necesario contar con el compilador `gcc` y herramientas de monitorización de procesos como `ps` y `time`.

## Compilar el programa

Para compilar el programa debes incluir la bandera `-pthread` para enlazar la biblioteca de hilos. Utiliza el nivel de optimización `-O2`:

```bash
gcc -O2 suma_hilos.c -o suma_hilos -pthread
```

## Ejecución y Medición

Ejecuta el programa variando la cantidad de hilos (por ejemplo, 1, 2 y 4) para comparar los tiempos de ejecución y notar la aceleración gracias al paralelismo:

```bash
for k in 1 2 4; do ./suma_hilos $k; done
```

## Observación de los hilos en el Sistema Operativo

Mientras el programa se encuentra en ejecución, puedes listar los hilos de este proceso desde otra terminal para observar cómo el sistema operativo los gestiona:

```bash
ps -eLf | grep suma_hilos
```

O también puedes examinar el sistema de archivos proc:

```bash
ls /proc/$(pgrep suma_hilos)/task
```
