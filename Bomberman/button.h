#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include "uiobject.h"

class UIFactory;

namespace UI {

	class Button : public UI::Object {
		friend class UIFactory;
	private:
		sf::Text m_text;
		sf::RectangleShape m_shape;
		sf::Color m_stdTextColor;
		sf::Color m_focusTextColor;
		sf::Color m_stdFillColor;
		sf::Color m_focusFillColor;
		sf::Color m_stdOutlineColor;
		sf::Color m_focusOutlineColor;
		unsigned int m_width;
		unsigned int m_height;

		/* Ctor */
		Button(const std::string& text, const sf::Font& font, float x, float y, 
			const sf::Color stdTextColor = sf::Color(), 
			const sf::Color stdFillColor = sf::Color(), 
			const sf::Color stdOutlineColor = sf::Color(),
			const unsigned int textSize = 30);
	public:
		/* Virtual Inheritance, override */
		void draw(sf::RenderTexture& renderTexture); //Draw the button
		sf::FloatRect getBoundings() const; //Get the bouding of the button
		void setFocus(bool focus); //Set the focus on it

		/* Methods */
		void setFocusFillColor(const sf::Color color); //Color on focus
		void setFocusOutlineColor(const sf::Color color); //Color on focus
		void setFocusTextColor(const sf::Color color); //Color on focus
		void setStdFillColor(const sf::Color color); //Color on non-focus
		void setStdOutlineColor(const sf::Color color); //Color on non-focus
		void setStdTextColor(const sf::Color color); //Color on non-focus
		void setText(const std::string& text); //Set the button text
		void setTextSize(const unsigned int size); //Set the button text size
	};

}

#endif