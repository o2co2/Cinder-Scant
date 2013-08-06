#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"

#include "Toolbar.h"
#include "Config.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;

Toolbar::Toolbar(){
	createColorButton( Config::DEFAULT_LINE_COLOR );
	createColorButton( 0x999999 );
	createColorButton( 0xF3F3F3 );
	createColorButton( 0xFFFFFF );
	createColorButton( 0xF2EECB );
	createColorButton( 0xF7BD8D );
	createColorButton( 0xF2AD2B );
	createColorButton( 0xE45F3C );
	createColorButton( 0x665543 );
	createColorButton( 0x2B6490 );
	createColorButton( 0x268691 );

	colorButtons[0]->setFocused( true );
	colorChangeSignal( colorButtons[0]->getColor() );

	gl::TextureRef wTex = gl::Texture::create( loadImage( loadResource( ICON_W ) ) );
	gl::TextureRef vTex = gl::Texture::create( loadImage( loadResource( ICON_V ) ) );
	gl::TextureRef mTex = gl::Texture::create( loadImage( loadResource( ICON_M ) ) );
	gl::TextureRef cTex = gl::Texture::create( loadImage( loadResource( ICON_C ) ) );
	gl::TextureRef sTex = gl::Texture::create( loadImage( loadResource( ICON_S ) ) );

	Vec2f buttonSize = Vec2f((float)Config::BUTTON_SIZE, (float)Config::BUTTON_SIZE);

	lineWidthButton = new ui::RoundValueButton( Vec2f(0,0), buttonSize, wTex, .5f );
	lineWidthButton->setValue( (float)Config::DEFAULT_LINE_SIZE / ((float)Config::MAX_LINE_SIZE - (float)Config::MIN_LINE_SIZE) );
	buttons.push_back( lineWidthButton );

	lineVarianceButton = new ui::RoundValueButton( Vec2f(0,0), buttonSize, vTex, .5f );
	lineVarianceButton->setValue( (float)Config::DEFAULT_LINE_VARIANCE / (float)Config::MAX_LINE_VARIANCE );
	buttons.push_back( lineVarianceButton );

	blendMultiplyButton = new ui::RoundIconButton( Vec2f(0,0), buttonSize, mTex );
	blendMultiplyButton->setToggleable( true );
	buttons.push_back( blendMultiplyButton );

	clearButton = new ui::RoundIconButton( Vec2f(0,0), buttonSize, cTex );
	buttons.push_back( clearButton );

	saveButton = new ui::RoundIconButton( Vec2f(0,0), buttonSize, sTex );
	buttons.push_back( saveButton );
}

Toolbar::~Toolbar() { 
	for each (ui::MouseWidget* b in colorButtons)
		b->releaseSignal.disconnect_all_slots();
}

void Toolbar::createColorButton( int hexColor ){
	Color color = Color::hex( hexColor );
	ui::RoundButton* b = new ui::RoundButton( Vec2f(0.0f,0.0f), Vec2f((float)Config::BUTTON_SIZE, (float)Config::BUTTON_SIZE) );
	b->setColor( color.r, color.g, color.b );
	b->releaseSignal.connect( std::bind( &Toolbar::onColorButtonRelease, this, std::_1 ) );
	colorButtons.push_back( b );
	buttons.push_back( b );
}

void Toolbar::onColorButtonRelease( ui::MouseWidget* button ) {
	for each (ui::RoundButton* b in colorButtons){
		b->setFocused( false );
	}
	button->setFocused( true );
	colorChangeSignal( button->getColor() );
}

void Toolbar::resize(){
	float xOffset = 50.0f + Config::BUTTON_SIZE/2;
	float y = app::getWindowHeight() - 50.0f;
	for (int i=0; i<(int)buttons.size(); i++) {
		ui::MouseWidget* b = buttons.at(i);
		b->setPosition( (float)(i * (Config::BUTTON_SIZE + Config::BUTTON_SPACE) + xOffset ), (float)y );
	}
}

void Toolbar::update(){
	for each (ui::MouseWidget* b in buttons)
		b->update();
}

void Toolbar::draw(){
	for each (ui::MouseWidget* b in buttons)
		b->draw();
}