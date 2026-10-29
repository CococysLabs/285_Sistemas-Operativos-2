#!/usr/bin/env bash
set -euo pipefail

set +e
docker run --rm --memory=64m python:3-alpine \
  python -c 'a = bytearray(200 * 1024 * 1024)'
estado=$?
set -e
printf 'Codigo de salida: %d (137 indica terminacion por OOM)\n' "$estado"
sudo dmesg | grep -i oom | tail -2 || true
