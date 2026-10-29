#!/usr/bin/env bash
set -euo pipefail

echo "Creando namespaces PID, de montaje y UTS."
sudo unshare --pid --fork --mount-proc --uts bash -c '
  hostname contenedor-so2
  echo "PID dentro del namespace: $$"
  hostname
  ps aux
'
