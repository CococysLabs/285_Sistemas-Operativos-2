# Semana 10: namespaces, cgroups y Kubernetes

Los scripts muestran el aislamiento de procesos, límites de Docker y la
terminación por OOM. Ejecútalos únicamente dentro de una VM de laboratorio.

```bash
sudo ./01_unshare.sh
sudo ./02_cgroups.sh
sudo ./03_oom.sh
kubectl apply --dry-run=client -f k8s/deployment.yaml
```

`02_cgroups.sh` espera cgroups v2 y muestra `134217728` y `50000 100000`.

| Error | Causa | Solución |
|---|---|---|
| Permiso denegado en Docker | El usuario no accede al daemon. | Configurar el grupo `docker` o usar la política de la VM. |
| No existe `memory.max` | El sistema usa cgroups v1. | Usar una VM con cgroups v2. |
| Aviso de swap limit | La capacidad no está habilitada. | Es un aviso; no afecta esta demostración. |
