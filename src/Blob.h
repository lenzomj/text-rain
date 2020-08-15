#pragma once

#include "ofGraphics.h"
#include "ofPolyline.h"

class Blob {

public:

   Blob(const std::vector<glm::vec3> &points);

   bool isPointWithinContour(const glm::vec3 &point);

   glm::vec3 getNearestPointOnContour(const glm::vec3 &point);

   void draw();

private:
   ofPolyline contour;

};
