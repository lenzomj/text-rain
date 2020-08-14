#include "ofApp.h"

#define RAIN_DENSITY 100
//#define DEFAULT_THRESHOLD_NEAR 230
//#define DEFAULT_THRESHOLD_FAR  50

//--------------------------------------------------------------
void ofApp::setup(){
   ofSetLogLevel(OF_LOG_VERBOSE);
   ofSetFrameRate(30);
   ofBackground(100, 100, 100);

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
      ofPoint point = ofPoint(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
      rain.push_back(point);
      text.push_back(ofRandom(0, 256));
      velocities.push_back(ofRandom(1.0,10.0));
   }
}

//--------------------------------------------------------------
void ofApp::update(){

   vision.update();

      /*for (int i = 0; i< RAIN_DENSITY; i++) {

         int smW = rain[i].x / ofGetWidth() * kinect.width;
         int smH = rain[i].y / ofGetHeight() * kinect.height;
         int p = (smW + smH*kinect.width);

         if (depthImageFg.getPixels()[p] < 127) {
            velocities[i] += 0.3;
            rain[i].y += velocities[i];
            if (rain[i].y > ofGetHeight()) {
                rain[i].y = 0;
                rain[i].x = ofRandom(ofGetWidth());
                text[i] = ofRandom(0, 256);
                velocities[i] = ofRandom(1, 10);
            }
         } else {
            int pAbove = (smW + (smH-velocities[i])*kinect.width);
            if (depthImageFg.getPixels()[pAbove] > 127) {
               rain[i].y -= velocities[i];
               if (rain[i].y < 0) {
                  rain[i].y = 0;
               }
            }
         }
      }
   }*/
   //ofRemove(boxes, ofxBox2dBaseShape::shouldRemoveOffScreen);
}

//--------------------------------------------------------------
void ofApp::draw(){

   ofSetHexColor(0xffffff);

   //depthImageFg.draw(10, 10, ofGetWidth(), ofGetHeight());


   //kinect.drawDepth(10, 10, 400, 300);
   //kinect.draw(420, 10, 400, 300);

   // Top-Left
	//colorImage.draw (10,  10,  400, 300);

   // Top-Right
	//depthImage.draw  (420, 10,  400, 300);

   // Bottom-Left
	//depthImageBg.draw(10 , 320, 400, 300);
   //depthImageFg.draw(10 , 320, 400, 300);

   // Bottom-Right
   //contourFinder.draw(420, 320, 400, 300);
	//depthImageFg.draw(420, 320, 400, 300);
   /*ofNoFill();
	ofDrawRectangle(420,320,400,300);
	int numBlobs = contourFinder.nBlobs;
	for (int i=0; i<numBlobs; i++){
		contourFinder.blobs[i].draw(420, 320);
	}*/

   //grayImage.draw(0, 0, ofGetWidth(), ofGetHeight());
   //contourFinder.draw(0, 0, ofGetWidth(), ofGetHeight());

   /*ofScale((ofGetWidth() / kinect.width), (ofGetHeight() / kinect.height), 1);
   ofSetColor(255,0,0); // red
   for (int i = 0; i < contourFinder.nBlobs; i++){
      ofxCvBlob& blob = contourFinder.blobs[i];
      blob.draw(0, 0);
   }
   ofSetColor(255,255,255); // reset to white
   ofScale(1,1,1);*/

    //for(auto &box : boxes) {
    //     ofFill();
    //     ofSetHexColor(0xe63b8b);
    //     box->draw();
    //  }
    //
    vision.draw(0, 0, ofGetWidth(), ofGetHeight());


   for (int i = 0; i< RAIN_DENSITY; i++) {
      //ofNoFill();
      //ofSetHexColor(0xffffff);
      //ofDrawCircle(rain[i], 5);
      //ofSetHexColor(0xff0000);
      ofSetHexColor(0xffffff);
      ofDrawBitmapString(text[i], rain[i]);
    }

	stringstream reportStream;
   reportStream << "(" << ofGetMouseX() << ", " << ofGetMouseY() << "): " << endl;
   ofDrawBitmapString(reportStream.str(), 10, 10);

   if(bShowConfig) {
      pnlConfig.draw();
   }

}

void ofApp::exit() {
   vision.exit();
   //kinect.setCameraTiltAngle(0);
   //kinect.close();
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
