#!/usr/bin/env python3
import argparse
import json
from pathlib import Path

# -------------------- 1. 命令行参数 --------------------
parser = argparse.ArgumentParser(description="")
parser.add_argument(
    "--iter",
    type=int,
    required=True,
    help="iter id you wanna submit"
)
args = parser.parse_args()

# -------------------- 2. 读取 JSON --------------------
rpt_file = Path(
    f"/hackathon-agents/outputs/out.json_perf_{args.iter}.json"
)

with rpt_file.open(encoding="utf-8") as f:
    data = json.load(f)

# -------------------- 3. 取出 speedup 列表 -----------
speedups = data.get("speedup", [])

total_speedups = sum(speedups)

# -------------------- 4. 一行打印 --------------------
# print(f", ".join(map(str, speedups)))
print(f"{total_speedups}")
