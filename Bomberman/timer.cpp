#include "timer.h"

namespace Utils {

	/* Watch Class */
	Watch::Watch(bool running)
		: m_buffer(sf::Time::Zero), m_running(running) {}

	Watch::~Watch() {}

	sf::Time Watch::getElapsedTime() const {
		if(m_running)
			return (m_buffer + m_clock.getElapsedTime());
		return m_buffer;
	}

	bool Watch::isRunning() const {
		return m_running;
	}

	void Watch::start() {
		if(!m_running) {
			m_running = true;
			m_clock.restart();
		}
	}

	void Watch::stop() {
		if(m_running) {
			m_buffer += m_clock.getElapsedTime();
			m_running = false;
		}
	}

	void Watch::restart(bool running) {
		m_buffer = sf::Time::Zero;
		m_running = running;
		m_clock.restart();
	}

	/* Timer Class */
	Timer::Timer()
		: m_clock(), m_timeLimit(sf::Time::Zero) {}

	Timer::Timer(sf::Time timeLimit, bool running)
		: m_clock(running), m_timeLimit(timeLimit) {
		if(timeLimit < sf::Time::Zero)
			throw std::invalid_argument("The time limit for a timer is below zero");
	}

	Timer::~Timer() {}

	sf::Time Timer::getRemainingTime() const {
		//Returns remaining time or zero(if remaining is negative
		return std::max((m_timeLimit - m_clock.getElapsedTime()), sf::Time::Zero);
	}

	bool Timer::isRunning() const {
		return m_clock.isRunning() && !isExpired();
	}

	bool Timer::isExpired() const {
		return m_clock.getElapsedTime() > m_timeLimit;
	}

	void Timer::start() {
		m_clock.start();
	}

	void Timer::stop() {
		m_clock.stop();
	}

	void Timer::restart(sf::Time timeLimit, bool running) {
		if(timeLimit < sf::Time::Zero)
			throw std::invalid_argument("The time limit for a timer is below zero");
		m_timeLimit = timeLimit;
		m_clock.restart(running);
	}

	void Timer::restart(bool running) {
		m_clock.restart(running);
	}

	/* Trigger Timer Class */
	TriggerTimer::TriggerTimer()
		: Timer(), m_expired(false), m_looping(false) {}

	TriggerTimer::TriggerTimer(sf::Time timeLimit, bool running, bool looping)
		: Timer(timeLimit, running), m_expired(false), m_looping(looping) {}

	TriggerTimer::~TriggerTimer() {}

	void TriggerTimer::setLooping(bool loop) {
		m_looping = loop;
	}

	bool TriggerTimer::isLooping() const {
		return m_looping;
	}

	void TriggerTimer::restart(sf::Time timeLimit, bool running) {
		Timer::restart(timeLimit, running);
		m_expired = false;
	}

	void TriggerTimer::restart(bool running) {
		Timer::restart(running);
		m_expired = false;
	}

	void TriggerTimer::addListener(boost::function<void()> function) {
		m_listener = function;
	}

	void TriggerTimer::update() {
		if(isExpired() && !m_expired) {
			m_expired = true;
			m_listener();

			if(m_looping)
				restart(true);
		}
	}
}