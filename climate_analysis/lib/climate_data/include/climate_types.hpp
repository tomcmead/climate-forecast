#ifndef CLIMATE_TYPES_HPP
#define CLIMATE_TYPES_HPP

#include <string>
#include <array>
#include <unordered_map>

template<typename T, size_t N>
struct DailyClimate {    
    std::array<std::string, N> time;
    std::array<std::string, N> sunrise;
    std::array<std::string, N> sunset;
    std::unordered_map<std::string, std::array<T, N>> data;
};

template<typename T, size_t N>
struct Climate {
    double latitude;
    double longitude;
    DailyClimate<T, N> daily_data;
    // HourlyClimateData hourly_data;
};

enum class ForecastDays {
    One = 1,
    Three = 3,
    Seven = 7,
    Fourteen = 14,
    Sixteen = 16
};

namespace climate_api{
    inline const std::string url = "https://api.open-meteo.com/v1/forecast?timezone=auto";
    inline const std::string forecast_days = "forecast_days";
    inline const std::string latitude = "latitude";
    inline const std::string longitude = "longitude";
    namespace daily {
        inline const std::array<std::string, 8> parameters = {
            "sunrise",
            "sunset",
            "uv_index_max",
            "temperature_2m_max",
            "temperature_2m_min",
            "rain_sum",
            "showers_sum",
            "snowfall_sum"
        };
    }
    namespace hourly {
        inline const std::array<std::string, 10> parameters = {
            "temperature_2m",
            "precipitation",
            "showers",
            "snowfall",
            "snow_depth",
            "cloud_cover",
            "visibility",
            "wind_speed_10m",
            "wind_direction_10m",
            "relative_humidity_2m"
        };
    }
}

#endif // CLIMATE_TYPES_HPP