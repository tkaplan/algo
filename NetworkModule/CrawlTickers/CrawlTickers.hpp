#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

namespace NetworkModule
{
  struct ticker;
  class CrawlTickers;
}

struct NetworkModule::ticker{
  std::string symbol;
  int32_t lastSale, marketCap, ipoYear;
  const char* adrTso, sector, industry, summaryQuote, name;
};

class NetworkModule::CrawlTickers
{
  public:
    explicit CrawlTickers();
    int downloadTickers();
    int getTickersForLetter(std::ostream&, const std::string&, const char&);
    
    std::map<std::string, ticker> tickers;
};