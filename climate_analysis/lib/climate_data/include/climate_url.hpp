#ifndef CLIMATE_URL_HPP
#define CLIMATE_URL_HPP

#include "climate_types.hpp"
#include <string>
#include <array>

/**
 * @class ClimateUrl
 * @brief Class for constructing climate API URLs using Method Chaining.
 */
class ClimateUrl {
public:
    ClimateUrl() = delete;

    ClimateUrl(double latitude, double longitude, ForecastDays days=ForecastDays::Seven) 
        : latitude(latitude), longitude(longitude), forecast_days(days) { }

    const std::string& get_url();

    const std::string& operator()() {
        return get_url();
    }
    
    ClimateUrl& set_forecast_days(const ForecastDays& days) {
        this->forecast_days = days;
        return *this;
    }
    ClimateUrl& set_latitude(const double& lat) {
        this->latitude = lat;
        return *this;
    }
    ClimateUrl& set_longitude(const double& lon) {
        this->longitude = lon;
        return *this;
    }
    ClimateUrl& set_daily(const bool& daily=true) {
        this->is_daily = daily;
        return *this;
    }
    ClimateUrl& set_hourly(const bool& hourly=true) {
        this->is_hourly = hourly;
        return *this;
    }

private:
    ForecastDays forecast_days;
    double latitude;
    double longitude;
    bool is_daily = true;
    bool is_hourly = true;
    std::string url;
};

#endif // CLIMATE_URL_HPP