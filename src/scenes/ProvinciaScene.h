#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "Data.h"


class ProvinciaScene : public ofxScene {
    
public:
    
    // set the scene name through the base class initializer
    ProvinciaScene(ofxSceneManager& sm, Data& d) : sceneManager(sm), data(d), ofxScene(PROVINCIA_SCENE_NAME, false) {
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
        
        int total = data.filteredProvincias.size();
        
        provincias.clear();
        provincias.assign(total,ofxAnimatableObject<ofTrueTypeFont>());
        
        for(int i=0; i<total; i++){
            provincias[i].ofTrueTypeFont::load("verdana.ttf",32);
            provincias[i].ofTrueTypeFont::setLineHeight(32);
            provincias[i].setText(data.filteredProvincias[i]->nombre);
            provincias[i].setAnchorPercent(0.5,0.5);
            provincias[i].setSize(1.);
            if(i<floor(total/3))
                provincias[i].setPosition(ofGetWidth()*0.25, ofGetHeight()*0.5 - 75*floor(total/3)/2 + i*75);
            else if(i>=floor(2*total/3))
                provincias[i].setPosition(ofGetWidth()*0.75, ofGetHeight()*0.5 - 75*floor(total/3)/2 + (i-floor(2*total/3))*75);
            else
                provincias[i].setPosition(ofGetWidth()*0.50, ofGetHeight()*0.5 - 75*floor(total/3)/2 + (i-floor(total/3))*75);

            provincias[i].setColor(ofColor(255,0));
        }
        
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
        
        // called on first enter update
        if(isEnteringFirst()) {
            selector.color.animateToAfterDelay(ofColor(255,255),0.0);
            
            for(int i=0;i<provincias.size();i++){
                provincias[i].color.animateTo(ofColor(255,255));
            }
            
            ofLogNotice(PROVINCIA_SCENE_NAME) << "update enter";
        }
        
        update();
        
        // call finishedEntering() to indicate scne is done entering
        if(!selector.isOrWillBeAnimating()) {
            finishedEntering();
            ofLogNotice(PROVINCIA_SCENE_NAME) << "update enter done";
        }
    }
    
    // normal update
    void update() {
        float t = ofGetElapsedTimef();
        float dt = t - time;
        time = t;
        
        for(int i=0;i<provincias.size();i++){
            provincias[i].update(dt);
        }
        
        selector.update(dt);
    }
    
    // called when scene is exiting
    void updateExit() {
        
        // called on first exit update
        if(isExitingFirst()) {
            selector.color.animateTo(ofColor(255,0));
            
            for(int i=0;i<provincias.size();i++){
                provincias[i].color.animateTo(ofColor(255,0));
            }
            
            ofLogNotice(PROVINCIA_SCENE_NAME) << "update exit";
        }
        
        update();
        
        // call finishedExiting() to indicate scene is done exiting
        if(!selector.isOrWillBeAnimating()) {
            finishedExiting();
            ofLogNotice(PROVINCIA_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {
        selector.draw();
        
        for(int i=0;i<provincias.size();i++){
            provincias[i].draw();
        }
    }
    
    // cleanup
    void exit() {
        ofLogNotice(PROVINCIA_SCENE_NAME) << "exit";
    }
    
    void mousePressed(int x, int y, int button){
        if(isExiting())
            return;
        
        for(int i=0;i<provincias.size();i++){
            if(provincias[i].inside(ofPoint(x,y))){
                data.applyProvinciaFilter(data.filteredProvincias[i]);
                provincias[i].size.animateTo(1.15);
                sceneManager.gotoScene(UNIVERSIDAD_SCENE_NAME);
                break;
            }
        }
    }
    
    ofxAnimatableObject<ofTexture> selector;
    vector< ofxAnimatableObject<ofTrueTypeFont> > provincias;
    float time;
    
    Data& data;
    ofxSceneManager& sceneManager;
};
