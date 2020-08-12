#include "Blob.h"

Blob::Blob() :
   area(0.0f),
   length(0.0f),
   boundingRect(),
   centroid(),
   hole(false),
   pts(),
   nPts(0) { }

void Blob::draw(float x = 0.0f, float y = 0.0f) {
   ofPushStyle();
   ofNoFill();
   ofSetHexColor(0x00FFFF);
   ofBeginShape();
   for (int i = 0; i < nPts; i++){
      ofVertex(x + pts[i].x, y + pts[i].y);
   }
   ofEndShape(true);
   ofSetHexColor(0xff0099);
   ofDrawRectangle(x + boundingRect.x, y + boundingRect.y, boundingRect.width, boundingRect.height);
   ofPopStyle();
}
