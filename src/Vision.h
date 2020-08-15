#ifndef VISION_H
#define VISION_H

#include "ofxKinect.h"
#include "Blob.h"

class Vision {

   public:
      Vision();
      void setup();
      void update(std::vector<Blob> &blobs);
      void draw();
      void exit();

      void setDepthThreshold(int near, int far);
      void setDepthThresholdNear(int near);
      void setDepthThresholdFar(int far);
      void learnBackground();

      int getViewHeight();
      int getViewWidth();

   private:
      ofxKinect kinect;
      ofImage   source;
      ofImage   background;

      int  thresholdNear;
      int  thresholdFar;

      bool bLearnBackground;
};
#endif
