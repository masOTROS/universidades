#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "Data.h"

#define PROV_MARGIN 75

class ProvinciaScene : public ofxScene {
    
public:
    
    // set the scene name through the base class initializer
    ProvinciaScene(ofxSceneManager& sm, Data& d) : sceneManager(sm), data(d), ofxScene(PROVINCIA_SCENE_NAME, false) {
    }
    
    // scene setup
    void setup() {
        int total = data.filteredProvincias.size();
        
        provincias.clear();
        provincias.assign(total,ofxAnimatableObject<ofTrueTypeFont>());
        
        for(int i=0; i<total; i++){
            provincias[i].ofTrueTypeFont::load("DINRegular.otf",44);
            provincias[i].ofTrueTypeFont::setLineHeight(32);
            provincias[i].setText(data.filteredProvincias[i]->nombre);
            provincias[i].setAnchorPercent(0.5,0.5);
            provincias[i].setSize(1.);
            if(i<floor(total/3))
                provincias[i].setPosition(ofGetWidth()*0.20, ofGetHeight()*0.5 - (floor(total/3)*PROV_MARGIN)/2.0f + i*PROV_MARGIN + PROV_MARGIN/2);
            else if(i>=ceil(2*total/3))
                provincias[i].setPosition(ofGetWidth()*0.80, ofGetHeight()*0.5 - ((total-ceil(2*total/3))*PROV_MARGIN)/2.0f + (i-ceil(2*total/3))*PROV_MARGIN + PROV_MARGIN/2);
            else
                provincias[i].setPosition(ofGetWidth()*0.50, ofGetHeight()*0.5 - ((ceil(2*total/3)-floor(total/3))*PROV_MARGIN)/2.0f + (i-floor(total/3))*PROV_MARGIN + PROV_MARGIN/2);

            provincias[i].setColor(ofColor(255,0));
        }
        
        selected=0;
        
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
        
        // called on first enter update
        if(isEnteringFirst()) {
            for(int i=0;i<provincias.size();i++){
                provincias[i].color.animateToAfterDelay(ofColor(255,255),i*0.1f);
            }
            
            ofLogNotice(PROVINCIA_SCENE_NAME) << "update enter";
        }
        
        update();
        
        // call finishedEntering() to indicate scne is done entering
        if(!provincias[selected].isOrWillBeAnimating()) {
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
    }
    
    // called when scene is exiting
    void updateExit() {
        
        // called on first exit update
        if(isExitingFirst()) {            
            for(int i=0;i<provincias.size();i++){
                provincias[i].color.animateTo(ofColor(255,0));
            }
            
            ofLogNotice(PROVINCIA_SCENE_NAME) << "update exit";
        }
        
        update();
        
        // call finishedExiting() to indicate scene is done exiting
        if(!provincias[selected].isOrWillBeAnimating()) {
            finishedExiting();
            ofLogNotice(PROVINCIA_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {
        for(int i=0;i<provincias.size();i++){
            provincias[i].draw();
        }
        
        float x0=(provincias[0].position.getCurrentPosition().x+provincias[provincias.size()/2].position.getCurrentPosition().x)/2;
        float x1=(provincias[provincias.size()/2].position.getCurrentPosition().x+provincias[provincias.size()-1].position.getCurrentPosition().x)/2;
        
        ofPushStyle();
        ofSetColor(provincias[0].color.getCurrentColor());
        ofDrawLine(x0,ofGetHeight()*0.5-PROV_MARGIN*provincias.size()/5,x0,ofGetHeight()*0.5+PROV_MARGIN*provincias.size()/5);
        ofDrawLine(x1,ofGetHeight()*0.5-PROV_MARGIN*provincias.size()/5,x1,ofGetHeight()*0.5+PROV_MARGIN*provincias.size()/5);
        ofPopStyle();
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
                selected=i;
                data.applyProvinciaFilter(data.filteredProvincias[i]);
                provincias[i].size.animateTo(1.15);
                if(!data.ramaFilterApplied)
                    sceneManager.gotoScene(RAMA_SCENE_NAME);
                else if(!data.universidadFilterApplied)
                    sceneManager.gotoScene(UNIVERSIDAD_SCENE_NAME);
                else
                    sceneManager.gotoScene(INFO_SCENE_NAME);
                break;
            }
        }
    }
    
    vector< ofxAnimatableObject<ofTrueTypeFont> > provincias;
    int selected;
    float time;
    
    Data& data;
    ofxSceneManager& sceneManager;
};
