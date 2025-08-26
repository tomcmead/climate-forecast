#include "climate_url.hpp"

// @brief Constructs full URL for climate API request.
// @return Constructed URL as string.
const std::string& ClimateUrl::get_url(){
    url = climate_api::climate_url;
    url += "&" + climate_api::forecast_days + "=" + std::to_string(static_cast<int>(forecast_days));
    url += "&" + climate_api::latitude + "=" + std::to_string(latitude);
    url += "&" + climate_api::longitude + "=" + std::to_string(longitude);

    if(is_daily){
        url += "&" + climate_api::daily::daily + "=" + climate_api::daily::sunrise;
        url += "&" + climate_api::daily::daily + "=" + climate_api::daily::sunset;
        for(const auto& param : climate_api::daily::parameters){
            url += "&" + climate_api::daily::daily + "=" + param;
        }
    }
    if(is_hourly){      
        for(const auto& param : climate_api::hourly::parameters){
            url += "&" + climate_api::hourly::hourly + "=" + param;
        }
    }

    return url;
}