#pragma once

#include <iostream>

#include "cinder/app/App.h"

#include "Widget.h"

namespace ui{

	class MouseWidget : public Widget {
		public:
			MouseWidget();
			virtual ~MouseWidget();

			void setFocused( bool value );
			bool getFocused();

			void setToggleable( bool value );
			bool getToggleable();

			void setSelected( bool value );
			bool getSelected();

			ci::signals::signal<void( MouseWidget* )> mouseDownSignal;
			ci::signals::signal<void( MouseWidget*, ci::Vec2i )> dragSignal;
			ci::signals::signal<void( MouseWidget* )> releaseSignal;
			ci::signals::signal<void( MouseWidget* )> mouseUpSignal;

		protected:
			virtual void onMouseDown( ci::app::MouseEvent &event );
			virtual void onMouseMove( ci::app::MouseEvent &event );
			virtual void onMouseDrag( ci::app::MouseEvent &event );
			virtual void onMouseUp( ci::app::MouseEvent &event );

			bool isOver;
			bool isDown;
			bool isDrag;
			bool isDraggable;
			bool isFocused;
			bool isToggleable;
			bool isSelected;

			ci::Vec2f mousePos;
			ci::Vec2f clickPos;
			ci::Color focusColor;

			ci::app::WindowRef window;
			ci::signals::scoped_connection mDownSignal, mMoveSignal, mDragSignal, mUpSignal;
	};

}