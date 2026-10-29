# Semana 8: monitoreo desde el kernel

El módulo `metricas.ko` informa contadores acumulados de CPU, memoria libre y
los cinco procesos con mayor RSS. Los contadores de CPU son ticks, no
porcentajes; para obtener porcentajes se necesitan dos muestras.

## Requisitos y ejecución

Requiere Linux 6.12, headers del kernel en ejecución, GCC, `make` y privilegios
para cargar módulos.

```bash
make
sudo insmod metricas.ko
sudo dmesg | grep 'met:'
./comparar.sh
sudo rmmod metricas
make clean
```

| Error | Causa | Solución |
|---|---|---|
| `kcpustat_cpu` no declarado | Falta `linux/kernel_stat.h`. | Instalar headers y conservar ese include. |
| Dereferencia nula en RSS | Se intentó leer un hilo del kernel. | Validar `p->mm`. |
| CPU no parece porcentaje | Son contadores acumulados. | Tomar dos muestras y calcular deltas. |
