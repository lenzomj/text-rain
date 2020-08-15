#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Vision.h"
#include "Particle.h"
#include "ofxBox2d.h"

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

      Vision vision;

      ofxPanel     pnlConfig;
      ofxIntSlider barThresholdNear;
      ofxIntSlider barThresholdFar;

      bool bShowConfig;

      vector<Particle> particles;
      vector<Blob> blobs;
};

