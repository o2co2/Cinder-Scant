#include "RoundIconButton.h"
#include "cinder/CinderMath.h"
#include "Config.h"

namespace ui{

	RoundIconButton::RoundIconButton( ci::Vec2f _pos, ci::Vec2f _size, ci::gl::TextureRef tex ) : RoundButton() {
		setPosition( _pos.x, _pos.y );
		setSize( _size.x, _size.y );
		setColor( ci::Color::hex(Config::BG_COLOR) );
		texture = tex;
		halfTexSize = texture->getSize() / 2;
	}

	void RoundIconButton::draw(){
		RoundButton::draw(); 

		/*float a = isDown ? ci::math<float>::max(0, getAlpha()-0.2f) : getAlpha();
		float s = getScale();*/

		if(texture){
			ci::gl::enableAlphaBlending();
			ci::gl::color( ci::Color( 1.0f, 1.0f, 1.0f ) );
			ci::gl::pushModelView(); 
			ci::gl::translate( getPosition() - halfTexSize );
			//ci::gl::rotate( getRotation() );
			//ci::gl::scale( s, s );
			ci::gl::draw( texture );
			ci::gl::popModelView();
			ci::gl::disableAlphaBlending();	
		}
	}


}
