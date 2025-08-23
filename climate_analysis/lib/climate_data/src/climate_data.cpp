#include "climate_data.hpp"

// @brief Constructor for ClimateData class.
// @param http Unique pointer to an IHttpHandler instance for HTTP requests.
ClimateData::ClimateData(std::unique_ptr<IHttpHandler> http) : http_handle(std::move(http)) {
    if (http_handle == nullptr) {
        spdlog::critical("ClimateData::ClimateData HTTP handler is null");
        throw std::runtime_error("HTTP handler initialization failed");
    }
}

// @brief Fetch (latitude, longitude) of city using the OpenMeteo Geocoding API.
// @param city Name of city to geocode.
// @return pair containing the (latitude, longitude) of city.
std::optional<std::pair<double, double>> ClimateData::get_city_coordinates(const std::string& city) {
    const std::string url = climate_api::geocode_url + city;

    auto response = http_handle->http_get(url);
    if (!response.has_value()) {
        spdlog::error("Failed to fetch geocode data for city: {}", city);
        return std::nullopt;           
    }

    JsonParser parser;
    return parser.parse_geocode<double>(response.value());
}