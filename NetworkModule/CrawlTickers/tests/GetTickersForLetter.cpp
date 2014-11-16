#include <CrawlTickers.hpp>
#define BOOST_TEST_MODULE GetTickersForLetter
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams


using namespace NetworkModule;

BOOST_AUTO_TEST_SUITE ( GetTickersForLetter )

BOOST_AUTO_TEST_CASE( test )
{
  CrawlTickers* crawlTickers = new CrawlTickers();
  int result;
  char letter = 'A';
  result = crawlTickers->getTickersForLetter(letter);
  BOOST_REQUIRE(result == 0);
}

BOOST_AUTO_TEST_SUITE_END()