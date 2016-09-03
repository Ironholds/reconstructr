bounce_rate_internal <- function(x, places){
  return(round(
    (
      length(x[!x %in% x[duplicated(x)]]) / length(x)
    ) * 100,
    digits = places
  ))
}

#'@title calculate the bounce rate within a session dataset
#'@description calculates the "bounce rate" within a set of sessions - the proportion of sessions
#'consisting only of a single event.
#'
#'@param sessions a sessions dataset, presumably generated with
#'\code{\link{sessionise}}.
#'
#'@param user_id a column that contains unique user IDs. NULL by default; if set, the assumption
#'will be that you want \emph{per-user} bounce rates.
#'
#'@param precision the number of decimal places to round the output to
#'- set to 2 by default.
#'
#'@return either a single numeric value, representing the percentage of sessions
#'\emph{overall} that are bounces, or a data.frame of user IDs and bounce rates if
#'\code{user_id} is set to a column rather than NULL.
#'
#'@seealso \code{\link{sessionise}} for session reconstruction, and
#'\code{\link{session_length}}, \code{\link{session_count}} and
#'\code{\link{time_on_page}} for other session-related metrics.
#'
#'@examples
#'#Load and sessionise the dataset
#'data("session_dataset")
#'sessions <- sessionise(session_dataset, timestamp, uuid)
#'
#'# Calculate overall bounce rate
#'rate <- bounce_rate(sessions)
#'
#'# Calculate bounce rate on a per-user basis
#'per_user <- bounce_rate(sessions, user_id = uuid)
#'
#'@export
bounce_rate <- function(sessions, user_id = NULL, precision = 2){
  
  user_id <- as.character(substitute(user_id))
  if(!length(user_id)){
    return(bounce_rate_internal(sessions$session_id, precision))
  }
  
  split_data <- split(x = sessions$session_id, f = sessions[,user_id])
  to_output <- lapply(split_data, bounce_rate_internal, places = precision)
  return(data.frame(user_id = names(to_output),
                    bounce_rate = unlist(to_output),
                    stringsAsFactors = FALSE))
}

#'@title Calculate time-on-page metrics
#'@description \code{time_on_page} generates metrics around the mean (or median)
#'time-on-page - on an overall, per-user, or per-session basis.
#'
#'@param sessions a sessions dataset, presumably generated with
#'\code{\link{sessionise}}.
#'
#'@param by_session Whether to generate time-on-page for the dataset overall (FALSE),
#'or on a per-session basis (TRUE). FALSE by default.
#'
#'@param precision the number of decimal places to round the output to
#'- set to 2 by default.
#'
#'@param median whether to generate the median (TRUE) or mean (FALSE)
#'time-on-page. FALSE by default.
#'
#'@return either a single numeric value, representing the mean/median time on page
#'for the overall dataset, or a data.frame of session IDs and numeric values if
#'\code{by_session} is TRUE.
#'
#'@seealso \code{\link{sessionise}} for session reconstruction, and
#'\code{\link{session_length}}, \code{\link{session_count}} and
#'\code{\link{bounce_rate}} for other session-related metrics.
#'
#'@examples
#'#Load and sessionise the dataset
#'data("session_dataset")
#'sessions <- sessionise(session_dataset, timestamp, uuid)
#'
#'# Calculate overall time on page
#'top <- time_on_page(sessions)
#'
#'# Calculate time-on-page on a per_session basis
#'per_session <- time_on_page(sessions, by_session = TRUE)
#'
#'# Use median instead of mean
#'top_med <- time_on_page(sessions, median = TRUE)
#'
#'@importFrom stats median aggregate
#'@export
time_on_page <- function(sessions, by_session = FALSE, median = FALSE,
                         precision = 2){
  
  if(median){
    func <- stats::median
  } else {
    func <- mean
  }
  
  if(!by_session){
    return(round(func(sessions$time_delta, na.rm = TRUE), digits = precision))
  }
  
  output <- stats::aggregate(formula = time_delta ~ session_id, data = sessions,
                             FUN = func, na.action = NULL, na.rm = TRUE)
  output$time_delta <- round(output$time_delta, digits = precision)
  names(output)[names(output) == "time_delta"] <- "time_on_page"
  return(output)
}

#'@title Calculate session length
#'@description Calculate the overall length of each session.
#'
#'@param sessions a dataset of sessions, presumably generated with
#'\code{\link{sessionise}}.
#'
#'@return a data.frame of two columns - \code{session_id}, containing unique
#'session IDs, and \code{session_length}, containing the length (in seconds)
#'of that particular session.
#'
#'Please note that these lengths should be considered a \emph{minimum};
#'because of how sessions behave, calculating the time-on-page of the last
#'event in a session is impossible.
#'
#'@seealso \code{\link{sessionise}} for session reconstruction, and
#'\code{\link{time_on_page}}, \code{\link{session_count}} and
#'\code{\link{bounce_rate}} for other session-related metrics.
#'
#'@examples
#'#Load and sessionise the dataset
#'data("session_dataset")
#'sessions <- sessionise(session_dataset, timestamp, uuid)
#'
#'# Calculate session length
#'len <- session_length(sessions)
#'
#'@export
session_length <- function(sessions){
  
  output <- stats::aggregate(formula = time_delta ~ session_id, data = sessions,
                             FUN = sum, na.action = NULL, na.rm = TRUE)
  names(output)[names(output) == "time_delta"] <- "session_length"
  return(output)
}

session_count_internal <- function(x){
  return(length(unique(x)))
}

#' @title Count the number of sessions in a sessionised dataset
#' @description \code{link{session_count}} counts the number of sessions in a sessionised
#' dataset, producing either a count for the overall dataset or on a per-user
#' basis (see below).
#' 
#' @param sessions a dataset of sessions, presumably generated by
#' \code{\link{sessionise}}
#' 
#' @param user_id the column of \code{sessions} containing user IDs. If
#' NULL (the default), a single count of sessions for the entire dataset
#' will be generated. Otherwise, a data.frame of user IDs and the session
#' count for each user ID will be returned.
#' 
#' @return either a single integer value or a data.frame (see above).
#' 
#' @examples
#' #Load and sessionise the dataset
#' data("session_dataset")
#' sessions <- sessionise(session_dataset, timestamp, uuid)
#' 
#' # Calculate overall bounce rate
#' count <- session_count(sessions)
#' 
#' # Calculate session count on a per-user basis
#' per_user <- session_count(sessions, user_id = uuid)
#' 
#' @export
session_count <- function(sessions, user_id = NULL){
  
  user_id <- as.character(substitute(user_id))
  if(!length(user_id)){
    return(session_count_internal(sessions$session_id))
  }
  
  split_data <- split(x = sessions$session_id, f = sessions[,user_id])
  to_output <- lapply(split_data, session_count_internal)
  return(data.frame(user_id = names(to_output),
                    session_count = unlist(to_output),
                    stringsAsFactors = FALSE))
}