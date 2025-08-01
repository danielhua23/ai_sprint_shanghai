# Reduce Examples

This is a collection of HIP example codes of parallel reduce. You can build and run kernels by command line.

## Open a Terminal in Jupyterlab
1. Click "+" icon to open a terminal:
   ![OPEN_TERMINAL_IN_NB_0](./assets/activate_terminal_in_nb_0.png)
2. Click the black Terminal icon:
   ![OPEN_TERMINAL_IN_NB_1](./assets/activate_terminal_in_nb_1.png)
3. The terminal opened will look like:
   ![OPEN_TERMINAL_IN_NB_2](./assets/activate_terminal_in_nb_2.png)

We will use this terminal to do all the following work.

## ROCm Compute Profiler Installation (Optional)

### Installation by script (RECOMMENDED)
Install the ROCm compute profiler by running this scripts:
```bash
cd /app/ai_sprint_shanghai/workshop/2_kernel_optimization_lab/1_HIP_examples/
./scripts/rocprof_compute_tool_setup.sh
```
After installation, activate the virtual environment:
```bash
source rocprof_env/bin/activate
```

### Manual Installation
Install the ROCm compute profiler manually by below steps:

1. Download prebuilts from https://github.com/ROCm/rocprofiler-compute/releases/tag/rocm-6.4.1 , by command:
    ```bash
    cd /app/ai_sprint_shanghai/workshop/2_kernel_optimization_lab/1_HIP_examples
    wget https://github.com/ROCm/rocprofiler-compute/releases/download/rocm-6.4.1/rocprofiler-compute-rocm-6.4.1.tar.gz
    ```
2. Uncompress tar file:
    ```bash
    tar xf rocprofiler-compute-rocm-6.4.1.tar.gz
    ```
3. Create and activate virtual environment:
    ```bash
    python3 -m venv rocprof_env
    source rocprof_env/bin/activate
    ```
4. Install rocprof-compute dependancies
    ```bash
    python3 -m pip install -r rocprofiler-compute-3.1.0/requirements.txt
    ```
5. Verify installation by executing the prebuilt binary:
    ```bash
    rocprofiler-compute-3.1.0/src/rocprof-compute -h
    ```
    If the installation succeed, the output will look like below:

    ![INSTALLATION_VERIFY](./assets/rocprof_install_verify.png)

6. Ensure 'en_US.UTF-8' is available on the system
   ```bash
   sudo apt update
   sudo apt install locales
   sudo locale-gen en_US.UTF-8
   ```
   If the installation succeed, the output will look like this:

   ![LOCALE_INSTALLATION_VERIFY](./assets/locale_install_verify.png)

## Build and Run

### Build and Benchmark reduce_v0 Kernel
Enter into `benchmark/reduce_v0/`, build the executable and run benchmark, by:
```console
cd /app/ai_sprint_shanghai/workshop/2_kernel_optimization_lab/1_HIP_examples/benchmark/reduce_v0/
make
./reduce_v0
```

### Build and Benchmark reduce_v1 Kernel
Enter into `benchmark/reduce_v1/`, build the executable and run benchmark, by:
```console
cd /app/ai_sprint_shanghai/workshop/2_kernel_optimization_lab/1_HIP_examples/benchmark/reduce_v1/
make
./reduce_v1
```

### Build and Benchmark reduce_v2 Kernel
Enter into `benchmark/reduce_v2/`, build the executable and run benchmark, by:
```console
cd /app/ai_sprint_shanghai/workshop/2_kernel_optimization_lab/1_HIP_examples/benchmark/reduce_v2/
make
./reduce_v2
```

### Build and Benchmark reduce_v3 Kernel
Enter into `benchmark/reduce_v3/`, build the executable and run benchmark, by:
```console
cd /app/ai_sprint_shanghai/workshop/2_kernel_optimization_lab/1_HIP_examples/benchmark/reduce_v3/
make
./reduce_v3
```

### Build and Benchmark reduce_v4 Kernel
Enter into `benchmark/reduce_v4/`, build the executable and run benchmark, by:
```console
cd /app/ai_sprint_shanghai/workshop/2_kernel_optimization_lab/1_HIP_examples/benchmark/reduce_v4/
make
./reduce_v4
```

### Build and Benchmark reduce_v5 Kernel
Enter into `benchmark/reduce_v5/`, build the executable and run benchmark, by:
```console
cd /app/ai_sprint_shanghai/workshop/2_kernel_optimization_lab/1_HIP_examples/benchmark/reduce_v5/
make
./reduce_v5
```

## Profile and Comparation

Profiling reduce_v3, by:
```bash
cd /app/ai_sprint_shanghai/workshop/2_kernel_optimization_lab/1_HIP_examples/benchmark/

/app/ai_sprint_shanghai/workshop/2_kernel_optimization_lab/1_HIP_examples/rocprofiler-compute-3.1.0/src/rocprof-compute profile -n reduce_v3_data -- ./reduce_v3/reduce_v3
```

Analyze reduce_v3, by:
```bash
/app/ai_sprint_shanghai/workshop/2_kernel_optimization_lab/1_HIP_examples/rocprofiler-compute-3.1.0/src/rocprof-compute analyze -p workloads/reduce_v3_data/MI300/ -o reduce_v3_profile.log
```

The above command will conduct analysis of reduce_v3's metrics data and the output will be dumped into reduce_v3_profile.log

Profiling reduce_v4, by:
```bash
cd /app/ai_sprint_shanghai/workshop/2_kernel_optimization_lab/1_HIP_examples/benchmark/

/app/ai_sprint_shanghai/workshop/2_kernel_optimization_lab/1_HIP_examples/rocprofiler-compute-3.1.0/src/rocprof-compute profile -n reduce_v4_data -- ./reduce_v4/reduce_v4
```

Compare reduce_v3's profile data with reduce_v4's, by:
```bash
cd /app/ai_sprint_shanghai/workshop/2_kernel_optimization_lab/1_HIP_examples/benchmark/

/app/ai_sprint_shanghai/workshop/2_kernel_optimization_lab/1_HIP_examples/rocprofiler-compute-3.1.0/src/rocprof-compute analyze -p workloads/reduce_v3_data/MI300/ -p workloads/reduce_v4_data/MI300/ | tee reduce_v3_v4_compare.log
```

The comparation analysis result can be find in output log file reduce_v3_v4_compare.log.

## Reference
1. https://rocm.docs.amd.com/projects/HIP/en/latest/tutorial/reduction.html#
2. https://github.com/ROCm/rocm-examples/tree/amd-staging
3. https://github.com/gerayking/hpc_learning