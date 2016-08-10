#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "Data.h"

#define UNI_MARGIN 75
#define UNI_MAX 6

class UniversidadScene : public ofxScene {
    
public:
    
    // set the scene name through the base class initializer
    UniversidadScene(ofxSceneManager& sm, Data& d) : sceneManager(sm), data(d), ofxScene(UNIVERSIDAD_SCENE_NAME, false) {
        ofImage img;
        ofLoadImage(img,"04_Universidad/up.png");
        up.loadData(img);
        up.setAnchorPercent(0.5,0.5);
        up.setPosition(ofPoint(ofGetWidth()*0.5,ofGetHeight()*0.2));
        
        ofLoadImage(img,"04_Universidad/down.png");
        down.loadData(img);
        down.setAnchorPercent(0.5,0.5);
        down.setPosition(ofPoint(ofGetWidth()*0.5,ofGetHeight()*0.7));
    }
    
    // scene setup
    void setup() {
        down.setColor(ofColor(255,0));
        up.setColor(ofColor(255,0));
        
        int total = data.filteredUniversidades.size();
        
        universidades.clear();
        universidades.assign(total,ofxAnimatableObject<ofTrueTypeFont>());
        
        for(int i=0; i<total; i++){
            universidades[i].ofTrueTypeFont::load("DINRegular.otf",32);
            universidades[i].ofTrueTypeFont::setLineHeight(32);
            universidades[i].setText(data.filteredUniversidades[i]->nombre);
            universidades[i].setAnchorPercent(0.5,0.5);
            universidades[i].setSize(1.);
            universidades[i].setPosition(ofGetWidth()*0.5, ofGetHeight()*0.25 + i*UNI_MARGIN + UNI_MARGIN/2);
            universidades[i].setColor(ofColor(255,0));
        }
        selected=0;
        
        offset=0;
        maxOffset=floor(total/UNI_MAX);
        translate.reset(0.);
        
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
        
        // called on first enter update
        if(isEnteringFirst()) {
            down.color.animateTo(ofColor(255,((maxOffset-offset)>0)?255:0));
            up.color.animateTo(ofColor(255,(offset>0)?255:0));
            
            for(int i=0;i<universidades.size();i++){
                if(i>=(offset*UNI_MAX) && i<((offset+1)*UNI_MAX))
                    universidades[i].color.animateTo(ofColor(255,255));
                else
                    universidades[i].color.animateTo(ofColor(255,0));
            }
            
            ofLogNotice(UNIVERSIDAD_SCENE_NAME) << "update enter";
        }
        
        update();
        
        // call finishedEntering() to indicate scne is done entering
        if(!universidades[selected].isOrWillBeAnimating()) {
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
        translate.update(dt);
        up.update(dt);
        down.update(dt);
    }
    
    // called when scene is exiting
    void updateExit() {
        
        // called on first exit update
        if(isExitingFirst()) {
            up.color.animateTo(ofColor(255,0));
            down.color.animateTo(ofColor(255,0));
            
            for(int i=0;i<universidades.size();i++){
                universidades[i].color.animateTo(ofColor(255,0));
            }
            
            ofLogNotice(UNIVERSIDAD_SCENE_NAME) << "update exit";
        }
        
        update();
        
        // call finishedExiting() to indicate scene is done exiting
        if(!universidades[selected].isOrWillBeAnimating()) {
            finishedExiting();
            ofLogNotice(UNIVERSIDAD_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {
        ofPushMatrix();
        ofTranslate(0,translate.getCurrentValue());
        for(int i=0;i<universidades.size();i++){
            universidades[i].draw();
        }
        ofPopMatrix();
        up.draw();
        down.draw();
    }
    
    // cleanup
    void exit() {
        ofLogNotice(UNIVERSIDAD_SCENE_NAME) << "exit";
    }
    
    void mousePressed(int x, int y, int button){
        if(isExiting())
            return;
        
        bool changed = false;
        
        if(up.inside(ofPoint(x,y))){
            if(offset>0){
                offset--;
                changed=true;
            }
        }
        else if(down.inside(ofPoint(x,y))){
            if(offset<(maxOffset-1)){
                offset++;
                changed=true;
            }
        }
        
        if(changed){
            down.color.animateTo(ofColor(255,((maxOffset-offset)>0)?255:0));
            up.color.animateTo(ofColor(255,(offset>0)?255:0));
            translate.animateTo(-((float)offset)*UNI_MAX*UNI_MARGIN);
            for(int i=0;i<universidades.size();i++){
                if(i>=(offset*UNI_MAX) && i<((offset+1)*UNI_MAX))
                    universidades[i].color.animateTo(ofColor(255,255));
                else
                    universidades[i].color.animateTo(ofColor(255,0));
            }
            return;
        }
        
        for(int i=(offset*UNI_MAX);i<universidades.size() && i<((offset+1)*UNI_MAX);i++){
            if(universidades[i].inside(ofPoint(x,y-translate.getCurrentValue()))){
                selected=i;
                data.applyUniversidadFilter(data.filteredUniversidades[i]);
                universidades[i].size.animateTo(1.15);
                if(!data.ramaFilterApplied)
                    sceneManager.gotoScene(RAMA_SCENE_NAME);
                else if(!data.provinciaFilterApplied)
                    sceneManager.gotoScene(PROVINCIA_SCENE_NAME);
                else
                    sceneManager.gotoScene(INFO_SCENE_NAME);
                break;
            }
        }
    }
    
    ofxAnimatableObject<ofTexture> up,down;
    vector< ofxAnimatableObject<ofTrueTypeFont> > universidades;
    int selected;
    unsigned int offset,maxOffset;
    ofxAnimatableFloat translate;
    float time;
    
    Data& data;
    ofxSceneManager& sceneManager;
};
