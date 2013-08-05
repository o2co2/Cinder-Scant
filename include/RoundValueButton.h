#pragma once

#include "cinder/app/App.h"
#include "cinder/Path2d.h"

#include "RoundIconButton.h"

namespace ui{

	class RoundValueButton : public RoundIconButton {
		public:
			RoundValueButton( ci::Vec2f pos, ci::Vec2f size, ci::gl::TextureRef tex, float value );

			virtual void update();
			virtual void draw();

			void setValue(float value);
			float getValue();

			ci::signals::signal<void( float value )> valueChangeSignal;
		private:
			RoundValueButton();
			virtual void onMouseDown( ci::app::MouseEvent &event );
			void updateArc();

			float value;
			float startAngle;
			float dragStartValue;
			ci::Color arcColor;
			ci::Path2d arcPath; 
	};

}