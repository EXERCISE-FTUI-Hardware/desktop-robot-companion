#include "server.hpp"

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

namespace Server {
    AsyncWebServer webServer(80);
    DNSServer dnsServer;
}

void Server::initialize() {
    dnsServer.start(53, "*", WiFi.softAPIP());

    webServer.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);

    webServer.begin();
}

void Server::update() {
    dnsServer.processNextRequest();
}