#include <iostream>
#include <string>
 
#include <curl/curl.h>
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
	
	//const std::string conf_doc = "test.json";

  	bool parsingSuccessful = reader.parse( currentprice_doc, root, true );
	if ( !parsingSuccessful )
	{
    	// report to the user the failure and their locations in the document.
    	std::cout  << "Failed to parse configuration\n"
              << reader.getFormattedErrorMessages();
    	return -1;
	}

	const Json::Value plugins = root["time"];
	std::cout << plugins.size();
	for ( int index = 0; index < plugins.size(); ++index ) {
 		  std::cout << plugins[index].asString() << std::endl;
 	}


  CURL *curl_handle;

  static const char *bodyfilename = "body.out";
  FILE *bodyfile;
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  // init the curl session  
  curl_handle = curl_easy_init();
 
  // set URL to get 
  curl_easy_setopt(curl_handle, CURLOPT_URL, "http://www.coindesk.com/calculator/");
 
  // no progress meter please  
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
 
  // send all data to this function  
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
 
 
  // open the body file  
  bodyfile = fopen(bodyfilename, "wb");
  if(!bodyfile) 
  {
    curl_easy_cleanup(curl_handle);
    return -1;
  }
 
  // we want the body be written to this file handle instead of stdout  
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, bodyfile);
 
  // get it! 
  curl_easy_perform(curl_handle);
 
  // close the body file 
  fclose(bodyfile);
 
  // cleanup curl stuff 
  curl_easy_cleanup(curl_handle);
 
  return 0;
}
