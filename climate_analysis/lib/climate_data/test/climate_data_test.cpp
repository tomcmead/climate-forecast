#include <gtest/gtest.h>
#include "climate_data.hpp"
#include "mock_http_handler.hpp"
#include "json_test_data.hpp"

TEST(ClimateDataTest, GetClimateForecast_ValidCity_ReturnsClimateData) {
    MockHttpHandler* mock_http = new MockHttpHandler();
    EXPECT_CALL(*mock_http, http_get(testing::_))
        .Times(2)
        .WillOnce(testing::Return(std::make_optional(json_test::mock_city_json)))
        .WillOnce(testing::Return(std::make_optional(json_test::mock_climate_json)));
    std::unique_ptr<IHttpHandler> mock_http_ptr(mock_http);
    ClimateData climate_data(std::move(mock_http_ptr));

    auto result = climate_data.GetClimateForecast<ForecastDays::One>("San Francisco");
    
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result.value().latitude, json_test::expected_climate.latitude);
    EXPECT_EQ(result.value().longitude, json_test::expected_climate.longitude);
    EXPECT_EQ(result.value().daily.time, json_test::expected_climate.daily.time);
    EXPECT_EQ(result.value().daily.sunrise, json_test::expected_climate.daily.sunrise);
    EXPECT_EQ(result.value().daily.sunset, json_test::expected_climate.daily.sunset);
    for (const auto& param : json_test::expected_climate.daily.data) {
        EXPECT_EQ(result.value().daily.data[param.first], param.second);
    }
    for (const auto& param : json_test::expected_climate.hourly.data) {
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