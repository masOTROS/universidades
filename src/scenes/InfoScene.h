#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "Data.h"

class InfoScene : public ofxScene {
    
public:
    
    // set the scene name through the base class initializer
    InfoScene(ofxSceneManager& sm, Data& d) : sceneManager(sm), data(d), ofxScene(INFO_SCENE_NAME, false) {
        
        ofImage img;
        ofLoadImage(img,"05_Ranking/titulo0.png");
        title.loadData(img);
        title.setAnchorPercent(0.5,0.5);
        title.setPosition(ofPoint(ofGetWidth()*0.5,ofGetHeight()*0.2));
        
        rankingFont.load("DIN-LightAlternate.ttf",32);
        rankingFontSmall.load("DIN-LightAlternate.ttf",16);
        
        ofLoadImage(img,"05_Ranking/positionsBack.png");
        rankingBack.loadData(img);
        rankingBack.setAnchorPercent(0.,0.6);
    }
    
    // scene setup
    void setup() {
        
        title.setColor(255,0);
        ofPixels img;
        ofLoadImage(img,"05_Ranking/titulo.png");
        title.allocate(img.getWidth(),img.getHeight(),GL_RGBA);
        title.loadData(img);
        title.setAnchorPercent(0.5,0.5);
        
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
		
        // called on first enter update
        if(isEnteringFirst()) {
            title.color.animateTo(ofColor(255,255));
    
            ofLogNotice(INFO_SCENE_NAME) << "update enter";
        }
        
        update();
		
        // call finishedEntering() to indicate scne is done entering
        if(!title.isOrWillBeAnimating()) {
            finishedEntering();
            ofLogNotice(INFO_SCENE_NAME) << "update enter done";
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
            title.color.animateTo(ofColor(255,0));
            
            ofLogNotice(INFO_SCENE_NAME) << "update exit";
        }
        
        update();
		
        // call finishedExiting() to indicate scene is done exiting
        if(!title.isOrWillBeAnimating()) {
            finishedExiting();
            ofLogNotice(INFO_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {
        title.draw();
    }
    
    // cleanup
    void exit() {
        ofLogNotice(INFO_SCENE_NAME) << "exit";
    }
    
    void mousePressed(int x, int y, int button){
        if(isExiting())
            return;
        sceneManager.gotoScene(INICIO_SCENE_NAME);
    }
    
    ofxAnimatableObject<ofTexture> title;
    ofTexture rankingBack,selectedBack;
    ofTrueTypeFont rankingFont,rankingFontSmall;
    float time;
    
    Data& data;
    ofxSceneManager& sceneManager;
};
