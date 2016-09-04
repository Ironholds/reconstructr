#'@title Reconstruct sessions (experimental)
#'
#'@description \code{sessionise} takes a data.frame of events
#'(including timestamps and user IDs) and sessionises them,
#'returning the same data.frame but with two additional columns -
#'one containing a unique session ID, and one the time difference between
#'successive events in the same session.
#'
#'@param x a data.frame of events.
#'
#'@param timestamp the name of the column of \code{x} containing timestamps,
#'which should be (either) a representation of the number of seconds, or a
#'POSIXct or POSIXlt date/time object. If it is neither, \code{\link{strptime}}
#'can be used to convert most representations of date-times into POSIX formats.
#'
#'@param user_id the name of the column of \code{x} containing unique user IDs.
#'
#'@param threshold the number of seconds to use as the intertime threshold -
#'the time that can elapse between two events before the second is considered
#'part of a new session. Set to 3600 (one hour) by default.
#'
#'@return \code{x}, ordered by userID and timestamp, with two new columns -
#'\code{session_id} (containing a unique ID for the session a row is in)
#'and \code{delta} (containing the time elapsed between that row's event,
#'and the previous event, if they were both in the same session).
#'
#'@seealso
#'\code{\link{bounce_rate}}, \code{\link{time_on_page}},
#'\code{\link{session_length}} and \code{\link{session_count}} - common metrics
#'that can be calculated with a sessionised dataset.
#'
#'@examples
#'# Take a dataset with URLs and similar metadata and sessionise it -
#'# retaining that metadata
#'
#'data("session_dataset")
#'sessionised_data <- sessionise(x = session_dataset,
#'                               timestamp = timestamp,
#'                               user_id = uuid,
#'                               threshold = 1800)
#'
#'@importFrom openssl md5
#'@importFrom stats rnorm
#'@export
sessionise <- function(x, timestamp, user_id, threshold = 3600){
  
  timestamp <- as.character(substitute(timestamp))
  user_id <- as.character(substitute(user_id))
  
  if(!is.numeric(x[,timestamp])){
    if("POSIXt" %in% class(x[,timestamp])){
      ts <- as.numeric(x[,timestamp])
      to_sessionise <- split(x = ts, f = x[, user_id], drop = TRUE)
    } else {
      stop("The timestamp column must be a numeric representation of the number
           of seconds, or a date/time object. See ?sessionise for details")
    }
  } else {
    to_sessionise <- split(x = x[, timestamp], f = x[, user_id], drop = TRUE)
  }
  
  eval(reconstructr_env$order_expr)
  holding <- sessionise_(split_timestamps = to_sessionise,
                         threshold = threshold,
                         out_nrow = nrow(x))
  
  # Look into hooking into this on the compiled code side maybe?
  hashes <- as.character(openssl::md5(x = as.character(seq_len(length(holding$hash_reps))),
                                      key = as.character(stats::rnorm(1))))
  return(cbind(x,
               data.frame(session_id = rep(x = hashes, holding$hash_reps),
                          time_delta = holding$delta,
                          stringsAsFactors = FALSE)))
}