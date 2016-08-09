#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"

class RamaScene : public ofxScene {
public:
    
    // set the scene name through the base class initializer
    RamaScene(ofxSceneManager& sm, Data& d) : sceneManager(sm), data(d), ofxScene(RAMA_SCENE_NAME, false) {
        ofImage img;
        ofLoadImage(img,"02_Rama/selector.png");
        selector.loadData(img);
        selector.setAnchorPercent(0.6,0.55);
        selector.setPosition(ofPoint(ofGetWidth()*0.5,ofGetHeight()*0.5));
    }
    
    // scene setup
    void setup() {
        selector.setColor(ofColor(255,0));
        selector.setSize(1.);
        
        ramas.clear();
        ramas.assign(data.filteredRamas.size(),ofxAnimatableObject<ofTrueTypeFont>());
        
        for(int i=0; i<data.filteredRamas.size(); i++){
            ramas[i].ofTrueTypeFont::load("verdana.ttf",32);
            ramas[i].ofTrueTypeFont::setLineHeight(32);
            ramas[i].setText(data.filteredRamas[i]->nombre);
            ramas[i].setAnchorPercent(0.5,0.5);
            ramas[i].setSize(1.);
            ramas[i].setPosition(ofGetWidth()*0.5, ofGetHeight()*0.5 - 75*data.filteredRamas.size()/2 + i*75);
            ramas[i].setColor(ofColor(255,0));
        }
        
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
		
        // called on first enter update
        if(isEnteringFirst()) {
            selector.color.animateToAfterDelay(ofColor(255,255),0.0);
            
            for(int i=0;i<ramas.size();i++){
                ramas[i].color.animateTo(ofColor(255,255));
            }
            
            ofLogNotice(RAMA_SCENE_NAME) << "update enter";
        }
        
        update();
		
        // call finishedEntering() to indicate scne is done entering
        if(!selector.isOrWillBeAnimating()) {
            finishedEntering();
            ofLogNotice(RAMA_SCENE_NAME) << "update enter done";
        }
    }
    
    // normal update
    void update() {
        float t = ofGetElapsedTimef();
        float dt = t - time;
        time = t;
        selector.update(dt);
        
        for(int i=0;i<ramas.size();i++){
            ramas[i].update(dt);
        }
    }
    
    // called when scene is exiting
    void updateExit() {
		
        // called on first exit update
        if(isExitingFirst()) {
            selector.color.animateTo(ofColor(255,0));
            
            for(int i=0;i<ramas.size();i++){
                ramas[i].color.animateTo(ofColor(255,0));
            }

            ofLogNotice(RAMA_SCENE_NAME) << "update exit";
        }
        
        update();
		
        // call finishedExiting() to indicate scene is done exiting
        if(!selector.isOrWillBeAnimating()) {
            finishedExiting();            
            ofLogNotice(RAMA_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {
        selector.draw();
        
        for(int i=0;i<ramas.size();i++){
            ramas[i].draw();
        }
    }
    
    // cleanup
    void exit() {
        ofLogNotice(RAMA_SCENE_NAME) << "exit";
    }
    
    void mousePressed(int x, int y, int button){
        if(isExiting())
            return;
        
        for(int i=0;i<ramas.size();i++){
            if(ramas[i].inside(ofPoint(x,y))){
                data.applyRamaFilter(data.filteredRamas[i]);
                ramas[i].size.animateTo(1.15);
                sceneManager.gotoScene(PROVINCIA_SCENE_NAME);
                break;
            }
        }
    }
    
    ofxAnimatableObject<ofTexture> selector;
    vector< ofxAnimatableObject<ofTrueTypeFont> > ramas;
    float time;

    Data& data;
    ofxSceneManager& sceneManager;
};
