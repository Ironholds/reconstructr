#' @title Example event dataset
#' 
#' @description an example dataset of events, for experimenting with
#' session reconstruction and analysis
#'
#' @format a data.frame of 63,524 rows consisting of:
#' \describe{
#'   \item{uuid}{Hashed and salted unique identifiers representing 10,000 unique clients.}
#'   \item{timestamp}{timestamps, as POSIXct objects}
#'   \item{url}{URLs, to demonstrate the carrying-along of metadata through the sessionisation
#'   process}
#' }
#' 
#' @source The \code{uuid} and \code{timestamp} columns come from an anonymised dataset of
#' Wikipedia readers; the URLs are from NASA's internal web server, because space is awesome.
#' 
#' @name session_dataset
"session_dataset"