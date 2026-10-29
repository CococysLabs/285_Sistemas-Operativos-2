# Revisión de seguridad

## Patrón inseguro (solo texto)

El patrón siguiente es inseguro y no forma parte de ningún archivo compilable:

```text
memcpy(buf, puntero_de_usuario, longitud);
umbral = simple_strtol(buf, NULL, 10);
```

Presenta tres problemas: copia un puntero de usuario sin `copy_from_user`,
permite una longitud mayor que el búfer y acepta contenido sin validación.

## Corrección aplicada

`so2proc_seguro.c` usa `capable(CAP_SYS_ADMIN)`, rechaza longitudes vacías o
mayores que el búfer, copia con `copy_from_user`, convierte con `kstrtoint`,
limita el rango a 0--65536 y protege el estado con un mutex. La entrada
`/proc/so2_monitor` se crea con permisos 0644.

Esta demostración es defensiva: no incluye exploits ni instrucciones para
abusar de la interfaz.
