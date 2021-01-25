#include "widgets.h" //server must know about widgets to parse or send them;
#include "server.h"

namespace ui
{
	
	
	void start_server(const char *username, const char *password)
	{
		dns_server.setErrorReplyCode(DNSReplyCode::NoError);
		dns_server.start(53, "*", WiFi.softAPIP());

		basicAuthUsername = username;
		basicAuthPassword = password;

		basicAuth = (username != nullptr && password != nullptr) ? true : false;

		server = new AsyncWebServer(80);
		ws = new AsyncWebSocket("/ws");

		ws->onEvent(ui_event);
		server->addHandler(ws);

		if (basicAuth && WS_AUTHENTICATION)
			ws->setAuthentication(username, password);

		server->on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
			if (basicAuth && !request->authenticate(basicAuthUsername, basicAuthPassword))
				return request->requestAuthentication();

			AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", HTML_INDEX);
			request->send(response);
		});


		server->on("/js/main.js", HTTP_GET, [](AsyncWebServerRequest *request) {
			if (basicAuth && !request->authenticate(basicAuthUsername, basicAuthPassword))
				return request->requestAuthentication();

			AsyncWebServerResponse *response = request->beginResponse_P(200, "application/javascript", JS_MAIN);
			request->send(response);
		});

		server->on("/css/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
			if (basicAuth && !request->authenticate(basicAuthUsername, basicAuthPassword))
				return request->requestAuthentication();

			AsyncWebServerResponse *response = request->beginResponse_P(200, "text/css", CSS_MAIN);
			request->send(response);
		});

		//capative portal
		server->onNotFound([](AsyncWebServerRequest *request) {
			AsyncResponseStream *response = request->beginResponseStream("text/plain");
			response->setCode(302);
			response->addHeader("Location", String("http://") + WiFi.softAPIP().toString());
			request->send(response);
		});
		//server->onNotFound([](AsyncWebServerRequest *request) { request->send(404); });

		server->begin();
	}
}
