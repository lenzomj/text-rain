#pragma once

#include "ofGraphics.h"
//#include "ofRectangle.h"
//#include "ofMathConstants.h"

class Blob {

public:

   float             area;
   float             length;
   ofRectangle       boundingRect;
   ofDefaultVec3     centroid;
   bool              hole;

   std::vector<ofDefaultVec3> pts;    // the contour of the blob
   int                        nPts;   // number of pts;

   Blob();
   void draw(float x, float y);
};
