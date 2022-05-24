#include "../../include/routes/info.h"

void SensorRouter::attach(ESP8266WebServer* server, NTPClient* timeClient) {
    server->on("/info/sensors", HTTP_GET, [server, timeClient]() {
        DynamicJsonDocument res(1024);

        res["time"] = timeClient->getEpochTime();
        res["temperature"] = Control::getRawTemperature();
        res["pressure"] = 7.64;

        uint8_t resLength = measureJsonPretty(res);
        char *buf = (char*) malloc(resLength * sizeof(char));
        
        serializeJsonPretty(res, buf, resLength);
        server->send(200, "application/json", (const char *)buf);

        free(buf);
    });
}