#include "ofApp.h"
#include "Data.h"

//--------------------------------------------------------------
void ofApp::setup() {
#ifdef _DEBUG
    ofShowCursor();
#else
	ofHideCursor();
#endif
	// setup for nice jaggy-less rendering
	ofSetVerticalSync(true);
	ofBackground(0);
    
    ofPixels img;
    ofLoadImage(img,"background.png");
    background.loadData(img);
    
    ofLoadImage(img,"inicio.png");
    inicio.loadData(img);
    inicio.setAnchorPercent(0.5,0.5);
    inicio.color.setDuration(0.75f);
    inicio.setPosition(ofPoint(ofGetWidth()*0.95,ofGetHeight()*0.1));
    inicio.setColor(ofColor(255,0));
    
    data.setup();
    
	// load scenes
    sceneManager.add(new InicioScene(sceneManager,data,inicio));
    sceneManager.add(new MenuScene(sceneManager,data));
    sceneManager.add(new RamaScene(sceneManager,data));
    sceneManager.add(new ProvinciaScene(sceneManager,data));
    sceneManager.add(new UniversidadScene(sceneManager,data));
    sceneManager.add(new InfoScene(sceneManager,data));
    
    // overlap scenes when transitioning
    //sceneManager.setOverlap(true);
    
    //sceneManager.setup(true);	// true = setup all the scenes now (not on the fly)
	ofSetLogLevel("ofxSceneManager", OF_LOG_VERBOSE); // lets see whats going on inside
	
	// start with a specific scene
	// set now to true in order to ignore the scene fade and change now
	sceneManager.gotoScene(INICIO_SCENE_NAME, false);
	lastScene = sceneManager.getCurrentSceneIndex();
	
	// you can also turn off the auto sceneManager update and draw calls with:
	setSceneManagerUpdate(false);
	setSceneManagerDraw(false);
	//
	// the input callbacks in your scenes will be called if they are implemented
	//
	setSceneManager(&sceneManager);

	time = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update() {
	float t = ofGetElapsedTimef();
	float dt = t - time;
	time = t;
    
    sceneManager.update();
    
    inicio.update(dt);
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofSetColor(255);
    background.draw(0,0);
    sceneManager.draw();
    inicio.draw();
    
#ifdef _DEBUG
	// draw current scene info using the ofxBitmapString stream interface
	// to ofDrawBitmapString
	ofSetColor(255);
	ofxBitmapString(12, ofGetHeight()-8)
		<< "Current Scene: " << sceneManager.getCurrentSceneIndex()
		<< " " << sceneManager.getCurrentSceneName() << endl;
#endif
}

// current scene input functions are called automatically before calling these
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
		case 'd':
			bDebug = !bDebug;
			break;
			
		case 'f':
			ofToggleFullscreen();
			break;
	
		case OF_KEY_LEFT:
			sceneManager.prevScene();
			break;
			
		case OF_KEY_RIGHT:
			sceneManager.nextScene();
			break;
			
		case OF_KEY_DOWN:
			if(sceneManager.getCurrentScene()) { // returns NULL if no scene selected
				lastScene = sceneManager.getCurrentSceneIndex();
			}
			sceneManager.noScene();
			break;
			
		case OF_KEY_UP:
			sceneManager.gotoScene(lastScene);
			break;
        
        case 'o':
            sceneManager.setOverlap(!sceneManager.getOverlap());
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    switch (key) {
        case '0':
            data.resetFiltered();
            cout<<"Reset filters:"<<endl;
            data.printFiltered();
            break;
            
        case 'r':
            data.applyRamaFilter(&data.Ramas[ofRandom(data.Ramas.size())]);
            cout<<"Rama filter applied:"<<endl;
            data.printFiltered();
            break;
            
        case 'p':
            data.applyProvinciaFilter(&data.Provincias[ofRandom(data.Provincias.size())]);
            cout<<"Provincia filter applied:"<<endl;
            data.printFiltered();
            break;
            
        case 'u':
            data.applyUniversidadFilter(&data.Universidades[ofRandom(data.Universidades.size())]);
            cout<<"Universidad filter applied:"<<endl;
            data.printFiltered();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    if(inicio.inside(ofPoint(x,y))){
        sceneManager.gotoScene(INICIO_SCENE_NAME, false);
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

	// set up transforms with new screen size
	//setNewScreenSize(w, h);
}
