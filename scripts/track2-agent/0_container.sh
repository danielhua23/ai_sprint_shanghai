CONTAINER_NAME="agent-container"
DOCKER_IMG="rocm/pytorch:latest"


running_container=$(docker ps -q --filter "name=$CONTAINER_NAME")

if [ $running_container ]; then
    echo "Stopping the already running $CONTAINER_NAME container"
    docker stop $CONTAINER_NAME
fi


if ! test -f hackathon-agent/requirements.txt; then echo "WARNING: This script assumes it is launched from a directory containing a cloned hackathon agent, but it was not found. Make sure hackathon agent is cloned at ${PWD}/hackathon-agent."; fi

echo "Starting a container based off $DOCKER_IMG..."
echo "With the following mounted folders:"
echo "$PWD/.hf_cache -> /root/.cache/huggingface/hub"
echo "$PWD -> /workspace"

docker run \
    -it \
    --ipc host \
    --name $CONTAINER_NAME \
    --privileged \
    --cap-add=CAP_SYS_ADMIN \
    --device=/dev/kfd \
    --device=/dev/dri \
    --device=/dev/mem \
    --cap-add=SYS_PTRACE \
    --security-opt seccomp=unconfined \
    -e PYTORCH_ROCM_ARCH="gfx942" \
    -e HSA_NO_SCRATCH_RECLAIM=1 \
    -e SAFETENSORS_FAST_GPU=1 \
    -v "$PWD/.hf_cache/":/root/.cache/huggingface/hub/ \
    -v "$PWD":/workspace \
    -v ${PWD}/hackathon-agent:/hackathon-agent \
    -w /workspace \
    $DOCKER_IMG 
