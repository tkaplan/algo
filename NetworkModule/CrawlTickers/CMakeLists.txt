include_directories(.)

add_library(CrawlTickers SHARED CrawlTickers.cpp)

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

target_link_libraries(
  CrawlTickers
  cpprest
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

add_subdirectory(tests)