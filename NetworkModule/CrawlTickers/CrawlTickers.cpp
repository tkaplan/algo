#include <stack>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/astreambuf.h>
#include <boost/tokenizer.hpp>
#include <CrawlTickers.hpp>

#define UINT32_TOK(prop) \
tickerPtr->prop = (uint32_t)(10000*std::stof(tok))

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

typedef boost::tokenizer< boost::char_separator<char>> tokenizer;

namespace NetworkModule
{ 
  
  void CrawlTickers::setTickerProp(int col, struct ticker* tickerPtr, std::string tok)
  {
    int prop = col % 18;
    switch(prop)
    {
      case 0:
        tickerPtr->symbol = tok;
        break;
      case 2:
        tickerPtr->name = tok;
        break;
      case 4:
        tickerPtr->lastSale = (uint32_t)(10000*std::stof(tok));
        break;
      case 6:
        std::cout << tickerPtr->symbol << " | " << tok << std::endl;
        tickerPtr->marketCap = (unsigned long)(100*std::stod(tok));
        std::cout << tickerPtr->symbol << " | " << tickerPtr->marketCap << std::endl;
        break;
      case 8:
        tickerPtr->adrTso = tok;
        break;
      case 10:
        tickerPtr->ipoYear = (uint32_t)(std::stoi(tok));
        break;
      case 12:
        tickerPtr->sector = tok;
        break;
      case 14:
        tickerPtr->industry = tok;
        break;
      case 16:
        tickerPtr->summaryQuote = tok;
        break;
    }
  }

  void CrawlTickers::buildTicker(stringstreambuf* ss)
  {
    boost::char_separator<char> sep("\"");
    // We need a pointer to keep track of our heap struct
    struct ticker* tickerPtr;

    // Tokenize columns
    tokenizer tokens(ss->collection(), sep);
    tickerPtr = new ticker;
    int col = 0;
    for( tokenizer::iterator tokPtr = tokens.begin(); tokPtr != tokens.end(); ++tokPtr)
    {
      // Extract raw string
      std::string tok = *tokPtr;

      try
      {
        setTickerProp(col, tickerPtr, tok);
      }
      catch(const std::exception &e)
      {
        // The property 2 stands for last sale
        // If there is no last sale, then we're
        // not interested in the data
        if(col % 18 == 4)
        {
          std::cout << ss->collection() << std::endl;
          std::cout << "Throwing ticker away: " << tickerPtr->symbol << std::endl;
          delete tickerPtr;
          return;
        }
      }
      col++;
    }
    // Add our ticker to our heap object
    this->tickers[tickerPtr->symbol]= tickerPtr;
    
    // Free up our stream buffer
    delete ss;
  }

  CrawlTickers::CrawlTickers()
  {

  }

  CrawlTickers::~CrawlTickers()
  {
    // Might need to iterate through
    // tickers map.
    for (auto& kv : this->tickers) {
      std::cout << kv.first << " has value " << kv.second << std::endl;
      delete kv.second;
    }
  }

  /* Return a pointer to our ticker map */
  std::map<std::string, ticker*> CrawlTickers::getTickers ()
  {
    return this->tickers;
  }

  /*  Return values are http returns */
  int CrawlTickers::downloadTickers()
  {
    for(char letter = 'A'; letter <= 'Z'; letter ++)
    {
      getTickersForLetter(letter);
    }

    return 0;
  }

  int CrawlTickers::getTickersForLetter(char letter)
  {
    // Create http_client to send the request.
    http_client client(U("http://www.nasdaq.com/screening/"));

    // Build request URI and start the request.
    uri_builder builder(U("/companies-by-name.aspx"));
    
    // Create query
    builder.append_query(U("letter"), U(letter));
    builder.append_query(U("render"), U("download"));

    pplx::task<void> requestTask = client.request(methods::GET, builder.to_string())
    .then([&](http_response response)
    {
      printf("Received response status code:%u\n", response.status_code());
      auto iStream = response.body();
      stringstreambuf firstLine;
      iStream.read_to_delim(firstLine, '\n').wait();
      while( !iStream.is_eof() )
      {
        stringstreambuf * ss = new stringstreambuf;
        // Read line
        auto task = iStream.read_to_delim(*ss, '\n').then(
          [=] (size_t w)
          {
            buildTicker(ss);
          }
        ).wait();
      }
      return response.body().close();
    });

    // Wait for all the outstanding I/O to complete and handle any exceptions
    try
    {
      requestTask.wait();
    }
    catch (const std::exception &e)
    {
      printf("Error exception:%s\n", e.what());
    }

    return 0;
  }

}