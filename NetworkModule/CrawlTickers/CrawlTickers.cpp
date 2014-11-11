#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <CrawlTickers.hpp>
#include <exception>
#include <string>
#include <stdexcept>
#include <sstream>

using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

#ifndef err_throw

#include <stdexcept>

/* Standard exception: */
#define err_throw(MSG) throw std::runtime_error("Error, exception thrown at line " + itoa(__LINE__) + 
                        " in file \"" + std::string(__FILE__) + "\": " + std::string(MSG))

#endif

namespace
{
    
    
    //basic string conversion:
    template<typename type>
    std::string itoa(const type& t)
    {
        std::stringstream ss;
        ss<< t;
        return ss.str();
    }
    
    template itoa<int>(const int&);
    
    
}

namespace NetworkModule
{

  CrawlTickers::CrawlTickers() : tickers()
  {
  }

  /*  Return values are http returns */
  int CrawlTickers::downloadTickers()
  {
    std::shared_ptr<ostream> fileStream = std::make_shared<ostream>();
    std::string file("ticker");

    for(char ch = 'A'; ch < 'Z'; ++ch)
    {
      file += ch
      getTickersForLetter(fileStream, (file + ".csv"), letter);
    }

    return 0;
  }

  int CrawlTickers::getTickersForLetter(std::ostream& fileStream, const std::string& file, char letter)
  {
    // Open stream to output file.
    pplx::task<void> requestTask = fstream::open_ostream(U(file)).then([=](ostream outFile)
    {
        if(fileStream.is_open()) fileStream.close();
        
        fileStream.rdbuf(outFile.rdbuf());
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
      return response.body().read_to_end(fileStream.rdbuf());
    })

    // Close the file stream.
    .then([=](size_t)
    {
        fileStream.close();
        return 0;
    });

    // Wait for all the outstanding I/O to complete and handle any exceptions
    try
    {
        //SUPER INEFFICIENT, please try to avoid this if at all possible.
        requestTask.wait();
    }
    catch (const std::exception &e)
    {
        err_throw(e.what());
    }

    return 0;
  }


}