#pragma once

#include "cinder/app/App.h"

#include "Widget.h"
#include "MouseWidget.h"
#include "RoundButton.h"
#include "RoundIconButton.h"
#include "RoundValueButton.h"

class Toolbar{
	public:
		Toolbar();
		~Toolbar();

		void update();
		void draw();
		void resize();
		void setColor(int hexColor);
		ci::signals::signal<void( ci::Color )> colorChangeSignal;
		ci::signals::signal<void( ci::Color )> lineWidthChangeSignal;
		ci::signals::signal<void( ci::Color )> lineVarianceChangeSignal;

		ui::RoundValueButton* lineWidthButton;
		ui::RoundValueButton* lineVarianceButton;
		ui::RoundIconButton* clearButton;
		ui::RoundIconButton* saveButton;
	private:
		void createColorButton( int color );
		void onColorButtonRelease( ui::MouseWidget* button );

		ci::Rectf rect;
		std::deque<ui::MouseWidget*> buttons;
		std::deque<ui::RoundButton*> colorButtons;
};
