# Climate Forecast
The Climate Forecast will be a Microservice Architecture demonstration to process and forecast climate data with display dashboard.

## Technologies
* **Google Test (GTest)**
* **cURL**
* **RapidJSON**
* **spdlog**
* **Doxygen**
* **Docker**

## How to Run
1. Install and run Docker: https://docs.docker.com/engine/install/
3. git pull https://github.com/tomcmead/climate-forecast.git
4. cd ./climate-forecast
5. docker build -t climate-forecast-image .
6. docker run -e climate-forecast-image