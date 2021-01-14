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





//Повідомлення які будуть відправленні при підключенні
ui::messages connect_messages;





//Наш віджет
namespace shim_widget {
	//Бокс який обгортає наш текст
	ui::box box;
	
	//Наш текстовий елемент звісно
	ui::text text;

	//Функція яка відправляє браузеру повідомлення про створення нових елементів
	void build()
	{
		connect_messages
			<< "type:" << ui::E_BOX << ":id:" << &box << ":parent:body:dir:h:text:Значення нашого шима:"
			<< "type:" << ui::E_TEXT << ":id:" << &text << ":parent:" << &box << ":text:" << analogRead(A0) << ":";
	}
};





//Що робити при підключенні клієнта до серверу
ui::messages ui::on_connect()
{
	connect_messages.clear(); //очищуємо попередні повідомлення
	
	shim_widget::build();
	return connect_messages; //Відправляюмо клієнту повідомлення про створення віджетів
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
		
		(ui::messages("id:") << &shim_widget::text << analogRead(A0)).flush(); //Оновлюємо наш віджет в браузері
		
		ui::ws->cleanupClients();
		old_millis += 1000;
	}
}
