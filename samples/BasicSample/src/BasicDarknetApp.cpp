#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Log.h"

#include "cinder/darknet/CinderYolo.h"

using namespace ci;
using namespace ci::app;

class BasicDarknetApp : public App {
public:
    void setup() final;
    void update() final;
    void draw() final;
	void keyDown( KeyEvent event ) final;
    
private:
	std::unique_ptr<yolo::CinderYolo> mCiDarknet;
	Surface32fRef mSurface;
	std::vector<yolo::CinderYolo::Detection> mDetectedObjects;
	gl::TextureRef mTexture;
	float mThreshold{ .1f };
};

void BasicDarknetApp::setup()
{
	mCiDarknet = std::make_unique<yolo::CinderYolo>( getAssetPath( "yolov3-tiny.cfg" ), getAssetPath( "yolov3-tiny.weights" ), getAssetPath( "coco.names" ) );
	mSurface = Surface32f::create( loadImage( loadAsset( "dog.jpg" ) ) );
	mTexture = gl::Texture::create( *(mSurface.get() ) );
}

void BasicDarknetApp::update()
{
	if( mCiDarknet && mSurface ) {
		mCiDarknet->runYolo( *mSurface.get(), mThreshold );
	}
}

void BasicDarknetApp::draw()
{
	gl::clear( Color( .2f, .2f, .2f ) );
	auto detections = mCiDarknet->getDetections();
	gl::draw( mTexture );
	for( const auto& detectedObject : detections ) {
			gl::ScopedColor scopedColor( detectedObject.mColor );
			gl::drawStrokedRect( detectedObject.mBoundingRect );
			gl::ScopedBlend scopedBlend( true );
			auto labelBgUL = detectedObject.mBoundingRect.getUpperLeft() - vec2( .0f, 20.f );
			auto labelBgBR = labelBgUL + vec2( 50.0f, 20.f );
			gl::drawSolidRect( Rectf( labelBgUL, labelBgBR ) ); 
			gl::drawString( detectedObject.mLabel, detectedObject.mBoundingRect.getUpperLeft() - vec2( 0.f, 10.f ), Color::black() );
	}
}

void BasicDarknetApp::keyDown( KeyEvent event )
{
	if( event.getChar() == 'i' ) {
		mThreshold += .05f;
		mThreshold = std::min( mThreshold, 1.0f );
		std::cout << "THRES " << mThreshold << std::endl;
	}
	else if( event.getChar() == 'd' ) {
		mThreshold -= .05f;
		mThreshold = std::max( mThreshold, 0.0f );
		std::cout << "THRES " << mThreshold << std::endl;
	}
}

CINDER_APP( BasicDarknetApp, RendererGl );