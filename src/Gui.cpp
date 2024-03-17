#include "../include/Gui.hpp"
#include "../include/T_main.hpp"
#include "../lib/Util.h"

bool Gui::mode;  // Definition
HWND hwndSpeedInput, hwndCountdownInput, hwndSaveButton;

// Constructor
Gui::Gui() {
    Gui::mode			= true;
    this->buttonStart	= L"Save";
    this->buttonCancel	= L"Cancel";
    // Create GUI with default values
    Util::readConfig(typingSpeed, countdown);
}
/**
 * @brief	Construct a new Gui:: Gui object
 * 
 * @param ts typing speed
 * @param cd countdown
 */
Gui::Gui(int ts, int cd) {
    Gui::mode			= false;
    this->buttonStart	= L"Start";
    this->buttonCancel	= L"Stop";
    this->typingSpeed	= ts;
    this->countdown	= cd;
}


/**
 * @brief   This function creates the GUI window
 * 
 */
void Gui::createGUI() {
    // Register window class
    WNDCLASS wc = { };
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = [](HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT {
        return Gui::WindowProc(hwnd, uMsg, wParam, lParam);
    };
    wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = L"AutoTyperGUI";
    RegisterClass(&wc);


    // Create window
    HWND hwnd = CreateWindowEx(0, L"AutoTyperGUI", L"Auto Typer Settings",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 170,
        NULL, NULL, wc.hInstance, NULL);

    if (!hwnd) {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return;
    }

    // Load and set the icon for the window
    HICON hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(MAIN_ICON), IMAGE_ICON, 0, 0, 0);
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);



	// Create controls
	// Title for Speed Input
	CreateWindowEx(0, L"STATIC", L"Delay:", WS_CHILD | WS_VISIBLE, 10, 20, 100, 20, hwnd, NULL, NULL, NULL);
	hwndSpeedInput = CreateWindowEx(0, L"EDIT", std::to_wstring(typingSpeed).c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
		120, 20, 100, 25, hwnd, NULL, NULL, NULL);
	SendMessage(hwndSpeedInput, EM_SETLIMITTEXT, 10, 0);

	// Title for Countdown Input
	CreateWindowEx(0, L"STATIC", L"Countdown:", WS_CHILD | WS_VISIBLE, 10, 60, 100, 20, hwnd, NULL, NULL, NULL);
	hwndCountdownInput = CreateWindowEx(0, L"EDIT", std::to_wstring(countdown).c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
		120, 60, 100, 25, hwnd, NULL, NULL, NULL);
	SendMessage(hwndCountdownInput, EM_SETLIMITTEXT, 2, 0);

	// Save button on the right side
	RECT rect;
	GetClientRect(hwnd, &rect);
	int width = rect.right - rect.left;
	hwndSaveButton = CreateWindowEx(0, L"BUTTON", buttonStart, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		width - 120, 100, 100, 30, hwnd, reinterpret_cast<HMENU>(1), NULL, NULL);



    // Apply modern font
    HFONT hFont = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
    SendMessage(hwndSpeedInput, WM_SETFONT, WPARAM(hFont), TRUE);
    SendMessage(hwndCountdownInput, WM_SETFONT, WPARAM(hFont), TRUE);
    SendMessage(hwndSaveButton, WM_SETFONT, WPARAM(hFont), TRUE);

    // Show window
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    // Run message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

/**
 * @brief   This function handles messages for the GUI window
 * 
 * @param hwnd		Handle to the window
 * @param uMsg		User message
 * @param wParam	Wide parameter
 * @param lParam	Long parameter
 * @return			Result of the message processing
 */
LRESULT CALLBACK Gui::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_COMMAND:
        if (HIWORD(wParam) == BN_CLICKED && HWND(lParam) == hwndSaveButton) {
            // Save button clicked, retrieve values and save them to config file
            int typingSpeed, countdown;
            wchar_t speedText[11], countdownText[3];

            GetWindowText(hwndSpeedInput, speedText, 11);
            typingSpeed = std::stoi(speedText);

            GetWindowText(hwndCountdownInput, countdownText, 3);
            countdown = std::stoi(countdownText);

			if (Gui::mode) { Util::writeConfig(typingSpeed, countdown); }
			else { T_main::t_main(typingSpeed, countdown); }

        }
        return 1;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
