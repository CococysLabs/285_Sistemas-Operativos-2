# Semana 7: reemplazo de páginas

Compara FIFO, LRU y Óptimo, y observa fallos menores al tocar 200 MiB de memoria.

## Requisitos

Linux, GCC, `make`, `/usr/bin/time` y `/proc/vmstat`.

## Ejecución

```bash
make
make test
./reemplazo -v 3 7 0 1 2 0 3 0 4 2 3 0 3 2
./medir_fallos.sh
make clean
```

La cantidad de fallos reales depende del kernel y del estado de la memoria.

| Error | Causa | Solución |
|---|---|---|
| `/usr/bin/time` no existe | Falta el paquete `time`. | Instalarlo con el gestor de paquetes de la distribución. |
| LRU coincide con FIFO | No se actualizó el uso en los aciertos. | Revisar `uso[pos] = i`. |
| Segmentation fault | Marcos fuera del rango permitido. | Usar entre 1 y 16 marcos. |
