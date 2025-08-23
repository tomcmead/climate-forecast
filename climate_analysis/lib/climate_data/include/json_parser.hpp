#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include "climate_types.hpp"
#include <rapidjson/document.h>
#include <spdlog/spdlog.h>
#include <string>
#include <array>
#include <optional>
#include <utility>

namespace {
    constexpr bool SUCCESS = true;
    constexpr bool FAILURE = false;
}

// @class JsonParser
// @brief Class for parsing JSON data from the climate API to ClimateData struct.
class JsonParser {
public:
    JsonParser() = default;
    template<typename T>
    std::optional<std::pair<T,T>> parse_geocode(const std::string& json_data);
    template<typename T, ForecastDays N>
    std::optional<Climate<T, N>> parse_climate(const std::string& json_data);

private:
    rapidjson::Document doc;
    template<typename T, ForecastDays N>
    bool get_daily(Climate<T, N>& climate);
    template<typename T, ForecastDays N>
    bool get_hourly(Climate<T, N>& climate);
};

// @brief Parses geocode JSON data and fills the latitude,longitude pair.
// @tparam T Type of latitude and longitude.
// @param json_data JSON string data to parse.
// @return Optional Pair with parsed data, or std::nullopt parse fails.
template<typename T>
std::optional<std::pair<T,T>> JsonParser::parse_geocode(const std::string& json_data){
    doc.Parse(json_data.c_str());

    if (doc.HasParseError()) {
        spdlog::error("JsonParser::parse_geocode JSON parse error");
        return std::nullopt;
    }

    if (!doc.HasMember("results") || !doc["results"].IsArray()) {
        spdlog::error("JsonParser::parse_geocode 'results' field is missing or not an array");
        return std::nullopt;
    }

    const rapidjson::Value& city = doc["results"][0];
    if(!city.IsObject() || 
       !city.HasMember("latitude") || !city.HasMember("longitude") ||
       !city["latitude"].IsNumber() || !city["longitude"].IsNumber()) {
        spdlog::error("JsonParser::parse_geocode 'latitude' or 'longitude' field is missing");
        return std::nullopt;
    }

    T latitude = static_cast<T>(city["latitude"].GetDouble());
    T longitude = static_cast<T>(city["longitude"].GetDouble());
    return std::make_pair(latitude, longitude);
}

// @brief Parses climate JSON data and fills the Climate struct.
// @tparam T Type climate data.
// @tparam N Number of days for climate data.
// @param json_data JSON string data to parse.
// @return Optional Climate struct with parsed data, or std::nullopt parse fails.
template<typename T, ForecastDays N>
std::optional<Climate<T, N>> JsonParser::parse_climate(const std::string& json_data){
    doc.Parse(json_data.c_str());

    if (doc.HasParseError()) {
        spdlog::error("JsonParser::parse_climate JSON parse error");
        return std::nullopt;
    }

    Climate<T, N> climate;

    if (!doc.HasMember("latitude") || !doc.HasMember("longitude")) {
        spdlog::error("JsonParser::parse_climate 'latitude' or 'longitude' field is missing");
        return std::nullopt;
    }

    climate.latitude = static_cast<T>(doc[climate_api::latitude.c_str()].GetDouble());
    climate.longitude = static_cast<T>(doc[climate_api::longitude.c_str()].GetDouble());
    
    if(get_daily<T, N>(climate) == FAILURE) {
        spdlog::error("JsonParser::parse_climate failed to get daily data");
        return std::nullopt;
    }

    if(get_hourly<T, N>(climate) == FAILURE) {
        spdlog::error("JsonParser::parse_climate failed to get hourly data");
        return std::nullopt;
    }

    return climate;
}

// @brief Parse daily climate data from JSON document.
// @tparam T Type climate data.
// @tparam N Number of days for climate data.
// @param climate Reference to Climate struct to fill with daily data.
// @return true if parse success, false otherwise.
template<typename T, ForecastDays N>
bool JsonParser::get_daily(Climate<T, N>& climate){
    const auto& daily = doc["daily"];
    if (!daily.IsObject()) {
        spdlog::error("JsonParser::parse 'daily' field is not JSON object");
        return FAILURE;
    }

    if (!daily.HasMember("time") || !daily["time"].IsArray() ||
        !daily.HasMember("sunset") || !daily["sunset"].IsArray() ||
        !daily.HasMember("sunrise") || !daily["sunrise"].IsArray()) {
        spdlog::error("JsonParser::parse 'time' or 'sunset' or 'sunrise' field is missing or not an array");
        return FAILURE;
    }
    const auto& times = daily["time"];
    const auto& sunset = daily["sunset"];
    const auto& sunrise = daily["sunrise"];
    for (rapidjson::SizeType i = 0; i < times.Size(); ++i) {
        climate.daily.time[i] = times[i].GetString();
        climate.daily.sunset[i] = sunset[i].GetString();
        climate.daily.sunrise[i] = sunrise[i].GetString();
    }

    for(const auto& param : climate_api::daily::parameters) {
        if (!daily.HasMember(param.c_str()) || !daily[param.c_str()].IsArray()) {
            spdlog::error("JsonParser::parse '{}' JSON field missing or not an array", param);
            return FAILURE;
        }
        const auto& values = daily[param.c_str()];
        for (rapidjson::SizeType i = 0; i < values.Size(); ++i) {
            climate.daily.data[param][i] = values[i].GetDouble();
        }
    }

    return SUCCESS;
}

// @brief Parse hourly climate data from JSON document.
// @tparam T Type climate data.
// @tparam N Number of days for climate data.
// @param climate Reference to Climate struct to fill with hourly data.
// @return true if parse success, false otherwise.
template<typename T, ForecastDays N>
bool JsonParser::get_hourly(Climate<T, N>& climate){
    const auto& hourly = doc["hourly"];
    if (!hourly.IsObject()) {
        spdlog::error("JsonParser::parse 'hourly' field is not JSON object");
        return FAILURE;
    }

    if (!hourly.HasMember("time") || !hourly["time"].IsArray()) {
        spdlog::error("JsonParser::parse 'time' field is missing or not an array");
        return FAILURE;
    }
    const auto& times = hourly["time"];
    for (rapidjson::SizeType i = 0; i < times.Size(); ++i) {
        climate.hourly.time[i] = times[i].GetString();
    }

    for(const auto& param : climate_api::hourly::parameters) {
        if (!hourly.HasMember(param.c_str()) || !hourly[param.c_str()].IsArray()) {
            spdlog::error("JsonParser::parse '{}' JSON field missing or not an array", param);
            return FAILURE;
        }
        const auto& values = hourly[param.c_str()];
        for (rapidjson::SizeType i = 0; i < values.Size(); ++i) {
            climate.hourly.data[param][i] = values[i].GetDouble();
        }
    }
    return SUCCESS;
}

#endif // JSON_PARSER_HPP