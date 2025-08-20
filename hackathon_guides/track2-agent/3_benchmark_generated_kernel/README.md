# Running kernel benchmark

> [!NOTE]  
> Scripts referred throughout this guide are available at https://github.com/danielhua23/ai_sprint_shanghai/blob/main/scripts/track2-agent.

## Install benchmark tool

```bash
pip install geak-eval
```

after your installation, run below and **ensure the version is 0.1.5**

```bash
pip list | grep geak-eval
geak-eval               0.1.5
```

## Run benchmark And submit result

**we suggest the `PATH_TO_KERNEL_FILE` better be under `/workspace`**

```bash
cd /workspace
export TEAM_NAME=<custom_team_name>
export PATH_TO_KERNEL_FILE=<your_generated_kernel_file>
./1_bench.sh perf 
```
* `PATH_TO_KERNEL_FILE` is the `output_file` used to store kernels agent generated, which is specified in the config file by default. for example, `export PATH_TO_KERNEL_FILE="reflexion_oneshot_tritonbench_1.json" ` where `1` in the cmd means you are benchmarking the 1st iter result. we suggest you input the biggest iteration file

clarify some output metrics:
* The **Call Accuracy** says the ratio of kernels generated compiling correctly
* The **Exec Accuracy** says the ratio of kernels generated executing the same result as the internal test units, but which is not indicating the kernel is right. see Tips in next section.

<img width="589" height="43" alt="image" src="https://github.com/user-attachments/assets/5dc1d8c3-25a8-446c-8e07-17a7cea59647" />

when the benchmark performance done, **by default, you can find a folder named `reflexion_oneshot_tritonbench_1` which include some files and folders like below**

<img width="959" height="359" alt="image" src="https://github.com/user-attachments/assets/910a1cf7-f2b0-4090-9ffa-0ec20b51007e" />

* `exec/gen_perf`: performance result and execution logs of kernels
* `exec/performance_analysis.txt`: performance analysis of kernels
* `exec/*.py`: generated kernels with perf test case
* `out.json or out.json_results_0.json`: detailed test log
* `out.json_all_passes.json`: precise test log
* `out.json_perf_0.json`: **performance result**
* `out.jsonpassk.txt`: ratio that pass all the unit tests

And you can see your scores at [https://daniehua-agent-leaderboard.hf.space/](https://daniehua-agent-leaderboard.hf.space/)

<img width="1089" height="155" alt="image" src="https://github.com/user-attachments/assets/0847d3f5-087b-4606-9975-8980bbe79225" />


### Tips

We left a challenge for you, sometimes although you see the log message saying **both call status and exec status are true** when you benchmark, like below picture, but there are no perf data of them in `exec/gen_perf`(you can check log under `exec/gen_perf` to find the details) . That means, the generated kernels reach the perf that exceeds the roofline, which is obviously incorrect. It's the limited test units that cause the unrobust kernels pass the test. So the call status and exec status are only for a reference, not the groudtruth. The solution is you can compare the baseline code in agent and generated code or use other methods to find the error and fix it.

<img width="1232" height="38" alt="image" src="https://github.com/user-attachments/assets/b6b94fe3-8627-4ec0-becf-1e8207b753f1" />

And this kind of kernel, you can see the log like:

<img width="967" height="106" alt="image" src="https://github.com/user-attachments/assets/f36b1469-2cd1-4b68-a7b3-1a55dcdda5f7" />

## submit your code to repo for review

before deadline, you must submit your modification to repo by creating a Pull Requests, following below steps

* step0: ensure you are under your forked repo

* step1: using git status see the files you changed

```bash
git status
```

* step2: using git add to pick your files for our review
    * agent code
    * agent-generated kernels file (.json) that matches your submissiong score. like `reflexion_oneshot_tritonbench_4.json`
    * outputs folder like `/workspace/reflexion_oneshot_tritonbench_9` including generated kernels whose performance is the best. 
    * performance file, like `reflexion_oneshot_tritonbench_9_out.json_perf_0.json`

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

* step5: create a Pull Request to danielhua23/hackathon_agent

Now, once you run `git push` successfully, you will see the create pull request button at the main page of repo, click it to submit a Pull Request
