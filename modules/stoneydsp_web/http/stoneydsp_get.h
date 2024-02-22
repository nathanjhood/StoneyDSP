

/**
 * @brief Adapted from https://curl.se/libcurl/c/simple.html
 *
 * @param url The HTTP URL to send the GET request to.
 * @param follow Whether to follow redirected URL requests.
 * @return int
 */
int stoneydsp_web_http_get(const char* url, const long& follow);

namespace StoneyDSP::Web::Http
{
int Get(const char* url, const long& follow);
int Post(const char* url, const char* data);
}
