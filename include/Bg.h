#pragma once

#include "cinder/app/App.h"

class Bg {
	public:
		Bg();
		void draw();
		void resize();
		void setColor(int hexColor);

	private:
		ci::Rectf rect;
		ci::Color color;
};
