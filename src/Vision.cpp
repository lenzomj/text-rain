#include "Vision.h"
#include "Blob.h"
#include "ofxOpenCv.h"

#define DEFAULT_THRESHOLD_NEAR 230
#define DEFAULT_THRESHOLD_FAR  50

Vision::Vision() :
   kinect(),
   source(),
   background(),
   thresholdNear(DEFAULT_THRESHOLD_NEAR),
   thresholdFar(DEFAULT_THRESHOLD_FAR),
   bLearnBackground(false) { }

void Vision::setup() {
   kinect.setRegistration(true);
   kinect.init();
   kinect.open();

   source.allocate(kinect.width, kinect.height, OF_IMAGE_COLOR);
   background.allocate(kinect.width, kinect.height, OF_IMAGE_GRAYSCALE);

   kinect.setCameraTiltAngle(15);
}

bool Vision::isWithinObject(float x, float y) {
   for(auto &blob : blobs) {
      // Check within object.
   }
   return false;
}

void Vision::update() {

   ofxCvGrayscaleImage depthField;
   ofxCvGrayscaleImage depthFieldBg;
   ofxCvGrayscaleImage depthFieldFg;

   depthField.allocate(kinect.width, kinect.height);
   depthFieldBg.allocate(kinect.width, kinect.height);
   depthFieldFg.allocate(kinect.width, kinect.height);

   ofxCvContourFinder  contourFinder;

   kinect.update();

   if(kinect.isFrameNew()) {

      blobs.clear();

      source.setFromPixels(kinect.getPixels());
      depthField.setFromPixels(kinect.getDepthPixels());

      depthFieldBg.setFromPixels(background.getPixels());
      if(bLearnBackground) {
         background.setFromPixels(depthField.getPixels());
         bLearnBackground = false;
      }

      depthFieldFg.absDiff(depthFieldBg, depthField);
      ofPixels &pix = depthFieldFg.getPixels();
      int numPixels = pix.size();
      for(int i = 0; i < numPixels; i++) {
         if(pix[i] < thresholdNear && pix[i] > thresholdFar) {
            pix[i] = 255;
         } else {
            pix[i] = 0;
         }
      }

      contourFinder.findContours(depthFieldFg, 50, (kinect.width*kinect.height)/3, 20, false);
      for(auto &blob : contourFinder.blobs) {
         blobs.push_back(Blob(blob.pts));
      }
   }
}

void Vision::draw(int x = 0,
                  int y = 0,
                  int width = 0,
                  int height = 0) {

   float scalex = 1.0f;
   float scaley = 1.0f;

   if (width != 0) {
      scalex = (float)width / (float)kinect.width;
   }

   if (height != 0) {
      scaley = (float)height / (float)kinect.height;
   }

   source.draw(x, y, width, height);

   ofPushMatrix();
   ofScale(scalex, scaley, 1.0f);
   for (auto & blob : blobs) {
      blob.draw();
   }
   ofPopMatrix();

  /* float scalex = 0.0f;
    float scaley = 0.0f;
    if( _width != 0 ) { scalex = w/_width; } else { scalex = 1.0f; }
    if( _height != 0 ) { scaley = h/_height; } else { scaley = 1.0f; }

    if(bAnchorIsPct){
        x -= anchor.x * w;
        y -= anchor.y * h;
    }else{
        x -= anchor.x;
        y -= anchor.y;
    }

    ofPushStyle();
	// ---------------------------- draw the bounding rectangle
	ofSetHexColor(0xDD00CC);
    ofPushMatrix();
    ofTranslate( x, y, 0.0 );
    ofScale( scalex, scaley, 0.0 );

	ofNoFill();
	for( int i=0; i<(int)blobs.size(); i++ ) {
		ofDrawRectangle( blobs[i].boundingRect.x, blobs[i].boundingRect.y,
                        blobs[i].boundingRect.width, blobs[i].boundingRect.height );
	}

	// ---------------------------- draw the blobs
	ofSetHexColor(0x00FFFF);

	for( int i=0; i<(int)blobs.size(); i++ ) {
		ofNoFill();
		ofBeginShape();
		for( int j=0; j<blobs[i].nPts; j++ ) {
			ofVertex( blobs[i].pts[j].x, blobs[i].pts[j].y );
		}
		ofEndShape();

	}
	ofPopMatrix();
	ofPopStyle();
*/

}

void Vision::exit() {
   kinect.close();
}

void Vision::setDepthThresholdNear(int near) {
   // TODO: Check bounds
   thresholdNear = near;
}

void Vision::setDepthThresholdFar(int far) {
   // TODO: Check bounds
   thresholdFar = far;
}

void Vision::setDepthThreshold(int near, int far) {
   setDepthThresholdNear(near);
   setDepthThresholdFar(far);
}

void Vision::learnBackground() {
   bLearnBackground = true;
}
