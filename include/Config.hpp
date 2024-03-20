#ifndef CONFIG_H
#define CONFIG_H

#include <Windows.h>    // Include the necessary header file
#include <iostream>     // used for input and output
#include <fstream>      // Include the necessary header file
#include <atomic>	   // Include the necessary header file


// util class
class Config {
    private:
		const	bool	MODE				= false;

		const	int		DEFAULF_SPEED		= 100;
		const	int		DEFAULT_COUNTDOWN	= 5;
		const	bool	DEFAULT_STATUS		= false;
		const std::string DEFAULT_FILE_NAME	= "config.txt";

		int				current_speed		= this->DEFAULF_SPEED;
		int				current_countdown	= this->DEFAULT_COUNTDOWN;
		std::string		file_name			= this->DEFAULT_FILE_NAME;
		bool			current_status		= this->DEFAULT_STATUS;
	
	
	public:
		static std::atomic<bool> typingStatus;// Atomic variable to stop typing
	

		// constructor
		Config();
		Config(bool mode);


		/**
		 * @brief   This function writes the given parameters to the configuration file
		 * 
		 * @param typingSpeed   The typing speed
		 * @param countdown     The countdown
		 */
		void writeConfig();
		void writeConfig(int typingSpeed, int countdown, bool status);

		/**
		 * @brief   This function writes the given parameters to the configuration file
		 * 
		 * @param typingSpeed   The typing speed
		 * @param countdown     The countdown
		 */
		void loadConfig();



		// Setters............

		// Setter for speed
		void updateConfig(int typingSpeed, int countdown, bool status);
		// Setter for speed
		void setLocalSpeed(int speed);
		// Setter for countdown
		void setLocalCountdown(int countdown);
		// Setter for status
		void setLocalStatus(bool status);
		// Setter for file name
		void setLocalFileName(std::string fileName);



		// Getters...................

		// Getter for speed
		int getLocalSpeed();
		// Getter for countdown
		int getLocalCountdown();
		// Getter for status
		bool getLocalStatus();
		// Getter for file name
		std::string getLocalFileName();
		// GETTER fot mode
		bool getMode();

};

#endif // CONFIG_H