# Semana 11: seguridad y auditoría

El módulo endurece una interfaz `/proc` con validación de entrada, copia segura,
control de capacidad y un rango explícito. `REVISION_SEGURIDAD.md` describe el
patrón inseguro solo como texto.

```bash
make
sudo insmod so2proc_seguro.ko
echo 512 | sudo tee /proc/so2_monitor
echo 70000 | sudo tee /proc/so2_monitor  # debe fallar
sudo rmmod so2proc_seguro
sudo ./auditoria.sh
sudo bpftrace trazar_execve.bt
make clean
```

La auditoría y bpftrace requieren `auditd`, `ausearch`, BTF y soporte de
tracepoints en el kernel.

| Error | Causa | Solución |
|---|---|---|
| `auditctl` no existe | Falta auditd. | Instalar y activar auditd en la VM. |
| Tracepoint no encontrado | Falta soporte de trazado. | Usar un kernel con `CONFIG_FTRACE_SYSCALLS` y BTF. |
| Usuario normal puede escribir | Permisos o capacidad incorrectos. | Usar 0644 y comprobar `CAP_SYS_ADMIN`. |
