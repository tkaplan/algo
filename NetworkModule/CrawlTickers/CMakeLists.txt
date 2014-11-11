include_directories(.)

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

add_library(CrawlTickers SHARED CrawlTickers.cpp)

target_link_libraries(
  CrawlTickers
  cpprest
)

add_subdirectory(tests)