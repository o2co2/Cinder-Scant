#pragma once

#include "cinder/app/App.h"

#include "MouseWidget.h"

namespace ui{

	class RoundButton : public MouseWidget {
		public:
			RoundButton( ci::Vec2f pos, ci::Vec2f size );

			virtual void draw();
			virtual bool contains(ci::Vec2f point);

		protected:
			RoundButton(){};
	};

}