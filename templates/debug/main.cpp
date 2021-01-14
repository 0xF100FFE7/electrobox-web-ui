/******************************************************************************

															Online C++ Compiler.
							 Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

/*#include <iostream>

using namespace std;

uintptr_t str_to_ptr(string str)
{
	size_t idx;
	uintptr_t ptr = 0;
	for(idx = 0; idx <= str.size(); ++idx) {
		ptr <<= 4;
		ptr |= str[idx] - 'a';
	}
	return ptr;
}

string ptr_to_str(uintptr_t ptr)
{
	volatile size_t idx;
	string str(sizeof(uintptr_t) * 2, 'a');
	for(size_t idx = str.size(); idx != (size_t)-1; --idx) {
		str[idx] = 'a' + (ptr & 0xF);
		ptr >>= 4;
	}
	return str;
}

int global = 1337;

int main()
{
		cout << ptr_to_str((uintptr_t)34434) << endl << "Hello World";

		return 0;
}*/

/*#include <iostream>
#include "main.h"

using namespace std;



#ifdef JSON_PTR_IS_SUPPORTED
	#define STR_TO_PTR(val) val;
	#define PTR_TO_STR(ref) ref;
#else
	#define STR_TO_PTR(val) (void *)str_to_ptr(val)
	#define PTR_TO_STR(ref) (string)ptr_to_str((uintptr_t)ref)
#endif

int global = 1337;

namespace flame_ui
{	
	uintptr_t str_to_ptr(string str)
	{
		size_t idx;
		uintptr_t ptr = 0;
		for(idx = 0; idx < str.size(); ++idx) {
			ptr <<= 4;
			ptr |= str[idx] - 'a';
		}
		return ptr;
	}

	string ptr_to_str(uintptr_t ptr)
	{
		size_t idx = (sizeof(uintptr_t) * 2 - 1);
		string str(sizeof(uintptr_t) * 2, 'a'); //Хак для ініціалізації
		for(; idx != (size_t)-1; --idx) {
			str[idx] = 'a' + (ptr & 0xF);
			ptr >>= 4;
		}
		return str;
	}
	
	end_of_message_t eom;
	
	messages& messages::operator , (string b)
	{
		this->buffer += (b + ":");
		return *this;
	}
	
	messages& messages::operator , (element_type b)
	{
		this->buffer += (to_string((int)b) + ":");
		return *this;
	}
	
	messages& messages::operator , (element_type b)
	{
		this->buffer += (to_string((int)b) + ":");
		return *this;
	}
		

	messages& messages::operator = (string b)
	{
		this->buffer = b + ":";
		return *this;
	}

	messages& messages::operator + (element_type b)
	{
		this->buffer += b;
		return *this;
	}
		
	messages& messages::operator | (string b)
	{
		this->buffer += "\n";
		return *this;
	}
	
	string operator + (element& a, string b)
	{
		return (PTR_TO_STR(a.generic) + b);
	}
	
	string operator + (string b, element& a)
	{
		return (b + PTR_TO_STR(a.generic));
	}
	
	string messages::get()
	{
		return buffer;
	}
	
	void messages::clear()
	{
		buffer = "";
	}
}*/
	
/*messages& eom(messages& m)
{
	return (m << "\n");
}*/


/*#include <stdarg.h>
#include <string.h>

flame_ui::element e;

int main()
{
	flame_ui::messages m;
	m = "type", flame_ui::E_BUTTON, "body", e;
	cout << m.get() << endl;
	return 0;
}*/


