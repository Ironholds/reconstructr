#include <Rcpp.h>
#include "sessionise.h"
#include "session_metrics.h"
using namespace Rcpp;

//'@title
//'sessionise
//'
//'@description
//'split a series of timestamps (or a series of series) associated with UUIDs, into sessions
//'
//'@details
//'\code{sessionise} splits timestamps associated with user events into "sessions",
//'enabling the simple calculation of various metrics such as session length or the number of events
//'within a session.
//'
//'@param timestamps a list of vectors of second values. These can be extracted by converting
//'POSIXlt or POSIXct timestamps into numeric elements through a call to \code{\link{as.numeric}},
//'or with the assistance of \code{\link{to_seconds}}.
//'
//'@param threshold the threshold, in seconds, for splitting out a new session. Set to 
//'3600 (one hour) by default.
//'
//'@return a list of vectors, each one representing a single session.
//'The returned list can be conveniently
//'passed into \code{\link{session_length}} or \code{\link{session_events}} for further analysis.
//'
//'@seealso \code{\link{session_length}} for calculating session length, \code{\link{bounce_rate}} for
//'calculating the bounce rate, and \code{\link{session_events}} for calculating the number of events in each session.
//'
//'@examples
//'#Take the inbuilt dataset and sessionise it
//'data("session_dataset")
//'session_dataset$timestamp <- to_seconds(x = session_dataset$timestamp, format = "%Y%m%d%H%M%S")
//'events_by_user <- split(session_dataset$timestamp, session_dataset$UUID)
//'sessions <- sessionise(events_by_user)
//'@export
// [[Rcpp::export]]
std::list < std::vector < int > > sessionise(std::list < std::vector < int > > timestamps, int threshold = 3600) {
   std::list < std::vector < int > > output = sessionise::c_sessionise(timestamps, threshold);
   return output;
}

//'@export
// [[Rcpp::export]]
std::vector < int > session_length(std::list < std::vector < int > > sessions, int padding_value = 430,
                                   bool preserve_single_events = false, bool strip_last = false){
  std::vector < int > output = session_metrics::c_session_length(sessions, padding_value, preserve_single_events, strip_last);
  return output;
}

//'@export
// [[Rcpp::export]]
std::vector < int > session_events(std::list < std::vector < int > > sessions){
  std::vector < int > output = session_metrics::c_session_events(sessions);
  return output;
}