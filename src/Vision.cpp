#include "Vision.h"

#define DEFAULT_THRESHOLD_NEAR 230
#define DEFAULT_THRESHOLD_FAR  50

Vision::Vision() :
   kinect(),
   colorImage(),
   grayImage(),
   grayImageFg(),
   depthImage(),
   depthImageBg(),
   depthImageFg(),
   contourFinder(),
   thresholdNear(DEFAULT_THRESHOLD_NEAR),
   thresholdFar(DEFAULT_THRESHOLD_FAR),
   bLearnBackground(false) { }

void Vision::setup() {
   kinect.setRegistration(true);
   kinect.init();
   kinect.open();

   colorImage.allocate(kinect.width, kinect.height);
   grayImage.allocate(kinect.width, kinect.height);
   grayImageFg.allocate(kinect.width, kinect.height);
   depthImage.allocate(kinect.width, kinect.height);
   depthImageBg.allocate(kinect.width, kinect.height);
   depthImageFg.allocate(kinect.width, kinect.height);

   kinect.setCameraTiltAngle(15);
}

void Vision::update() {
   kinect.update();

   if(kinect.isFrameNew()) {

      colorImage.setFromPixels(kinect.getPixels());
      grayImage = colorImage;

      depthImage.setFromPixels(kinect.getDepthPixels());

      if(bLearnBackground) {
         depthImageBg = depthImage;
         bLearnBackground = false;
      }

      depthImageFg.absDiff(depthImageBg, depthImage);
      ofPixels &pix = depthImageFg.getPixels();
      int numPixels = pix.size();
      for(int i = 0; i < numPixels; i++) {
         if(pix[i] < thresholdNear && pix[i] > thresholdFar) {
            pix[i] = 255;
         } else {
            pix[i] = 0;
         }
      }

      contourFinder.findContours(depthImageFg, 50, (kinect.width*kinect.height)/3, 20, false);
   }

}

void Vision::draw(int width, int height) {
   grayImage.draw(0, 0, ofGetWidth(), ofGetHeight());
   contourFinder.draw(0, 0, ofGetWidth(), ofGetHeight());
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
