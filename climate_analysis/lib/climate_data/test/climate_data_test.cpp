#include <gtest/gtest.h>
#include "climate_data.hpp"
#include "mock_http_handler.hpp"

namespace {
    const std::string mock_climate_json = R"({
        "latitude": 37.77,
        "longitude": -122.41,
        "daily": {
            "time": ["2023-10-01"],
            "sunrise": ["06:30"],
            "sunset": ["18:30"],
            "uv_index_max": [5],
            "temperature_2m_max": [20.0],
            "temperature_2m_min": [15.0],
            "rain_sum": [0.0],
            "showers_sum": [0.0],
            "snowfall_sum": [0.0]
        },
        "hourly": {
            "time": ["2023-10-01T00:00", "2023-10-01T01:00", "2023-10-01T02:00", "2023-10-01T03:00",
                     "2023-10-01T04:00", "2023-10-01T05:00", "2023-10-01T06:00", "2023-10-01T07:00",
                     "2023-10-01T08:00", "2023-10-01T09:00", "2023-10-01T10:00", "2023-10-01T11:00",
                     "2023-10-01T12:00", "2023-10-01T13:00", "2023-10-01T14:00", "2023-10-01T15:00",
                     "2023-10-01T16:00", "2023-10-01T17:00", "2023-10-01T18:00", "2023-10-01T19:00",
                     "2023-10-01T20:00", "2023-10-01T21:00", "2023-10-01T22:00", "2023-10-01T23:00"],
            "temperature_2m": [15.0, 14.5, 14.0, 13.5, 13.0, 12.5, 12.0, 11.5,
                               11.0, 10.5, 10.0, 9.5, 9.0, 8.5, 8.0, 7.5,
                               7.0, 6.5, 6.0, 5.5, 5.0, 4.5, 4.0, 3.5],
            "precipitation": [0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                              0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8],
            "showers": [0.0, 0.05, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 0.0, 0.05, 0.1, 0.15, 0.2,
                        0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6],
            "snowfall": [0.0, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
                         0.01, 0.01, 0.01, 0.01, 0.02, 0.03, 0.04, 0.05,
                         0.06, 0.07, 0.08, 0.09, 0.1, 0.11, 0.12, 0.13],
            "snow_depth": [0.0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07,
                           0.08, 0.09, 0.1, 0.11, 0.12, 0.13, 0.14, 0.15,
                           0.16, 0.17, 0.18, 0.19, 0.2, 0.21, 0.22, 0.23],
            "cloud_cover": [20, 30, 50, 20, 30, 50, 20, 30,
                            50, 20, 30, 50, 20, 30, 50, 20,
                            30, 50, 20, 30, 50, 60, 70, 20],
            "visibility": [10, 9, 8, 7, 6, 5, 4, 3,
                               2, 1, 0, 1, 2, 3, 4, 5,
                               6, 7, 8, 9, 10, 11, 12, 13],
            "wind_speed_10m": [5.0, 4.5, 4.0, 3.5, 3.0, 2.5, 2.0, 1.5,
                               1.0, 0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 2.5,
                               2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0],
            "wind_direction_10m": [180, 190, 200, 210, 220, 230, 240, 250,
                                   260, 270, 280, 290, 300, 310, 320, 330,
                                   340, 350, 0, 10, 20, 30, 40, 50],
            "relative_humidity_2m": [60, 65, 70, 75, 80, 85, 90, 95,
                                     100, 95, 90, 85, 80, 75, 70, 65,
                                     60, 55, 50, 45, 40, 35, 30, 25]
        }
    })";

    const std::string mock_city_json = R"({
        "results": [
            {
                "id": 2950159,
                "name": "Berlin",
                "latitude": 52.52437,
                "longitude": 13.41053,
                "elevation": 74.0,
                "feature_code": "PPLC",
                "country_code": "DE",
                "admin1_id": 2950157,
                "admin3_id": 6547383,
                "admin4_id": 6547539,
                "timezone": "Europe/Berlin",
                "population": 3426354,
                "postcodes": ["10967", "13347"],
                "country_id": 2921044,
                "country": "Germany",
                "admin1": "State of Berlin",
                "admin3": "Berlin, Stadt",
                "admin4": "Berlin"
            }
        ],
        "generationtime_ms": 0.46432018
    })";

    const Climate<double, ForecastDays::One> expected_climate = {
        37.77,
        -122.41,
        {
            {"2023-10-01"},
            {"06:30"},
            {"18:30"},
            {
                {"uv_index_max", {5.0}},
                {"temperature_2m_max", {20.0}},
                {"temperature_2m_min", {15.0}},
                {"rain_sum", {0.0}},
                {"showers_sum", {0.0}},
                {"snowfall_sum", {0.0}}
            },
        },
        {
            {"2023-10-01T00:00", "2023-10-01T01:00", "2023-10-01T02:00", "2023-10-01T03:00",
                "2023-10-01T04:00", "2023-10-01T05:00", "2023-10-01T06:00", "2023-10-01T07:00",
                "2023-10-01T08:00", "2023-10-01T09:00", "2023-10-01T10:00", "2023-10-01T11:00",
                "2023-10-01T12:00", "2023-10-01T13:00", "2023-10-01T14:00", "2023-10-01T15:00",
                "2023-10-01T16:00", "2023-10-01T17:00", "2023-10-01T18:00", "2023-10-01T19:00",
                "2023-10-01T20:00", "2023-10-01T21:00", "2023-10-01T22:00", "2023-10-01T23:00"},
            {                
                {"temperature_2m", {15.0, 14.5, 14.0, 13.5, 13.0, 12.5, 12.0, 11.5,
                                    11.0, 10.5, 10.0, 9.5, 9.0, 8.5, 8.0, 7.5,
                                    7.0, 6.5, 6.0, 5.5, 5.0, 4.5, 4.0, 3.5}},
                {"precipitation", {0.0, 0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                    0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8}},
                {"showers", {0.0, 0.05, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
                                    0.0, 0.0, 0.0, 0.0, 0.05, 0.1, 0.15, 0.2,
                                    0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6}},
                {"snowfall", {0.0, 0.02, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
                                    0.01, 0.01, 0.01, 0.01, 0.02, 0.03, 0.04, 0.05,
                                    0.06, 0.07, 0.08, 0.09, 0.1, 0.11, 0.12, 0.13}},
                {"snow_depth", {0.0, 0.01, 0.02, 0.03, 0.04, 0.05, 0.06, 0.07,
                                    0.08, 0.09, 0.1, 0.11, 0.12, 0.13, 0.14, 0.15,
                                    0.16, 0.17, 0.18, 0.19, 0.2, 0.21, 0.22, 0.23}},
                {"cloud_cover", {20, 30, 50, 20, 30, 50, 20, 30,
                                    50, 20, 30, 50, 20, 30, 50, 20,
                                    30, 50, 20, 30, 50, 60, 70, 20}},
                {"visibility", {10, 9, 8, 7, 6, 5, 4, 3,
                                    2, 1, 0, 1, 2, 3, 4, 5,
                                    6, 7, 8, 9, 10, 11, 12, 13}},
                {"wind_speed_10m", {5.0, 4.5, 4.0, 3.5, 3.0, 2.5, 2.0, 1.5,
                                    1.0, 0.5, 0.0, 0.5, 1.0, 1.5, 2.0, 2.5,
                                    2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0}},
                {"wind_direction_10m", {180, 190, 200, 210, 220, 230, 240, 250,
                                        260, 270, 280, 290, 300, 310, 320, 330,
                                        340, 350, 0, 10, 20, 30, 40, 50}},
                {"relative_humidity_2m", {60, 65, 70, 75, 80, 85, 90, 95,
                                            100, 95, 90, 85, 80, 75, 70, 65,
                                            60, 55, 50, 45, 40, 35, 30, 25}}
            }
        }
    };
}

