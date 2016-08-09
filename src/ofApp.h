#pragma once

#include "ofMain.h"
#include "ofxAppUtils.h"
#include "ofxAnimatableObject.h"

#include "scenes/scenes.h"
#include "Data.h"

#define _DEBUG

class ofApp : public ofxApp { // <-- inherits ofxApp instead of ofBaseApp
	
	public:
	
		ofApp()  {}
	
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
		void windowResized(int w, int h);
		
		// handles the scenes
		ofxSceneManager sceneManager;
		int lastScene;
        
        ofTexture background;
        ofxAnimatableObject<ofTexture> inicio;
    
    Data data;
    
		float time;
};
