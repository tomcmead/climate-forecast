#ifndef CLIMATE_DATA_HPP
#define CLIMATE_DATA_HPP

#include "http_handler.hpp"
#include "json_parser.hpp"
#include "climate_url.hpp"
#include <memory>

class ClimateData {
public:
    explicit ClimateData(std::unique_ptr<IHttpHandler> http);
    template<ForecastDays days=ForecastDays::Seven>
    std::optional<Climate<days>> GetClimateForecast(const std::string& city);

private:
    std::unique_ptr<IHttpHandler> http_handle;
    std::optional<std::pair<double, double>> get_city_coordinates(const std::string& city);
};

// @brief Fetch climate forecast for a city.
// @tparam days Number of forecast days, default is 7.
// @param city Name of city to get forecast.
// @return Optional Climate data if successful, otherwise nullopt.
template<ForecastDays days>
std::optional<Climate<days>> ClimateData::GetClimateForecast(const std::string& city){
    auto coordinates = get_city_coordinates(city);
    if(!coordinates.has_value()) {
        spdlog::error("ClimateData::GetClimateForecast Failed to get coordinates for city: {}", city);
        return std::nullopt;
    }

    auto [latitude, longitude] = coordinates.value();
    if(latitude<-90.0 || latitude>90.0 || longitude<-180.0 || longitude>180.0) {
        spdlog::error("ClimateData::GetClimateForecast Invalid coordinates {}: ({}, {})", city, latitude, longitude);
        return std::nullopt;
    }

    ClimateUrl url(latitude, longitude, days);    
    auto response = http_handle->http_get(url());
    if (!response.has_value()) {
        spdlog::error("ClimateData::GetClimateForecast Failed to retrieve data from URL: {}", url());
        return std::nullopt;
    }

    JsonParser parser;
    return parser.parse_climate<days>(response.value());
}

#endif // CLIMATE_DATA_HPP