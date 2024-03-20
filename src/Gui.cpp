#include "../include/Gui.hpp"


// Initialize static member variables
HWND Gui::hwndStartButton	= nullptr;		// Handle to the start button
HWND Gui::hwndStopButton	= nullptr;		// Handle to the stop button
Gui* Gui::currentInstance	= nullptr;		// Pointer to the current instance of the class


// Constructor with parameters
Gui::Gui(Config conf) : config(conf) {
    if (!this->config.getMode()) {
		this->buttonStart	= L"Start";
		this->buttonStop	= L"Stop";
	} else {
		this->buttonStart	= L"Save";
		this->buttonStop	= L"Cancel";
	}
}

// Change the status of the typing operation
void Gui::changeStatus(bool status) {
	this->config.setLocalStatus(status);
	Config::typingStatus = status;
}


// Function to create the GUI window
void Gui::createGUI() {
	// Register window class
	WNDCLASS wc			= {};
	wc.lpfnWndProc		= Gui::WindowProc; // Use the static member function
	wc.hInstance		= GetModuleHandle(NULL);
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName	= L"AutoTyperGUI";
	RegisterClass(&wc);
	Gui::currentInstance = this; // Store the current instance

	// Create window
	HWND hwnd = CreateWindowEx(0, L"AutoTyperGUI", L"Auto Typer Settings",
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT, 300, 180, // Increased height to accommodate the new button
		NULL, NULL, wc.hInstance, NULL);

	if (!hwnd) {
		MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// Load and set the icon for the window
	HICON baseIcon		= (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(TYPING_ICON), IMAGE_ICON, 0, 0, 0);
	HICON typingIcon	= (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(MAIN_ICON), IMAGE_ICON, 0, 0, 0);
	SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)baseIcon);

	// Create controls
	// Title for Speed Input
	CreateWindowEx(0, L"STATIC", L"Delay:", WS_CHILD | WS_VISIBLE, 10, 20, 100, 20, hwnd, NULL, NULL, NULL);
	this->hwndSpeedInput = CreateWindowEx(0, L"EDIT", std::to_wstring(this->config.getLocalSpeed()).c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
		120, 20, 100, 25, hwnd, NULL, NULL, NULL);
	SendMessage(this->hwndSpeedInput, EM_SETLIMITTEXT, 10, 0);

	// Title for Countdown Input
	CreateWindowEx(0, L"STATIC", L"Countdown:", WS_CHILD | WS_VISIBLE, 10, 60, 100, 20, hwnd, NULL, NULL, NULL);
	this->hwndCountdownInput = CreateWindowEx(0, L"EDIT", std::to_wstring(this->config.getLocalCountdown()).c_str(), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
		120, 60, 100, 25, hwnd, NULL, NULL, NULL);
	SendMessage(this->hwndCountdownInput, EM_SETLIMITTEXT, 2, 0);

	// Save button on the left side
	this->hwndStartButton = CreateWindowEx(0, L"BUTTON", this->buttonStart, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		30, 100, 100, 30, hwnd, reinterpret_cast<HMENU>(1), NULL, NULL);

	// Stop button on the right side
	this->hwndStopButton = CreateWindowEx(0, L"BUTTON", this->buttonStop, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		160, 100, 100, 30, hwnd, reinterpret_cast<HMENU>(2), NULL, NULL);

	// Apply modern font
	HFONT hFont = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Segoe UI");
	SendMessage(this->hwndSpeedInput,		WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(this->hwndCountdownInput,	WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(this->hwndStartButton,		WM_SETFONT, WPARAM(hFont), TRUE);
	SendMessage(this->hwndStopButton,		WM_SETFONT, WPARAM(hFont), TRUE);

	// Show window
	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);


	// Run message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		// Change the icon based on the typing status
		if ( Config::typingStatus )	SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)baseIcon);
		else						SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)typingIcon);
	}
}



// Function to handle messages for the GUI window
LRESULT CALLBACK Gui::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_COMMAND:
			if (HIWORD(wParam) == BN_CLICKED) {
				if		(HWND(lParam) == currentInstance->hwndStartButton)		currentInstance->handleStartButton();
				else if (HWND(lParam) == currentInstance->hwndStopButton)	currentInstance->handleStopButton();
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}



// This function accesses non-static members to handles the save button click
void Gui::handleStartButton() {
	if (Config::typingStatus) return;
	this->changeStatus(true);

	std::cout << "Start button clicked" << std::endl;
	// Save button clicked, retrieve values and save them to config file
		wchar_t speedText[11], countdownText[3];

	GetWindowText(this->hwndSpeedInput, speedText, 11);
	this->config.setLocalSpeed(std::stoi(speedText));

	GetWindowText(this->hwndCountdownInput, countdownText, 3);
	this->config.setLocalCountdown(std::stoi(countdownText));

	// Save the values to the configuration file
	if (this->config.getMode())	this->config.writeConfig();
	else{
		// Launch a separate thread to execute the typing operation
		std::thread typingThread([this]() {
			T_main::t_main(this->config);
			this->changeStatus(false);
		});
		typingThread.detach(); // Detach the thread so it runs independently
	}

}



// This function accesses non-static members to handles the stop button click
void Gui::handleStopButton() {
	this->changeStatus(false);
	std::cout << "Stop button clicked" << std::endl;
	// Stop button clicked, perform stop action
	if (this->config.getMode())	this->config.updateConfig(this->config.getLocalSpeed(), this->config.getLocalCountdown(), false);			
}
