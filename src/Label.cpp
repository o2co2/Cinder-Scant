#include "Label.h"

namespace ui{

	Label::Label( std::string t, ci::gl::TextureFontRef f) : Widget() {
		setText( t );
		setFont( f );
	}

	void Label::draw(){
		ci::gl::enableAlphaBlending();
		ci::gl::color( color );
		ci::gl::pushModelView(); 
		ci::gl::translate( getPosition() );
		ci::gl::translate( -size.x*1.5f, -size.y/2 );
		font->drawString( text, size );
		ci::gl::popModelView();
		ci::gl::disableAlphaBlending();
	}

	void Label::textSizeToRect(){
		ci::Vec2f ts = font->measureString( text );
		setSize( ts.x, ts.y );
	}

	void Label::setText( std::string t ){
		text = t;
		if( font )
			textSizeToRect();
	}
	std::string Label::getText(){
		return text;
	}

	void Label::setFont( ci::gl::TextureFontRef f ){
		font = f;
		if( !text.empty() )
			textSizeToRect();
	}

}