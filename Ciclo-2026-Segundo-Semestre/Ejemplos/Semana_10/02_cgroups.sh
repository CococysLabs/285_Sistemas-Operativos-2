#!/usr/bin/env bash
set -euo pipefail

limpiar() { docker rm -f web >/dev/null 2>&1 || true; }
trap limpiar EXIT
if [[ "$(stat -fc %T /sys/fs/cgroup)" != "cgroup2fs" ]]; then
  echo "Se requiere cgroups v2." >&2
  exit 1
fi
docker rm -f web >/dev/null 2>&1 || true
docker run -d --name web --memory=128m --cpus=0.5 nginx >/dev/null
pid=$(docker inspect -f '{{.State.Pid}}' web)
ps -o pid,comm -p "$pid"
sudo lsns -p "$pid"
cg=$(awk -F: '$1 == 0 { print $3 }' "/proc/$pid/cgroup")
cat "/sys/fs/cgroup$cg/memory.max"
cat "/sys/fs/cgroup$cg/cpu.max"
