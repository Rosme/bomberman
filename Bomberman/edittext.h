#ifndef UI_EDITTEXT_H
#define UI_EDITTEXT_H

#include <vector>
#include <boost/function.hpp>
#include "uiobject.h"

class UIFactory;

namespace UI {

	class EditText : public UI::Object {
		friend class UIFactory;
	public:
		enum KeyFilter {
			None,
			AlphaNum
		};
	private:
		bool m_fullFocus;
		sf::Text m_text;
		sf::Color m_stdColor;
		sf::Color m_focusColor;
		unsigned int m_inputLimit;
		unsigned int m_currentCount;
		bool m_takeFocus;
		KeyFilter m_filter;
		boost::signals2::signal<void(sf::Keyboard::Key)> m_textSignal;

		/* Ctor */
		EditText(float x, float y, const sf::Font& font, const sf::Color color, unsigned int size = 30);

		/* Methods */
		bool applyFilter(sf::Keyboard::Key key); //Apply the filter on the key
		void updateText(sf::Keyboard::Key key); //Update the text value from the key
	public:

		/* Virtual override */
		void draw(sf::RenderTexture& renderTexture); //Draw the text edit
		void emit(sf::Event& event); //Emit the signal
		sf::FloatRect getBoundings() const; //Get the boundings of the text edit
		void setFocus(bool focus); //Set the focus on it

		/* Methods */
		std::string getText(); //Return the text in the field
		void setFocusColor(const sf::Color color); //Color on focus
		void setFullFocus(bool focus); //Set focus for typing
		void resetText(); //Reset the text
		void setStdColor(const sf::Color color); //Color on non-focus
		void setInputLimit(unsigned int inputLimit, bool takeFocus = false); //Set the maximum amount of char
		void setKeyFilter(KeyFilter filter); //Apply a filter on keys
		void setText(const std::string text); //Predefined a text
	};

}

#endif