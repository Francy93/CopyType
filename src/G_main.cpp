
#include "../include/G_main.hpp"
#include "../include/Gui.hpp"
#include "../lib/Util.h"

// Main function
int G_main::g_main() {
    // Retrieve parameters from configuration file
    int typingSpeed, countdown;
    Util::readConfig(typingSpeed, countdown);
    return G_main::g_main(typingSpeed, countdown);
}
int G_main::g_main(int& typingSpeed, int& countdown) {

    // object of class Gui
    Gui GUI(typingSpeed, countdown);

    // Run the GUI
    GUI.createGUI();

    return 0;
}