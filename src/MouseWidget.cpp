#include "MouseWidget.h"
#include "Config.h"

namespace ui{
	MouseWidget::MouseWidget() : Widget(){
		window = ci::app::getWindow();

		isDown = false;
		isOver = false;
		isDrag = false;
		isDraggable = false;
		isFocused = false;
		isToggleable = false;
		isSelected = false;

		focusColor = ci::Color::hex( Config::WIDGET_FOCUS_COLOR );

		mDownSignal = window->getSignalMouseDown().connect( std::bind( &MouseWidget::onMouseDown, this, std::_1 ) );
		mMoveSignal = window->getSignalMouseMove().connect( std::bind( &MouseWidget::onMouseMove, this, std::_1 ) );
		mDragSignal = window->getSignalMouseDrag().connect( std::bind( &MouseWidget::onMouseDrag, this, std::_1 ) );
		mUpSignal = window->getSignalMouseUp().connect( std::bind( &MouseWidget::onMouseUp, this, std::_1 ) );
	}

	MouseWidget::~MouseWidget() { 
		mDownSignal.disconnect();
		mMoveSignal.disconnect();
		mDragSignal.disconnect();
		mUpSignal.disconnect();
	}

	void MouseWidget::setFocused( bool value ){
		isFocused = value;
	}
	bool MouseWidget::getFocused(){
		return isFocused;
	}

	void MouseWidget::setToggleable( bool value ){
		isToggleable = value;
		if(!isToggleable)
			setSelected(false);
	}
	bool MouseWidget::getToggleable(){
		return isToggleable;
	}

	void MouseWidget::setSelected( bool value ){
		if(isToggleable)
			isSelected = value;
		else
			isSelected = false;
	}
	bool MouseWidget::getSelected(){
		return isSelected;
	}

	void MouseWidget::onMouseDown( ci::app::MouseEvent &event ){
		isOver = contains( event.getPos() );
		if( !isDown ){
			if( isOver ){
				isDown = true;
				clickPos.set( (float)event.getPos().x, (float)event.getPos().y );
				mouseDownSignal( this );
				//ci::app::console() << "MouseWidget::mouseDown" << std::endl;
			}
		}
	}

	void MouseWidget::onMouseMove( ci::app::MouseEvent &event ){
		isOver = contains( event.getPos() );
		mousePos = event.getPos();
	}

	void MouseWidget::onMouseUp( ci::app::MouseEvent &event ){
		isOver = contains( event.getPos() );
		if( isDown ){
			//ci::app::console() << "MouseWidget::mouseUp" << std::endl;
			if( isOver ){
				//ci::app::console() << "MouseWidget release" << std::endl;
				if(isToggleable)
					isSelected = !isSelected;
				releaseSignal( this );
			}
			if( isDrag ){
				//ci::app::console() << "MouseWidget stop drag" << std::endl;
				isDrag = false;
			}
			isDown = false;
			mouseUpSignal( this );
		}

		if( isDrag ) isDrag = false;
	}

	void MouseWidget::onMouseDrag( ci::app::MouseEvent &event ){
		isOver = contains( event.getPos() );
		if(isDraggable){
			if( isOver && isDown && !isDrag ){
				//ci::app::console() << "MouseWidget start drag" << std::endl;
				isDrag = true;
			}
		}
		mousePos = event.getPos();
	}

}