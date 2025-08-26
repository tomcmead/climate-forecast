#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include "climate_types.hpp"
#include <rapidjson/document.h>
#include <spdlog/spdlog.h>
#include <optional>
#include <utility>

namespace {
    enum class ParseStatus { SUCCESS, FAILURE };
}

// @class JsonParser
// @brief Class for parsing JSON data from the climate API to ClimateData struct.
class JsonParser {
public:
    JsonParser() = default;
    std::optional<std::pair<double,double>> parse_geocode(const std::string& json_data);
    template<ForecastDays N>
    std::optional<Climate<N>> parse_climate(const std::string& json_data);

private:
    rapidjson::Document doc;
    template<ForecastDays N>
    ParseStatus get_daily(Climate<N>& climate);
    template<ForecastDays N>
    ParseStatus get_hourly(Climate<N>& climate);
};

// @brief Parses climate JSON data and fills the Climate struct.
// @tparam N Number of days for climate data.
// @param json_data JSON string data to parse.
// @return Optional Climate struct with parsed data, or std::nullopt parse fails.
template<ForecastDays N>
std::optional<Climate<N>> JsonParser::parse_climate(const std::string& json_data){
    doc.Parse(json_data.c_str());

    if (doc.HasParseError()) {
        spdlog::error("JsonParser::parse_climate JSON parse error");
        return std::nullopt;
    }

    Climate<N> climate;

    if (!doc.HasMember(climate_api::latitude.c_str()) || !doc.HasMember(climate_api::longitude.c_str())) {
        spdlog::error("JsonParser::parse_climate 'latitude' or 'longitude' field is missing");
        return std::nullopt;
    }

    climate.latitude = doc[climate_api::latitude.c_str()].GetDouble();
    climate.longitude = doc[climate_api::longitude.c_str()].GetDouble();
    
    if(get_daily<N>(climate) == ParseStatus::FAILURE) {
        spdlog::error("JsonParser::parse_climate failed to get daily data");
        return std::nullopt;
    }

    if(get_hourly<N>(climate) == ParseStatus::FAILURE) {
        spdlog::error("JsonParser::parse_climate failed to get hourly data");
        return std::nullopt;
    }

    return climate;
}

// @brief Parse daily climate data from JSON document.
// @tparam N Number of days for climate data.
// @param climate Reference to Climate struct to fill with daily data.
// @return true if parse success, false otherwise.
template<ForecastDays N>
ParseStatus JsonParser::get_daily(Climate<N>& climate){
    const auto& daily = doc[climate_api::daily::daily.c_str()];
    if (!daily.IsObject()) {
        spdlog::error("JsonParser::parse 'daily' field is not JSON object");
        return ParseStatus::FAILURE;
    }

    if (!daily.HasMember(climate_api::time.c_str()) || !daily[climate_api::time.c_str()].IsArray() ||
        !daily.HasMember(climate_api::daily::sunset.c_str()) || !daily[climate_api::daily::sunset.c_str()].IsArray() ||
        !daily.HasMember(climate_api::daily::sunrise.c_str()) || !daily[climate_api::daily::sunrise.c_str()].IsArray()) {
        spdlog::error("JsonParser::parse 'time' or 'sunset' or 'sunrise' field is missing or not an array");
        return ParseStatus::FAILURE;
    }
    const auto& times = daily[climate_api::time.c_str()];
    const auto& sunset = daily[climate_api::daily::sunset.c_str()];
    const auto& sunrise = daily[climate_api::daily::sunrise.c_str()];
    for (rapidjson::SizeType i = 0; i < times.Size(); ++i) {
        climate.daily.time[i] = times[i].GetString();
        climate.daily.sunset[i] = sunset[i].GetString();
        climate.daily.sunrise[i] = sunrise[i].GetString();
    }

    for(const auto& param : climate_api::daily::parameters) {
        if (!daily.HasMember(param.c_str()) || !daily[param.c_str()].IsArray()) {
            spdlog::error("JsonParser::parse '{}' JSON field missing or not an array", param);
            return ParseStatus::FAILURE;
        }
        const auto& values = daily[param.c_str()];
        for (rapidjson::SizeType i = 0; i < values.Size(); ++i) {
            climate.daily.data[param][i] = values[i].GetDouble();
        }
    }

    return ParseStatus::SUCCESS;
}

// @brief Parse hourly climate data from JSON document.
// @tparam N Number of days for climate data.
// @param climate Reference to Climate struct to fill with hourly data.
// @return true if parse success, false otherwise.
template<ForecastDays N>
ParseStatus JsonParser::get_hourly(Climate<N>& climate){
    const auto& hourly = doc[climate_api::hourly::hourly.c_str()];
    if (!hourly.IsObject()) {
        spdlog::error("JsonParser::parse 'hourly' field is not JSON object");
        return ParseStatus::FAILURE;
    }

    if (!hourly.HasMember(climate_api::time.c_str()) || !hourly[climate_api::time.c_str()].IsArray()) {
        spdlog::error("JsonParser::parse 'time' field is missing or not an array");
        return ParseStatus::FAILURE;
    }
    const auto& times = hourly[climate_api::time.c_str()];
    for (rapidjson::SizeType i = 0; i < times.Size(); ++i) {
        climate.hourly.time[i] = times[i].GetString();
    }

    for(const auto& param : climate_api::hourly::parameters) {
        if (!hourly.HasMember(param.c_str()) || !hourly[param.c_str()].IsArray()) {
            spdlog::error("JsonParser::parse '{}' JSON field missing or not an array", param);
            return ParseStatus::FAILURE;
        }
        const auto& values = hourly[param.c_str()];
        for (rapidjson::SizeType i = 0; i < values.Size(); ++i) {
            climate.hourly.data[param][i] = values[i].GetDouble();
        }
    }
    return ParseStatus::SUCCESS;
}

#endif // JSON_PARSER_HPP