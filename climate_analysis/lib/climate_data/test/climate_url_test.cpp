#include <gtest/gtest.h>
#include "climate_url.hpp"

namespace {
    const std::array<ForecastDays, 5> days = {
        ForecastDays::One,
        ForecastDays::Three,
        ForecastDays::Seven,
        ForecastDays::Fourteen,
        ForecastDays::Sixteen
    };
}

TEST(ClimateUrlTest, GetUrlValidDailyAllDays_ValidUrl){
    ClimateUrl generate_url(37.77, -122.41);
    generate_url.set_hourly(false);
    const std::array<std::string, 5> expected_urls{
        std::string("https://api.open-meteo.com/v1/forecast?timezone=auto&forecast_days=1&latitude=37.770000&longitude=-122.410000&daily=sunrise&daily=sunset&daily=uv_index_max&daily=temperature_2m_max&daily=temperature_2m_min&daily=rain_sum&daily=showers_sum&daily=snowfall_sum"),
        std::string("https://api.open-meteo.com/v1/forecast?timezone=auto&forecast_days=3&latitude=37.770000&longitude=-122.410000&daily=sunrise&daily=sunset&daily=uv_index_max&daily=temperature_2m_max&daily=temperature_2m_min&daily=rain_sum&daily=showers_sum&daily=snowfall_sum"),
        std::string("https://api.open-meteo.com/v1/forecast?timezone=auto&forecast_days=7&latitude=37.770000&longitude=-122.410000&daily=sunrise&daily=sunset&daily=uv_index_max&daily=temperature_2m_max&daily=temperature_2m_min&daily=rain_sum&daily=showers_sum&daily=snowfall_sum"),
        std::string("https://api.open-meteo.com/v1/forecast?timezone=auto&forecast_days=14&latitude=37.770000&longitude=-122.410000&daily=sunrise&daily=sunset&daily=uv_index_max&daily=temperature_2m_max&daily=temperature_2m_min&daily=rain_sum&daily=showers_sum&daily=snowfall_sum"),
        std::string("https://api.open-meteo.com/v1/forecast?timezone=auto&forecast_days=16&latitude=37.770000&longitude=-122.410000&daily=sunrise&daily=sunset&daily=uv_index_max&daily=temperature_2m_max&daily=temperature_2m_min&daily=rain_sum&daily=showers_sum&daily=snowfall_sum")
    };

    for(size_t i = 0; i < days.size(); ++i) {
        generate_url.set_forecast_days(days[i]);
        const std::string url = generate_url.get_url();
        EXPECT_EQ(url, expected_urls[i]);
    }
}

TEST(ClimateUrlTest, GetUrlValidHourlyAllDays_ValidUrl){
    ClimateUrl generate_url(77.77, -99.99);
    generate_url.set_daily(false);
    const std::array<std::string, 5> expected_urls{
        std::string("https://api.open-meteo.com/v1/forecast?timezone=auto&forecast_days=1&latitude=77.770000&longitude=-99.990000&hourly=temperature_2m&hourly=precipitation&hourly=showers&hourly=snowfall&hourly=snow_depth&hourly=cloud_cover&hourly=visibility&hourly=wind_speed_10m&hourly=wind_direction_10m&hourly=relative_humidity_2m"),
        std::string("https://api.open-meteo.com/v1/forecast?timezone=auto&forecast_days=3&latitude=77.770000&longitude=-99.990000&hourly=temperature_2m&hourly=precipitation&hourly=showers&hourly=snowfall&hourly=snow_depth&hourly=cloud_cover&hourly=visibility&hourly=wind_speed_10m&hourly=wind_direction_10m&hourly=relative_humidity_2m"),
        std::string("https://api.open-meteo.com/v1/forecast?timezone=auto&forecast_days=7&latitude=77.770000&longitude=-99.990000&hourly=temperature_2m&hourly=precipitation&hourly=showers&hourly=snowfall&hourly=snow_depth&hourly=cloud_cover&hourly=visibility&hourly=wind_speed_10m&hourly=wind_direction_10m&hourly=relative_humidity_2m"),
        std::string("https://api.open-meteo.com/v1/forecast?timezone=auto&forecast_days=14&latitude=77.770000&longitude=-99.990000&hourly=temperature_2m&hourly=precipitation&hourly=showers&hourly=snowfall&hourly=snow_depth&hourly=cloud_cover&hourly=visibility&hourly=wind_speed_10m&hourly=wind_direction_10m&hourly=relative_humidity_2m"),
        std::string("https://api.open-meteo.com/v1/forecast?timezone=auto&forecast_days=16&latitude=77.770000&longitude=-99.990000&hourly=temperature_2m&hourly=precipitation&hourly=showers&hourly=snowfall&hourly=snow_depth&hourly=cloud_cover&hourly=visibility&hourly=wind_speed_10m&hourly=wind_direction_10m&hourly=relative_humidity_2m")
    };

    for(size_t i = 0; i < days.size(); ++i) {
        generate_url.set_forecast_days(days[i]);
        const std::string url = generate_url.get_url();
        EXPECT_EQ(url, expected_urls[i]);
    }
}

