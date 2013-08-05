#include "Utils.h"
#include "cinder/CinderMath.h"

namespace Utils{

	float distance( ci::Vec2f p1, ci::Vec2f p2 ){
		float dx = p1.x - p2.x;
		float dy = p1.y - p2.y;
		return ci::math<float>::sqrt(dx*dx + dy*dy);
	}

	float angleBetweenPoints( ci::Vec2f p1, ci::Vec2f p2 ){
		float dx = p2.x - p1.x;
		float dy = p2.y - p1.y;
		float angleInDegrees = ci::math<float>::atan2(dy, dx) * 180 / (float)M_PI;
		return angleInDegrees;
	}

	bool ellipseContainsPoint( ci::Vec2f p1, ci::Vec2f centerPoint, ci::Vec2f size ){
		float dx = p1.x - centerPoint.x;
		float dy = p1.y - centerPoint.y;
		return ( dx * dx ) / ( size.x * size.x ) + ( dy * dy ) / ( size.y * size.y ) <= 1;
	}

};