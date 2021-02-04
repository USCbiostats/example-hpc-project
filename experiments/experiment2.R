library(slurmR) # This loads parallel
library(Rcpp)

# Check if this is the first run. This utility function returns TRUE if
# the function has not been called before, and FALSE otherwise.
# I will use this to make sure that I only source the C++ and R
# source files only once during the simulation.
is_this_first <- function() {
  if (!exists("yes_this_is_first", envir = .GlobalEnv)) {
    assign("yes_this_is_first", TRUE, envir = .GlobalEnv)
    return(TRUE)
  } else {
    FALSE
  }
}

# Trying it out, 
is_this_first() # TRUE
is_this_first() # FALSE

# This will generate a 100 simulations over 20 cores (see the option -njobs-).
# slurm options can be passed using -sbatch_opt-
ans <- Slurm_lapply(
  # Common options in lapply()
  X   = 1:100,
  FUN = function(s) {
    
    # This will run only the first time it is called within
    # the job.
    if (is_this_first()) {
      message("Sourcing rwrapper.cpp")
      Rcpp::sourceCpp("programs/rwrapper.cpp")
      source("programs/wrap_sim.R")
    }
    
    out <- sim_events(1000, 100, seed = s)
    wrap_sim(out)
  },
  # Named list of objects I need to export
  export = c("is_this_first"), 
  # How many cores I want to use
  njobs = 20L,
  # Options to pass to Slurm
  sbatch_opt = list(
    account = "dconti_624",
    mem     = "2GB"
    )
)

str(ans)

saveRDS(ans, "experiments/experiment2.rds")

