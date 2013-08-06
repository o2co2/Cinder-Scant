#include "RoundIconButton.h"
#include "cinder/CinderMath.h"
#include "Config.h"

namespace ui{

	RoundIconButton::RoundIconButton( ci::Vec2f pos, ci::Vec2f size, ci::gl::TextureRef tex ) : RoundButton( pos, size ) {
		setColor( ci::Color::hex(Config::BG_COLOR) );
		texture = tex;
		halfTexSize = texture->getSize() / 2;
	}

	void RoundIconButton::draw(){
		RoundButton::draw(); 

		if(texture){
			ci::gl::enableAlphaBlending();
			ci::gl::color( ci::Color( 1.0f, 1.0f, 1.0f ) );
			ci::gl::pushModelView(); 
			ci::gl::translate( getPosition() - halfTexSize );
			ci::gl::draw( texture );
			ci::gl::popModelView();
			ci::gl::disableAlphaBlending();	
		}
	}


}
