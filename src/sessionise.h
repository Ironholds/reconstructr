#include <Rcpp.h>
using namespace Rcpp;

#ifndef __SESSIONISE_INCLUDED__
#define __SESSIONISE_INCLUDED__

/**
 * A class of functions for session generation, through
 * tokenizing event streams into sessions.
 */
class sessionise {
  private:
    /**
     * A function for reconstructing a single stream of events.
     * Called by reconstruct_sessions over each input vector.
     * 
     * @param timestamps a vector of the numeric values of
     * a set of timestamps
     * 
     * @param threshold an integer representing the threshold -
     * when the gap between timestamps is greater than the
     * threshold, a new session is created.
     * 
     * @return a list of vectors of timestamps, each vector
     * representing one session.
     */
    static std::list < std::vector < int > > single_sessionise(std::vector < int > timestamps, int threshold);
    
  public:
    /**
     * A function for reconstructing a multiple stream of events.
     * 
     * @param timestamps a list of vectors, each vector containing
     * the numeric representation of event-associated timestamps for
     * one user/ID.
     * 
     * @param threshold an integer representing the threshold -
     * when the gap between timestamps is greater than the
     * threshold, a new session is created.
     * 
     * @return a list of vectors of timestamps, each vector
     * representing one session.
     */
    std::list < std::vector < int > > reconstruct_sessions(std::list < std::vector < int > > timestamps, int threshold);
};

#endif