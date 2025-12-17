# Full Exmaple Walkthrough of Simulating FCPs using remage extension

This readme will include examples of simulating FCPs using longleaf, and also will include how to run jupyter notebooks used for post-processing
This is also only works for Longleaf/NERSC


### Step 1, Install remage,LEGEND-base, convert to a .sif file 

```bash
apptainer build remage.sif docker://legendexp/remage

apptainer build legend-base.sif docker://legendexp/legend-base

```

### Step 2, extend remage 

```bash

apptainer shell remage.sif

#Navigate to the fcp-simulations/build

cd /path/to/fcp-simulations
mkdir build
cd build

cmake ..

make -j$(nproc)


#Now check your build folder and there should be an executable called 'FCP_Simulations'

```

### Step 3, Run the simulation


Creata a batch script 

```bash

nano script.sh

```
Code for the script 

```bash

#!/bin/bash
#SBATCH --job-name=remage_run        # Name of the job
#SBATCH --output=remage_run_muon.out      # Single output file for all tasks
#SBATCH --error=remage_run_muon.err       # Single error file for all tasks
#SBATCH --partition=general         
#SBATCH --array=1-10                   # Partition to use
#SBATCH --time=15:00:00              #Time Limit
#SBATCH --ntasks=1                   # Number of tasks (1 process)
#SBATCH --cpus-per-task=10            # Allocate 8 CPU threads
#SBATCH --mem=60G                    # Memory required (adjust as needed)

module load apptainer

# Define path to the container
CONTAINER_PATH="/path/to/remage.sif"

# Define output file to be in the job's working directory
OUTPUT_FILE="path/to/output_file${SLURM_ARRAY_TASK_ID}.lh5"


echo "Running on: $(hostname)"
echo "SLURM Task ID: $SLURM_ARRAY_TASK_ID"
echo "Using container: $CONTAINER_PATH"
echo "Output file: $OUTPUT_FILE"

export HDF5_USE_FILE_LOCKING=FALSE  # Prevent HDF5 file locking issues

apptainer exec "$CONTAINER_PATH" ./fcp-simulations/build/FCP_Simulations \
  --gdml l200.gdml \
  --macro l200_fcp_macro.txt \
  --nthreads 10  \
  --particle "0.04 100 GeV"\
  --output "$OUTPUT_FILE" \



echo "Job finished. Output saved to $OUTPUT_FILE"

```

Exit out of nano.sh 

Run 

```bash

sbatch script.sh

```


Now you have run your simulations, and the files have been outputted as .lh5 files. From here you can do what you want but to see the rest of the tutorial check
the jupyter notebooks



