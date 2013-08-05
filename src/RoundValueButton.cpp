#include "RoundValueButton.h"
#include "cinder/CinderMath.h"
#include "Config.h"

namespace ui{

	RoundValueButton::RoundValueButton( ci::Vec2f pos, ci::Vec2f size, ci::gl::TextureRef tex, float value ) : RoundIconButton( pos, size, tex ) {
		isDraggable = true;
		startAngle = ci::toRadians(-90.0f);

		arcColor = ci::Color::hex( Config::BUTTON_VALUE_COLOR );
		setValue( value );
	}

	void RoundValueButton::onMouseDown( ci::app::MouseEvent &event ){
		MouseWidget::onMouseDown( event );
		if( isOver ){
			dragStartValue = value;
			ci::app::console() << "dragStartValue " << dragStartValue << std::endl;
		}
	}

	void RoundValueButton::update(){
		if(isDrag){
			float value = ci::math<float>::clamp( dragStartValue + (clickPos.y - mousePos.y) * .01f );
			setValue( value );
			updateArc();
		}
		if(needsUpdate){
			RoundIconButton::update();
			updateArc();
		}
	}

	void RoundValueButton::updateArc(){
		arcPath.clear();
		float endAngle = ci::lmap<float>( value, 0.0f , 1.0f , 0.0f , ci::toRadians(360.0f) ); 
		arcPath.arc( ci::Vec2f(0,0), getWidth()/2 + borderWidth/2, startAngle, endAngle + startAngle, true);
	}

	void RoundValueButton::draw(){
		RoundIconButton::draw(); 

		ci::gl::enableAlphaBlending();

		ci::gl::lineWidth( borderWidth );
		ci::gl::color( ci::ColorA( arcColor, alpha ) );
		ci::gl::pushModelView(); 
		ci::gl::translate( getPosition() );
		ci::gl::draw( arcPath );
		ci::gl::popModelView();

		ci::gl::disableAlphaBlending();
	}

	void RoundValueButton::setValue(float _value){
		value = ci::math<float>::clamp( _value, 0.0f, 1.0f);
		invalidate();
		valueChangeSignal( value );
	}
	float RoundValueButton::getValue(){
		return value; 
	}

	

}
