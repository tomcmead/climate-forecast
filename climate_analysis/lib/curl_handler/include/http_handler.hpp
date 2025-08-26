#ifndef HTTP_HANDLER_HPP
#define HTTP_HANDLER_HPP

#include <string>
#include <optional>

enum class HttpCode : long{
    ok = 200L,
    bad_request = 400L,
    internal_server_error = 500L
};

// @class IHttpHandler
// @brief Interface for handling HTTP GET requests.
class IHttpHandler {
public:
    virtual std::optional<std::string> http_get(const std::string& url) = 0;
    virtual ~IHttpHandler() = default;
};

#endif // HTTP_HANDLER_HPP