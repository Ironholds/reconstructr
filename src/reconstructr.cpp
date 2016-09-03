#include <Rcpp.h>
using namespace Rcpp;

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