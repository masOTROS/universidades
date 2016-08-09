#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "Data.h"

class MenuScene : public ofxScene {
    
public:
    
    // set the scene name through the base class initializer
    MenuScene(ofxSceneManager& sm, Data& d) : sceneManager(sm), data(d), ofxScene(MENU_SCENE_NAME, false) {
        ofImage img;
        
        ofLoadImage(img,"01_Menu/titulo.png");
        title.loadData(img);
        title.setAnchorPercent(0.5,0.5);
        title.setPosition(ofPoint(ofGetWidth()*0.5,ofGetHeight()*0.2));
        
        ofLoadImage(img,"01_Menu/rama.png");
        rama.loadData(img);
        rama.setAnchorPercent(0.5,0.5);
        rama.setPosition(ofPoint(ofGetWidth()*0.25,ofGetHeight()*0.5));
        
        ofLoadImage(img,"01_Menu/provincia.png");
        provincia.loadData(img);
        provincia.setAnchorPercent(0.5,0.5);
        provincia.setPosition(ofPoint(ofGetWidth()*0.5,ofGetHeight()*0.5));
        
        ofLoadImage(img,"01_Menu/universidad.png");
        universidad.loadData(img);
        universidad.setAnchorPercent(0.5,0.5);
        universidad.setPosition(ofPoint(ofGetWidth()*0.75,ofGetHeight()*0.5));
    }
    
    // scene setup
    void setup() {
        title.setColor(ofColor(255,0));

        rama.setColor(ofColor(255,0));
        rama.setSize(1.);
        
        provincia.setColor(ofColor(255,0));
        provincia.setSize(1.);
        
        universidad.setColor(ofColor(255,0));
        universidad.setSize(1.);

        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
		
        // called on first enter update
        if(isEnteringFirst()) {
            title.color.animateTo(ofColor(255,255));
            
            rama.color.animateTo(ofColor(255,255));
            provincia.color.animateTo(ofColor(255,255));
            universidad.color.animateTo(ofColor(255,255));
            
            ofLogNotice(MENU_SCENE_NAME) << "update enter";
        }
        
        update();
		
        // call finishedEntering() to indicate scne is done entering
        if(!rama.isOrWillBeAnimating() && !provincia.isOrWillBeAnimating() && !universidad.isOrWillBeAnimating()) {
            finishedEntering();
            ofLogNotice(MENU_SCENE_NAME) << "update enter done";
        }
    }
    
    // normal update
    void update() {
        float t = ofGetElapsedTimef();
        float dt = t - time;
        time = t;
        title.update(dt);
        rama.update(dt);
        provincia.update(dt);
        universidad.update(dt);
    }
    
    // called when scene is exiting
    void updateExit() {
		
        // called on first exit update
        if(isExitingFirst()) {            
            
            title.color.animateTo(ofColor(255,0));
            
            rama.color.animateTo(ofColor(255,0));
            provincia.color.animateTo(ofColor(255,0));
            universidad.color.animateTo(ofColor(255,0));
            
            ofLogNotice(MENU_SCENE_NAME) << "update exit";
        }
        
        update();
		
        // call finishedExiting() to indicate scene is done exiting
        if(!rama.isOrWillBeAnimating() && !provincia.isOrWillBeAnimating() && !universidad.isOrWillBeAnimating()) {
            finishedExiting();
            ofLogNotice(MENU_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {
        title.draw();
        
        rama.draw();
        provincia.draw();
        universidad.draw();
    }
    
    // cleanup
    void exit() {
        ofLogNotice(MENU_SCENE_NAME) << "exit";
    }
    
    void mousePressed(int x, int y, int button){
        if(isExiting())
            return;
        if(rama.inside(ofPoint(x,y))){
            sceneManager.gotoScene(RAMA_SCENE_NAME);
        }
        else if(provincia.inside(ofPoint(x,y))){
            sceneManager.gotoScene(PROVINCIA_SCENE_NAME);
        }
        else if(universidad.inside(ofPoint(x,y))){
            sceneManager.gotoScene(UNIVERSIDAD_SCENE_NAME);
        }
    }
    
    ofxAnimatableObject<ofTexture> title;
    ofxAnimatableObject<ofTexture> rama,provincia,universidad;
    float time;
    
    Data& data;
    ofxSceneManager& sceneManager;
};
