#ifndef VISION_H
#define VISION_H

#include "ofxKinect.h"
#include "Blob.h"

class Vision {

   public:
      Vision();
      void setup();
      void update();
      void draw(int x, int y, int width, int height);
      void exit();

      void setDepthThreshold(int near, int far);
      void setDepthThresholdNear(int near);
      void setDepthThresholdFar(int far);
      void learnBackground();

      bool isWithinObject(float x, float y);

   private:
      ofxKinect kinect;
      ofImage   source;
      ofImage   background;

      vector<Blob> blobs;

      int  thresholdNear;
      int  thresholdFar;

      bool bLearnBackground;
};
#endif
