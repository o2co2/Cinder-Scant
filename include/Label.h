#pragma once

#include <iostream>

#include "cinder/App/App.h"
#include "cinder/gl/TextureFont.h"

#include "Widget.h"

namespace ui{

	class Label : public Widget {
		public:
			Label( std::string t, ci::gl::TextureFontRef f);

			void draw();

			void setText( std::string t );
			std::string getText();

			void setFont( ci::gl::TextureFontRef f );

		protected:
			Label() {};

			void textSizeToRect();

			std::string text;
			int fontSize;
			ci::gl::TextureFontRef font;
	};

}