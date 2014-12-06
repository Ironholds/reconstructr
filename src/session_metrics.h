#include <Rcpp.h>
using namespace Rcpp;

class session_metrics{

  public:
    
    //Calculate the length of a session
    static std::vector < int > c_session_length(std::list < std::vector < int > > sessions, int padding_value,
                                                bool preserve_single_events, bool strip_last);
                                                
    //Calculate the number of sessions in a dataset
    static std::vector < int > c_session_events(std::list < std::vector < int > > sessions);
    
};

//Calculate the length of a session
std::vector < int > session_metrics::c_session_length(std::list < std::vector < int > > sessions,
                                                      int padding_value, bool preserve_single_events,
                                                      bool strip_last){
  
  //Declare output object, holding objects, iterator.
  std::list < std::vector < int > >::const_iterator iterator;
  std::vector < int > output;
  std::vector < int > holding;
  int sum_holding;
  int in_size = holding.size();
  
  //For each list entry...
  for (iterator = sessions.begin(); iterator != sessions.end(); ++iterator) {
    
    //Extract
    holding = *iterator;
    
    //If there's only one page, return -1
    if(in_size < 2){
      
      //Unless the user wants single-event sessions preserved, and strip_last is FALSE
      if(preserve_single_events & !strip_last){
        output.push_back(padding_value);
      } else {
        output.push_back(-1);
      }

    } else {
      
      //If we want to strip_last, just resize in_size
      if(strip_last){
        in_size -= 1;
      }
      
      //Work out the intertimes and add them, plus the padding value
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