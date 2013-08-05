#include "RoundButton.h"
#include "Config.h"
#include "Utils.h"

namespace ui{

	RoundButton::RoundButton( ci::Vec2f _pos, ci::Vec2f _size ) : MouseWidget() {
		setPosition( _pos.x, _pos.y );
		setSize( _size.x, _size.y );
	}

	void RoundButton::draw(){
		float r1 = getWidth() * .5f;
		float r2 = getHeight() * .5f;

		if(isDown){
			ci::gl::color( borderDownColor );
		}else if(isFocused){
			ci::gl::color( focusColor );
		}else if(isOver){
			ci::gl::color(  borderOverColor );
		}else{
			ci::gl::color( borderColor );
		}

		ci::gl::drawSolidEllipse( getPosition(), r1 + borderWidth, r2 + borderWidth );
		ci::gl::color( color );
		ci::gl::drawSolidEllipse( getPosition(), r1, r2 );
	}

	bool RoundButton::contains(ci::Vec2f point){
		return Utils::ellipseContainsPoint( point, pos, size/2 );
	}

}
