#ifndef OPTIONS_LOADER_H
#define OPTIONS_LOADER_H

#include <vector>
#include <string>
#include "profile.h"

namespace Options {

	class Loader : sf::NonCopyable {
	private:
		std::vector<Options::Profile> m_profileList;
		std::size_t m_currentProfileIndex;
		std::string m_profilePath;
		bool m_firstgame;

		void loadProfiles();
	public:
		/* Ctor */
		Loader(const std::string& profilePath);

		/* Methods */
		void createProfile(Options::Profile profile); //Create the profile
		void deleteProfile(const std::string& name); //Delete a profile
		Options::Profile& getCurrentProfile(); //Return the current one that is loaded
		Options::Profile& getProfile(const std::string& name); //Return a profile
		bool isFirstGame() const; //Return if there is a profile at all. No profile = new game
		std::vector<std::string> getProfilesName(); //Return the list of the profiles names
		void saveCurrentProfile(); //Save current one
		void saveProfiles(); //Save all profiles
		void setCurrentProfile(const std::string& name); //Set the current one
	};

}

#endif