# Semana 3: Rastreando llamadas al sistema

Esta semana contiene un archivo relacionado con la creación de procesos y la observación del flujo entre el usuario y el kernel:

- `procesos.c` es un programa que crea un proceso hijo, ejecuta un comando (`ls -l`) y espera su terminación. Además, muestra cómo realizar invocaciones directas mediante `syscall()`.

La ejecución y rastreo de este programa nos permitirá observar las llamadas al sistema subyacentes como `clone`, `execve`, y `wait4` utilizando la herramienta `strace`.

## Requisitos

En tu máquina virtual con Linux (ej. Linux Mint), necesitas tener instalado el compilador de C (`gcc`) y la herramienta de rastreo (`strace`):

```bash
sudo apt update
sudo apt install -y gcc strace
```

## Compilar y ejecutar el programa

Entra en la carpeta donde se encuentra el archivo y compílalo usando `gcc`:

```bash
gcc procesos.c -o procesos
```

El resultado será un archivo ejecutable llamado `procesos`. Para ejecutarlo y rastrear simultáneamente las llamadas al sistema (incluyendo las del proceso hijo), utiliza `strace` con los siguientes filtros:

```bash
strace -f -e trace=getpid,clone,execve,wait4,exit_group ./procesos
```

## Interpretación de resultados

Al ejecutar el comando de rastreo, observarás una salida que intercala la ejecución estándar del programa con las llamadas interceptadas por `strace`. Presta atención a las siguientes llamadas:

1. `getpid()`: Invocada directamente para obtener el identificador del proceso.
2. `clone()`: Es la llamada al sistema subyacente que `glibc` utiliza para implementar la función `fork()`.
3. `execve()`: Muestra la ejecución del binario `/usr/bin/ls` con sus respectivos argumentos.
4. `wait4()`: Utilizada por el proceso padre para esperar el cambio de estado del hijo.
5. `exit_group()`: Indica la terminación del proceso.