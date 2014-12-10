#'@title bounce_rate
#'@description calculates the "bounce rate" within a set of sessions - the proportion of sessions
#'consisting only of a single event.
#'
#'@param sessions a list of sessions, generated with \code{\link{sessionise}}
#'
#'@param decimal_places the number of decimal places to round the output to - set to 2 by default.
#'
#'@return a single numeric value, representing the percentage of sessions that are bounces.
#'
#'@seealso \code{\link{session_events}} for generaliseable event-level calculations.
#'
#'@examples
#'#Calculate the bounce rate in the provided dataset.
#'#Load, convert timestamps to seconds, split
#'data("session_dataset")
#'session_dataset$timestamp <- to_seconds(x = session_dataset$timestamp, format = "%Y%m%d%H%M%S")
#'events_by_user <- split(session_dataset$timestamp, session_dataset$UUID)
#'
#'#Sessionise and calculate bounce rate
#'sessions <- sessionise(events_by_user)
#'bounce_rate(sessions)
#'#[1]58
#'@export
bounce_rate <- function(sessions, decimal_places = 2){
  events <- session_events(sessions)
  return(round((length(events[events == 1])/(length(events))), digits = decimal_places)*100)
}