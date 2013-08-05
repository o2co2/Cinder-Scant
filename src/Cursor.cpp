#include "Cursor.h"
#include "Config.h"

using namespace ci;
using namespace ci::app;

Cursor::Cursor() {
	setMode( Cursor::BRUSH_UP );
	setSize( (float)Config::DEFAULT_LINE_SIZE );
	setColor( Color::hex(Config::DEFAULT_LINE_COLOR) );
	visible = false;
};

void Cursor::show(){
	visible = true;
}
void Cursor::hide(){
	visible = false;
}

float Cursor::isVisible(){
	return visible;
}

void Cursor::setMode(Cursor::Mode mode){
	this->mode = mode;
}
Cursor::Mode Cursor::getMode(){
	return mode;
}

void Cursor::setSize(float size){
	this->size = size;
}
float Cursor::getSize(){
	return size;
}

void Cursor::setColor(float r, float g, float b){
	color.set( r, g, b );
}
void Cursor::setColor(Color c){
	color.set( c.r, c.g, c.b );
}
ci::Color Cursor::getColor(){
	return color;
}

void Cursor::draw( Vec2f mousePos ){
	if(visible){
		//gl::enableAlphaBlending();
		glLineWidth( 2 );
		gl::color(color);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
		switch(mode){
			case BRUSH_UP:
				gl::drawStrokedCircle(mousePos, size/2);
				break;
			case BRUSH_DOWN:
				gl::drawSolidCircle(mousePos, size/2);
				break;
		}
		glDisable(GL_BLEND);
		//gl::disableAlphaBlending();
	}
}
