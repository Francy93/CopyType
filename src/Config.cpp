
#include "../include/Config.hpp"

std::atomic<bool> Config::typingStatus(false); // Initialization of static member variable

Config::Config(bool mode) : MODE(mode){
	if (mode)	this->loadConfig();
 }
Config::Config() : MODE(false){ }
/**
 * @brief   This function writes the given parameters to the configuration file
 * 
 * @param typingSpeed   The typing speed
 * @param countdown     The countdown
 */
void Config::writeConfig() { this->writeConfig(this->current_speed, this->current_countdown, this->current_status); }
void Config::writeConfig(int typingSpeed, int countdown, bool status) {
	std::ofstream configFile(this->file_name);
	if (configFile.is_open()) {
		configFile << typingSpeed << " " << countdown << " " << status;
		configFile.close();
	}
}

/**
 * @brief   This function writes the given parameters to the configuration file
 * 
 * @param typingSpeed   The typing speed
 * @param countdown     The countdown
 */
void Config::loadConfig() { 
	std::ifstream configFile(this->file_name);
	if (configFile.is_open()) {
		configFile >> this->current_speed >> this->current_countdown >> this->current_status;
		configFile.close();
	} else {
		// If the file does not exist, create it with default values
		this->updateConfig(this->DEFAULF_SPEED, this->DEFAULT_COUNTDOWN, this->DEFAULT_STATUS);
	}
}


void Config::updateConfig(int typingSpeed, int countdown, bool status) {
	this->current_speed		= typingSpeed;
	this->current_countdown	= countdown;
	this->current_status	= status;
	this->writeConfig();
}


// Getter for speed
int Config::getLocalSpeed() { return this->current_speed; }
// Getter for countdown
int Config::getLocalCountdown() { return this->current_countdown; }
// Getter for status
bool Config::getLocalStatus() { return this->current_status; }
// Getter for file name
std::string Config::getLocalFileName() { return this->file_name; }
// GETTER fot mode
bool Config::getMode() { return this->MODE; }

// Setter for speed
void Config::setLocalSpeed(int speed) { this->current_speed = speed; }
// Setter for countdown
void Config::setLocalCountdown(int countdown) { this->current_countdown = countdown; }
// Setter for status
void Config::setLocalStatus(bool status) { this->current_status = status; }
// Setter for file name
void Config::setLocalFileName(std::string fileName) { this->file_name = fileName; }