/*#include <iostream>
#include <string>

using namespace std;

		enum element_type : uint8_t {
			E_HEADER,
			E_TAB,
			
			E_RESERVED,
			
			E_BOX,
			E_TEXT,
			E_BUTTON,
			E_CHECKBOX,
			E_FIELD,
			E_RANGE,
		};

	uintptr_t str_to_ptr(string str)
	{
		size_t idx;
		uintptr_t ptr = 0;
		for(idx = 0; idx < str.size(); ++idx) {
			ptr <<= 4;
			ptr |= str[idx] - 'a';
		}
		return ptr;
	}

	string ptr_to_str(uintptr_t ptr)
	{
		size_t idx = (sizeof(uintptr_t) * 2);
		string str(idx + 1, '_'); //Хак для ініціалізації
		for(; idx != 0; --idx) {
			str[idx] = 'a' + (ptr & 0xF);
			ptr >>= 4;
		}
		return str;
	}
	
	#define STR_TO_PTR(val) (void *)str_to_ptr(val)
	#define PTR_TO_STR(ref) (string)ptr_to_str((uintptr_t)ref)
	
struct lex {
	size_t begin = 0;
	size_t end = 0;
};

string replaceAll(string str, const string &from, const string &to)
{
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != string::npos)
		{
				str.replace(start_pos, from.length(), to);
				start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
		}
		return str;
}

string escape(string str)
{
	return replaceAll(str, ":", "\\:");
}

string unescape(string str)
{
	return replaceAll(str, "\\:", ":");
}

string parse_message(string str, size_t& end)
{
	while (true) {
		if (end >= str.size()) {
			return "";
		} else if (str[end] == ':') {
			end++;
			continue;
		}
		break;
	}

	size_t begin = end;
	
	for (; end < str.size(); end++)
		if (str[end] == ':' && str[end-1] != '\\') break;
	
	return str.substr(begin, end - begin);
}

void some_action(int s)
{
	cout << s << endl;
}

struct button {
	void (*callback)(int state);
};

void parse_messages(string str)
{
	size_t begin = 0;
	string msg;
	
	#define NEXT_MSG msg = parse_message(str, begin)
	switch (stoi(NEXT_MSG))
	{
		case E_BOX:
			NEXT_MSG;
			((button*)STR_TO_PTR(msg))->callback(12);
		break;
		default: break;
	}
}

volatile int global = 1337;

int main()
{
	button btn;
	btn.callback = some_action;
	string str = "3:" + PTR_TO_STR(&btn) + ":" + escape("fuck : you noob :") + ":hello";
	parse_messages(str);
	//cout <<  STR_TO_PTR(PTR_TO_STR(&btn)) << endl << &btn << endl;
	//cout << parse(str, l) << endl << parse(str, l) << endl << parse(str, l) << endl << parse(str, l) << endl << parse(str, l) << endl << parse(str, l);	
	return 0;
}*/
/*	#include <iostream>
	#include <string>
	
	using namespace std;

namespace ui {
	#define STR_TO_PTR(val) (void *)ui::str_to_ptr(val)
	#define PTR_TO_STR(ref) (string)ui::ptr_to_str((uintptr_t)ref)

	uintptr_t str_to_ptr(string str)
	{
		size_t idx;
		uintptr_t ptr = 0;
		for(idx = 0; idx < str.size(); ++idx) {
			ptr <<= 4;
			ptr |= str[idx] - 'a';
		}
		return ptr;
	}

	string ptr_to_str(uintptr_t ptr)
	{
		size_t idx = (sizeof(uintptr_t) * 2);
		string str(idx + 1, '_'); //Хак для ініціалізації
		for(; idx != 0; --idx) {
			str[idx] = 'a' + (ptr & 0xF);
			ptr >>= 4;
		}
		return str;
	}

	enum element_type : uint8_t {
		E_HEADER,
		E_TAB,
		
		E_RESERVED,
			
		E_BOX,
		E_TEXT,
		E_BUTTON,
		E_CHECKBOX,
		E_FIELD,
		E_RANGE,
	};

	enum button_state : uint8_t {
		E_BUTTON_DOWN,
		E_BUTTON_UP,
	};

	enum switcher_state : uint8_t {
		E_SWITCHER_ENABLED,
		E_SWITCHER_DISABLED,
	};

	struct element {
		union {
			void (*button)(void *id);
			void (*field)(void *id, string value);
			void (*range)(void *id, int value);
			
			void *callback;
		};
		element_type type;
		
		element (element_type t = E_TEXT, void *cb = nullptr);
	};
	
	struct end_of_message_t {};
	
	struct messages {
		string buffer;
		size_t begin, end;
		
		messages& operator << (string);
		messages& operator << (void *);
		messages& operator << (int);
		messages& operator << (float);
		messages& operator << (end_of_message_t);
		
		string next();
		void parse();
		void flush();
		void clear();
	};

	messages connect;
	messages stream;

	element::element(element_type t, void *cb)
	{
		type = t;
		callback = cb;
	}
	
	end_of_message_t eom;

	messages& messages::operator << (string b)
	{
		//escape(b);
		this->buffer += b;
		return *this;
	}

	messages& messages::operator << (void* b)
	{
		this->buffer += PTR_TO_STR(b);
		return *this;
	}
		
	messages& messages::operator << (int b)
	{
		this->buffer += to_string(b);
		return *this;
	}
		
	messages& messages::operator << (float b)
	{
		this->buffer += to_string(b);
		return *this;
	}
		
	messages& messages::operator << (end_of_message_t)
	{
		return (*this << "\n");
	}

	string messages::next()
	{
		while (true) {
			if (end >= buffer.length()) {
				return "";
			} else if (buffer[end] == ':') {
				end++;
				continue;
			}
			break;
		}

		begin = end;
		
		for (; end < buffer.length(); end++)
			if (buffer[end] == ':' && buffer[end-1] != '\\') break;
		
		return buffer.substr(begin, end - begin);
	}

	void messages::parse()
	{
		begin = end = 0;
		string msg;
		element e;
		
		#define NEXT_MSG (msg = next())
		while (NEXT_MSG != "") {
			cout << STR_TO_PTR(msg) << endl;
			//exit(1);
			e = *(element*)STR_TO_PTR(msg);
			switch (e.type) {
			case E_BUTTON:
				e.button(&e);
				break;
				
			case E_FIELD:
				e.field(&e, NEXT_MSG);
				break;
				
			case E_RANGE:
				e.range(&e, stoi(NEXT_MSG));
				break;
			default:
				NEXT_MSG;
				break;
			}
		}
	}

	void messages::flush()
	{
		cout << stream.buffer << endl;
		stream.buffer = "";
	}
	
	void messages::clear()
	{
		stream.buffer = "";
	}
}	

	void some_action(void *id)
	{
		static int i = 0;
		ui::stream << "type:" << ui::E_TEXT << ":id:FUCKING_SUCCESS:parent:body:text:" << i++;
		ui::stream.flush();
	}

	struct weekly_schedule {
		ui::element parent;
		
		struct colon {
			ui::element e;
			colon() : e(ui::E_BOX) {};
		} cols[4];

		ui::element desc[4];
		ui::element days[7];

		struct field {
			ui::element e;
			long unsigned time;
			field() : e(ui::E_FIELD, (void*)field_act) {};
		} froms[7], tos[7];
		
		struct switcher {
			ui::element e;
			bool enabled;
			switcher() : e(ui::E_BUTTON, (void*)switcher_act), enabled(false) {};
		} switchers[7];
		
		static void field_act(void *id, string val)
		{
			field *f = (field *)id;
			f->time = stoi(val);
		}
		
		static void switcher_act(void *id)
		{
			switcher *s = (switcher*)id;
			s->enabled = !s->enabled;
			if (s->enabled)
				ui::stream << "id:" << id << ":color:red:";
			else
				ui::stream << "id:";
			ui::stream.flush();
		}
		
		void init(string id)
		{
			static const char* col_names[] = {"Дні тижня", "Старт зарядки", "Стоп зарядки", "Включити"};
			static const char* day_names[] = {"Понеділок", "Вівторок", "Середа", "Четверг", "П'ятниця", "Суботта", "Неділя"};
			parent.type = ui::E_BOX;
			ui::connect << "type:" << parent.type << ":id:" << id << ":parent:body:dir:h:text:Тижневий розклад:";
			for (int i = 0; i < 4; i++)
				ui::connect
					<< "type:" << cols[i].e.type << ":id:" << &cols[i] << ":parent:" << &parent << ":"
					<< "type:" << desc[i].type << ":id:" << &desc[i] << ":parent:" << &cols[i] << ":text:" << col_names[i] << ":";
			
			for (int row = 0; row < 7; row++)
				ui::connect 
					<< "type:" << days[row].type << ":id:" << &days[row] << ":parent:" << &cols[0] << ":text:" << day_names[row] << ":"
					<< "type:" << froms[row].e.type << ":id:" << &froms[row] << ":parent:" << &cols[1] << ":"
					<< "type:" << tos[row].e.type << ":id:" << &tos[row] << ":parent:" << &cols[2] << ":"
					<< "type:" << switchers[row].e.type << ":id:" << &switchers[row] << ":parent:" << &cols[3] << ":";
		}
		
		
		weekly_schedule(string str)
		{
			init(str);
		}
		
		weekly_schedule(void *id)
		{
			init(ui::ptr_to_str((uintptr_t)id));
		}
		
		weekly_schedule()
		{
			init("body");
		}
	};

	ui::element btn(ui::E_BUTTON, (void*)some_action);
int main()
{
	//ui::connect << PTR_TO_STR(&btn) << ":";
	weekly_schedule w;
	cout << ui::connect.buffer << endl;
	//ui::connect.parse();
	//cout <<  STR_TO_PTR(PTR_TO_STR(&btn)) << endl << &btn << endl;
	//cout << parse(str, l) << endl << parse(str, l) << endl << parse(str, l) << endl << parse(str, l) << endl << parse(str, l) << endl << parse(str, l);	
	return 0;
}*/

