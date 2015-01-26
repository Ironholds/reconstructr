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
  }
  return output;

}