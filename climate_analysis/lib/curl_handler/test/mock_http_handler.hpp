#ifndef MOCK_HTTP_HANDLER_HPP
#define MOCK_HTTP_HANDLER_HPP

#include <gmock/gmock.h>
#include "http_handler.hpp"

class MockHttpHandler : public IHttpHandler {
public:
    MOCK_METHOD(std::optional<std::string>, http_get, (const std::string& url), (override));
};

#endif // MOCK_HTTP_HANDLER_HPP