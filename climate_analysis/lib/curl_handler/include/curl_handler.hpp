#ifndef CURL_HANDLER_HPP
#define CURL_HANDLER_HPP

#include "http_handler.hpp"
#include <curl/curl.h>

namespace curlconfig {
    constexpr long timeout_ms = 50000;
}

class CurlHandler final : public IHttpHandler {
public:
    std::optional<std::string> http_get(const std::string& url) override;
private:
    static size_t curl_write_callback(void *contents, size_t size, size_t nmemb, void *userp);
};

#endif // CURL_HANDLER_HPP