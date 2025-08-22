#ifndef CLIMATE_URL_HPP
#define CLIMATE_URL_HPP

#include <string>
#include <array>

enum class ForecastDays {
    One = 1,
    Three = 3,
    Seven = 7,
    Fourteen = 14,
    Sixteen = 16
};

namespace climate_api{
    inline const std::string url = "https://api.open-meteo.com/v1/forecast?timezone=auto";
    inline const std::string forecast_days = "forecast_days=";
    inline const std::string latitude = "latitude=";
    inline const std::string longitude = "longitude=";
    namespace daily {
        inline const std::array<std::string, 8> parameters = {
            "daily=sunrise",
            "daily=sunset",
            "daily=uv_index_max",
            "daily=temperature_2m_max",
            "daily=temperature_2m_min",
            "daily=rain_sum",
            "daily=showers_sum",
            "daily=snowfall_sum"
        };
    }
    namespace hourly {
        inline const std::array<std::string, 10> parameters = {
            "hourly=temperature_2m",
            "hourly=precipitation",
            "hourly=showers",
            "hourly=snowfall",
            "hourly=snow_depth",
            "hourly=cloud_cover",
            "hourly=visibility",
            "hourly=wind_speed_10m",
            "hourly=wind_direction_10m",
            "hourly=relative_humidity_2m"
        };
    }
}

class ClimateUrl {
public:
    ClimateUrl() = default;

    ClimateUrl(double latitude, double longitude, ForecastDays days=ForecastDays::Seven) 
        : latitude(latitude), longitude(longitude), forecast_days(days) { }

    const std::string& get_url() {
        url = climate_api::url;
        url += "&" + climate_api::forecast_days + std::to_string(static_cast<int>(forecast_days));
        url += "&" + climate_api::latitude + std::to_string(latitude);
        url += "&" + climate_api::longitude + std::to_string(longitude);

        if (is_daily) {  
            for (const auto& param : climate_api::daily::parameters) {
                url += "&" + param;
            }
        }
        if(is_hourly) {      
            for (const auto& param : climate_api::hourly::parameters) {
                url += "&" + param;
            }
        }

        return url;
    }

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