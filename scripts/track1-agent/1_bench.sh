#Usage:
# ./1_bench.sh perf <iteration id>
# ./1_bench.sh submit <team_name> (runs perf + submits to leaderboard)

LB_URL="https://daniehua-track1-agent-leaderboard.hf.space/"

# Check iter id for perf mode
if [ $1 == "perf" ] || [ $1 == "submit" ]; then
    if [ ! -z "$2" ]; then
        ITER="$2"
    elif [ ! -z "$ITER" ]; then
        ITER="$ITER"
    else
        echo "ERROR: iteration id required for perf mode"
        echo "Usage: ./1_bench.sh perf <iteration id>"
        echo "Or set ITER environment variable"
        exit 1
    fi
    echo "INFO: benching iteration: $ITER"
fi

# Check team name for submit mode
if [ $1 == "submit" ]; then
    if [ ! -z "$2" ]; then
        TEAM_NAME="$2"
    elif [ ! -z "$TEAM_NAME" ]; then
        TEAM_NAME="$TEAM_NAME"
    else
        echo "ERROR: Team name required for submit mode"
        echo "Usage: ./1_bench.sh submit <team_name>"
        echo "Or set TEAM_NAME environment variable"
        exit 1
    fi
    echo "INFO: Using team name: $TEAM_NAME"
fi


if [ $1 == "perf" ] || [ $1 == "submit" ]; then
    do
	sleep 1
    done
    echo "INFO: perf"
    date=$(date +'%b%d_%H_%M_%S')
    if [ ! -z "$PATH_TO_KERNEL_FILE" ]; then
        PATH_TO_KERNEL_FILE="$PATH_TO_KERNEL_FILE"
    else
        echo "ERROR: PATH_TO_KERNEL_FILE required for perf or submit mode"
        echo "Pls set PATH_TO_KERNEL_FILE environment variable"
        exit 1
    fi
    echo "INFO: benching kernels in $PATH_TO_KERNEL_FILE"

    geak-eval -f $(PATH_TO_KERNEL_FILE) -o output_perf -ds tbg

    PERF_OUTPUT=$(python show_results.py --iter $ITER)
    echo "$PERF_OUTPUT"
fi



if [ $1 == "submit" ]; then
    # if [ ! -z "$PERF_OUTPUT" ]; then
    #     PERF_OUTPUT="$PERF_OUTPUT"
    # else
    #     echo "ERROR: perf mode required before submit mode"
    #     echo "Usage: 1. ./1_bench.sh perf <iteration id> 2. ./1_bench.sh submit <team_name>"
    #     exit 1
    # fi

    echo "INFO: Submitting results for team: $TEAM_NAME"

    PERF_LINE=$(echo "$PERF_OUTPUT" | grep -E "[0-9]+\.[0-9]+.*,[[:space:]]*[0-9]+\.[0-9]+" | tail -1)
    TTFT=$(echo "$PERF_LINE" | awk -F',' '{gsub(/^[[:space:]]+|[[:space:]]+$/, "", $1); print $1}')     # Convert ms to seconds
    TPOT=$(echo "$PERF_LINE" | awk -F',' '{gsub(/^[[:space:]]+|[[:space:]]+$/, "", $2); print $2}')     # Convert ms to seconds  
    ITL=$(echo "$PERF_LINE" | awk -F',' '{gsub(/^[[:space:]]+|[[:space:]]+$/, "", $3); print $3}')      # Convert ms to seconds
    E2E=$(echo "$PERF_LINE" | awk -F',' '{gsub(/^[[:space:]]+|[[:space:]]+$/, "", $4); print $4}')      # Convert ms to seconds
    THROUGHPUT=$(echo "$PERF_LINE" | awk -F',' '{gsub(/^[[:space:]]+|[[:space:]]+$/, "", $5); print $5}')
        
    # Parse accuracy metrics from lm_eval output
    BITS_PER_BYTE=$(echo "$ACCURACY_OUTPUT" | grep -oE "bits_per_byte[^0-9]*([0-9]+\.[0-9]+)" | grep -oE "[0-9]+\.[0-9]+")
    BYTE_PERPLEXITY=$(echo "$ACCURACY_OUTPUT" | grep -oE "byte_perplexity[^0-9]*([0-9]+\.[0-9]+)" | grep -oE "[0-9]+\.[0-9]+")
    WORD_PERPLEXITY=$(echo "$ACCURACY_OUTPUT" | grep -oE "word_perplexity[^0-9]*([0-9]+\.[0-9]+)" | grep -oE "[0-9]+\.[0-9]+")
    
    # Default to 0.0 if parsing fails
    CALL_ACC=${CALL_ACC:-0.0}
    EXEC_ACC=${EXEC_ACC:-0.0}
    SPEEDUP1=${SPEEDUP1:-0.0}
    
    echo "Performance metrics:"
    echo "  call acc: ${TTFT}ms"
    echo "  exec acc: ${TPOT}ms"
    echo "  speedup for kernel: ${SPEEDUP1}ms"
    
    # Submit to leaderboard
    echo "Submitting to leaderboard..."
    curl -X POST $LB_URL/gradio_api/call/submit_results -s -H "Content-Type: application/json" -d "{
        \"data\": [
            \"$TEAM_NAME\",
            $TTFT,
            $TPOT,
            $ITL,
            $E2E,
            $THROUGHPUT,
            $BITS_PER_BYTE,
            $BYTE_PERPLEXITY,
            $WORD_PERPLEXITY
        ]
    }" | awk -F'"' '{ print $4}' | read EVENT_ID

    sleep 2

    echo "SUCCESS: Results submitted to leaderboard! 🤗 Check it out @ $LB_URL"
fi