/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include <time.h>

struct tm *u;
char *f;

char * settime(struct tm *u)
{
	char s[80];
	char *tmp;
	int length = strftime(s, 80, "%d.%m.%Y %H:%M:%S ", u);
	switch (u->tm_wday)
	{
		case 1: strcpy(s + length, " понедельник"); break;
		case 2: strcpy(s + length, " вторник");     break;
		case 3: strcpy(s + length, " среда");       break;
		case 4: strcpy(s + length, " четверг");     break;
		case 5: strcpy(s + length, " пятница");     break;
		case 6: strcpy(s + length, " суббота");     break;
		case 0: strcpy(s + length, " воскресенье"); break;
	}
	tmp = (char*)malloc(80);
	strcpy(tmp, s);
	return(tmp);
}

int schedule[7][2][2] = {
	{{15, 0},	{20, 0}}, //ponedilok
	{{17, 0},	{20, 0}}, //vivtorok
	{{20, 0},	{20, 0}}, //sereda
	{{22, 0},	{20, 0}}, //chetverg
	{{10, 0},	{20, 0}}, //piatnicia
	{{2, 0},	{20, 0}}, //subota
	{{13, 0},	{20, 0}}, //nedila
}; 

bool enabled[7] = {
	true,
	true,
	true,
	true,
	true,
	true,
	true
};

