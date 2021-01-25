#ifndef UI_SERVER_GUARD
#define UI_SERVER_GUARD

#include "Arduino.h"

#define private public        //This is the hack to access priviate variables of any class 
#define protected public     // This is the hack to access protected variables of any class  
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>

#include "dataIndexHTML.h"
#include "dataStyleCSS.h"
#include "dataMainJS.h"

#define WS_AUTHENTICATION false

namespace ui {
	extern const char* basicAuthUsername;
	extern const char* basicAuthPassword;
	extern bool basicAuth;
	
	extern DNSServer dns_server;
	extern AsyncWebServer* server;
	extern AsyncWebSocket* ws;
}

#endif
