# A wrapper for the simulation output
wrap_sim <- function(x) {
  structure(
    as.data.frame(do.call(cbind, x$data)),
    names = x$cnames
  )
}