struct day_time_range
{
	int begin, end;
	bool enabled;
};

//Base on week day we get the
bool try_scheduled_charge()
{
	int cur_day = (u->tm_wday - 1) % 7;
	bool cur_enabled = enabled[cur_day];
	int cur_time = u->tm_hour * 60 + u->tm_min;
	int cur_day_begin_time = schedule[cur_day][0][0] * 60 + schedule[cur_day][0][1]; //Full time in minutes
	int cur_day_end_time = schedule[cur_day][1][0] * 60 + schedule[cur_day][1][1];
	
	int prev_day = (cur_day - 1) % 7;
	bool prev_enabled = enabled[prev_day];
	int prev_day_begin_time = schedule[prev_day][0][0] * 60 + schedule[prev_day][0][1];
	int prev_day_end_time = schedule[prev_day][1][0] * 60 + schedule[prev_day][1][1];
	
	if (
		cur_enabled && (cur_time >= cur_day_begin_time && cur_time < cur_day_end_time ||
			cur_day_begin_time >= cur_day_end_time && cur_time >= cur_day_begin_time) ||
		
		prev_enabled && (prev_day_begin_time >= prev_day_end_time && cur_time < prev_day_end_time)
	)
		return true;
	return false;
}

int main()
{
	auto initial_clock = clock();
	auto last_clock = clock();
	
	while (true) {
		if (clock() > last_clock + 100) {
			auto multiplier = (clock() - initial_clock) * 10;
			time_t timer = time(NULL) + multiplier;
			u = localtime(&timer);
			f = settime(u);
			printf("%ld соответствует ", timer);
			puts(f);
			printf("try_scheduled_charge() = %s\n", try_scheduled_charge() ? "true" : "false");
			fflush(stdout);
			free(f);
			last_clock += 100;
		}
		Sleep(0);
	}
		
	return 0;
}*/
/*#include <stdio.h>

char a[80] = "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww";
char b[80] = "lorem_ipsum_dolor_sit_amet,_consectetur_adipiscing_elit,_sed_do_eiusmod_tempor.";

struct window {
	bool exceed = false;
	int max_data_size = 80;
	int data_size = 0;
	
	int begin, len;
	char *data;
	
	void put(char c)
	{
		if (data_size == max_data_size)
			exceed = true;
			
		if (data_size >= begin + len)
			begin++;
			
		data[data_size++ % max_data_size] = c;
	}
	
	void dump()
	{
		int end = begin + len;
		if (end >= data_size && !exceed) end = data_size;
		for (int i = begin; i < end; i++)
			putchar(a[i % max_data_size]);
		putchar('\n');
	}
	
	window(char *d, int l)
	{
		begin = 0;
		len = l < max_data_size ? l : max_data_size;
		data = d;
	};
} w(a, 80);

int main()
{	
	for (int j = 0; j < 1; j++)
	{
		for (int i = 0; i < 81; i++) {
			w.put(b[i % 80]);
			printf("%i\n", w.data_size);
		}
	}
	w.dump();
	return 0;
}*/

