#include "curl_handler.hpp"
#include <spdlog/spdlog.h>

/// @brief Execute HTTP GET request for target URL
/// @param url target URL address
/// @return HTTP response as a string, or std::nullopt on failure
std::optional<std::string>  CurlHandler::http_get(const std::string& url) {
    CURL *curl_handle = curl_easy_init();
    if(curl_handle == nullptr){
        spdlog::critical("CurlHandler::http_get curl_easy_init() unsuccessful");
        return std::nullopt;
    }

    std::string response;
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, curl_write_callback);
    curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT_MS, curlconfig::timeout_ms);
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_handle, CURLOPT_NOSIGNAL, 1L);

    const CURLcode curl_code = curl_easy_perform(curl_handle);
    if(curl_code != CURLE_OK){
        spdlog::critical("CurlHandler::http_get HTTP GET request cURL failure {}", curl_easy_strerror(curl_code));
        return std::nullopt;
    }

    long http_code;
    curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &http_code);

    curl_easy_cleanup(curl_handle);

    if(http_code!=static_cast<long>(HttpCode::ok)){
        spdlog::critical("CurlHandler::http_get HTTP status GET error {}", http_code);
        return std::nullopt;
    }
    return response;
}

/// @brief Libcurl write callback for HTTP GET request
size_t CurlHandler::curl_write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}