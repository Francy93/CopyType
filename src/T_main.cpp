
#include "../include/T_main.hpp"



/**
 * @brief   This function counts down from the given number
 * @param countdown The number to count down from
 */
void T_main::countDown(int countdown) {
	for (int i = countdown; i >= 1; --i) {
		std::wcout << L"Starting in " << i << L"...\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}


// Main function
int T_main::t_main() {
	// Retrieve parameters from configuration file
    Config conf = Config(true);
    return T_main::t_main(conf);
}
int T_main::t_main(Config& config) {

	// object of class Type
	Type Typer(config);
	Typer.printClipboard();

	// Countdown before typing
	T_main::countDown(config.getLocalCountdown());

	// Type text from clipboard
	Typer.typeText();

	std::cout << "\nWe fooled them! :D" << std::endl;

	return 0;
}