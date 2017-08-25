## Session reconstruction and analysis in R

__Author:__ Oliver Keyes<br/>
__License:__ [MIT](http://opensource.org/licenses/MIT)<br/>
__Status:__ Stable

[![Travis-CI Build Status](https://travis-ci.org/Ironholds/reconstructr.svg?branch=master)](https://travis-ci.org/Ironholds/reconstructr) [![CRAN_Status_Badge](http://www.r-pkg.org/badges/version/reconstructr)](https://cran.r-project.org/package=reconstructr) ![downloads](http://cranlogs.r-pkg.org/badges/grand-total/reconstructr)

### Description

A well-studied part of web analytics and human-computer interaction is
the concept of a "session": a series of linked user actions. This is used
for anything from evaluating the impact of design or engineering changes
on users, to providing common, high-level metrics such as time-on-page
or bounce rate.

<code>reconstructr</code> is a library designed to efficiently reconstruct
sessions from a series of user events, and then generate common metrics
from that session-based data, including bounce rate, session length and time-on-page.
It features heavy internal use of C++ to make it lightning-fast over datasets
containing millions or tens of millions of events, along with a wide range of options
with each function, allowing you to heavily customise what data is produced and
what data is evaluated. For more information, see the
[introductory vignette](https://github.com/Ironholds/reconstructr/blob/master/vignettes/Introduction.Rmd).

The package  is under active development: if you find bugs or have suggestions
for new features, please feel free to [report them](https://github.com/Ironholds/reconstructr/issues).

### Usage

So you've got a session dataset, which we'll call, well, `session_dataset`. It looks like this:

```
library(reconstructr)
data("session_dataset")
str(session_dataset)

# 'data.frame':	63524 obs. of  3 variables:
#  $ uuid     : chr  "47dc43895814861e21a2edf93348c826" "a736822df1890011694e7049cb3abef3" "674d2d00e096a3319874a4347caa1f4a" "f62d315398e6d04a3f2fa02e8ae42d49" ...
#  $ timestamp: POSIXlt, format: "2014-01-07 00:00:15" "2014-01-07 00:01:11" "2014-01-07 00:01:54" ...
#  $ url      : chr  "https://www.nasa.gov/history/mercury/mercury.html" "https://www.nasa.gov/images/ksclogosmall.gif" "https://www.nasa.gov/elv/hot.gif" "https://www.nasa.gov/facts/faq04.html" ...
```

You have timestamps, you have UUIDs for each user, and you have the URL (or any other metadata you might need!). What you really want to do is divide the data up into 'sessions' - distinguishable blocks of browsing activity by a single user. For this we use `sessionise`, passing it the dataset, the column names for timestamps and user IDs, and a threshold - the number of seconds after which to decide a user has entered a new session. By default this is 3600 (1 hour):

```
sessionised_data <- sessionise(session_dataset, "timestamp", "uuid")

str(sessionised_data)
# 'data.frame':	63524 obs. of  5 variables:
#  $ uuid      : chr  "0005839b3e8483d50870f61f50307fa7" "000b047bad36484451f12c114ab5eb28" "000b047bad36484451f12c114ab5eb28" "000b047bad36484451f12c114ab5eb28" ...
#  $ timestamp : POSIXlt, format: "2014-01-14 12:47:59" "2014-01-07 14:25:11" "2014-01-09 12:47:17" ...
#  $ url       : chr  "https://www.nasa.gov/history/apollo/images/footprint-logo.gif" "https://www.nasa.gov/ksc.html" "https://www.nasa.gov/biomed/threat/gif/beachmousefinsmall.gif" "https://www.nasa.gov/shuttle/resources/orbiters/atlantis.html" ...
#  $ session_id: chr  "9c77ea18bbef377253be1b22957071c1" "eda2ec544d96f0f1e3271902cbb693b7" "ee6d08bdaf1fb3c28edd0ac3290b82f5" "ee6d08bdaf1fb3c28edd0ac3290b82f5" ...
#  $ time_delta: int  NA NA NA 45 4 75 274 47 NA 28 ...
```

This adds two new columns - a unique ID for each session, and (for each event) the time elapsed between that event and the next one in a session.

From this we can calculate a lot of commmon session-related metrics:

```
# Number of sessions per user
sess_count <- session_count(sessionised_data, "uuid")
str(sess_count)

# 'data.frame':	10000 obs. of  2 variables:
#  $ user_id      : chr  "0005839b3e8483d50870f61f50307fa7" "000b047bad36484451f12c114ab5eb28" "000b2bc1a5438d8d54d4fbec139a2fd5" "001b6e80a14ba8d809c4ff18cdbade40" ...
#  $ session_count: int  1 2 1 1 1 6 1 1 1 1 ...

# Length of each session
sess_length <- session_length(sessionised_data)
str(sess_length)

# 'data.frame':	20820 obs. of  2 variables:
#  $ session_id    : chr  "0000664732878ba3409c138d4870a42d" "00029b1cd83040b8e14d7d65e057029e" "0002e5a2e75610bfb6c0598ea228a9d1" "00097364d131b6d6580d3c69a3e0a868" ...
#  $ session_length: int  0 62 101 0 83 7 3113 0 4071 0 ...

# The 'bounce rate' (overall or per user!)

sess_bounce <- bounce_rate(sessionised_data)
str(sess_bounce)
# num 18.9

sess_bounce <- bounce_rate(sessionised_data, "uuid")
str(sess_bounce)
# 'data.frame':	10000 obs. of  2 variables:
#  $ user_id    : chr  "0005839b3e8483d50870f61f50307fa7" "000b047bad36484451f12c114ab5eb28" "000b2bc1a5438d8d54d4fbec139a2fd5" "001b6e80a14ba8d809c4ff18cdbade40" ...
#  $ bounce_rate: num  100 14.3 0 100 100 ...

# And many others
```

### Installation

For the current release version:

    install.packages("reconstructr")
    
For the development version:

    library(devtools)
    install_github("ironholds/reconstructr")
    
### Dependencies
* R. Doy.
* [Rcpp](https://cran.r-project.org/package=Rcpp)

