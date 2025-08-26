#include "json_parser.hpp"

// @brief Parses geocode JSON data and fills the latitude,longitude pair.
// @param json_data JSON string data to parse.
// @return Optional Pair with parsed data, or std::nullopt parse fails.
std::optional<std::pair<double,double>> JsonParser::parse_geocode(const std::string& json_data){
    doc.Parse(json_data.c_str());

    if (doc.HasParseError()) {
        spdlog::error("JsonParser::parse_geocode JSON parse error");
        return std::nullopt;
    }

    if (!doc.HasMember(climate_api::results.c_str()) || !doc[climate_api::results.c_str()].IsArray()) {
        spdlog::error("JsonParser::parse_geocode 'results' field is missing or not an array");
        return std::nullopt;
    }

    const rapidjson::Value& city = doc[climate_api::results.c_str()][0];
    if(!city.IsObject() || 
       !city.HasMember(climate_api::latitude.c_str()) || !city.HasMember(climate_api::longitude.c_str()) ||
       !city[climate_api::latitude.c_str()].IsNumber() || !city[climate_api::longitude.c_str()].IsNumber()) {
        spdlog::error("JsonParser::parse_geocode 'latitude' or 'longitude' field is missing");
        return std::nullopt;
    }

    double latitude = city[climate_api::latitude.c_str()].GetDouble();
    double longitude = city[climate_api::longitude.c_str()].GetDouble();
    return std::make_pair(latitude, longitude);
}