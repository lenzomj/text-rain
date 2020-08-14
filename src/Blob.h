#pragma once

#include "ofGraphics.h"
#include "ofPolyline.h"

class Blob {

public:

   Blob(std::vector<ofDefaultVec3> &pts);

   void draw();

private:
   ofPolyline contour;

};
