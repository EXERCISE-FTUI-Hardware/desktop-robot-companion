#include "website.hpp"

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>

namespace Website {
    class CaptiveRequestHandler : public AsyncWebHandler {
        public:
        bool canHandle(AsyncWebServerRequest *request) const override {
            if (request->url().equals("/")) {
                return false;
            }

            return true;
        }

        void handleRequest(AsyncWebServerRequest *request) {
            AsyncWebServerResponse *response = request->beginResponseStream("text/plain");
            response->setCode(302);
            response->addHeader("Location", String("http://") + apIp.toString());
            request->send(response);
        }
    };
}

namespace Website {
    AsyncWebServer webServer(80);
    DNSServer dnsServer;
}

void Website::initialize() {
    Serial.println(F("Initializing WiFi AP..."));

    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIp, apIp, apMask);
    WiFi.softAP(ssid);

    Serial.print(F("WiFi AP is up.\nAP address is "));
    Serial.println(WiFi.softAPIP());

    Serial.println(F("Initializing DNS server..."));
    dnsServer.start(53, "*", apIp);
    Serial.println(F("DNS server is up."));

    webServer.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);
    webServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        AsyncResponseStream *response = request->beginResponseStream("text/html");
        response->setCode(200);
        response->print(F("<!DOCTYPE html><html><head></head><body><p>hello world!</p></body></html>"));
        request->send(response);
    });

    Serial.println(F("Initializing web server..."));
    webServer.begin();
    Serial.println(F("Web server is up."));
}

void Website::update() {
    dnsServer.processNextRequest();
}