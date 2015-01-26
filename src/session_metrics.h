#include <Rcpp.h>
using namespace Rcpp;

#ifndef __METRICS_INCLUDED__
#define __METRICS_INCLUDED__

/**
 * A class of functions for taking reconstructed session
 * data and calculating common web analytics metrics,
 * such as time-on-page or session length.
 */
class session_metrics {
  
  private:
  
    /**
     * Calculates inter-time values between events in a session.
     * This is used to calculate time-on-page and session length.
     * 
     * @param session a vector of integers, representing a single
     * session, with each value being the (numeric) representation
     * of the event's timestamp.
     * 
     * @return a vector of integers, sized [input-1], containing
     * the inter-time values.
     */
    static std::vector < int > time_event_single(std::vector < int > session);
    
  public:
    
    /**
     * Calculates inter-time values between events in a series
     * of sessions; essentially a wrapper around time_event_single.
     * The result is equivalent to time-on-page - or, a best-guess
     * approximation, at least.
     * 
     * @param sessions a list of sessions, produced by
     * reconstruct_sessions.
     * 
     * @return a list of vectors of integers, each vector consisting of
     * the inter-time values for that session.
     */
    static std::list < std::vector < int > > c_time_event(std::list < std::vector < int > > sessions);
    
    /**
     * Calculates the length of each session within a series.
     * 
     * @param sessions a list of sessions, produced by
     * reconstruct_sessions.
     * 
     * @param padding_value a value to pad sessions with to
     * represent the time on the last page.
     * 
     * @param preserve_single_events whether to pad and return
     * single-event sessions, or return -1 as a representation
     * instead.
     * 
     * @Param strip_last whether to strip the final event in the session,
     * as an alternative to padding.
     * 
     * @return a vector of integers, representing the length of each
     * input session.
     */
    static std::vector < int > c_session_length(std::list < std::vector < int > > sessions, int padding_value,
                                                bool preserve_single_events, bool strip_last);
                                                
    /**
     * Calculates the number of events in each session within a series
     * 
     * @param sessions a list of sessions, produced by
     * reconstruct_sessions.
     * 
     * @return a vector of integers, representing the number of events
     * within each input session.
     */
    static std::vector < int > c_session_events(std::list < std::vector < int > > sessions);
    
};

#endif