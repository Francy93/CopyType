
#include "../include/T_main.hpp"
#include "../include/Type.hpp"
#include "../lib/Util.h"


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
    int typingSpeed, countdown;
    Util::readConfig(typingSpeed, countdown);
    return T_main::t_main(typingSpeed, countdown);
}
int T_main::t_main(int typingSpeed, int countdown) {
    
    // object of class Type
    Type Typer(typingSpeed);
    Typer.printClipboard();
    
    // Countdown before typing
    T_main::countDown(countdown);

    // Type text from clipboard
    Typer.typeText();

    std::cout << "\nWe fooled them! :D" << std::endl;

    return 0;
}