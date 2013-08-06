#include "Widget.h"
#include "Config.h"

namespace ui{

	Widget::Widget(){
		setSize( 20.0f, 20.0f );
		setPosition( 0.0f, 0.0f );
		color = ci::Color::hex( Config::WIDGET_COLOR );
		borderColor = ci::Color::hex( Config::WIDGET_BORDER_COLOR );
		borderOverColor = ci::Color::hex( Config::WIDGET_BORDER_OVER_COLOR );
		borderDownColor = ci::Color::hex( Config::WIDGET_BORDER_DOWN_COLOR );
		borderWidth = (float) Config::WIDGET_BORDER_WIDTH;

		invalidate();
	}

	Widget::~Widget() { 
	}

	void Widget::invalidate(){
		needsUpdate = true;
	}

	void Widget::update(){
		if(needsUpdate){
			rect.set( pos.x, pos.y, size.x, size.y);
			needsUpdate = false;
			//ci::app::console() << "Widget::update " <<  this << std::endl;
		}
	}

	bool Widget::contains(ci::Vec2f point){
		return rect.contains(point);
	}

	/*ci::Rectf Widget::getRect(){
		return rect;
	}*/

	void Widget::setSize(float w, float h){
		size.set( w, h );
		invalidate();
	}
	ci::Vec2f Widget::getSize(){
		return size;
	}

	void Widget::setWidth(float w){
		size.x = w;
		invalidate();
	}
	float Widget::getWidth(){
		return size.x;
	}

	void Widget::setHeight(float h){
		size.y = h;
		invalidate();
	}
	float Widget::getHeight(){
		return size.y;
	}

	void Widget::setPosition(float x, float y){
		pos.set( x, y );
		invalidate();
	}
	ci::Vec2f Widget::getPosition(){
		return pos;
	}

	void Widget::setColor(ci::Color c){
		color.set( c.r, c.g, c.b );
	}
	void Widget::setColor(float r, float g, float b){
		color.set( r, g, b );
	}
	ci::Color Widget::getColor(){
		return color;
	}
}