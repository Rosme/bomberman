#include "label.h"

namespace UI {

	Label::Label(const std::string& text, const sf::Font& font, float x, float y, const sf::Color stdColor, const unsigned int textSize)
		: UI::Object(x, y), m_text(text, font, textSize), m_stdColor(stdColor), m_focusColor(stdColor) {
		m_text.setPosition(x, y);
		m_text.setFillColor(stdColor);
		m_text.setOutlineColor(stdColor);
	}

	void Label::draw(sf::RenderTexture& renderTexture) {
		renderTexture.draw(m_text);
	}

	sf::FloatRect Label::getBoundings() const {
		return m_text.getGlobalBounds();
	}

	void Label::setFocus(bool focus) {
		UI::Object::setFocus(focus);
		if(focus) {
			m_text.setFillColor(m_focusColor);
			m_text.setOutlineColor(m_focusColor);
		} else {
			m_text.setFillColor(m_stdColor);
			m_text.setOutlineColor(m_stdColor);
		}
	}

	void Label::setText(const std::string& text) {
		m_text.setString(text);
	}

	void Label::setStdColor(const sf::Color color) {
		m_stdColor = color;
		if(!m_focus) {
			m_text.setFillColor(m_stdColor);
			m_text.setOutlineColor(m_stdColor);
		}
	}

	void Label::setFocusColor(const sf::Color color) {
		m_focusColor = color;
		if(m_focus) {
			m_text.setFillColor(m_focusColor);
			m_text.setOutlineColor(m_focusColor);
		}
	}

	void Label::setTextSize(const unsigned int size) {
		m_text.setCharacterSize(size);
	}

	std::string Label::getText() const {
		return m_text.getString().toAnsiString();
	}
}