context("to_seconds")

test_that("to_seconds handles non-POSIX formats", {
  expect_that(to_seconds("20140107000015","%Y%m%d%H%M%S"), equals(1389070815))
})

test_that("to_seconds handles POSIXlt timestamps", {
  expect_that(to_seconds(as.POSIXlt("2014-12-06 18:49:21 EST")), equals(1417909761))
})

test_that("to_seconds handles POSIXlt timestamps", {
  expect_that(to_seconds(as.POSIXct("2014-12-06 18:49:21 EST")), equals(1417909761))
})