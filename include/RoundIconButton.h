#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/Texture.h"

#include "RoundButton.h"

namespace ui{

	class RoundIconButton : public RoundButton {
		public:
			RoundIconButton( ci::Vec2f pos, ci::Vec2f size, ci::gl::TextureRef tex );

			virtual void draw();
		private:
			RoundIconButton();

			ci::Vec2f halfTexSize;
			ci::gl::TextureRef texture;
	};

}