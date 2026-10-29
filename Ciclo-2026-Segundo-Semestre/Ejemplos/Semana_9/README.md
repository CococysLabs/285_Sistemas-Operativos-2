# Semana 9: comunicación kernel-usuario

`so2proc.ko` expone `/proc/so2_monitor`, devuelve una línea JSON y permite
cambiar el umbral de memoria libre con una entrada validada.

```bash
make
sudo insmod so2proc.ko
cat /proc/so2_monitor | python3 -m json.tool
echo 4096 | sudo tee /proc/so2_monitor
python3 lector.py
echo abc | sudo tee /proc/so2_monitor  # debe fallar
sudo rmmod so2proc
make clean
```

| Error | Causa | Solución |
|---|---|---|
| Tipo incompatible con `file_operations` | Kernel moderno usa `proc_ops`. | Usar los campos `proc_*`. |
| No existe `/proc/so2_monitor` | Módulo no cargado o falló `proc_create`. | Revisar `dmesg` y `lsmod`. |
| Lectura infinita | `read` no actualiza la posición. | Usar `single_open` y `seq_read`. |
