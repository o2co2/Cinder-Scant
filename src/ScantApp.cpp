#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Utilities.h"
#include "cinder/ImageIo.h"
#include "cinder/Font.h"
#include "cinder/gl/TextureFont.h"

#include "Resources.h"
#include "Config.h"
#include "Cursor.h"
#include "Bg.h"
#include "Toolbar.h"
#include "Canvas.h"
#include "MouseWidget.h"
#include "RoundButton.h"
#include "Label.h"
#include "Line.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ScantApp : public AppNative {
	public:
		void prepareSettings( Settings *settings );
		void setup();
		void resize();
		void mouseMove( MouseEvent event );	
		void mouseDown( MouseEvent event );	
		void mouseDrag( MouseEvent event );	
		void mouseUp( MouseEvent event );
		void mouseWheel( MouseEvent event );
		void keyDown (KeyEvent event);
		void update();
		void draw();
	private:
		void onLineColorChange( Color color );
		void onLineWidthChange( float value );
		void onLineVarianceChange( float value );
		void onBlendMultiplyButtonRelease();
		void onClearButtonRelease();
		void onSaveButtonRelease();
		Vec2f calcCanvasSize();

		Cursor cursor;
		Bg bg;
		Toolbar* toolbar;
		Canvas* canvas;
		ui::Label* titleLabel;

		Vec2f mousePos;
		bool isClick;
		bool isRelease;
		bool isMouseDown;
		bool isDrag;
		bool isDrawing;

		ci::gl::TextureFontRef font;
};

void ScantApp::prepareSettings( Settings *settings ) {
	settings->setWindowSize( Config::APP_WIDTH, Config::APP_HEIGHT );
	//settings->setResizable( false );
	settings->setFrameRate( (float)Config::FPS );
}

void ScantApp::setup(){
	gl::disableVerticalSync();

	getWindow()->setTitle("Scant");

	isClick = false;
	isRelease = false;
	isDrag = false;
	isMouseDown = false;
	isDrawing = false;

	Font f( Font( loadResource( UI_FONT ), 33 ) );
    font = ci::gl::TextureFont::create( f );
	titleLabel = new ui::Label( "SCANT", font );
	titleLabel->setColor( Color::hex(Config::LABEL_COLOR) );

	canvas = new Canvas( Vec2f(50.0f, 50.0f), calcCanvasSize() );

	toolbar = new Toolbar();
	toolbar->colorChangeSignal.connect( std::bind(&ScantApp::onLineColorChange, this, std::_1));
	toolbar->lineWidthButton->valueChangeSignal.connect( std::bind( &ScantApp::onLineWidthChange, this, std::_1 ) );
	toolbar->lineVarianceButton->valueChangeSignal.connect( std::bind( &ScantApp::onLineVarianceChange, this, std::_1 ) );
	toolbar->blendMultiplyButton->releaseSignal.connect( std::bind( &ScantApp::onBlendMultiplyButtonRelease, this ) );
	toolbar->clearButton->releaseSignal.connect( std::bind( &ScantApp::onClearButtonRelease, this ) );
	toolbar->saveButton->releaseSignal.connect( std::bind( &ScantApp::onSaveButtonRelease, this ) );

	//ci::app::console() << "GL_LINE_WIDTH_RANGE " << GL_LINE_WIDTH_RANGE << std::endl;
}

void ScantApp::mouseDown( MouseEvent event ){
	isClick = true;
	isMouseDown = true;
}

void ScantApp::mouseMove( MouseEvent event ){
	mousePos.set( event.getPos() );
}

void ScantApp::mouseDrag( MouseEvent event ){
	mousePos.set( event.getPos() );
	isDrag = true;
}

void ScantApp::mouseUp( MouseEvent event ){
	isDrag = false;
	isMouseDown = false;
	isRelease = true;
}

void ScantApp::mouseWheel( MouseEvent event ){

}

