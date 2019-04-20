#ifndef UTIL_TIMER_H
#define UTIL_TIMER_H

#include <boost/function.hpp>
#include <SFML/System.hpp>

namespace Utils {

	class Watch {
	private:
		/* Members */
		sf::Time m_buffer;
		bool m_running;
		sf::Clock m_clock;
	public:
		/* Methods */
		Watch(bool running = false);
		~Watch();

		/**
		 * Get the amount of time passed since the clock started
		 **/
		sf::Time getElapsedTime() const;
		bool isRunning() const;
		void start();
		void stop();
		void restart(bool running = false);
	};


	class Timer {
	private:
		/* Members */
		Watch m_clock;
		sf::Time m_timeLimit;
	public:
		/* Methods */
		Timer();
		Timer(sf::Time timeLimit, bool running = false);
		virtual ~Timer();

		/**
		 * Returns the amount of time based on how much has passed and the limit
		 **/
		sf::Time getRemainingTime() const;
		bool isRunning() const;
		bool isExpired() const;
		void start();
		void stop();
		virtual void restart(sf::Time timeLimit, bool running = false);
		virtual void restart(bool running = false);
	};

	class TriggerTimer : public Timer {
	private:
		/* Members */
		bool m_expired;
		bool m_looping;
		boost::function<void()> m_listener;
	public:
		/* Methods */
		TriggerTimer();
		TriggerTimer(sf::Time timeLimit, bool running = false, bool looping = false);
		virtual ~TriggerTimer();

		/**
		 * Define if the timer is gonna restart automatically after it triggers
		 **/
		void setLooping(bool loop = true);
		bool isLooping() const;
		void restart(sf::Time timeLimit, bool running = false);
		void restart(bool running = false);
		/**
		 * Add the function listener to execute on triggering
		 **/
		void addListener(boost::function<void()> function);
		/**
		 * Evaluate if the timer is to be trigger or not
		 **/
		void update();
	};
}

#endif