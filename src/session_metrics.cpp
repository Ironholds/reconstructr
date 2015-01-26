#include "session_metrics.h"

std::vector < int > session_metrics::time_event_single(std::vector < int > session){
  
  //Declare output object
  std::vector < int > output;
  int in_size = session.size();
  
  //If there's only one entry, report as such - otherwise, sort, calculate each intertime and add
  //on to a vector.
  if(in_size < 2){
    output.push_back(-1);
  } else {
    std::sort(session.begin(),session.end());
    for(int i = 1; i < in_size; i++) {
      output.push_back(session[i] - session[i-1]);
    }
  }
  
  //Return
  return output;
  
}


//Calculate the time on each event
std::list < std::vector < int > > session_metrics::c_time_event(std::list < std::vector < int > > sessions){
  
  //Declare output object, holding objects, iterator.
  std::list < std::vector < int > >::const_iterator iterator;
  std::list < std::vector < int > > output;
  std::vector < int > holding;
  
  //For each list entry, extract, identify intertimes and add
  for(iterator = sessions.begin(); iterator != sessions.end(); ++iterator) {
    holding = *iterator;
    output.push_back(session_metrics::time_event_single(holding));
  }
  
  //Return
  return output;
}
    
//Calculate the length of a session
std::vector < int > session_metrics::c_session_length(std::list < std::vector < int > > sessions,
                                                      int padding_value, bool preserve_single_events,
                                                      bool strip_last){
  
  //Declare output object, holding objects, iterator.
  std::list < std::vector < int > >::const_iterator iterator;
  std::vector < int > output;
  std::vector < int > holding;
  int sum_holding = 0;
  
  //For each list entry...
  for (iterator = sessions.begin(); iterator != sessions.end(); ++iterator) {
    
    //Extract
    holding = *iterator;
    int in_size = holding.size();
    
    //If strip_last is true, reduce in_size
    if(strip_last){
      in_size -= 1;
    }
    
    //If there's only one page, after this, return -1 - unless preserve_single_events is true.
    if(in_size < 2){
      
      if(!preserve_single_events){
        output.push_back(-1);
      } else {
        output.push_back(padding_value);
      }
      
    //Otherwise...
    } else {
      
      //sort, work out the intertimes, and add them (plus the padding value)
      std::sort(holding.begin(),holding.end());
      for(int i = 1; i < in_size; i++) {
        sum_holding += (holding[i] - holding[i-1]);
      }
      sum_holding += padding_value;
      output.push_back(sum_holding);
      sum_holding = 0;

    }
  }
  
  return output;
}

//Count the number of events in each session
std::vector < int > session_metrics::c_session_events(std::list < std::vector < int > > sessions) {
  
  //Holding and output objects
  std::vector < int > output;
  std::vector < int > holding;
  std::list < std::vector < int > >::const_iterator iterator;
  
  for (iterator = sessions.begin(); iterator != sessions.end(); ++iterator) {
    
    holding = *iterator;
    output.push_back(holding.size());
  }
  
  return output;
}