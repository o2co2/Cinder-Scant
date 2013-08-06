#pragma once

#include "cinder/app/App.h"

namespace ui{

	class Widget {
		public:

			Widget();
			virtual ~Widget();

			virtual void draw() = 0; // pure virtual - defined only in subclasses
			virtual void invalidate(); 
			virtual void update(); 

			virtual bool contains(ci::Vec2f point);

			void setSize(float w, float h);
			ci::Vec2f getSize();

			void setWidth(float w);
			float getWidth();

			void setHeight(float h);
			float getHeight();

			void setPosition(float x, float y);
			ci::Vec2f getPosition();

			void setColor(ci::Color c);
			void setColor(float r, float g, float b);
			ci::Color getColor();

		protected:
			ci::Rectf rect;
			ci::Vec2f size;
			ci::Vec2f pos;
			ci::Color color;
			ci::Color borderColor;
			ci::Color borderOverColor;
			ci::Color borderDownColor;
			float borderWidth;
			bool needsUpdate;
	};

}