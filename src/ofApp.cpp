#include "ofApp.h"

#define RAIN_DENSITY 200

//--------------------------------------------------------------
void ofApp::setup(){
   ofSetLogLevel(OF_LOG_VERBOSE);
   ofSetFrameRate(30);
   ofBackground(28, 28, 28);

   pnlConfig.setup();
   barThresholdNear.addListener(this, &ofApp::thresholdNearChanged);
   barThresholdFar.addListener(this, &ofApp::thresholdFarChanged);
   pnlConfig.add(barThresholdNear.setup("Near: ",
                                       230,
                                        0, 255));
   pnlConfig.add(barThresholdFar.setup("Far: ",
                                      50,
                                       0, 255));
   bShowConfig = false;

   vision.setup();

   for (int i = 0; i < RAIN_DENSITY; i++) {
      Particle p(vision.getViewWidth(), vision.getViewHeight());
      particles.push_back(p);
   }
}

//--------------------------------------------------------------
void ofApp::update(){

   blobs.clear();

   vision.update(blobs);

   for(auto &particle : particles) {
      particle.update();
      for(auto &blob : blobs) {
         if(blob.isPointWithinContour(particle.getLocation())) {
            glm::vec3 onContour = blob.getNearestPointOnContour(particle.getLocation());
            particle.setLocation(onContour);
         }
      }
   }
}

//--------------------------------------------------------------
void ofApp::draw(){

   float scalex = (float)ofGetWidth()/vision.getViewWidth();
   float scaley = (float)ofGetHeight()/vision.getViewHeight();

   ofSetHexColor(0x66ff66);

   ofPushMatrix();
   ofScale(scalex, scaley, 1.0f);
   //vision.draw();

   for(auto &blob : blobs) {
      blob.draw();
   }

   for(auto &particle : particles) {
      particle.draw();
   }

	stringstream reportStream;
   reportStream << "(" << ofGetMouseX() << ", " << ofGetMouseY() << "): " << endl;
   ofDrawBitmapString(reportStream.str(), 10, 10);

   ofPopMatrix();

   if(bShowConfig) {
      pnlConfig.draw();
   }
}

void ofApp::exit() {
   vision.exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
   switch (key) {
      case ' ':
         vision.learnBackground();
         //bLearnBackground = true;
         break;
      case 'c':
         bShowConfig = !bShowConfig;
         break;
      /*case 'b':
         float w = ofRandom(4, 20);
		   float h = ofRandom(4, 20);
         auto box = make_shared<ofxBox2dRect>();
		   box->setPhysics(3.0, 0.53, 0.1);
		   box->setup(box2d.getWorld(), mouseX, mouseY, w, h);
         boxes.push_back(box);
         break;*/
   }
}

void ofApp::thresholdNearChanged(int &newThresholdNear) {
   vision.setDepthThresholdNear(newThresholdNear);
   //thresholdNear = newThresholdNear;
}

void ofApp::thresholdFarChanged(int &newThresholdFar) {
   vision.setDepthThresholdFar(newThresholdFar);
   //thresholdFar = newThresholdFar;
}

/*
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
*/
