#include <iostream>
#include <string>
#include <fstream>
 
#include "json/json.h"
#include "json/json-forwards.h"

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}
 
int main(void)
{

	Json::Value root;   // starts as "null"; will contain the root value ater parsing
	Json::Reader reader;
	const std::string currentprice_doc = "currentprice.json";

	int get = system ("wget http://api.coindesk.com/v1/bpi/currentprice.json");
	if (get == -1) {
		std::cout  << "Error wget currentprice.json \n";
    	return get;
	}

	std::filebuf fb;
	if (fb.open ("currentprice.json",std::ios::in))
	{
		std::istream is(&fb);

		bool parsingSuccessful = reader.parse( is, root, true );
		if ( !parsingSuccessful )
		{
    		std::cout  << "Failed to parse configuration\n"
      	        << reader.getFormattedErrorMessages();
    		return -1;
		}
		
		fb.close();
	}
	
	std::cout << root["bpi"]["USD"]["code"].asString() << " ";
	std::cout << root["bpi"]["USD"]["rate"].asString() << std::endl;

	std::cout << root["bpi"]["EUR"]["code"].asString() << " ";
	std::cout << root["bpi"]["EUR"]["rate"].asString() << std::endl;

	std::cout << root["bpi"]["GBP"]["code"].asString() << " ";
	std::cout << root["bpi"]["GBP"]["rate"].asString() << std::endl;
 
  return 0;
}
