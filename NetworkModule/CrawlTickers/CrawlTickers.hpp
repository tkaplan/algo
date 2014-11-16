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

// Prices will be calculated using integers
// and accuracy will be to 4 orders of magnitude
struct NetworkModule::ticker{
  std::string symbol;
  std::string name;
  std::string sector;
  std::string industry;
  std::string summaryQuote;
  std::string adrTso;
  uint32_t lastSale;
  unsigned long marketCap;
  uint32_t ipoYear;
};

class NetworkModule::CrawlTickers
{
  private:
    std::map<std::string, struct ticker*> tickers;
    void buildTicker(stringstreambuf*);
    void setTickerProp(int, struct ticker*, std::string);
  public:
    CrawlTickers();
    ~CrawlTickers();
    std::map<std::string, ticker*> getTickers();
    int downloadTickers();
    int getTickersForLetter(char);
};