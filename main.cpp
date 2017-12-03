#include "Gui.h"
#include "Window.h"
#include "Panel.h"

#include <iostream>

#include "Event.h"

void e_key() { std::cout << "e_key\n"; }
void e_char() { std::cout << "e_char\n"; }
void e_cursorpos() { std::cout << "e_cursorpos\n"; }
void e_cursorenter() { std::cout << "e_cursorenter\n"; }
void e_mousebutton() { std::cout << "e_mousebutton\n"; }
void e_scroll() { std::cout << "e_scroll\n"; }

int main() {
	Gui gui;
	gui.Init();
	
	Window w(&gui, 500, 500, "Window");
	Window w2(&gui, 300, 300, "Window2");

	gui.connect(&w, Signal(INPUT_EVENT, INPUT_KEY, GLFW_KEY_E, GLFW_PRESS), &e_key);
	gui.connect(&w, Signal(INPUT_EVENT, INPUT_CHAR, 'a'), &e_char);
	gui.connect(&w.windowPanel, Signal(INPUT_EVENT, INPUT_CURSORPOS), &e_cursorpos);
	gui.connect(&w, Signal(INPUT_EVENT, INPUT_CURSORENTER, INPUT_CURSOR_ENTERED), &e_cursorenter);
    gui.connect(&w.windowPanel, Signal(INPUT_EVENT, INPUT_MOUSEBUTTON, GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS), &e_mousebutton);
    gui.connect(&w, Signal(INPUT_EVENT, INPUT_SCROLL), &e_scroll);

	auto EventLoop = std::async(std::launch::async, &Gui::EventLoop, &gui);
	gui.eventLoopThread = std::move(EventLoop);

	return 0;
}