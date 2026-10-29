#!/usr/bin/env bash
set -euo pipefail
head -1 /proc/stat
free -k
ps -eo pid,comm,rss --sort=-rss | head -6
