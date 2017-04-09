#include "uifactory.h"

/* Static initialisation of members */
boost::shared_ptr<Ressources::Manager> UIFactory::m_ressources(nullptr);

UIFactory::UIFactory() {}

void UIFactory::registerRessourceManager(boost::shared_ptr<Ressources::Manager> manager) {
	m_ressources = manager;
}

Labelptr UIFactory::makeLabel(const std::string& text, const std::string& font, float x, float y, sf::Color textColor, const unsigned int textSize) {
	Labelptr label(new UI::Label(text, m_ressources->getFont(font), x, y, textColor, textSize));
	return label;
}

Buttonptr UIFactory::makeButton(const std::string& text, const std::string& font, float x, float y, 
		sf::Color textColor, sf::Color fillColor, sf::Color outlineColor, const unsigned int textSize) {
	Buttonptr button(new UI::Button(text, m_ressources->getFont(font), x, y, textColor, fillColor, outlineColor, textSize));
	return button;
}

EditTextptr UIFactory::makeEditText(const std::string& font, float x, float y, const sf::Color color, unsigned int size) {
	EditTextptr editText(new UI::EditText(x, y, m_ressources->getFont(font), color, size));
	return editText;
}