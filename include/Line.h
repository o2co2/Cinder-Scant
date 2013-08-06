#pragma once

#include "cinder/app/App.h"

enum LineBlendMode{ LINE_BLEND_NORMAL, LINE_BLEND_MULTIPLY };

struct Line{
	ci::Vec2f startPos;
	ci::Vec2f endPos;
	ci::Color color;
	float width;
	LineBlendMode blendMode;
};