TEST(ClimateUrlTest, GetUrlValidDailyHourlyAllDays_ValidUrl){
    ClimateUrl generate_url(77.77, -99.99);
    const std::array<std::string, 5> expected_urls{
        std::string("https://api.open-meteo.com/v1/forecast?timezone=auto&forecast_days=1&latitude=77.770000&longitude=-99.990000&daily=sunrise&daily=sunset&daily=uv_index_max&daily=temperature_2m_max&daily=temperature_2m_min&daily=rain_sum&daily=showers_sum&daily=snowfall_sum&hourly=temperature_2m&hourly=precipitation&hourly=showers&hourly=snowfall&hourly=snow_depth&hourly=cloud_cover&hourly=visibility&hourly=wind_speed_10m&hourly=wind_direction_10m&hourly=relative_humidity_2m"),
        std::string("https://api.open-meteo.com/v1/forecast?timezone=auto&forecast_days=3&latitude=77.770000&longitude=-99.990000&daily=sunrise&daily=sunset&daily=uv_index_max&daily=temperature_2m_max&daily=temperature_2m_min&daily=rain_sum&daily=showers_sum&daily=snowfall_sum&hourly=temperature_2m&hourly=precipitation&hourly=showers&hourly=snowfall&hourly=snow_depth&hourly=cloud_cover&hourly=visibility&hourly=wind_speed_10m&hourly=wind_direction_10m&hourly=relative_humidity_2m"),
        std::string("https://api.open-meteo.com/v1/forecast?timezone=auto&forecast_days=7&latitude=77.770000&longitude=-99.990000&daily=sunrise&daily=sunset&daily=uv_index_max&daily=temperature_2m_max&daily=temperature_2m_min&daily=rain_sum&daily=showers_sum&daily=snowfall_sum&hourly=temperature_2m&hourly=precipitation&hourly=showers&hourly=snowfall&hourly=snow_depth&hourly=cloud_cover&hourly=visibility&hourly=wind_speed_10m&hourly=wind_direction_10m&hourly=relative_humidity_2m"),
        std::string("https://api.open-meteo.com/v1/forecast?timezone=auto&forecast_days=14&latitude=77.770000&longitude=-99.990000&daily=sunrise&daily=sunset&daily=uv_index_max&daily=temperature_2m_max&daily=temperature_2m_min&daily=rain_sum&daily=showers_sum&daily=snowfall_sum&hourly=temperature_2m&hourly=precipitation&hourly=showers&hourly=snowfall&hourly=snow_depth&hourly=cloud_cover&hourly=visibility&hourly=wind_speed_10m&hourly=wind_direction_10m&hourly=relative_humidity_2m"),
        std::string("https://api.open-meteo.com/v1/forecast?timezone=auto&forecast_days=16&latitude=77.770000&longitude=-99.990000&daily=sunrise&daily=sunset&daily=uv_index_max&daily=temperature_2m_max&daily=temperature_2m_min&daily=rain_sum&daily=showers_sum&daily=snowfall_sum&hourly=temperature_2m&hourly=precipitation&hourly=showers&hourly=snowfall&hourly=snow_depth&hourly=cloud_cover&hourly=visibility&hourly=wind_speed_10m&hourly=wind_direction_10m&hourly=relative_humidity_2m")
    };

    for(size_t i = 0; i < days.size(); ++i) {
        generate_url.set_forecast_days(days[i]);
        const std::string url = generate_url.get_url();
        EXPECT_EQ(url, expected_urls[i]);
    }
}

TEST(ClimateUrlTest, ChainMethodsFunctorValid_ValidUrl) {
    ClimateUrl generate_url(50, 50);
    const std::string expected_url = "https://api.open-meteo.com/v1/forecast?timezone=auto&forecast_days=7&latitude=10.000000&longitude=100.000000";

    generate_url.set_forecast_days(ForecastDays::Seven)
                .set_latitude(10)
                .set_longitude(100)
                .set_daily(false)
                .set_hourly(false);
    const std::string url = generate_url();

    EXPECT_EQ(url, expected_url);
}