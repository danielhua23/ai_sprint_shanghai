# Running kernel benchmark

> [!NOTE]  
> Scripts referred throughout this guide are available at https://github.com/danielhua23/ai_sprint_shanghai/blob/main/scripts/track1-agent.

## Install benchmark tool

```bash
pip install geak-eval
```

## Run benchmark

**I suggest run benchmark first and then submit results in next section**

```bash
cd /workspace
export PATH_TO_KERNEL_FILE="your_generated_kernel_file"
./1_bench.sh perf iteration_id
```
* `iteration_id` is the id you wanna test perf, since you will generate kernels in every iteration, usually, the bigger id is, the perf is better.
* `PATH_TO_KERNEL_FILE` is the `output_file` used to store kernels agent generated, which is specified in the config file by default. for example, `/hackathon-agent/outputs/reflexion_oneshot_rocm_1.json` where `1` in the cmd means you are benchmarking the 1st iter result.

when the benchmark performance done, by default, you can find a folder named `/hackathon-agent/outputs/reflexion_oneshot_rocm_1` which include some files and folders like below

<img width="959" height="359" alt="image" src="https://github.com/user-attachments/assets/910a1cf7-f2b0-4090-9ffa-0ec20b51007e" />

* `exec/perf`: performance result of kernels that pass all the unit tests
* `exec/rocm_performance_analysis.txt`: performance analysis of kernels that pass all the unit tests
* `exec/test*.py`: the unit tests of kernels
* `out.json and out.json_results_0.json`: detailed test log
* `out.json_all_passes.json`: precise test log
* `out.json_perf_0.json`: **performance result**
* `out.jsonpassk.txt`: ratio that pass all the unit tests

## Submit to leaderboard

```bash
cd /workspace
export PATH_TO_FOLDER_OR_FILE="your_generated_kernel_dir"
./1_bench.sh submit your_team_name
```

This will show you the results you get above and submit them to a leaderboard. The leaderboard is hosted 
as a Huggingface 🤗 space and is available at [https://daniehua-track1-agent-leaderboard.hf.space/](https://daniehua-track1-agent-leaderboard.hf.space/).

## submit your code to repo for review

before deadline, you must submit your modification to repo by creating a Pull Requests, following below steps

* step1: using git status see the files you changed

```bash
git status
```

* step2: using git add to pick your files for our review
    * agent code 
    * outputs folder like `/hackathon-agent/outputs/reflexion_oneshot_rocm_5.json` including generated kernels whose performance is the best. 
    * performance file, like `out.json_perf_0.json`

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
