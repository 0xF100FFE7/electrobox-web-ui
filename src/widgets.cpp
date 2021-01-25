/*struct element {
	element_type type;
	
	union {
		void (*button)(void *id, uint32_t sender);
		void (*field)(void *id, String value);
		void (*range)(void *id, int value);
		void (*time)(time_t t);
		void (*frame)(void *sender);
		
		void *callback;
	};

	element (element_type t = E_UNKNOWN, void *cb = nullptr);
};*/
#include "attributes.h"

struct element {
	element_type type;
	
	void create()
	void set_attributes()
}

struct tab {
}

struct tab {
	ui::element element;
	
	ui::messages update(String text)
	{
		return ui::messages("id:") << this << ":text:" << text << ":";
	}
	
	tab() : element(ui::E_TAB) {};
};

struct text {
	ui::element element;
	
	ui::messages update(String text)
	{
		return ui::messages("id:") << this << ":text:" << text << ":";
	}
	
	text() : element(ui::E_TEXT) {};
};

struct box {
	ui::element element;
	
	ui::messages update(String text)
	{
		return ui::messages("id:") << this << ":text:" << text << ":";
	}
	
	box() : element(ui::E_BOX) {};
};

struct field {
	ui::element element;
	String val;
	
	ui::messages update(String v)
	{
		val = v;
		return ui::messages("id:") << this << ":value:" << val << ":";
	}
	
	field(void *callback) : element(ui::E_FIELD, callback) {};
};

/*struct ifield {
	ui::element element;
	int val;
	
	ui::messages update(String v)
	{
		val = v.toInt();
		return ui::messages("id:") << this << ":value:" << v << ":";
	}
	
	ifield(void *callback) : element(ui::E_FIELD, callback) {};
};*/

ui::messages ifield::update(String v)
{
	val = v.toInt();
	return ui::messages("id:") << this << ":value:" << v << ":";
}

ifield::ifield(void *callback) : element(ui::E_FIELD, callback) {};

struct tfield {
	ui::element element;
	int hours, minutes;
		
	ui::messages attributes()
	{
		return ui::messages("value:") << hours_and_minutes_to_str(hours, minutes) << ":";
	}
	
	ui::messages update(String val)
	{	
		//Both are good - old is less complex, but new is much flexible :)
		
		//old parser (unresistant to bad format/errors)
		//hours = val.toInt() % 24;
		//minutes = val.substring(val.indexOf(":") + 1).toInt() % 60;
		
		//new parser (resistant to bad format/errors)
		int i = 0;
		int skip_digits = 2;
		
		for (; i < val.length(); i++) //search hours digits
			if (isDigit(val[i])) {
				hours = val.substring(i).toInt() % 24;
				break;
			}
		
		for (; i < val.length() && skip_digits && isDigit(val[i]); i++, skip_digits--); //skip hour digits

		for (; i < val.length(); i++) //search for minutes digits
			if (isDigit(val[i])) {
				minutes = val.substring(i).toInt() % 60;
				break;
			}
		
		return ui::messages("id:") << this << ":" << attributes();
	}
	
	tfield(void *callback) : element(ui::E_TIME_FIELD, callback) {};
};

struct radio {
	ui::element element;
	
	ui::messages attributes(bool enabled)
	{
		return enabled ? ui::messages("backcolor:green:") : ui::messages("backcolor:#666:");
	}
	
	ui::messages turn(void *old_id)
	{
		return ui::messages("id:") << old_id << ":" << attributes(false) //disable old radio button
			<< "id:" << this << ":" << attributes(true);
	}
	
	radio(void *callback) : element(ui::E_BUTTON, callback) {};
};

struct button {
	ui::element element;
	
	ui::messages disable(bool &enabled)
	{
		enabled = false;
		return ui::messages("id:") << this << ":disabled:true:";
	}
	
	ui::messages enable(bool &enabled)
	{
		enabled = true;
		return ui::messages("id:") << this << ":disabled:false:";	
	}
	
	button(void *callback) : element(ui::E_BUTTON, callback) {};
};

struct switcher {
	ui::element element;
	
	ui::messages attributes(bool enabled)
	{
		return enabled ? ui::messages("backcolor:green:text:&#10003;:") : ui::messages("backcolor:red:text:&#10008;:");
	}
	
	ui::messages turn(bool &enabled)
	{
		enabled = !enabled;
		return ui::messages("id:") << this << ":" << attributes(enabled);
	}
	
	switcher(void *callback) : element(ui::E_BUTTON, callback) {};
};

struct range {
	ui::element element;
	
	ui::messages slide(int &val, int new_val)
	{
		val = new_val;
		return ui::messages("id:") << this << ":value:" << val << ":";
	}
	
	range(void *callback) : element(ui::E_RANGE, callback) {};
};

struct time {
	ui::element element;
	
	time(void *callback) : element(ui::GET_TIME, callback) {};
};

struct dialog {
	ui::element element;
	
	dialog() : element(ui::E_DIALOG) {};
};

frame::frame(void *callback) : element(ui::FRAME, callback) {};
