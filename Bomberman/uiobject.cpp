#include "uiobject.h"

namespace UI {
	Object::Object(float x, float y)
		: m_x(x), m_y(y), m_focus(false) {}
	
	Object::~Object() {}

	void Object::setPosition(sf::Vector2f position) {
		m_x = position.x;
		m_y = position.y;
	}

	void Object::setX(float x) {
		m_x = x;
	}

	void Object::setY(float y) {
		m_y = y;
	}

	void Object::setFocus(bool focus) {
		m_focus = focus;
	}

	void Object::connect(sf::Event::EventType type, boost::signal<void()>::slot_function_type slot) {
		m_eventType = type;
		m_signal.connect(slot);
	}

	void Object::emit(sf::Event& event) {
		if(event.type == m_eventType) {
			m_signal();
		}
	}
}