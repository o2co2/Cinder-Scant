#include "Bg.h"
#include "Config.h"

using namespace ci;
using namespace ci::app;

Bg::Bg(){
	setColor( Config::BG_COLOR );
}

void Bg::setColor(int hexColor){
	color = Color::hex( hexColor );
}

void Bg::resize(){
	rect.set( 0, 0, (float)app::getWindowWidth(), (float)app::getWindowHeight() );
}

void Bg::draw(){
	gl::color( color );
	gl::drawSolidRect( rect );
}