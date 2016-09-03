context("sessionisation")

test_that("sessionisation works", {
  
  data("session_dataset")
  sessionised_data <<- sessionise(x = session_dataset,
                                 timestamp = timestamp,
                                 user_id = uuid,
                                 threshold = 1800)
  
  testthat::expect_equal(nrow(session_dataset), nrow(sessionised_data))
  testthat::expect_equal(ncol(sessionised_data), 5)
  testthat::expect_equal(union(names(session_dataset), c("session_id", "time_delta")),
                         names(sessionised_data))
  
})

test_that("Bounce rates can be computed", {
  rate <- bounce_rate(sessionised_data)
  user_rate <- bounce_rate(sessionised_data, user_id = uuid)
  
  testthat::expect_true(is.numeric(rate))
  testthat::expect_equal(rate, 20.68)
  
  testthat::expect_true(is.data.frame(user_rate))
  testthat::expect_equal(nrow(user_rate), 10000)
  testthat::expect_equal(names(user_rate), c("user_id", "bounce_rate"))
})

test_that("Time on page can be computed", {
  
  top <- time_on_page(sessionised_data)
  by_session <- time_on_page(sessionised_data, by_session = TRUE)
})