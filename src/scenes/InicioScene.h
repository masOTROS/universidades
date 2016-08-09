#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "Data.h"

class InicioScene : public ofxScene {
public:
    // set the scene name through the base class initializer
    InicioScene(ofxSceneManager& sm, Data& d) : sceneManager(sm), data(d), ofxScene(INICIO_SCENE_NAME, false) {
        ofImage img;
        ofLoadImage(img,"00_Inicio/titulo-01.png");
        title.loadData(img);
        title.setAnchorPercent(0.5,0.5);
        title.position.setDuration(2.);
        title.position.setCurve(BOUNCY);
    }
    
    // scene setup
    void setup() {
        title.setPosition(ofGetWidth()*0.5,-ofGetHeight()*0.6);
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
		
        // called on first enter update
        if(isEnteringFirst()) {
            title.position.animateTo(ofPoint(ofGetWidth()*0.5,ofGetHeight()*0.5));
            ofLogNotice(INICIO_SCENE_NAME) << "update enter";
        }
        
        update();
		
        // call finishedEntering() to indicate scne is done entering
        if(!title.isOrWillBeAnimating()) {
            finishedEntering();
            ofLogNotice(INICIO_SCENE_NAME) << "update enter done";
        }
    }
    
    // normal update
    void update() {
        float t = ofGetElapsedTimef();
        float dt = t - time;
        time = t;
        title.update(dt);
    }
    
    // called when scene is exiting
    void updateExit() {
		
        // called on first exit update
        if(isExitingFirst()) {
            title.position.animateTo(ofPoint(ofGetWidth()*0.5,ofGetHeight()*1.6));
            
            ofLogNotice(INICIO_SCENE_NAME) << "update exit";
        }
        
        update();
		
        // call finishedExiting() to indicate scene is done exiting
        if(!title.isOrWillBeAnimating()) {
            finishedExiting();
            ofLogNotice(INICIO_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {        
        title.draw();
    }
    
    // cleanup
    void exit() {
        ofLogNotice(INICIO_SCENE_NAME) << "exit";
    }
    
    void mousePressed(int x, int y, int button){
        if(isExiting())
            return;
        sceneManager.gotoScene(MENU_SCENE_NAME);
    }
    
    ofxAnimatableObject<ofTexture> title;
    float time;
    
    Data& data;
    ofxSceneManager& sceneManager;
};
