#include "simulation.h"

// Simulate Police Force Events
//
// This function generates data similar to that featured in the paper. Events
// are drawn at random, as the number of officers per event. The outcome variable,
// whether the officer points his gun or not, is drawn sequentially as a poisson
// process.
//
// @param nevents,nofficers Integers. Number of events and officers to simulate.
// @param min_per_event,max_per_event Integers. Lower and upper bounds for the
// number of officers in the event.
// @param min_year,max_years Integers. Lower and upper bounds for the number
// of years of experience of the officers.
// @param min_rate,max_rate Doubles. Lower and upper bounds for the reaction
// rates (see details).
// @param female_par,years_par,rho_par,exposure_par Doubles. Parameters (coefficients) for
// the logistic probabilities.
// @param seed Integer. Seed for the pseudo-number generation.
//
// @details
// The simulation process goes as follow:
// 1. The officers are simulated. Female ~ Bernoulli(0.5),
//    Action rate ~ Unif(min_rate, max_rate),
//    Years of experience ~ Discrete Unif[min_years, max_year]
// 2. Events are simulated, each event has a nofficers ~ Discrete Unif[min_per_event, max_per_event]
//    Once the event is done, a sequence of reaction is given by each officers'
//    action rate (Poisson process). Whether an officer points or not is set by
//    a logistic model
//
//    point ~ female + years of experience + has any pointed? + previous exposure
//
//    The corresponding parameters are as specified by the user. Events are simulated
//    one at a time.
// @returns
// A data frame with the following columns
// - Officer id
// - Whether the officer is female
// - Years of experience
// - Incident id
// - Whether the officer pointed a gun
//
// Each row represents one report per officer involved in the event.
// @export
// @examples
// x <- simulate_njforce(1000, 400)
// [[Rcpp::export(rng = false, name = "sim_events")]]
List sim_events(
    int nevents,
    int nofficers,
    int min_per_event = 1,
    int max_per_event = 5,
    int min_year = 0,
    int max_year = 10,
    int min_rate = 5,
    int max_rate = 5,
    double par_officer_female = -.5,
    double par_officer_years = -.5,
    double par_exposure_event = 0,
    double par_exposure_prev = .5,
    double par_event_violence = 1.0,
    double par_officer_fe = 1.0,
    int nsims = 1,
    int seed = 123
) {
  
  // Preparing the simulation object
  Simulation sim(
      nevents, nofficers, min_per_event, max_per_event,
      min_year, max_year, min_rate, max_rate, par_officer_female, par_officer_years,
      par_exposure_event, par_exposure_prev, par_event_violence, par_officer_fe,
      seed
  );
  
  // Running the simulation
  sim.run();
  
  Vec< Vec< double > > ans(sim.get_data(false));
  
  if (nsims > 1) {
    // Re-running and recovering only the behavior
    for (int i = 1u; i < nsims; ++i) {
      sim.run(true);
      ans.push_back(sim.get_response());
    }
  }
  
  Vec< std::string > cnames={"officer_id",
    "officer_female",
    "years",
    "officer_fe",
    "event_id",
    "event_violence",
    "response_time",
    "not_first",
    "exposed",
    "pointed"};
  
  return List::create(
    _["data"] = ans,
    _["cnames"] = cnames
    );
  
}

// [[Rcpp::export(rng = false, name = "sim_events2")]]
std::vector<std::vector<double>> sim_events2(
    std::vector< int > event_id,
    std::vector< int > officer_id,
    std::vector< bool > officer_female,
    std::vector< double > officer_rate,
    std::vector< double > officer_fe,
    std::vector< int > officer_years,
    double par_officer_female,
    double par_officer_years,
    double par_exposure_event,
    double par_exposure_prev,
    double par_event_violence,
    double par_officer_fe,
    int nsims,
    int seed
) {
  
  // Creating the simulation object
  Simulation sim(
      event_id, officer_id, officer_female, officer_rate, officer_fe,
      officer_years, par_officer_female, par_officer_years, par_exposure_event,
      par_exposure_prev, par_event_violence, par_officer_fe, seed
  );
  
  // Running the simulation
  sim.run();
  
  Vec< Vec< double > > ans(sim.get_data(false));
  
  if (nsims > 1) {
    // Re-running and recovering only the behavior
    for (int i = 1u; i < nsims; ++i) {
      sim.run(true);
      ans.push_back(sim.get_response());
    }
  }
  
  return ans;
  
}

/***R
# ans <- sim_events(10000, 1000, par_exposure_event = 1, seed = 123)
# 
# 
# 
# summary(glm(pointed ~ -1 + female + years, data = ans, family = binomial("logit")))
*/