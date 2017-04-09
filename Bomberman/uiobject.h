#ifndef UI_UIOBJECT_H
#define UI_UIOBJECT_H

#include <boost/signal.hpp>
#include <SFML/Graphics.hpp>

namespace UI {
	
	class Object {
	private:
		boost::signal<void()> m_signal;
	protected:
		float m_x;
		float m_y;
		bool m_focus;
		sf::Event::EventType m_eventType;
	public:
		/* Ctor */
		Object(float x, float y);
		/* Dtor */
		virtual ~Object();

		/* Pure virtual methods */
		virtual void draw(sf::RenderTexture& renderTexture) = 0;
		virtual sf::FloatRect getBoundings() const = 0;
		
		/* Virtual methods */
		virtual void emit(sf::Event& event); //Emit the signal
		virtual void setFocus(bool focus); //Set the focus on object

		/* Methods */
		void connect(sf::Event::EventType type, boost::signal<void()>::slot_function_type slot); //Connect a slot/function to the signal
		void setPosition(sf::Vector2f position); //Set the object position
		void setX(float x); //Set object X
		void setY(float y); //Set object Y
	};

}

#endif