/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include <time.h>

struct tm *u;
char *f;

char * settime(struct tm *u)
{
	char s[80];
	char *tmp;
	int length = strftime(s, 80, "%d.%m.%Y %H:%M:%S ", u);
	switch (u->tm_wday)
	{
		case 1: strcpy(s + length, " понедельник"); break;
		case 2: strcpy(s + length, " вторник");     break;
		case 3: strcpy(s + length, " среда");       break;
		case 4: strcpy(s + length, " четверг");     break;
		case 5: strcpy(s + length, " пятница");     break;
		case 6: strcpy(s + length, " суббота");     break;
		case 0: strcpy(s + length, " воскресенье"); break;
	}
	tmp = (char*)malloc(80);
	strcpy(tmp, s);
	return(tmp);
}

int schedule[7][2][2] = {
	{{15, 0},	{20, 0}}, //ponedilok
	{{17, 0},	{20, 0}}, //vivtorok
	{{20, 0},	{20, 0}}, //sereda
	{{22, 0},	{20, 0}}, //chetverg
	{{10, 0},	{20, 0}}, //piatnicia
	{{2, 0},	{20, 0}}, //subota
	{{13, 0},	{20, 0}}, //nedila
}; 

bool enabled[7] = {
	true,
	true,
	false,
	true,
	true,
	true,
	true
};

struct day_time_range
{
	int begin, end;
	bool enabled;
};

//Base on week day we get the
bool try_scheduled_charge()
{
	int cur_day = (u->tm_wday - 1) % 7;
	bool cur_enabled = enabled[cur_day];
	if (!cur_enabled)
		return false; //no blocking today
		
	int cur_time = u->tm_hour * 60 + u->tm_min;
	int cur_day_begin_time = schedule[cur_day][0][0] * 60 + schedule[cur_day][0][1]; //Full time in minutes
	int cur_day_end_time = schedule[cur_day][1][0] * 60 + schedule[cur_day][1][1];
	
	int prev_day = (cur_day - 1) % 7;
	bool prev_enabled = enabled[prev_day];
	int prev_day_begin_time = schedule[prev_day][0][0] * 60 + schedule[prev_day][0][1];
	int prev_day_end_time = schedule[prev_day][1][0] * 60 + schedule[prev_day][1][1];
	
		if (prev_enabled && prev_day_begin_time >= prev_day_end_time && cur_time < prev_day_end_time) {
			return false;
		} else if (cur_day_begin_time < cur_day_end_time) {
			if (cur_time >= cur_day_begin_time && cur_time < cur_day_end_time)
				return false;
		} else if (cur_time >= cur_day_begin_time) {
				return false;
		}
			return true;
}

