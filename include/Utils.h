#pragma once

#include "cinder/app/App.h"

namespace Utils{

	float distance( ci::Vec2f p1, ci::Vec2f p2 );
	float angleBetweenPoints( ci::Vec2f p1, ci::Vec2f p2 );
	bool ellipseContainsPoint( ci::Vec2f p1, ci::Vec2f centerPoint, ci::Vec2f size );

};
