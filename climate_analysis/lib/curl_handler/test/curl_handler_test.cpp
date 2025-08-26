#include <gtest/gtest.h>
#include "curl_handler.hpp"

class CurlHandlerTest : public ::testing::Test {
protected:
    CurlHandler curl_handle;
    const std::string test_url = "https://mock.httpstatus.io/";
    const std::string http_ok = "200";
    const std::string http_bad_request = "400";
    const std::string http_internal_server_error = "500";
    const std::string http_forbidden = "403";

    void SetUp() override {
        CURLcode global_init_res = curl_global_init(CURL_GLOBAL_DEFAULT);
        if (global_init_res != CURLE_OK) {
            std::cerr << "curl_global_init() failed: " << curl_easy_strerror(global_init_res) << std::endl;
        }
    }

    void TearDown() override {
        curl_global_cleanup();
    }
};

TEST_F(CurlHandlerTest, HttpGetOk_ResponseOk) {
    const std::string url_ok = test_url + http_ok;
    const std::string response_ok = "200 OK";

    const auto response = curl_handle.http_get(url_ok);

    EXPECT_EQ(response, response_ok);
}

TEST_F(CurlHandlerTest, HttpGetBadRequest_ResponseNullopt) {
    const std::string url_bad_request = test_url + http_bad_request;
    const std::optional<std::string> response_bad_request = std::nullopt; 

    const auto response = curl_handle.http_get(url_bad_request);

    EXPECT_EQ(response, response_bad_request);
}

TEST_F(CurlHandlerTest, HttpGetServerError_ResponseNullopt) {
    const std::string url_server_error = test_url + http_internal_server_error;
    const std::optional<std::string> response_server_error = std::nullopt; 

    const auto response = curl_handle.http_get(url_server_error);

    EXPECT_EQ(response, response_server_error);
}

TEST_F(CurlHandlerTest, HttpGetUnknownError_ResponseNullopt) {
    const std::string url_forbidden = test_url + http_forbidden;
    const std::optional<std::string> response_forbidden = std::nullopt; 

    const auto response = curl_handle.http_get(url_forbidden);

    EXPECT_EQ(response, response_forbidden);
}