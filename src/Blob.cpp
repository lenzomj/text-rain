#include "Blob.h"

Blob::Blob(const std::vector<glm::vec3> &points) {
   ofPolyline outline;
   for (auto &point : points) {
      outline.addVertex(point);
   }
   outline.close();
   contour = outline.getSmoothed(2, 1);
}

bool Blob::isPointWithinContour(const glm::vec3 &point) {
   return ofInsidePoly(point.x, point.y, contour.getVertices());
}

glm::vec3 Blob::getNearestPointOnContour(const glm::vec3 &point) {
   return contour.getClosestPoint(point);
}

void Blob::draw() {
   ofPushStyle();
   ofNoFill();
   ofBeginShape();
   for (auto &point : contour.getVertices()) {
      ofVertex(point.x, point.y);
   }
   ofEndShape(true);
   //TODO: Optional bounding box
   /*ofSetHexColor(0xff0099);
   ofRectangle boundingRect = contour.getBoundingBox();
   ofDrawRectangle(boundingRect.x,
                   boundingRect.y,
                   boundingRect.width,
                   boundingRect.height);*/
   ofPopStyle();
}
