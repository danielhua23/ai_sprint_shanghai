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

## submit your code to repo for review

before deadline, you must submit your modification to repo by creating a Pull Requests, following below steps

* step1: using git status see the files you changed

```bash
git status
```

* step2: using git add to pick what you submit

```bash
git add files_you_will_submit
```

* step3: using git commit to submit, **note the info is your team name** which keep same as the name you submit to leaderboard

```bash
git commit -m "your_team_name"
```

* step4: using git push to push to remote

```bash
git push
```

* step5: create a Pull Request

Now, once you run `git push` successfully, you will see the create pull request button at the main page of repo, click it to submit a Pull Request
