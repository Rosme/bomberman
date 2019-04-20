#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "profileloader.h"
#include "utils.h"
#include <sfml/System/Err.hpp>

namespace Options {
	namespace bfs = boost::filesystem;
	Loader::Loader(const std::string& profilePath)
		: m_currentProfileIndex(0), m_profilePath(profilePath), m_firstgame(false) {
			bfs::path path(m_profilePath);

			//Creating directory if it doesn't exist
			if(!bfs::exists(path)) {
				bfs::create_directory(path);
			}

			if(bfs::is_directory(path)) {
				loadProfiles();
			}
	}

	void Loader::loadProfiles() {
		bfs::path path(m_profilePath);
		std::ifstream profileFile;

		for(auto it = bfs::directory_iterator(path), end = bfs::directory_iterator(); it != end; ++it) {
			if((*it).path().extension().string() == ".plr") {
				profileFile.open((*it).path().string());

				try {
					boost::archive::xml_iarchive ia(profileFile);
					Options::Profile profile("useless");
					ia >> BOOST_SERIALIZATION_NVP(profile);
					m_profileList.push_back(profile);
					//profileFile.close();
					break;
				} catch (const boost::archive::archive_exception& e) {
					sf::err() << e.code << " " << e.what();
				}
				
				profileFile.close();
			}
		}

		if(!bfs::exists(m_profilePath + "lastUser.lplr")) {
			m_firstgame = true;
		} else {
			m_firstgame = false;
			std::ifstream last(m_profilePath + "lastUser.lplr");
			if(!last)
				throw std::runtime_error("Couldn't load the last user profile file");
			std::string name;
			std::getline(last, name);
			setCurrentProfile(name);
		}
	}

	void Loader::createProfile(Options::Profile profile) {
		std::ofstream profileFile(m_profilePath + profile.getName() + ".plr");

		boost::archive::xml_oarchive oa(profileFile);
		oa << BOOST_SERIALIZATION_NVP(profile);
		
		std::ofstream last(m_profilePath + "lastUser.lplr");
		if(!last)
			throw std::runtime_error("Couldn't load the last user profile file");
		m_profileList.push_back(profile);
		last << profile.getName();
		setCurrentProfile(profile.getName());
	}

	void Loader::saveProfiles() {
		std::ofstream profileFile;
		
		for(auto it = m_profileList.begin(), end = m_profileList.end(); it != end; ++it) {
			profileFile.open(m_profilePath + it->getName() + ".plr");

			boost::archive::xml_oarchive oa(profileFile);
			oa << BOOST_SERIALIZATION_NVP((*it));

			profileFile.close();
		}
	}

	void Loader::deleteProfile(const std::string& name) {
		if(m_profileList.size() > 1) {
			const std::string currentName = m_profileList[m_currentProfileIndex].getName();
			for(auto it = m_profileList.begin(), end = m_profileList.end(); it != end; ++it) {
				if(Utils::formatText(it->getName()) == Utils::formatText(name)) {

					bfs::path p(m_profilePath + it->getName() + ".plr");
					bfs::remove(p);
					m_profileList.erase(it);

					setCurrentProfile(m_profileList[0].getName());
					return; //Hack
				}
			}
		}
	}

	Options::Profile& Loader::getProfile(const std::string& name) {
		for(auto it = m_profileList.begin(), end = m_profileList.end(); it != end; ++it) {
			if(it->getName() == name) {
				return (*it);
			}
		}
		throw
			std::runtime_error("No profile by the name of " + name + " was found");
	}

	Options::Profile& Loader::getCurrentProfile() {
		return m_profileList[m_currentProfileIndex];
	}

	std::vector<std::string> Loader::getProfilesName() {
		std::vector<std::string> names;
		for(auto it = m_profileList.begin(), end = m_profileList.end(); it != end; ++it) {
			names.push_back(it->getName());
		}
		return names;
	}

	void Loader::setCurrentProfile(const std::string& name) {
		for(unsigned int i = 0; i < m_profileList.size(); ++i) {
			if(Utils::formatText(m_profileList[i].getName()) == Utils::formatText(name)) {
				m_currentProfileIndex = i;
				std::ofstream last(m_profilePath + "lastUser.lplr");
				if(!last)
					throw std::runtime_error("Couldn't load the last user profile file");
				last << m_profileList[i].getName();
				i = m_profileList.size();
			}
		}
	}

	bool Loader::isFirstGame() const {
		return m_firstgame;
	}

	void Loader::saveCurrentProfile() {
		Options::Profile& currentProfile = getCurrentProfile();
		std::ofstream profileFile(m_profilePath + currentProfile.getName() + ".plr");
		if(!profileFile)
			throw std::runtime_error("Couldn't modify the current profile file");
		boost::archive::xml_oarchive oa(profileFile);
		oa << BOOST_SERIALIZATION_NVP(currentProfile);
		profileFile.close();
	}
}