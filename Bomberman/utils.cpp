#include "utils.h"

namespace Utils {

	std::string getKeyName(const sf::Keyboard::Key key) {
		switch(key) {
		default:
		case sf::Keyboard::Unknown:
			return "Unknown";
		case sf::Keyboard::A:
			return "A";
		case sf::Keyboard::B:
			return "B";
		case sf::Keyboard::C:
			return "C";
		case sf::Keyboard::D:
			return "D";
		case sf::Keyboard::E:
			return "E";
		case sf::Keyboard::F:
			return "F";
		case sf::Keyboard::G:
			return "G";
		case sf::Keyboard::H:
			return "H";
		case sf::Keyboard::I:
			return "I";
		case sf::Keyboard::J:
			return "J";
		case sf::Keyboard::K:
			return "K";
		case sf::Keyboard::L:
			return "L";
		case sf::Keyboard::M:
			return "M";
		case sf::Keyboard::N:
			return "N";
		case sf::Keyboard::O:
			return "O";
		case sf::Keyboard::P:
			return "P";
		case sf::Keyboard::Q:
			return "Q";
		case sf::Keyboard::R:
			return "R";
		case sf::Keyboard::S:
			return "S";
		case sf::Keyboard::T:
			return "T";
		case sf::Keyboard::U:
			return "U";
		case sf::Keyboard::V:
			return "V";
		case sf::Keyboard::W:
			return "W";
		case sf::Keyboard::X:
			return "X";
		case sf::Keyboard::Y:
			return "Y";
		case sf::Keyboard::Z:
			return "Z";
		case sf::Keyboard::Num0:
			return "0";
		case sf::Keyboard::Num1:
			return "1";
		case sf::Keyboard::Num2:
			return "2";
		case sf::Keyboard::Num3:
			return "3";
		case sf::Keyboard::Num4:
			return "4";
		case sf::Keyboard::Num5:
			return "5";
		case sf::Keyboard::Num6:
			return "6";
		case sf::Keyboard::Num7:
			return "7";
		case sf::Keyboard::Num8:
			return "8";
		case sf::Keyboard::Num9:
			return "9";
		case sf::Keyboard::Escape:
			return "Escape";
		case sf::Keyboard::LControl:
			return "LControl";
		case sf::Keyboard::LShift:
			return "LShift";
		case sf::Keyboard::LAlt:
			return "LAlt";
		case sf::Keyboard::LSystem:
			return "LSystem";
		case sf::Keyboard::RControl:
			return "RControl";
		case sf::Keyboard::RShift:
			return "RShift";
		case sf::Keyboard::RAlt:
			return "RAlt";
		case sf::Keyboard::RSystem:
			return "RSystem";
		case sf::Keyboard::Menu:
			return "Menu";
		case sf::Keyboard::LBracket:
			return "LBracket";
		case sf::Keyboard::RBracket:
			return "RBracket";
		case sf::Keyboard::SemiColon:
			return "SemiColon";
		case sf::Keyboard::Comma:
			return "Comma";
		case sf::Keyboard::Period:
			return "Period";
		case sf::Keyboard::Quote:
			return "Quote";
		case sf::Keyboard::Slash:
			return "Slash";
		case sf::Keyboard::BackSlash:
			return "BackSlash";
		case sf::Keyboard::Tilde:
			return "Tilde";
		case sf::Keyboard::Equal:
			return "Equal";
		case sf::Keyboard::Dash:
			return "Dash";
		case sf::Keyboard::Space:
			return "Space";
		case sf::Keyboard::Return:
			return "Return";
		case sf::Keyboard::BackSpace:
			return "BackSpace";
		case sf::Keyboard::Tab:
			return "Tab";
		case sf::Keyboard::PageUp:
			return "PageUp";
		case sf::Keyboard::PageDown:
			return "PageDown";
		case sf::Keyboard::End:
			return "End";
		case sf::Keyboard::Home:
			return "Home";
		case sf::Keyboard::Insert:
			return "Insert";
		case sf::Keyboard::Delete:
			return "Delete";
		case sf::Keyboard::Add:
			return "Add";
		case sf::Keyboard::Subtract:
			return "Subtract";
		case sf::Keyboard::Multiply:
			return "Multiply";
		case sf::Keyboard::Divide:
			return "Divide";
		case sf::Keyboard::Left:
			return "Left";
		case sf::Keyboard::Right:
			return "Right";
		case sf::Keyboard::Up:
			return "Up";
		case sf::Keyboard::Down:
			return "Down";
		case sf::Keyboard::Numpad0:
			return "0";
		case sf::Keyboard::Numpad1:
			return "1";
		case sf::Keyboard::Numpad2:
			return "2";
		case sf::Keyboard::Numpad3:
			return "3";
		case sf::Keyboard::Numpad4:
			return "4";
		case sf::Keyboard::Numpad5:
			return "5";
		case sf::Keyboard::Numpad6:
			return "6";
		case sf::Keyboard::Numpad7:
			return "7";
		case sf::Keyboard::Numpad8:
			return "8";
		case sf::Keyboard::Numpad9:
			return "9";
		case sf::Keyboard::F1:
			return "F1";
		case sf::Keyboard::F2:
			return "F2";
		case sf::Keyboard::F3:
			return "F3";
		case sf::Keyboard::F4:
			return "F4";
		case sf::Keyboard::F5:
			return "F5";
		case sf::Keyboard::F6:
			return "F6";
		case sf::Keyboard::F7:
			return "F7";
		case sf::Keyboard::F8:
			return "F8";
		case sf::Keyboard::F9:
			return "F9";
		case sf::Keyboard::F10:
			return "F10";
		case sf::Keyboard::F11:
			return "F11";
		case sf::Keyboard::F12:
			return "F12";
		case sf::Keyboard::F13:
			return "F13";
		case sf::Keyboard::F14:
			return "F14";
		case sf::Keyboard::F15:
			return "F15";
		case sf::Keyboard::Pause:
			return "Pause";
		}
	}

