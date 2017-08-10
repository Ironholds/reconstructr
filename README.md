## Session reconstruction and analysis in R

__Author:__ Oliver Keyes<br/>
__License:__ [MIT](http://opensource.org/licenses/MIT)<br/>
__Status:__ Stable

![downloads](http://cranlogs.r-pkg.org/badges/grand-total/reconstructr)

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

### Installation

For the current release version:

    install.packages("reconstructr")
    
For the development version:

    library(devtools)
    install_github("ironholds/reconstructr")
    
### Dependencies
* R. Doy.
* [Rcpp](https://cran.r-project.org/package=Rcpp)

