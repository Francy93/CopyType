#ifndef GUI_HXX
#define GUI_HXX
#define MAIN_ICON 101

#include <Windows.h>    // Used for the Windows API
#include <fstream>      // Used for file input and output
#include <string>       // Used for string


// gui class
class Gui {
    public:

        int typingSpeed, countdown;
        static bool mode;
        LPCWSTR buttonStart;
        LPCWSTR buttonCancel;

        // Constructor
        Gui();
        // Constructor
        Gui(int typingSpeed, int countdown);

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
};

#endif // GUI_HXX