#include "sessionise.h"

std::list < std::vector < int > > sessionise::single_sessionise(std::vector < int > timestamps, int threshold){
  
  //Generate size, output object, holding objects
  int input_size = timestamps.size();
  std::list < std::vector < int > > output;
  int intertime_hold;
  std::vector < int > holding;
  
  //Sort, push the first timestamp on to the holding vector
  std::sort(timestamps.begin(),timestamps.end());
  holding.push_back(timestamps[0]);
  
  //For each timestamp after the first one..
  for(int i = 1; i < input_size; ++i){
    
    //Generate an intertime
    intertime_hold = (timestamps[i] - timestamps[i-1]);
    
    //If the intertime is > the local minimum, throw to a new vector.
    if(intertime_hold > threshold){
      output.push_back(holding);
      holding.clear();
    }
    
    //Regardless, write to holding
    holding.push_back(timestamps[i]);
  }
  
  //Final check
  if(holding.size() > 0){
    output.push_back(holding);
  }
  
  //Return
  return output;
  
}

std::list < std::vector < int > > sessionise::reconstruct_sessions(std::list < std::vector < int > > timestamps, int threshold){

  std::list < std::vector < int > > output;
  std::list < std::vector < int > >::const_iterator iterator;
  std::list < std::vector < int > > holding;
  for (iterator = timestamps.begin(); iterator != timestamps.end(); ++iterator) {
    holding = single_sessionise(*iterator, threshold);
    output.splice(output.end(), holding);
    holding.clear();
    Rcpp::checkUserInterrupt();
  }

  return output;

}

void single_session(IntegerVector timestamps, IntegerVector& delta_output,
                    int& ts_iter_count, int& threshold, std::deque <int>& hash_reps){
  
  int delta_holding;
  int hash_rep_holding = 1;
  delta_output[ts_iter_count] = NA_INTEGER;
  
  if(timestamps.size() >= 2) {
    std::sort(timestamps.begin(), timestamps.end());
    for(unsigned int i = 1; i < timestamps.size(); i++){
      ts_iter_count++;
      delta_holding = (timestamps[i] - timestamps[i-1]);
      if(delta_holding > threshold){
        delta_output[ts_iter_count] = NA_INTEGER;
        hash_reps.push_back(hash_rep_holding);
        hash_rep_holding = 1;
      } else {
        if(timestamps[i] == NA_INTEGER || timestamps[i-1] == NA_INTEGER){
          delta_output[ts_iter_count] = NA_INTEGER;
        } else {
          delta_output[ts_iter_count] = delta_holding;
        }
        hash_rep_holding++;
      }
    }
  }
  hash_reps.push_back(hash_rep_holding);
  ts_iter_count++;
}

//[[Rcpp::export]]
List sessionise_(List split_timestamps, int threshold, int out_nrow){
  
  IntegerVector delta_output(out_nrow);
  std::deque <int> hash_reps;
  int ts_iter_count = 0;
  
  for(unsigned int i = 0; i < split_timestamps.size(); i++){
    Rcpp::checkUserInterrupt();
    single_session(split_timestamps[i], delta_output,
                   ts_iter_count, threshold, hash_reps);
  }
  
  return List::create(Rcpp::Named("hash_reps") = hash_reps,
                      Rcpp::Named("delta") = delta_output);
  
}