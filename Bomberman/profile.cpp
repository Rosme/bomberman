#include "profile.h"

namespace Options {

	Profile::Profile(const std::string& name)
		: m_name(name), m_musicLevel(50), m_soundLevel(50) {}
	

	Options::Option& Profile::getOption() {
		return m_option;
	}

	void Profile::raiseMusicLevel() {
		if(m_musicLevel != 100)
			m_musicLevel += 5;

	}

	void Profile::lowerMusicLevel() {
		if(m_musicLevel != 0)
			m_musicLevel -= 5;
	}

	unsigned int Profile::getMusicLevel() const {
		return m_musicLevel;
	}

	void Profile::raiseSoundLevel() {
		if(m_soundLevel != 100)
			m_soundLevel += 5;
	}

	void Profile::lowerSoundLevel() {
		if(m_soundLevel != 0)
			m_soundLevel -= 5;
	}

	unsigned int Profile::getSoundLevel() const {
		return m_soundLevel;
	} 

	std::string& Profile::getName() {
		return m_name;
	}
}