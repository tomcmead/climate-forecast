#include <iostream>
#include "climate_data.hpp"
#include "curl_handler.hpp"

int main() {
    ClimateData climate_data(std::make_unique<CurlHandler>());
    auto data = climate_data.GetClimateForecast<ForecastDays::Three>("New York");
    if (!data.has_value()) {
        return 1;
    }

    std::cout << "Latitude: " << data.value().latitude << ", Longitude: " << data.value().longitude << "\n\n";

    // Daily Data   
    for(size_t i = 0; i < data.value().daily.time.size(); ++i) {
        std::cout << "Day: " << data.value().daily.time[i] 
                    << "\nSunrise: " << data.value().daily.sunrise[i] 
                    << "\nSunset: " << data.value().daily.sunset[i] << std::endl;
        for(const auto& param : data.value().daily.data) {
            std::cout << param.first << ": " << param.second[i] << std::endl;
        }
        std::cout << "------------------------\n";
    }

    // Hourly Data
    for(size_t i = 0; i < data.value().hourly.time.size(); ++i) {
        std::cout << "Hour: " << data.value().hourly.time[i] << std::endl;
        for(const auto& param : data.value().hourly.data) {
            std::cout << param.first << ": " << param.second[i] << std::endl;
        }
        std::cout << "------------------------\n";
    }
    return 0;
}