#include "ofMain.h"
#include "ofApp.h"

int main(){
#ifdef _DEBUG
	ofSetupOpenGL(1920, 1080, OF_WINDOW);
#else
	ofSetupOpenGL(1920, 1080, OF_FULLSCREEN);
#endif
	// this replaces ofRunApp() and kicks off the running of the app
	// with the app utils
	ofRunAppWithAppUtils(new ofApp());
}
