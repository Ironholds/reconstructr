#' @title Example event dataset
#' 
#' @description an example dataset of events, drawn from the Wikimedia web properties, for experimenting with
#' when performing session reconstruction and analysis
#'
#' @format a data.frame of 63,524 rows consisting of:
#' \describe{
#'   \item{UUID}{Hashed and salted unique identifiers representing 10,000 unique clients.}
#'   \item{timestamp}{timestamps, pre-converted using \code{\link{to_seconds}} to be immediately usable by \code{\link{sessioniser}}}
#' }
#' @name session_dataset
NULL