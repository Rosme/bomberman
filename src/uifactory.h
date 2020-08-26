#ifndef UI_UIFACTORY_H
#define UI_UIFACTORY_H

#include <memory>
#include <SFML/System/NonCopyable.hpp>
#include "ressourcesmanager.h"
#include "ui.h"

typedef std::shared_ptr<UI::Label> Labelptr;
typedef std::shared_ptr<UI::Button> Buttonptr;
typedef std::shared_ptr<UI::EditText> EditTextptr;

class UIFactory : sf::NonCopyable {
private:
	static std::shared_ptr<Ressources::Manager> m_ressources;
	/* Private Ctor for non construction(static class) */
	UIFactory();
public:
	/* Methods */
	static void registerRessourceManager(std::shared_ptr<Ressources::Manager> manager); //Register the ressource manager to make things
	static Labelptr makeLabel(const std::string& text, const std::string& font, float x, float y, sf::Color textColor, const unsigned int textSize = 30); //Make a label smart pointer
	static Buttonptr makeButton(const std::string& text, const std::string& font, float x, float y, 
		sf::Color textColor, sf::Color fillColor, sf::Color outlineColor, const unsigned int textSize = 30); //Make a button smart pointer
	static EditTextptr makeEditText(const std::string& font, float x, float y, const sf::Color color, unsigned int size = 30); //Make an edit text smart pointer
};


#endif