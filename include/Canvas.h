#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/Fbo.h"

#include "Line.h"

class Canvas {
	public:
		Canvas( ci::Vec2f pos, ci::Vec2f size );

		void draw();
		void clear();
		
		//void updateRect();
		ci::Area getBounds();

		void setPosition(float x, float y);
		ci::Vec2f getPosition();

		void setSize(ci::Vec2f size);
		void setSize(float width, float height);
		ci::Vec2f getSize();

		void setColor(float r, float g, float b);
		void setColor(int hexColor);
		ci::Color getColor();

		void setLineColor(float r, float g, float b);
		void setLineColor(ci::Color color);
		ci::Color getLineColor();

		void setLineSize(float value);
		float getLineSize();

		void setLineVariance(float value);
		float getLineVariance();

		void setLineBlendMode(LineBlendMode bm);
		LineBlendMode getLineBlendMode();

		void addLine( ci::Vec2f endPos );
		void addLine( ci::Vec2f startPos, ci::Vec2f endPos );
		void saveUndo();
		void undo();
		void clearUndo();

	private:
		void initFbos();
		void drawLineToFbo( ci::gl::Fbo fbo, Line* line );
		void trimUndoLength();
		void clearFbo( ci::gl::Fbo target );

		ci::Vec2f size;
		ci::Vec2f pos;
		ci::Color color;
		ci::Color lineColor;
		float lineSize;
		float lineVariance;
		LineBlendMode lineBlendMode;

		ci::Vec2f lastEndPos;
		float pointRecordDelay;
		double lastPointRecordTime;
		float yOffset;

		ci::gl::Fbo::Format msaaFormat;
		ci::gl::Fbo fbo;
		ci::gl::Fbo undoFbo;

		ci::gl::TextureRef canvasTexture;

		std::deque<Line*> linesList; // Line segments
		std::deque<unsigned int> strokeIndexList; // Stroke indices
};