#ifndef GUI_HXX
#define GUI_HXX
#define MAIN_ICON 100
#define TYPING_ICON 101


#include <Windows.h>    // Used for the Windows API
#include <fstream>      // Used for file input and output
#include <string>       // Used for string
#include <thread>		// Used for threads


#include "../include/T_main.hpp"
#include "../include/Config.hpp"


// gui class
class Gui {
	public:

		Config	config;			// Configuration file
		LPCWSTR	buttonStart;	// Start button
		LPCWSTR	buttonStop;		// Cancel button

		// Constructor
		Gui();
		// Constructor
		Gui(Config conf);

		/**
		 * @brief   This function handles messages for the GUI window
		 * 
		 * @param hwnd		Handle to the window
		 * @param uMsg		User message
		 * @param wParam	Wide parameter
		 * @param lParam	Long parameter
		 * @return			Result of the message processing
		 */
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		// Function to create the GUI window
		void createGUI();


    private:

		HWND	hwndSpeedInput;			// Handle to the speed input
		HWND	hwndCountdownInput;		// Handle to the countdown input
		static	HWND hwndStartButton;	// Handle to the start button
		static	HWND hwndStopButton;	// Handle to the stop button
		static	Gui* currentInstance;	// Pointer to the current instance of the class
		

		// change stauses
		void changeStatus(bool status);

		/**
		 * @brief	This function accesses non-static members to handles the save button click
		 * 
		 * @param hwnd	Handle to the window
		 */
		void handleStartButton();
		/**
		 * @brief	This function accesses non-static members to handles the stop button click
		 * 
		 * @param hwnd	Handle to the window
		 */
		void handleStopButton();
};

#endif // GUI_HXX