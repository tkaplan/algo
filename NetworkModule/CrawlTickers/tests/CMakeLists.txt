add_executable( DownloadTickers DownloadTickers.cpp )

add_executable( GetTickersForLetter GetTickersForLetter.cpp )

include_directories( .. )

find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

target_link_libraries(
  DownloadTickers
  CrawlTickers
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

target_link_libraries(
  GetTickersForLetter
  CrawlTickers
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)