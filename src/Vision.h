#ifndef VISION_H
#define VISION_H

#include "ofxOpenCv.h"
#include "ofxKinect.h"

class Vision {

   public:
      Vision();
      void setup();
      void update();
      void draw(int width, int height);
      void exit();

      void setDepthThreshold(int near, int far);
      void setDepthThresholdNear(int near);
      void setDepthThresholdFar(int far);
      void learnBackground();

   private:
      ofxKinect kinect;
      ofxCvColorImage     colorImage;
      ofxCvGrayscaleImage grayImage;
      ofxCvGrayscaleImage grayImageFg;
      ofxCvGrayscaleImage depthImage;
      ofxCvGrayscaleImage depthImageBg;
      ofxCvGrayscaleImage depthImageFg;
      ofxCvContourFinder  contourFinder;

      int  thresholdNear;
      int  thresholdFar;

      bool bLearnBackground;
};
#endif
