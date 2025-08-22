#include "climate_data.hpp"

ClimateData::ClimateData(std::unique_ptr<IHttpHandler> http) : http_handle(std::move(http)) {
    if (http_handle == nullptr) {
        spdlog::critical("ClimateData::ClimateData HTTP handler is null");
        throw std::runtime_error("HTTP handler initialization failed");
    }
}

std::optional<std::string> ClimateData::GetClimateForecast(double latitude, double longitude, ForecastDays days) {
    if(latitude<-90.0 || latitude>90.0 || longitude<-180.0 || longitude>180.0) {
        spdlog::error("ClimateData::GetClimateForecast Invalid latitude or longitude: ({}, {})", latitude, longitude);
        return std::nullopt;
    }

    ClimateUrl url(latitude, longitude, days);
    
    auto response = http_handle->http_get(url());
    if (!response) {
        spdlog::error("Failed to retrieve data from URL: {}", url());
        return std::nullopt;
    }

    return "";
}