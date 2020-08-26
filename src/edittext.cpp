#include "edittext.h"
#include "utils.h"

namespace UI {

	EditText::EditText(float x, float y, const sf::Font& font, const sf::Color color, unsigned int size)
		: UI::Object(x, y), m_fullFocus(false), m_text("...", font, size), 
		m_stdColor(color), m_focusColor(color), m_inputLimit(0), 
		m_currentCount(0), m_takeFocus(false), m_filter(EditText::None) {
			
			m_text.setPosition(x, y);
			m_text.setFillColor(color);
			m_text.setOutlineColor(color);
		  m_textSignal = [this] (sf::Keyboard::Key key) {
			  updateText(key);
		  };
		}

	void EditText::draw(sf::RenderTexture& renderTexture) {
		renderTexture.draw(m_text);
	}

	sf::FloatRect EditText::getBoundings() const {
		return m_text.getGlobalBounds();
	}

	void EditText::setFocus(bool focus) {
		if(!m_fullFocus) {
			UI::Object::setFocus(focus);
		}

		if(m_fullFocus) {
			m_text.setFillColor(m_focusColor);
			m_text.setOutlineColor(m_focusColor);
		} else if(m_focus) {
			m_text.setFillColor(m_focusColor);
			m_text.setOutlineColor(m_focusColor);
		} else {
			m_text.setFillColor(m_stdColor);
			m_text.setOutlineColor(m_stdColor);
		}
	}

	void EditText::setFullFocus(bool focus) {
		if(focus) {
			m_text.setString("...");
		}
		m_fullFocus = focus;
		UI::Object::setFocus(focus);
		setFocus(focus);
	}

	void EditText::emit(sf::Event& event) {
		if(m_fullFocus && event.type == sf::Event::KeyPressed) {
			m_textSignal(event.key.code);
		} else {
			UI::Object::emit(event);
		}
	}

	void EditText::updateText(sf::Keyboard::Key key) {
		std::string sKey = Utils::getKeyName(key);
		sf::String currentString = m_text.getString();
		if(currentString == "...") {
			currentString = "";
			m_currentCount = 0;
		}
		if(sKey == "BackSpace") {
			if(currentString.getSize() > 0) {
				currentString.erase(currentString.getSize()-1);
				if(m_inputLimit > 0)
					--m_currentCount;
			}
		} else if(sKey == "Return") {
			setFullFocus(false);
		} else {
			if(m_inputLimit > 0) {
				if(m_currentCount < m_inputLimit) {
					++m_currentCount;
					if(applyFilter(key)) {
						currentString += sKey;
					}
				}
				if(m_currentCount >= m_inputLimit && m_takeFocus) {
					setFullFocus(false);
				}
			} else {
				if(applyFilter(key)) {
					currentString += sKey;
				}
			}
		}
		if(currentString.getSize() <= 0) {
			currentString = "...";
		}
		m_text.setString(currentString);
	}

	std::string EditText::getText() {
		return m_text.getString().toAnsiString();
	}

	void EditText::setStdColor(const sf::Color color) {
		m_stdColor = color;
	}

	void EditText::setFocusColor(const sf::Color color) {
		m_focusColor = color;
	}

	void EditText::resetText() {
		m_text.setString("...");
	}

	void EditText::setInputLimit(unsigned int inputLimit, bool takeFocus) {
		m_takeFocus = takeFocus;
		m_inputLimit = inputLimit;
		m_currentCount = 0;
	}
	
	void EditText::setText(const std::string text) {
		m_text.setString(text);
	}

	void EditText::setKeyFilter(EditText::KeyFilter filter) {
		m_filter = filter;
	}

	bool EditText::applyFilter(sf::Keyboard::Key key) {
		if(m_filter == EditText::None)
			return true;
		if(m_filter == EditText::AlphaNum) {
			if(key >= sf::Keyboard::A && key <= sf::Keyboard::Num9 || 
				key >= sf::Keyboard::Numpad0 && key <= sf::Keyboard::Numpad9)
				return true;
		}
		return false;
	}
}