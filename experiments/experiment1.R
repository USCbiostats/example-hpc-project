library(slurmR) # This loads parallel
library(Rcpp)


# But we need to setup the program in a cluster
library(parallel)
cl  <- makePSOCKcluster(4)
out <- clusterEvalQ(cl, {
  library(Rcpp)
  sourceCpp("programs/rwrapper.cpp")
})

# Sending the wrap_sim function to the offspring sessions
# This could have been sourced in -clusterEvalQ- too
source("programs/wrap_sim.R")
clusterExport(cl, "wrap_sim")

# Trying it out, generating 100 simulations in parallel
ans <- parLapply(cl, 1:100, function(s) {
  out <- sim_events(1000, 100, seed = s)
  wrap_sim(out)
})

str(ans)

saveRDS(ans, "experiments/experiment1.rds")

