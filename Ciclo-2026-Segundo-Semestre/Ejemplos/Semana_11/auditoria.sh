#!/usr/bin/env bash
set -euo pipefail

regla_activa=1
trap 'if [[ "$regla_activa" == 1 ]]; then sudo auditctl -W /proc/so2_monitor -p wa -k so2cfg || true; fi' EXIT
sudo auditctl -w /proc/so2_monitor -p wa -k so2cfg
echo 512 | sudo tee /proc/so2_monitor >/dev/null
if echo 9999999999999999999999999999999999999999 | sudo tee /proc/so2_monitor; then
  echo "La entrada invalida fue aceptada inesperadamente." >&2
  exit 1
fi
sudo ausearch -k so2cfg -i | tail -5
sudo auditctl -W /proc/so2_monitor -p wa -k so2cfg
regla_activa=0
