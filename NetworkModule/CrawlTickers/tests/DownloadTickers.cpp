#include <CrawlTickers.hpp>
#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>

//using namespace NetworkModule;

BOOST_AUTO_TEST_CASE( my_test )
{
  NetworkModule::CrawlTickers* crawlTickers = new NetworkModule::CrawlTickers();
  int result = crawlTickers->downloadTickers();
  BOOST_REQUIRE(result == 0);
}