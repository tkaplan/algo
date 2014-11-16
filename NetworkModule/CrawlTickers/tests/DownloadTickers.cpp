#include <CrawlTickers.hpp>
#include <iostream>
#define BOOST_TEST_MODULE DownloadTickers
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE ( DownloadTickers )

BOOST_AUTO_TEST_CASE( tickers )
{
  NetworkModule::CrawlTickers* crawlTickers = new NetworkModule::CrawlTickers();
  int result = crawlTickers->downloadTickers();
  BOOST_REQUIRE(result == 0);
  auto tickers = crawlTickers->getTickers();
  std::string symbol;
  while(true)
  {
    try
    {
      std::cout << "Which ticker do you want to see?" << std::endl;
      std::cin >> symbol;
      auto ticker = tickers[symbol];
      std::cout << "Name: " << ticker->name << std::endl;
      std::cout << "Last Sale: " << ticker->lastSale << std::endl;
      std::cout << "Market Capital: " << ticker->marketCap << std::endl;
      std::cout << "Industry: " << ticker->industry << std::endl;
    }
    catch(const std::exception &e)
    {
      std::cout << "An exception" << std::endl;
    }

  }
}

BOOST_AUTO_TEST_SUITE_END()