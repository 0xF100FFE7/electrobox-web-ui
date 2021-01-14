#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include <flame_ui.h>

namespace network {
	char SSID[40] = "ElektroBOX";
	char PASS[40] = "";
	IPAddress ip(7, 7, 7, 7);
	IPAddress gateway (7, 7, 7, 1);
	IPAddress subnet (255, 255, 255, 0);
}

ui::messages ui::on_connect()
{
	//При підключенні відправляються повідомлення які поверне ця функція.
	
	//type 3 - це бокс
	//type 4 - тескт
	//body - головний parent елемент нашого браузера
	//dir:h - піделементи слідують одне за одним по горизонталі
	
	return ui::messages(String("") +
		"type:3:" + "id:some_box:" + "parent:body:" + "dir:h:" + "text:Значення нашого шима:" +
		"type:4:" + "id:some_text:" + "parent:some_box:" + "text:" + analogRead(A0) + ":"
	);
};

void setup()
{
	WiFi.mode(WIFI_AP);
	WiFi.softAPConfig(network::ip, network::gateway, network::subnet);
	WiFi.softAP(network::SSID, network::PASS);
	
	ui::init_server(); //Ініціалізація нашого web ui
}

void loop()
{
	static unsigned long old_millis = 0;
	if (millis() >= old_millis + 1000) { //Умова виконується раз в секунду
		
		//Для оновлення елементу потрібно лише відправити його ID і атрібути.
		//Flush відправляє всі повідомлення і очищує буфер messages.
		ui::messages(String("") + "id:some_text:" + "text:" + analogRead(A0) + ":").flush();
		
		ui::ws->cleanupClients();
		old_millis += 1000;
	}
}
