#ifndef UI_LABEL_H
#define UI_LABEL_H

#include "uiobject.h"

class UIFactory;

namespace UI {

	class Label : public UI::Object {
		friend class UIFactory;
	private:
		sf::Text m_text;
		sf::Color m_stdColor;
		sf::Color m_focusColor;

		/* Ctor */
		Label(const std::string& text, const sf::Font& font, float x, float y, const sf::Color stdColor = sf::Color(), const unsigned int textSize = 30);
	public:
		/* Virtual inheritance, override */
		void draw(sf::RenderTexture& RenderTexture); //Draw the label
		sf::FloatRect getBoundings() const; //Get it's boundings
		void setFocus(bool focus); //Set focus on it

		/* Methods */
		std::string getText() const; //Get the text
		void setFocusColor(const sf::Color color); //Color on focus
		void setStdColor(const sf::Color color); //Color on non-focus
		void setText(const std::string& text); //Set the text
		void setTextSize(const unsigned int size); //Set the text size
		
	};

}

#endif