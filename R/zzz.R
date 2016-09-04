reconstructr_env <- new.env(parent = emptyenv())

# This makes me feel like a bad person. Basically, radix is the fastest, but also
# horribly unstable and unusable for these purposes below 3.3.0. So we check what
# the version is, and then...oy.
.onLoad <- function(...) {
  
  minor <- as.numeric(version$minor)
  major <- as.numeric(version$major)
  
  if(major < 3 || minor < 3.0){
    expr <- expression(x <- x[order(x[,user_id], x[,timestamp], method = "shell"),])
  } else {
    expr <- expression(x <- x[order(x[,user_id], x[,timestamp], method = "radix"),])
  }
  
  assign("order_expr", expr, envir = reconstructr_env)
}