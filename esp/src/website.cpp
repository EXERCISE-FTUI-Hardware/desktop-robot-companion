#include "website.hpp"

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>

class CaptiveRequestHandler : public AsyncWebHandler {
    public:
    bool canHandle(__unused AsyncWebServerRequest *request) const override {
        return true;
    }

    void handleRequest(AsyncWebServerRequest *request) {
        AsyncResponseStream *response = request->beginResponseStream("text/html");
        request->send(response);
    }
};

namespace Website {
    AsyncWebServer webServer(80);
    DNSServer dnsServer;
}

void Website::initialize() {
    Serial.println(F("Initializing WiFi AP..."));

    WiFi.softAPConfig(ip, INADDR_NONE, INADDR_NONE);
    WiFi.softAP(ssid);

    Serial.print(F("AP address is "));
    Serial.println(WiFi.softAPIP());

    dnsServer.start(53, "*", WiFi.softAPIP());

    webServer.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);

    webServer.begin();
}

void Website::update() {
    dnsServer.processNextRequest();
}