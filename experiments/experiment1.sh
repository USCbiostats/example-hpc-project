#!/bin/sh
#SBATCH --job-name=Experiment-1
#SBATCH --account=dconti_624
#SBATCH --mail-user=vegayon@usc.edu
#SBATCH --mail-type=END,FAIL
#SBATCH --time=01:00:00
#SBATCH --mem=4GB
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
#SBATCH --output=experiments/experiment1-%j.out
module load usc
module load r/4.0.0
Rscript --vanilla experiments/experiment1.R
