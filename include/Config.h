#pragma once

#include <iostream>
#include "cinder/app/App.h"

struct Config{
	static const int APP_WIDTH = 930;
	static const int APP_HEIGHT = 650;

	static const int FPS = 200;

	static const int UNDO_LENGTH = 10;

	static const int BG_COLOR = 0x333333;
	static const int WIDGET_COLOR = 0xFFFFFF;
	static const int WIDGET_BORDER_WIDTH = 5;
	static const int WIDGET_BORDER_COLOR = 0x444444;
	static const int WIDGET_BORDER_OVER_COLOR = 0x666666;
	static const int WIDGET_BORDER_DOWN_COLOR = 0x444444;
	static const int WIDGET_FOCUS_COLOR = 0x888888;
	static const int BUTTON_VALUE_COLOR = 0x888888;
	static const int BUTTON_SIZE = 40;
	static const int BUTTON_SPACE = 16;

	static const int LABEL_COLOR = 0x666666;
	static const int CANVAS_COLOR = 0xFFFFFF;
	static const int DEFAULT_LINE_COLOR = 0x333333;

	static const int DEFAULT_LINE_SIZE = 4;
	static const int MIN_LINE_SIZE = 2;
	static const int MAX_LINE_SIZE = 25;
	static const int DEFAULT_LINE_VARIANCE = 1;
	static const int MAX_LINE_VARIANCE = 3;
};
