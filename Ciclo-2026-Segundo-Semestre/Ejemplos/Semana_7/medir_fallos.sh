#!/usr/bin/env bash
set -euo pipefail

valor_vmstat() { awk -v clave="$1" '$1 == clave { print $2 }' /proc/vmstat; }
antes=$(valor_vmstat pgfault)
mayores_antes=$(valor_vmstat pgmajfault)
./toca
despues=$(valor_vmstat pgfault)
mayores_despues=$(valor_vmstat pgmajfault)
printf 'pgfault delta: %d\npgmajfault delta: %d\n' \
  "$((despues - antes))" "$((mayores_despues - mayores_antes))"
/usr/bin/time -v ./toca 2>&1 | grep -i 'page faults' || true
