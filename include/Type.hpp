#ifndef TYPE_HXX
#define TYPE_HXX

#include <Windows.h>    // Include the necessary header file
#include <iostream>     // used for input and output
#include <thread>       // Iused for thread in function countDown

class Type {
    private:
        int speed;
        std::wstring textToType;

    public:
        // Constructor
        Type(const int S);
        // Destructor
        ~Type();

        // Function to simulate a new line
        void simulateShiftEnterKey();
        // Function to simulate a key press
        void simulateKeyPress(wchar_t c);

        // Typing function
        void typeText();
        void typeText(const std::wstring& text, int delay);

        // read clipboard function
        std::wstring readClipboard();

        // Function to read the clipboard and type the content
        void readType();

        // Getter for speed
        int getSpeed();

        // Getter for textToType
        std::wstring getTextToType();

        // Function to print the clipboard
        void printClipboard();

};


#endif