#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "Data.h"


class UniversidadScene : public ofxScene {
    
public:
    
    // set the scene name through the base class initializer
    UniversidadScene(ofxSceneManager& sm, Data& d) : sceneManager(sm), data(d), ofxScene(UNIVERSIDAD_SCENE_NAME, false) {
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
        
        universidades.clear();
        universidades.assign(data.filteredUniversidades.size(),ofxAnimatableObject<ofTrueTypeFont>());
        
        for(int i=0; i<data.filteredUniversidades.size(); i++){
            universidades[i].ofTrueTypeFont::load("verdana.ttf",32);
            universidades[i].ofTrueTypeFont::setLineHeight(32);
            universidades[i].setText(data.filteredUniversidades[i]->nombre);
            universidades[i].setAnchorPercent(0.5,0.5);
            universidades[i].setSize(1.);
            universidades[i].setPosition(ofGetWidth()*0.5, ofGetHeight()*0.5 - 75*data.filteredUniversidades.size()/2 + i*75);
            universidades[i].setColor(ofColor(255,0));
        }
        
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
        
        // called on first enter update
        if(isEnteringFirst()) {
            selector.color.animateToAfterDelay(ofColor(255,255),0.0);
            
            for(int i=0;i<universidades.size();i++){
                universidades[i].color.animateTo(ofColor(255,255));
            }
            
            ofLogNotice(UNIVERSIDAD_SCENE_NAME) << "update enter";
        }
        
        update();
        
        // call finishedEntering() to indicate scne is done entering
        if(!selector.isOrWillBeAnimating()) {
            finishedEntering();
            ofLogNotice(UNIVERSIDAD_SCENE_NAME) << "update enter done";
        }
    }
    
    // normal update
    void update() {
        float t = ofGetElapsedTimef();
        float dt = t - time;
        time = t;
        
        for(int i=0;i<universidades.size();i++){
            universidades[i].update(dt);
        }
        
        selector.update(dt);
    }
    
    // called when scene is exiting
    void updateExit() {
        
        // called on first exit update
        if(isExitingFirst()) {
            selector.color.animateTo(ofColor(255,0));
            
            for(int i=0;i<universidades.size();i++){
                universidades[i].color.animateTo(ofColor(255,0));
            }
            
            ofLogNotice(UNIVERSIDAD_SCENE_NAME) << "update exit";
        }
        
        update();
        
        // call finishedExiting() to indicate scene is done exiting
        if(!selector.isOrWillBeAnimating()) {
            finishedExiting();
            ofLogNotice(UNIVERSIDAD_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {
        selector.draw();
        
        for(int i=0;i<universidades.size();i++){
            universidades[i].draw();
        }
    }
    
    // cleanup
    void exit() {
        ofLogNotice(UNIVERSIDAD_SCENE_NAME) << "exit";
    }
    
    void mousePressed(int x, int y, int button){
        if(isExiting())
            return;
        
        for(int i=0;i<universidades.size();i++){
            if(universidades[i].inside(ofPoint(x,y))){
                data.applyUniversidadFilter(data.filteredUniversidades[i]);
                universidades[i].size.animateTo(1.15);
                sceneManager.gotoScene(INFO_SCENE_NAME);
                break;
            }
        }
    }
    
    ofxAnimatableObject<ofTexture> selector;
    vector< ofxAnimatableObject<ofTrueTypeFont> > universidades;
    float time;
    
    Data& data;
    ofxSceneManager& sceneManager;
};
