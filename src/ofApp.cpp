#include "ofApp.h"

#define RAIN_DENSITY 100

//--------------------------------------------------------------
void ofApp::setup(){
   ofSetLogLevel(OF_LOG_VERBOSE);
   ofSetFrameRate(30);
   ofBackground(100, 100, 100);

   // enable depth->video image calibration
   kinect.setRegistration(true);

   kinect.init();
   kinect.open();

   colorImage.allocate(kinect.width, kinect.height);
   grayImage.allocate(kinect.width, kinect.height);
   grayImageBg.allocate(kinect.width, kinect.height);
   grayImageFg.allocate(kinect.width, kinect.height);

   bLearnBackground = true;
   thresholdValue = 50; //70

   kinect.setCameraTiltAngle(15);

   for (int i = 0; i < RAIN_DENSITY; i++) {
      ofPoint point = ofPoint(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
      rain.push_back(point);
      text.push_back(ofRandom(0, 256));
      velocities.push_back(ofRandom(1.0,10.0));
   }
}

//--------------------------------------------------------------
void ofApp::update(){

   kinect.update();

   if(kinect.isFrameNew()) {

      colorImage.setFromPixels(kinect.getPixels());
      //grayImage.setFromPixels(kinect.getDepthPixels());
      grayImage = colorImage;
      grayImage.blurGaussian();

      if(bLearnBackground) {
         grayImageBg = grayImage;
         bLearnBackground = false;
      }

      grayImageFg.absDiff(grayImageBg, grayImage);
      grayImageFg.threshold(thresholdValue);

      //contourFinder.findContours(grayImageFg, 10, (kinect.width*kinect.height)/3, 20, false);

      for (int i = 0; i< RAIN_DENSITY; i++) {

         int smW = rain[i].x / ofGetWidth() * kinect.width;
         int smH = rain[i].y / ofGetHeight() * kinect.height;
         int p = (smW + smH*kinect.width);

         if (grayImageFg.getPixels()[p] < 127) {
            velocities[i] += 0.3;
            rain[i].y += velocities[i];
            if (rain[i].y > ofGetHeight()) {
                rain[i].y = 0;
                rain[i].x = ofRandom(ofGetWidth());
                text[i] = ofRandom(0, 256);
                velocities[i] = ofRandom(1, 10);
            }
         } else {
            /*int pAbove = (smW + (smH-1)*kinect.width);
            if (grayImageFg.getPixels()[pAbove] > 127) {
               rain[i].y -= 1;
               if (rain[i].y < 0) {
                  rain[i].y = 0;
               }
            }*/
         }
      }
   }
}

//--------------------------------------------------------------
void ofApp::draw(){

   //grayImageFg.draw(10, 10, ofGetWidth(), ofGetHeight());


   //kinect.drawDepth(10, 10, 400, 300);
   //kinect.draw(420, 10, 400, 300);

   // Top-Left
	//colorImage.draw (10,  10,  400, 300);

   // Top-Right
	//grayImage.draw  (420, 10,  400, 300);

   // Bottom-Left
	//grayImageBg.draw(10 , 320, 400, 300);
   //grayImageFg.draw(10 , 320, 400, 300);

   // Bottom-Right
   //contourFinder.draw(420, 320, 400, 300);
	//grayImageFg.draw(420, 320, 400, 300);
   /*ofNoFill();
	ofDrawRectangle(420,320,400,300);
	int numBlobs = contourFinder.nBlobs;
	for (int i=0; i<numBlobs; i++){
		contourFinder.blobs[i].draw(420, 320);
	}*/

   ofSetHexColor(0xffffff);
   colorImage.draw(0, 0, ofGetWidth(), ofGetHeight());

   for (int i = 0; i< RAIN_DENSITY; i++) {
      ofNoFill();
      ofSetHexColor(0xffffff);
      ofDrawCircle(rain[i], 5);
      ofSetHexColor(0xff0000);
      ofDrawBitmapString(text[i], rain[i]);
    }

	stringstream reportStream;
   reportStream << "(" << ofGetMouseX() << ", " << ofGetMouseY() << "): " << endl;
   ofDrawBitmapString(reportStream.str(), 10, 10);
}

void ofApp::exit() {
   //kinect.setCameraTiltAngle(0);
   kinect.close();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
   switch (key) {
      case ' ':
         bLearnBackground = true;
         break;
   }
}

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
