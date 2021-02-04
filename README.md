# Example HPC project

https://github.com/USCbiostats/example-hpc-project

1. Setup a Git repository (optional, but good idea)

2. Prepare the R environment: R packages to be installed.

3. Copy the data: [`scp`](https://www.computerhope.com/unix/scp.htm),  [`rsync`](https://www.computerhope.com/unix/rsync.htm), or [filezilla](https://filezilla-project.org/).

4. Prepare the R script (using [`slurmR`](https://github.com/USCbiostats/slurmR).

5. Submit the job using [slurm](https://slurm.schedmd.com/overview.html).

## Dependencies

This depends on the [slurmR](https://github.com/USCbiostats/slurmR) package.
