#pragma once

#include "ofGraphics.h"

class Particle {

public:

   Particle(int xDrift, int yDrift) {
      this->xDrift = xDrift;
      this->yDrift = yDrift;
      randomize();
   }

   void randomize() {
      location.x = ofRandom(xDrift);
      location.y = ofRandom(yDrift);
      velocity = ofRandom(1.0, 10.0);
      value = ofRandom(0, 256);
   }

   void update() {
      velocity += 0.3;
      location.y += velocity;
      if(location.y > yDrift) {
         randomize();
         location.y = 0;
      }
   }

   void setXLocation(float x) {
      location.x = x;
   }

   void setYLocation(float y) {
      location.y = y;
   }

   void setLocation(const glm::vec3 &location) {
      this->location.x = location.x;
      this->location.y = location.y;
   }

   glm::vec3 getLocation() {
      return location;
   }

   void draw() {
      ofPushStyle();
      ofNoFill();
      // TODO: Enlarge font and randomize color
      //ofSetHexColor(0xffffff);
      //ofDrawCircle(location, 5);
      //ofSetHexColor(0xff0000);
      ofDrawBitmapString(value, location);
      ofPopStyle();
   }

private:
   int       xDrift;
   int       yDrift;
   glm::vec3 location;
   float     velocity;
   char      value;
};
