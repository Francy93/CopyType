#include "../include/Type.hpp"

//Constructor with param speed
Type::Type(const int S) {
    this->speed = S;
    this->textToType = this->readClipboard();
}

// Destructor
Type::~Type() {}


// Function to simulate a new line
void Type::simulateShiftEnterKey() {
    // Press the "Shift" key
    keybd_event(VK_SHIFT, 0, 0, 0);
    // Press the "Enter" key
    keybd_event(VK_RETURN, 0, 0, 0);
    // Release the "Enter" key
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
    // Release the "Shift" key
    keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
}

/**
 * @brief   This function simulates typing by pasting clipboard content
 * 
 * @param c character to type
 */
void Type::simulateKeyPress(wchar_t c) {
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = 0;
    input.ki.wScan = c;
    input.ki.dwFlags = KEYEVENTF_UNICODE;
    SendInput(1, &input, sizeof(INPUT));

    input.ki.dwFlags |= KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

/**
 * @brief This function simulates typing by pasting clipboard content
 * 
 * @param text text to type
 * @param delay speed of typing in milliseconds
 */
void Type::typeText() { this->typeText(this->textToType, this->speed); }
void Type::typeText(const std::wstring& text, int delay) {
    for (wchar_t c : text) {
        if (c == L'\n') this->simulateShiftEnterKey();
        else            this->simulateKeyPress(c);

        // Delay between key presses
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}


// read clipboard function
std::wstring Type::readClipboard() {
    std::wstring text;
    if (OpenClipboard(NULL)) {
        HANDLE hData = GetClipboardData(CF_UNICODETEXT);
        wchar_t* pszText = static_cast<wchar_t*>(GlobalLock(hData));
        if (pszText != NULL) {
            text = pszText;
            GlobalUnlock(hData);
        }
        CloseClipboard();
    }
    return text;
}

/**
 * @brief This function reads the clipboard and types the content
 * 
 */
void Type::readType() {
   this->textToType = readClipboard();

    // Output clipboard text for debugging
    printClipboard();
    typeText(textToType, this->speed);
}



// ----  getters  -----

// Getter for speed
int Type::getSpeed() {
    return this->speed;
}

// Getter for textToType
std::wstring Type::getTextToType() {
    return this->textToType;
}

void Type::printClipboard() {
        // Output clipboard text for debugging
    std::wcout << L"Clipboard Text:\n" << this->textToType << "\n"<< std::endl;
}
