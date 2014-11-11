#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <CrawlTickers.hpp>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

namespace NetworkModule
{

  CrawlTickers::CrawlTickers()
  {

  }

  /* Return a pointer to our ticker map */
  std::map<std::string, ticker>* CrawlTickers::getTickers ()
  {
    return &tickers;
  }

  /*  Return values are http returns */
  int CrawlTickers::downloadTickers()
  {
    std::shared_ptr<ostream> fileStream = std::make_shared<ostream>();
    
    int i;

    for(i = 0; i < 26; i ++)
    {
      std::string file = "ticker";
      char letter = (char)((int)'A' + i);
      file += letter;
      file += ".csv";
      getTickersForLetter(fileStream, file, letter);
    }

    return 0;
  }

  int CrawlTickers::getTickersForLetter(std::shared_ptr<ostream> fileStream, std::string file, char letter)
  {
    // Open stream to output file.
    pplx::task<void> requestTask = fstream::open_ostream(U(file)).then([=](ostream outFile)
    {
      *fileStream = outFile;
      // Create http_client to send the request.
      http_client client(U("http://www.nasdaq.com/screening/"));

      // Build request URI and start the request.
      uri_builder builder(U("/companies-by-name.aspx"));
      builder.append_query(U("letter"), U(letter));
      builder.append_query(U("render"), U("download"));
      return client.request(methods::GET, builder.to_string());
    })

    // Handle response headers arriving.
    .then([=](http_response response)
    {
      printf("Received response status code:%u\n", response.status_code());

      // Write response body into the file.
      return response.body().read_to_end(fileStream->streambuf());
    })

    // Close the file stream.
    .then([=](size_t)
    {
      return fileStream->close();
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