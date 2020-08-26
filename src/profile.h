#ifndef OPTIONS_PROFILE_H
#define OPTIONS_PROFILE_H

#include <string>
#include <cereal/access.hpp>
#include "option.h"

namespace Options {

	class Profile {
		/* For serialization into file */
		friend class cereal::access;

		template<class Archive>
		void serialize(Archive & ar, const unsigned int /* file version */) {
			ar(m_name);
			ar(m_option);
			ar(m_musicLevel);
			ar(m_soundLevel);
		}

	private:
		std::string m_name;
		Options::Option m_option;
		unsigned int m_musicLevel;
		unsigned int m_soundLevel;

	public:
		/* Ctor */
		Profile(const std::string& name);

		/* Methods */
		unsigned int getMusicLevel() const; //Return music level for player
		std::string& getName(); //Return the player's name
		Options::Option& getOption(); //Return the options
		unsigned int getSoundLevel() const; //Return the sound level for player
		void lowerMusicLevel(); //Less music
		void lowerSoundLevel(); //Less sounds
		void raiseMusicLevel(); //More music
		void raiseSoundLevel(); //More sound
	};

}

#endif