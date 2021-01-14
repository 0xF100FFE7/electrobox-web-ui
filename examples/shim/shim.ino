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





//Помічні структури для зручності.
struct box {
	ui::element element;	
	box() : element(ui::E_BOX) {};
};

struct text {
	ui::element element; //Елемент, адрес якого буде переданий у браузер як ID (this)
	
	//Функція яка відправляє повідомлення про оновлення елементу в браузер. Потрібно відправити id і атрибут text, звісно і сам текст
	ui::messages update(String text)
	{
		return ui::messages("id:") << this << ":text:" << text << ":";
	}

	text() : element(ui::E_TEXT) {};
};





//Наш віджет
namespace shim_widget {
	//Бокс який обгортає наш текст
	box parent;
	
	//Наш текстовий елемент звісно
	text text;

	//Функція яка відправляє браузеру повідомлення про створення нових елементів
	void build()
	{
		connect_messages
			<< "type:" << ui::E_BOX << ":id:" << &parent << ":parent:body:dir:h:text:Значення нашого шима:"
			<< "type:" << ui::E_TEXT << ":id:" << &text << ":parent:" << &parent << ":text:" << analogRead(A0) << ":";
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
		
		shim_widget::text.update(String(analogRead(A0))).flush(); //Оновлюємо наш віджет в браузері
		
		ui::ws->cleanupClients();
		old_millis += 1000;
	}
}