	sf::Keyboard::Key getKeyValue(const std::string& key) {
		if(key == "A") {
			return sf::Keyboard::A;
		} else if(key == "B") {
			return sf::Keyboard::B;
		} else if(key == "C") {
			return sf::Keyboard::C;
		} else if(key == "D") {
			return sf::Keyboard::D;
		} else if(key == "E") {
			return sf::Keyboard::E;
		} else if(key == "F") {
			return sf::Keyboard::F;
		} else if(key == "G") {
			return sf::Keyboard::G;
		} else if(key == "H") {
			return sf::Keyboard::H;
		} else if(key == "I") {
			return sf::Keyboard::I;
		} else if(key == "J") {
			return sf::Keyboard::J;
		} else if(key == "K") {
			return sf::Keyboard::K;
		} else if(key == "L") {
			return sf::Keyboard::L;
		} else if(key == "M") {
			return sf::Keyboard::M;
		} else if(key == "N") {
			return sf::Keyboard::N;
		} else if(key == "O") {
			return sf::Keyboard::P;
		} else if(key == "Q") {
			return sf::Keyboard::Q;
		} else if(key == "R") {
			return sf::Keyboard::R;
		} else if(key == "S") {
			return sf::Keyboard::S;
		} else if(key == "T") {
			return sf::Keyboard::T;
		} else if(key == "U") {
			return sf::Keyboard::U;
		} else if(key == "V") {
			return sf::Keyboard::V;
		} else if(key == "W") {
			return sf::Keyboard::W;
		} else if(key == "X") {
			return sf::Keyboard::X;
		} else if(key == "Y") {
			return sf::Keyboard::Y;
		} else if(key == "Z") {
			return sf::Keyboard::Z;
		} else if(key == "0") {
			return sf::Keyboard::Num0;
		} else if(key == "1") {
			return sf::Keyboard::Num1;
		} else if(key == "2") {
			return sf::Keyboard::Num2;
		} else if(key == "3") {
			return sf::Keyboard::Num3;
		} else if(key == "4") {
			return sf::Keyboard::Num4;
		} else if(key == "5") {
			return sf::Keyboard::Num5;
		} else if(key == "6") {
			return sf::Keyboard::Num6;
		} else if(key == "7") {
			return sf::Keyboard::Num7;
		} else if(key == "8") {
			return sf::Keyboard::Num8;
		} else if(key == "9") {
			return sf::Keyboard::Num9;
		} else if(key == "Space") {
			return sf::Keyboard::Space;
		} else if(key == "Escape") {
			return sf::Keyboard::Escape;
		} else if(key == "LControl") {
			return sf::Keyboard::LControl;
		} else if(key == "LShift") {
			return sf::Keyboard::LShift;
		} else if(key == "LAlt") {
			return sf::Keyboard::LAlt;
		} else if(key == "LSystem") {
			return sf::Keyboard::LSystem;
		} else if(key == "RControl") {
			return sf::Keyboard::RControl;
		} else if(key == "RShift") {
			return sf::Keyboard::RShift;
		} else if(key == "RAlt") {
			return sf::Keyboard::RAlt;
		} else if(key == "RSystem") {
			return sf::Keyboard::RSystem;
		} else if(key == "Menu") {
			return sf::Keyboard::Menu;
		} else if(key == "LBracket") {
			return sf::Keyboard::LBracket;
		} else if(key == "RBracket") {
			return sf::Keyboard::RBracket;
		} else if(key == "SemiColon") {
			return sf::Keyboard::SemiColon;
		} else if(key == "Comma") {
			return sf::Keyboard::Comma;
		} else if(key == "Period") {
			return sf::Keyboard::Period;
		} else if(key == "Quote") {
			return sf::Keyboard::Quote;
		} else if(key == "Slash") {
			return sf::Keyboard::Slash;
		} else if(key == "BackSlash") {
			return sf::Keyboard::BackSlash;
		} else if(key == "Tilde") {
			return sf::Keyboard::Tilde;
		} else if(key == "Equal") {
			return sf::Keyboard::Equal;
		} else if(key == "Dash") {
			return sf::Keyboard::Dash;
		} else if(key == "Return") {
			return sf::Keyboard::Return;
		} else if(key == "BackSpace") {
			return sf::Keyboard::BackSpace;
		} else if(key == "Tab") {
			return sf::Keyboard::Tab;
		} else if(key == "PageUp") {
			return sf::Keyboard::PageUp;
		} else if(key == "PageDown") {
			return sf::Keyboard::PageDown;
		} else if(key == "End") {
			return sf::Keyboard::End;
		} else if(key == "Home") {
			return sf::Keyboard::Home;
		} else if(key == "Insert") {
			return sf::Keyboard::Insert;
		} else if(key == "Delete") {
			return sf::Keyboard::Delete;
		} else if(key == "Add") {
			return sf::Keyboard::Add;
		} else if(key == "Subtract") {
			return sf::Keyboard::Subtract;
		} else if(key == "Multiply") {
			return sf::Keyboard::Multiply;
		} else if(key == "Divide") {
			return sf::Keyboard::Divide;
		} else if(key == "Left") {
			return sf::Keyboard::Left;
		} else if(key == "Right") {
			return sf::Keyboard::Right;
		} else if(key == "Up") {
			return sf::Keyboard::Up;
		} else if(key == "Down") {
			return sf::Keyboard::Down;
		} else if(key == "F1") {
			return sf::Keyboard::F1;
		} else if(key == "F2") {
			return sf::Keyboard::F2;
		} else if(key == "F3") {
			return sf::Keyboard::F3;
		} else if(key == "F4") {
			return sf::Keyboard::F4;
		} else if(key == "F5") {
			return sf::Keyboard::F5;
		} else if(key == "F6") {
			return sf::Keyboard::F6;
		} else if(key == "F7") {
			return sf::Keyboard::F7;
		} else if(key == "F8") {
			return sf::Keyboard::F8;
		} else if(key == "F9") {
			return sf::Keyboard::F9;
		} else if(key == "F10") {
			return sf::Keyboard::F10;
		} else if(key == "F11") {
			return sf::Keyboard::F11;
		} else if(key == "F12") {
			return sf::Keyboard::F12;
		} else if(key == "F13") {
			return sf::Keyboard::F13;
		} else if(key == "F14") {
			return sf::Keyboard::F14;
		} else if(key == "F15") {
			return sf::Keyboard::F15;
		} else if(key == "Pause") {
			return sf::Keyboard::Pause;
		} else {
			return sf::Keyboard::Unknown;
		}
	}

	float getFps(const sf::Time& time) {
		return (1000000.0f / time.asMicroseconds());
	}

	std::string formatText(std::string text) {
		text[0] = toupper(text[0]);
		for(unsigned int i = 1; i < text.size(); ++i) {
			text[i] = tolower(text[i]);
		}
		return text;
	}

}