#include "Blob.h"

Blob::Blob(std::vector<ofDefaultVec3> &pts) {
   for (auto &p : pts) {
      contour.addVertex(p);
   }
   contour.close();
}

void Blob::draw() {
   ofPushStyle();
   ofNoFill();
   ofSetHexColor(0x00FFFF);
   ofBeginShape();
   for (auto &p : contour.getVertices()) {
      ofVertex(p.x, p.y);
   }
   ofEndShape(true);
   ofSetHexColor(0xff0099);
   ofRectangle boundingRect = contour.getBoundingBox();
   ofDrawRectangle(boundingRect.x, boundingRect.y, boundingRect.width, boundingRect.height);
   ofPopStyle();
}
