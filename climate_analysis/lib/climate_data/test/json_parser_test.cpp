#include <gtest/gtest.h>
#include "json_test_data.hpp"
#include "json_parser.hpp"


TEST(JsonParserTest, ParseValidClimateDouble_ValidClimateData){
    JsonParser parser;

    auto climate_data = parser.parse_climate<double, ForecastDays::One>(json_test::mock_climate_json);

    ASSERT_TRUE(climate_data.has_value());
    EXPECT_EQ(climate_data.value().latitude, json_test::expected_climate.latitude);
    EXPECT_EQ(climate_data.value().longitude, json_test::expected_climate.longitude);
    EXPECT_EQ(climate_data.value().daily.time, json_test::expected_climate.daily.time);
    EXPECT_EQ(climate_data.value().daily.sunrise, json_test::expected_climate.daily.sunrise);
    EXPECT_EQ(climate_data.value().daily.sunset, json_test::expected_climate.daily.sunset);
    for (const auto& param : json_test::expected_climate.daily.data) {
        EXPECT_EQ(climate_data.value().daily.data[param.first], param.second);
    }
    for (const auto& param : json_test::expected_climate.hourly.data) {
        EXPECT_EQ(climate_data.value().hourly.data[param.first], param.second);
    }
}

TEST(JsonParserTest, ParseValidClimateInt_ValidClimateData){
    JsonParser parser;

    auto climate_data = parser.parse_climate<int, ForecastDays::One>(json_test::mock_climate_json);

    ASSERT_TRUE(climate_data.has_value());
    EXPECT_EQ(climate_data.value().latitude, static_cast<int>(json_test::expected_climate.latitude));
    EXPECT_EQ(climate_data.value().longitude, static_cast<int>(json_test::expected_climate.longitude));
}

TEST(JsonParserTest, ParseInvalidJson_Nullopt){
    JsonParser parser;
    const std::string invalid_json_data = json_test::mock_climate_json + "}";

    auto climate_data = parser.parse_climate<int, ForecastDays::One>(invalid_json_data);

    ASSERT_FALSE(climate_data.has_value());
}

TEST(JsonParserTest, ParseClimateMissingFields_Nullopt){
    JsonParser parser;
    const std::string missing_fields_json = R"({
        "latitude": 37.77,
        "daily": {
            "time": ["2023-10-01"],
            "sunrise": ["06:30"],
            "sunset": ["18:30"]
        }
    })";

    auto climate_data = parser.parse_climate<double, ForecastDays::One>(missing_fields_json);

    ASSERT_FALSE(climate_data.has_value());
}

TEST(JsonParserTest, ParseGeocodeValidJson_ValidCoordinates){
    JsonParser parser;

    auto coordinates = parser.parse_geocode<double>(json_test::mock_city_json);

    ASSERT_TRUE(coordinates.has_value());
    EXPECT_EQ(coordinates.value().first, json_test::expected_coordinates.first);
    EXPECT_EQ(coordinates.value().second, json_test::expected_coordinates.second);
}

TEST(JsonParserTest, ParseGeocodeInvalidJson_Nullopt){
    JsonParser parser;

    auto coordinates = parser.parse_geocode<double>(R"({"lat": 37.77, "lon": -122.41})");

    ASSERT_FALSE(coordinates.has_value());
}