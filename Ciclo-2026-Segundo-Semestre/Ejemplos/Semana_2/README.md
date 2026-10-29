# Semana 2: módulo de kernel con parámetros

Esta semana contiene los archivos correspondientes a un módulo que saluda a un nombre recibido como parámetro y muestra la versión del kernel.

- `saludo.c` es un módulo de kernel que comprueba su ciclo de vida registrando mensajes al cargarlo y retirarlo.

La compilación de módulos de kernel debe hacerse sobre una máquina Linux. El módulo debe coincidir con la versión exacta del kernel en ejecución.

## Requisitos

En Linux Mint (o distribuciones basadas en Debian/Ubuntu), instala las herramientas de compilación y los headers correspondientes al kernel en ejecución:

```bash
sudo apt update
sudo apt install -y build-essential linux-headers-$(uname -r)
```

## Compilar y cargar el módulo de ejemplo

Entra en la carpeta del módulo y compílalo:

```bash
make
```

El resultado es saludo.ko. Cárgalo enviando el parámetro, verifica que se encuentre en ejecución y revisa los mensajes del kernel:

```bash
sudo insmod saludo.ko nombre="Estudiante"
lsmod | grep saludo
cat /sys/module/saludo/parameters/nombre
modinfo saludo.ko
sudo dmesg | tail -n 3
```

Cuando termines, retíralo y verifica el registro de salida:

```bash
sudo rmmod saludo
sudo dmesg | tail -n 3
```

Para borrar los archivos generados:

```bash
make clean
```