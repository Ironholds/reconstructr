% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/metrics.R
\name{bounce_rate}
\alias{bounce_rate}
\title{calculate the bounce rate within a session dataset}
\usage{
bounce_rate(sessions, user_id = NULL, precision = 2)
}
\arguments{
\item{sessions}{a sessions dataset, presumably generated with
\code{\link{sessionise}}.}

\item{user_id}{a column that contains unique user IDs. NULL by default; if set, the assumption
will be that you want \emph{per-user} bounce rates.}

\item{precision}{the number of decimal places to round the output to
- set to 2 by default.}
}
\value{
either a single numeric value, representing the percentage of sessions
\emph{overall} that are bounces, or a data.frame of user IDs and bounce rates if
\code{user_id} is set to a column rather than NULL.
}
\description{
Calculates the "bounce rate" within a set of sessions - the proportion of sessions
consisting only of a single event.
}
\examples{
#Load and sessionise the dataset
data("session_dataset")
sessions <- sessionise(session_dataset, timestamp, uuid)

# Calculate overall bounce rate
rate <- bounce_rate(sessions)

# Calculate bounce rate on a per-user basis
per_user <- bounce_rate(sessions, user_id = uuid)

}
\seealso{
\code{\link{sessionise}} for session reconstruction, and
\code{\link{session_length}}, \code{\link{session_count}} and
\code{\link{time_on_page}} for other session-related metrics.
}
