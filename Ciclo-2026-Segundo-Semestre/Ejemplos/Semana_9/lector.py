#!/usr/bin/env python3
import json
import time

for _ in range(5):
    with open("/proc/so2_monitor", encoding="utf-8") as entrada:
        print(json.load(entrada))
    time.sleep(1)
