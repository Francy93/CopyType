#ifndef T_MAIN_HXX
#define T_MAIN_HXX

// hpp file for type.cpp
#include <iostream> // used for input and output
#include <string>   // used for string
#include <chrono>   // used for time in function countDown    
#include <thread>   // Iused for thread in function countDown
// Function to read parameters from configuration file
#include <fstream>  // Include the necessary header file

#include "../include/Type.hpp"
#include "../include/Config.hpp"


//T_main class
class T_main {
	public:
		// Countdown function   
		static void countDown(int countdown);

		// main function
		static int t_main();
		static int t_main(Config& config);
};


#endif // MAIN_H
