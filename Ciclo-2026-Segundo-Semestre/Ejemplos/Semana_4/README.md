# Semana 4: Explorando task_struct desde un módulo del kernel

Esta semana contiene los archivos relacionados con la lectura de los campos del PCB (`task_struct`) de un proceso a partir de su PID utilizando un módulo del kernel.

- `pcbinfo.c` es un módulo del kernel que, dado un PID, localiza su `task_struct` de forma segura (usando RCU) y muestra en el registro del sistema información como nombre, PID, TGID, PPID, estado, UID y memoria residente.

La compilación de módulos de kernel debe hacerse sobre una máquina Linux que coincida exactamente con la versión del kernel para la cual se está compilando. 

## Requisitos

Asegúrate de contar con una máquina virtual con el kernel compilado adecuadamente (incluyendo sus respectivos headers), y de tener instaladas las herramientas de compilación básicas:

```bash
sudo apt update
sudo apt install -y build-essential linux-headers-$(uname -r)
```

## Compilar y cargar el módulo de ejemplo

Asegúrate de contar con tu archivo fuente `pcbinfo.c` y tu `Makefile` configurado con `obj-m += pcbinfo.o`. Entra en la carpeta del módulo y compílalo:

```bash
make
```

El resultado será el archivo `pcbinfo.ko`. Puedes cargarlo pasando el PID de tu sesión de terminal actual (`$$`) como parámetro, retirarlo inmediatamente, y luego revisar los últimos mensajes del kernel impresos en `dmesg`:

```bash
sudo insmod pcbinfo.ko pid=$$ && sudo rmmod pcbinfo
sudo dmesg | tail -3
```

Para corroborar que la información que expone el módulo es correcta y coherente con el sistema, puedes compararla directamente con lo que el propio sistema de archivos `proc` expone para ese mismo proceso:

```bash
grep -E 'Name|State|PPid|Uid|VmRSS' /proc/$$/status
```

Cuando termines y quieras limpiar tu entorno de trabajo, borra los archivos generados durante la compilación:

```bash
make clean
```

## Notas adicionales

- La lista de procesos en el kernel cambia constantemente; este módulo utiliza `rcu_read_lock()` para leer la lista de forma segura sin bloquear a otros escritores.
- Los hilos propios del kernel no cuentan con espacio de usuario, por lo que su `mm` (memory map) es `NULL`.
- Recuerda siempre probar estas operaciones en un entorno controlado (Máquina Virtual) ya que los módulos operan con privilegios absolutos a nivel de kernel.