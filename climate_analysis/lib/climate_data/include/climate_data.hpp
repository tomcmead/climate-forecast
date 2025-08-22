#ifndef CLIMATE_DATA_HPP
#define CLIMATE_DATA_HPP

#include "http_handler.hpp"
#include "climate_url.hpp"
#include <spdlog/spdlog.h>
#include <string>
#include <array>
#include <memory>

class ClimateData {
public:
    explicit ClimateData(std::unique_ptr<IHttpHandler> http);
    void GetClimateForecast(double latitude, double longitude, ForecastDays days=ForecastDays::Seven);

private:
    std::unique_ptr<IHttpHandler> http_handle;
};

#endif // CLIMATE_DATA_HPP