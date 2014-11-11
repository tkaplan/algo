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
  const char* name;
  int32_t lastSale;
  uint32_t marketCap;
  const char* adrTso;
  uint32_t ipoYear;
  const char* sector;
  const char* industry;
  const char* summaryQuote;
};

class NetworkModule::CrawlTickers
{
  private:
    std::map<std::string, ticker*> tickers;
  public:
    CrawlTickers();
    ~CrawlTickers();
    std::map<std::string, ticker*> getTickers();
    int downloadTickers();
    int getTickersForLetter(std::shared_ptr<ostream>, std::string, char);
};