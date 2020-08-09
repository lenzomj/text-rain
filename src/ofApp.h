#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

#define CANVAS_WIDTH 1024
#define CANVAS_HEIGHT 768

class ofApp : public ofBaseApp{

   public:
      void setup();
      void update();
      void draw();
      void exit();

      void keyPressed(int key);
      void thresholdNearChanged(int &newThresholdNear);
      void thresholdFarChanged(int &newThresholdFar);
      //void keyReleased(int key);
      //void mouseMoved(int x, int y );
      //void mouseDragged(int x, int y, int button);
      //void mousePressed(int x, int y, int button);
      //void mouseReleased(int x, int y, int button);
      //void mouseEntered(int x, int y);
      //void mouseExited(int x, int y);
      //void windowResized(int w, int h);
      //void dragEvent(ofDragInfo dragInfo);
      //void gotMessage(ofMessage msg);

      ofxKinect kinect;
      ofxCvColorImage     colorImage;
      ofxCvGrayscaleImage depthImage;
      ofxCvGrayscaleImage depthImageBg;
      ofxCvGrayscaleImage depthImageFg;
      ofxCvGrayscaleImage depthImageFgNear;
      ofxCvGrayscaleImage depthImageFgFar;
      ofxCvContourFinder  contourFinder;

      int  thresholdNear;
      int  thresholdFar;

      ofxPanel     pnlConfig;
      ofxIntSlider barThresholdNear;
      ofxIntSlider barThresholdFar;

      bool bShowConfig;
      bool bLearnBackground;

      vector<ofPoint> rain;
      vector<char> text;
      vector<float> velocities;
};

