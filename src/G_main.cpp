
#include "../include/G_main.hpp"


// Main function
int G_main::g_main() {
	// Retrieve parameters from configuration file
	Config conf = Config(true);
	return G_main::g_main(conf);
}
int G_main::g_main(Config& conf) {

	// object of class Gui
	Gui GUI(conf);

	// Run the GUI
	GUI.createGUI();

	return 0;
}