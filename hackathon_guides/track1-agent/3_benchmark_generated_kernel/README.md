# Running kernel benchmark

> [!NOTE]  
> Scripts referred throughout this guide are available at https://github.com/danielhua23/ai_sprint_shanghai/blob/main/scripts/track1-agent.

## Install benchmark tool

```bash
pip install geak-eval
```

## Run benchmark(Optional)

you can skip this section if you want to run benchmark and submit results together, and go to next section

```bash
cd /workspace
export PATH_TO_KERNEL_FILE="your_generated_kernel_file"
./1_bench.sh perf
```

where `PATH_TO_KERNEL_FILE` is the `output_file` used to store kernels agent generated, which is specified in the config file by default. 

`NAME_OF_OUTPUT_FILE` is prefix of output file name, results will store in `PATH_TO_FOLDER_OR_FILE` dir

for example, ```tb_eval -f /hackathon-agent/outputs/_1.json -o out -ds tbg```

## Submit to leaderboard

```bash
cd /workspace
export PATH_TO_FOLDER_OR_FILE="your_generated_kernel_dir"
./1_bench.sh submit your_team_name
```

This will submit run `perf` benchmarks, show you the results and submit them to a leaderboard. The leaderboard is hosted 
as a Huggingface 🤗 space and is available at [https://huggingface.co/spaces/daniehua/track1_leaderboard](https://huggingface.co/spaces/daniehua/track1_leaderboard).
