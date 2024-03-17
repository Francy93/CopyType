#ifndef UTIL_H
#define UTIL_H

#include <Windows.h>    // Include the necessary header file
#include <iostream>     // used for input and output
#include <fstream>      // Include the necessary header file

// util class
class Util {
    public:

		static const int DEFAULF_SPEED      = 100;
		static const int DEFAULT_COUNTDOWN	= 5;
		static std::string fileName(){ return "config.txt"; }


		/**
		 * @brief   This function writes the given parameters to the configuration file
		 * 
		 * @param typingSpeed   The typing speed
		 * @param countdown     The countdown
		 */
		static void writeConfig(int typingSpeed, int countdown) {
			std::ofstream configFile(fileName());
			if (configFile.is_open()) {
				configFile << typingSpeed << " " << countdown;
				configFile.close();
			}
		}

		/**
		 * @brief   This function writes the given parameters to the configuration file
		 * 
		 * @param typingSpeed   The typing speed
		 * @param countdown     The countdown
		 */
		static void readConfig(int& typingSpeed, int& countdown) {
			std::ifstream configFile(fileName());
			if (configFile.is_open()) {
				configFile >> typingSpeed >> countdown;
				configFile.close();
			} else {
				// If the file does not exist, create it with default values
				typingSpeed	= DEFAULF_SPEED;
				countdown	= DEFAULT_COUNTDOWN;
				writeConfig(typingSpeed, countdown);
			}
		}

};

#endif // UTIL_H