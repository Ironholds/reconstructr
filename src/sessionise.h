#include <Rcpp.h>
using namespace Rcpp;

class sessionise {
  
  private:
  
    //Code necessary to turn a single set of entries into sessions.
    static std::list < std::vector < int > > single_sessionise(std::vector < int > timestamps, int threshold){
    
    //Generate size, output object, holding objects
    int input_size = timestamps.size();
    std::list < std::vector < int > > output;
    int intertime_hold;
    std::vector < int > holding;
    
    //Push the first timestamp on to the holding vector
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
    
  public:
  
    //Public function for actually turning a list of numeric representations of timestamps
    //into a session.
    static std::list < std::vector < int > > c_sessionise(std::list < std::vector < int > > timestamps, int threshold){
    
      //Create output object, holding object, iterator
      std::list < std::vector < int > > output;
      std::list < std::vector < int > >::const_iterator iterator;
      std::list < std::vector < int > > holding;
      
      //For each list entry, take the timestamps and pass them into single_sessionise to,
      //well, sessionise them. The results then get spliced on to output, and the holding object
      //cleared for the next run.
      for (iterator = timestamps.begin(); iterator != timestamps.end(); ++iterator) {
        holding = single_sessionise(*iterator, threshold);
        output.splice(output.end(), holding);
        holding.clear();
      }
            
      //Return
      return(output);
    
    }
};