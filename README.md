# Example HPC project with R

## Experiments

Currently, this project illustrates how to leverage parallel computing in R with
Slurm. The main files are located at [experiments/]. There are two different
examples:

1. `experiment1.R` uses a PSOCK cluster with 4 cores to make 100 simulations.
   Up to 24 cores is reasonable.

2. `experiment2.R` uses the `slurmR` package to run the same experiment, with
   the difference that, instead of 4, we request 20 cores. Now, this number
   can be significantly larger (e.g. 200).

Both programs generate an RDS file that contains the results of the simulations.
And furthermore, both programs generate exactly the same results.


## General pointers

1. Setup a Git repository (optional, but good idea)

2. Prepare the R environment: R packages to be installed.

3. Copy the data: [`scp`](https://www.computerhope.com/unix/scp.htm),  [`rsync`](https://www.computerhope.com/unix/rsync.htm), or [filezilla](https://filezilla-project.org/).

4. Prepare the R script (using [`slurmR`](https://github.com/USCbiostats/slurmR).

5. Submit the job using [slurm](https://slurm.schedmd.com/overview.html).


## Dependencies

This depends on the [slurmR](https://github.com/USCbiostats/slurmR) package.
