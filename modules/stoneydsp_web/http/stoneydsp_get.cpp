#include "stoneydsp_get.h"

int stoneydsp_web_http_get(const char* url, const long& follow)
{
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, follow); // 'follow'

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return EXIT_SUCCESS;
};


namespace StoneyDSP::Web::Http
{
int Get(const char* url, const long& follow)
{
    return stoneydsp_web_http_get(url, follow);
};
}
