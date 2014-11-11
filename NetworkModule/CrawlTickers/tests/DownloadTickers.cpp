#include <CrawlTickers.hpp>
#include <iostream>
#define BOOST_TEST_MODULE DownloadTickers
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE ( DownloadTickers )

BOOST_AUTO_TEST_CASE( get_all_tests )
{
  NetworkModule::CrawlTickers* crawlTickers = new NetworkModule::CrawlTickers();
  int result = crawlTickers->downloadTickers();
  BOOST_REQUIRE(result == 0);
  auto tickers = crawlTickers->getTickers();
  auto ticker = tickers["GAS"];
  std::cout << ticker->name << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()