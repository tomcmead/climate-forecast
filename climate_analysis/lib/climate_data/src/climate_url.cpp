#include "climate_url.hpp"

const std::string& ClimateUrl::get_url(){
    url = climate_api::url;
    url += "&" + climate_api::forecast_days + std::to_string(static_cast<int>(forecast_days));
    url += "&" + climate_api::latitude + std::to_string(latitude);
    url += "&" + climate_api::longitude + std::to_string(longitude);

    if(is_daily){  
        for(const auto& param : climate_api::daily::parameters){
            url += "&" + param;
        }
    }
    if(is_hourly){      
        for(const auto& param : climate_api::hourly::parameters){
            url += "&" + param;
        }
    }

    return url;
}