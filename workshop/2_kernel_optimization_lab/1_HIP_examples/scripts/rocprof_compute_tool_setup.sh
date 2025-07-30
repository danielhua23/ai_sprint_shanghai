#/bin/bash

# get rocprofiler-compute tool
wget https://github.com/ROCm/rocprofiler-compute/releases/download/rocm-6.4.1/rocprofiler-compute-rocm-6.4.1.tar.gz
tar xf rocprofiler-compute-rocm-6.4.1.tar.gz

# create and activate a virtual environment
python3 -m venv rocprof_env
source rocprof_env/bin/activate
# install the rocprofiler-compute tool's dependencies
python3 -m pip install -r rocprofiler-compute-3.1.0/requirements.txt
# verify the installation
rocprofiler-compute-3.1.0/src/rocprof-compute -h

# set up locale for rocprofiler-compute tool
sudo apt update
sudo apt install locales
sudo locale-gen en_US.UTF-8