int main()
{
	auto initial_clock = clock();
	auto last_clock = clock();
	
	while (true) {
		if (clock() > last_clock + 100) {
			auto multiplier = (clock() - initial_clock) * 10;
			time_t timer = time(NULL) + multiplier;
			u = localtime(&timer);
			f = settime(u);
			printf("%ld соответствует ", timer);
			puts(f);
			printf("blocking = %s\n", try_scheduled_charge() ? "true" : "false");
			fflush(stdout);
			free(f);
			last_clock += 100;
		}
		Sleep(0);
	}
		
	return 0;
}*/

/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include <time.h>

struct all_time_statistics {
	struct kwt_range {
		time_t from;
		time_t offset;
		
		size_t delta;
		size_t kwt;

		//kwt_range_statistics(time_t f, time_t o) : from(f), offset(o) {};
	};
	
	size_t total_kwt;

	kwt_range
		ranges[5];
		
	all_time_statistics(time_t now) : total_kwt(0) {
		ranges[0] = {now, 60 * 60, 0, 0}; //hour
		ranges[1] = {now, 60 * 60 * 24, 0, 0}; //day
		ranges[2] = {now, 60 * 60 * 24 * 7, 0, 0}; //week
		ranges[3] = {now, 60 * 60 * 24 * 7 * 4, 0, 0}; //month
		ranges[4] = {now, 60 * 60 * 24 * 7 * 4 * 12, 0, 0}; //year
	}

	void update(time_t now, size_t kwt) {
		total_kwt += kwt;
		
		for (int i = 0; i < 5; i++)
			if (now > ranges[i].from + ranges[i].offset) {
				ranges[i].from = now;
				ranges[i].delta = ranges[i].kwt;
				ranges[i].kwt = 0;
			} else {
				ranges[i].kwt += kwt;
			}
	}
} stat(0);

struct tm *u;
char *f;

char * settime(struct tm *u)
{
	char s[80];
	char *tmp;
	int length = strftime(s, 80, "%d.%m.%Y %H:%M:%S ", u);
	switch (u->tm_wday)
	{
		case 1: strcpy(s + length, " понедельник"); break;
		case 2: strcpy(s + length, " вторник");     break;
		case 3: strcpy(s + length, " среда");       break;
		case 4: strcpy(s + length, " четверг");     break;
		case 5: strcpy(s + length, " пятница");     break;
		case 6: strcpy(s + length, " суббота");     break;
		case 0: strcpy(s + length, " воскресенье"); break;
	}
	tmp = (char*)malloc(80);
	strcpy(tmp, s);
	return(tmp);
}

int schedule[7][2][2] = {
	{{15, 0},	{20, 0}}, //ponedilok
	{{17, 0},	{20, 0}}, //vivtorok
	{{20, 0},	{20, 0}}, //sereda
	{{22, 0},	{20, 0}}, //chetverg
	{{10, 0},	{20, 0}}, //piatnicia
	{{2, 0},	{20, 0}}, //subota
	{{13, 0},	{20, 0}}, //nedila
}; 

bool enabled[7] = {
	true,
	true,
	false,
	true,
	true,
	true,
	true
};

int main()
{
	auto initial_clock = clock();
	auto last_clock = clock();
	
	while (true) {
		if (clock() > last_clock + 100) {
			auto multiplier = (clock() - initial_clock) * 10;
			time_t timer = time(NULL) + multiplier;
			u = localtime(&timer);
			f = settime(u);
			printf("%ld соответствует ", timer);
			puts(f);
			stat.update(timer, rand()%3);
			printf("hour: %ld\n", stat.ranges[0].delta);
			printf("day: %ld\n", stat.ranges[1].delta);
			printf("week %s: %ld\n", f, stat.ranges[2].delta);
			printf("month: %ld\n", stat.ranges[3].delta);
			printf("year: %ld\n", stat.ranges[4].delta);
			fflush(stdout);
			free(f);
			last_clock += 100;
		}
		Sleep(0);
	}
		
	return 0;
}
*/

