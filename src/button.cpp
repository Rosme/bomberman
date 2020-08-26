#include "button.h"

namespace UI {

	/* Ctor
	 * Focus color is assign the standard one. Unless it gets change, on focus the color will never change
	 **/
	Button::Button(const std::string& text, const sf::Font& font, float x, float y, 
		const sf::Color stdTextColor, 
		const sf::Color stdFillColor, 
		const sf::Color stdOutlineColor, 
		const unsigned int textSize)
		: UI::Object(x, y), 
		m_text(text, font, textSize), 
		m_stdTextColor(stdTextColor), 
		m_focusTextColor(stdTextColor),
		m_stdFillColor(stdFillColor),
		m_focusFillColor(stdFillColor),
		m_stdOutlineColor(stdOutlineColor),
		m_focusOutlineColor(stdOutlineColor) {
			/* Creating the button by setting the shape of the button, and filling the text within */
			m_shape.setFillColor(stdFillColor);
			m_shape.setOutlineColor(stdOutlineColor);
			m_shape.setOutlineThickness(1.0);
			m_shape.setPosition(x, y);
			m_shape.setSize(sf::Vector2f(m_text.getGlobalBounds().width+10, m_text.getGlobalBounds().height+10));
			m_text.setFillColor(stdTextColor);
			m_text.setOutlineColor(stdTextColor);
			m_text.setPosition(x+5, y);
		}

	void Button::draw(sf::RenderTexture& renderTexture) {
		renderTexture.draw(m_shape);
		renderTexture.draw(m_text);
	}

	sf::FloatRect Button::getBoundings() const {
		return m_shape.getGlobalBounds();
	}

	void Button::setFocus(bool focus) {
		UI::Object::setFocus(focus);
		if(focus) {
			m_shape.setFillColor(m_focusFillColor);
			m_shape.setOutlineColor(m_focusOutlineColor);
			m_text.setFillColor(m_focusTextColor);
			m_text.setOutlineColor(m_focusTextColor);
		} else {
			m_shape.setFillColor(m_stdFillColor);
			m_shape.setOutlineColor(m_stdOutlineColor);
			m_text.setFillColor(m_stdTextColor);
			m_text.setOutlineColor(m_stdTextColor);
		}
	}

	void Button::setStdTextColor(const sf::Color color) {
		m_stdTextColor = color;
		if(!m_focus) {
			m_text.setFillColor(m_stdTextColor);
			m_text.setOutlineColor(m_stdTextColor);
		}
	}

	void Button::setFocusTextColor(const sf::Color color) {
		m_focusTextColor = color;
		if(m_focus) {
			m_text.setFillColor(m_focusTextColor);
			m_text.setOutlineColor(m_focusTextColor);
		}
	}

	void Button::setStdFillColor(const sf::Color color) {
		m_stdFillColor = color;
		if(!m_focus) {
			m_shape.setFillColor(color);
		}
	}

	void Button::setFocusFillColor(const sf::Color color) {
		m_focusFillColor = color;
		if(m_focus) {
			m_shape.setFillColor(color);
		}
	}

	void Button::setStdOutlineColor(const sf::Color color) {
		m_stdOutlineColor = color;
		if(!m_focus) {
			m_shape.setOutlineColor(color);
		}
	}

	void Button::setFocusOutlineColor(const sf::Color color) {
		m_focusOutlineColor = color;
		if(m_focus) {
			m_shape.setOutlineColor(color);
		}
	}

	void Button::setTextSize(const unsigned int size) {
		m_text.setCharacterSize(size);
		m_shape.setSize(sf::Vector2f(m_text.getGlobalBounds().width+10, m_text.getGlobalBounds().height+10));
	}
}