TEST(ClimateDataTest, GetClimateForecast_ValidCity_ReturnsClimateData) {
    MockHttpHandler* mock_http = new MockHttpHandler();
    EXPECT_CALL(*mock_http, http_get(testing::_))
        .Times(2)
        .WillOnce(testing::Return(std::make_optional(mock_city_json)))
        .WillOnce(testing::Return(std::make_optional(mock_climate_json)));
    std::unique_ptr<IHttpHandler> mock_http_ptr(mock_http);
    ClimateData climate_data(std::move(mock_http_ptr));

    auto result = climate_data.GetClimateForecast<ForecastDays::One>("San Francisco");
    
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().latitude, expected_climate.latitude);
    EXPECT_EQ(result.value().longitude, expected_climate.longitude);
    EXPECT_EQ(result.value().daily.time, expected_climate.daily.time);
    EXPECT_EQ(result.value().daily.sunrise, expected_climate.daily.sunrise);
    EXPECT_EQ(result.value().daily.sunset, expected_climate.daily.sunset);
    for (const auto& param : expected_climate.daily.data) {
        EXPECT_EQ(result.value().daily.data[param.first], param.second);
    }
    for (const auto& param : expected_climate.hourly.data) {
        EXPECT_EQ(result.value().hourly.data[param.first], param.second);
    }
}

TEST(ClimateDataTest, GetClimateForecast_InvalidCity_ReturnsEmpty) {
    MockHttpHandler* mock_http = new MockHttpHandler();
    EXPECT_CALL(*mock_http, http_get(testing::_))
        .Times(1)
        .WillOnce(testing::Return(std::nullopt));
    std::unique_ptr<IHttpHandler> mock_http_ptr(mock_http);
    ClimateData climate_data(std::move(mock_http_ptr));

    auto result = climate_data.GetClimateForecast<ForecastDays::One>("Invalid City");
    
    EXPECT_FALSE(result.has_value());
}