/*#include <iostream>
#include <string>
	
using namespace std;

	uintptr_t str_to_ptr(string str)
	{
		size_t idx;
		uintptr_t ptr = 0;
		//cout << str.length() << endl;
		for(idx = str.length(); idx > 0; --idx) {
			ptr <<= 4;
			ptr |= str[idx - 1] - 'a';
			//cout << str[idx] - 'a' << " ";
		}
		//cout << endl;
		return ptr;
	}

	//Переводить вказівникі в строки з базою 16 в виключно буквенній інтерпретації.
	string ptr_to_str(uintptr_t ptr)
	{
		//size_t idx = (sizeof(uintptr_t) * 2 - 1);
		string str;//((uintptr_t)1 << idx, BIN); //Хак для ініціалізації
		do {
			str += 'a' + (ptr & 0xF);
			ptr >>= 4;
		} while (ptr > 0);
		return str;
	}

volatile int global = 1337;

int main()
{
	cout << ptr_to_str((uintptr_t)&global) << endl;
	cout << hex << (uintptr_t)str_to_ptr("abaeae") << endl;
	cout << hex << (uintptr_t)&global << endl;
	cout << dec << *(int*)str_to_ptr(ptr_to_str((uintptr_t)&global)) << endl;
	cout << endl;
}*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include <time.h>

struct all_time_statistics {
	struct kwt_range {
		time_t from;
		time_t offset;
		
		size_t delta;
		size_t kwt;

		//kwt_range_statistics(time_t f, time_t o) : from(f), offset(o) {};
	};
	
	size_t total_kwt;
		
	kwt_range ranges[5] = {
		{0, 60 * 60, 0, 0}, //hour
		{0, 60 * 60 * 24, 0, 0}, //day
		{0, 60 * 60 * 24 * 7, 0, 0}, //week
		{0, 60 * 60 * 24 * 7 * 4, 0, 0}, //month
		{0, 60 * 60 * 24 * 7 * 4 * 12, 0, 0}, //year
	};

	void update(time_t now, size_t kwt) {
		total_kwt += kwt;
		
		for (int i = 0; i < 5; i++)
			if (now > ranges[i].from + ranges[i].offset) {
				ranges[i].from = now;
				ranges[i].delta = ranges[i].kwt + kwt;
				ranges[i].kwt = 0;
			} else {
				ranges[i].kwt += kwt;
			}
	}
} stat;

struct tm *u;
char *f;

char * settime(struct tm *u)
{
	char s[80];
	char *tmp;
	int length = strftime(s, 80, "%d.%m.%Y %H:%M:%S ", u);
	switch (u->tm_wday)
	{
		case 1: strcpy(s + length, " понедельник"); break;
		case 2: strcpy(s + length, " вторник");     break;
		case 3: strcpy(s + length, " среда");       break;
		case 4: strcpy(s + length, " четверг");     break;
		case 5: strcpy(s + length, " пятница");     break;
		case 6: strcpy(s + length, " суббота");     break;
		case 0: strcpy(s + length, " воскресенье"); break;
	}
	tmp = (char*)malloc(80);
	strcpy(tmp, s);
	return(tmp);
}

int main()
{
	auto initial_clock = clock();
	auto last_clock = clock();
	int cycle = 0;
	
	stat.update(time(NULL), 0);
	while (true) {
		if (clock() > last_clock + 100) {
			auto multiplier = (clock() - initial_clock) * (cycle % 10 ? 10 : 10);
			time_t timer = time(NULL) + multiplier;
			u = localtime(&timer);
			f = settime(u);
			puts(f);
			stat.update(timer, rand()%3);
			printf("(hour: %ld) (hour: %ld)\n", stat.ranges[0].delta, stat.ranges[0].kwt);
			printf("(day: %ld) (day: %ld)\n", stat.ranges[1].delta, stat.ranges[1].kwt);
			printf("(week: %ld) (week: %ld)\n", stat.ranges[2].delta, stat.ranges[2].kwt);
			printf("(month: %ld) (month: %ld)\n", stat.ranges[3].delta, stat.ranges[3].kwt);
			printf("(year: %ld) (year: %ld)\n\n", stat.ranges[4].delta, stat.ranges[4].kwt);
			fflush(stdout);
			free(f);
			last_clock += 100;
			cycle++;
		}
		Sleep(0);
	}
		
	return 0;
}
