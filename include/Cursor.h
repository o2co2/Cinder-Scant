#pragma once

#include "cinder/app/App.h"

class Cursor {
	public:
		enum Mode{
			BRUSH_UP,
			BRUSH_DOWN
		};

		Cursor();

		void show();
		void hide();
		float isVisible();
		void draw( ci::Vec2f mousePos );

		void setMode(Mode mode);
		Mode getMode();

		void setSize(float size);
		float getSize();

		void setColor(float r, float g, float b);
		void setColor(ci::Color c);
		ci::Color getColor();

	private:
		Mode mode;
		bool visible;
		float size;
		ci::Color color;
};