void ScantApp::keyDown (KeyEvent event){
	if( event.getCode() == KeyEvent::KEY_UP ) {
		toolbar->lineWidthButton->setValue( toolbar->lineWidthButton->getValue() + 0.02f );
	}

	if( event.getCode() == KeyEvent::KEY_DOWN ) {
		toolbar->lineWidthButton->setValue( toolbar->lineWidthButton->getValue() - 0.02f );
	}
	
	if( event.isControlDown() ){
		if( event.getCode() == KeyEvent::KEY_z ) {
			canvas->undo();
		}
	}
}

void ScantApp::resize(){
	bg.resize();
	toolbar->resize();
	canvas->setSize( calcCanvasSize() );
	canvas->setPosition( 50.0f, 50.0f );

	titleLabel->setPosition( 50.0f + titleLabel->getWidth()/2, 22.0f );
}

void ScantApp::update(){
	if( canvas->getBounds().contains( mousePos )  ){
		if(!cursor.isVisible()){
			hideCursor();
			cursor.show();
		}
	}else{
		if(cursor.isVisible()){
			showCursor();
			cursor.hide();
		}
	}

	if(isClick){
		isClick = false;
		if( canvas->getBounds().contains( mousePos )  ){
			isDrawing = true;
			//canvas->saveUndo();
			cursor.setMode( Cursor::BRUSH_DOWN );
			canvas->addLine( mousePos, mousePos );
		}
	}

	if(isRelease){
		isRelease = false;
		isDrawing = false;
		cursor.setMode( Cursor::BRUSH_UP );
		canvas->saveUndo();
	}

	if(isDrawing && isDrag){
		canvas->addLine( mousePos );
	}

	toolbar->update();
}

void ScantApp::draw(){
	gl::clear( Color( 1.0f, 1.0f, 1.0f ) ); 
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	bg.draw();

	titleLabel->draw();

	canvas->draw();

	toolbar->draw();

	cursor.draw( mousePos );

	//gl::drawString( "FPS: " + toString( (int)getAverageFps() ), Vec2f( 10.0f, 10.0f ), Color::white() );
}

Vec2f ScantApp::calcCanvasSize(){
	float w = ci::math<float>::clamp( getWindowWidth() - 100.0f, 0.0f, 3000.0f );
	float h = ci::math<float>::clamp( getWindowHeight() - 150.0f, 0.0f, 3000.0f );
	return Vec2f( w, h );
}

//*****************************************************************************
// SIGNALS
//*****************************************************************************

void ScantApp::onLineColorChange( Color color ) {
	canvas->setLineColor( color.r, color.g, color.b );
	cursor.setColor( color.r, color.g, color.b );
}

void ScantApp::onLineWidthChange( float value ){
	float size = ((float)Config::MAX_LINE_SIZE - (float)Config::MIN_LINE_SIZE) * value + (float)Config::MIN_LINE_SIZE;
	canvas->setLineSize( size );
	cursor.setSize( size );
}

void ScantApp::onLineVarianceChange( float value ){
	float variance = (float)Config::MAX_LINE_VARIANCE * value;
	canvas->setLineVariance( variance );
}

void ScantApp::onBlendMultiplyButtonRelease(){
	if( toolbar->blendMultiplyButton->getSelected() )
		canvas->setLineBlendMode( LINE_BLEND_MULTIPLY );
	else
		canvas->setLineBlendMode( LINE_BLEND_NORMAL );
}

void ScantApp::onClearButtonRelease( ) {
	canvas->clear();
}

void ScantApp::onSaveButtonRelease( ) {
	Surface s = copyWindowSurface( canvas->getBounds() );
	vector<string> ext = vector<string>();
	ext.push_back("png");
	//fs::path pngPath = getSaveFilePath( getHomeDirectory().string() + "scant.png" , ext );
	fs::path pngPath = getSaveFilePath( "", ext );
	if( !pngPath.empty() ) {
		writeImage( pngPath, s, ImageTarget::Options(), "png" );
	}
}

CINDER_APP_NATIVE( ScantApp, RendererGl )