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

//'@title
//'session_length
//'
//'@description
//'Counts the length of each session within a set
//' 
//'@param sessions a list of sessions, extracted via \code{\link{sessionise}}
//'
//'@param padding_value the time to use for padding the session length, to accomodate the time spent idling
//'on the last event in the session or (in the case of one-event sessions) the only event in the session.
//'
//'@param preserve_single_events whether to attempt to calculate values for single page sessions (TRUE), or ignore
//'them and instead return the value -1 (FALSE). Set to FALSE by default.
//'
//'@param strip_last whether to strip the last event in a session (TRUE) or include it and attempt
//'to calculate the time spent on it via \code{padding_value}. Set to FALSE by default.
//'
//'@details
//'\code{session_length} takes a list of sessions (generated via \code{\link{sessionise}})
//'and calculates the approximate length (in seconds) of each session. See the "session metrics"
//'vignette for more details.
//'
//'\code{session_length} does not compute the length of sessions that consist of a single event,
//'unless \code{single_page_sessions} is set to true. Instead, it returns the numeric value -1
//'for those sessions.
//'
//'@return a vector of session length counts, in seconds, with -1 for sessions containing a single event
//'(or not. See the \code{single_page_sessions} parameter).
//' 
//'@seealso
//'\code{\link{sessionise}}, for generating sessions, \code{\link{session_events}} for
//'simply counting the number of events in each session, and \code{\link{bounce_rate}} for calculating
//'the bounce rate of the session set overall.
//'
//'@examples
//'\dontrun{
//'#With a sessionised dataset (see ?sessionise for an example)
//'lengths <- session_length(sessions = sessions, padding_value = 200, preserve_single_events = TRUE)
//'}
//'@export
// [[Rcpp::export]]
std::vector < int > session_length(std::list < std::vector < int > > sessions, int padding_value = 430,
                                   bool preserve_single_events = false, bool strip_last = false){
  std::vector < int > output = session_metrics::c_session_length(sessions, padding_value, preserve_single_events, strip_last);
  return output;
}

//'@title session_events
//'@description count the number of pages in a session (or set of sessions)
//'
//'@details \code{session_events} counts the number of events in a session, or in multiple
//'sessions, based on a provided "sessions" list (which can be generated via \code{\link{sessionise}})).
//'
//'@param sessions a list of sessions generated via \code{\link{sessionise}}
//'
//'@seealso \code{\link{sessionise}} for generating sessions, \code{\link{session_length}}
//'for session length, and \code{\link{bounce_rate}} for the bounce rate represented by a set
//'of sessions.
//'
//'@examples
//'\dontrun{
//'#With a sessionised dataset (see ?sessionise for an example)
//'event_counts <- session_events(sessions)
//'}
//'@export
// [[Rcpp::export]]
std::vector < int > session_events(std::list < std::vector < int > > sessions){
  std::vector < int > output = session_metrics::c_session_events(sessions);
  return output;
}