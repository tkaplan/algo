#include <CrawlTickers.hpp>
#define BOOST_TEST_MODULE DownloadTickers
#include <boost/test/unit_test.hpp>

using namespace NetworkModule;

BOOST_AUTO_TEST_CASE( DownloadTickers )
{
  CrawlTickers* crawlTickers = new CrawlTickers();
  int result;
  std::string file = "ticker";
  char letter = 'A';
  file += letter;
  file += ".csv";
  result = crawlTickers->getTickersForLetter(fileStream, file, letter);
  BOOST_REQUIRE(result == 0);
}