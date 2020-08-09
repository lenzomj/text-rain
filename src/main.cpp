#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
   // Options: OF_WINDOW or OF_FULLSCREEN
	ofSetupOpenGL(CANVAS_WIDTH , CANVAS_HEIGHT, OF_FULLSCREEN);
	ofRunApp(new ofApp());
}
