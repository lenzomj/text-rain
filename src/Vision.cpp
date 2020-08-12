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
         Blob newBlob;
         newBlob.area = blob.area;
         newBlob.length = blob.length;
         newBlob.boundingRect = blob.boundingRect;
         newBlob.centroid = blob.centroid;
         newBlob.hole = blob.hole;
         newBlob.pts = blob.pts;
         newBlob.nPts = blob.nPts;
         blobs.push_back(newBlob);
      }
   }
}

void Vision::draw(int width, int height) {
   source.draw(0, 0, ofGetWidth(), ofGetHeight());
   for (auto & blob : blobs) {
      blob.draw(0, 0);
   }
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
