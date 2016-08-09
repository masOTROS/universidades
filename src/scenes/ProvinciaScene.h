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
        ofLoadImage(img,"03_Nivel/selector.png");
        selector.loadData(img);
        selector.setAnchorPercent(0.6,0.55);
        selector.setPosition(ofPoint(ofGetWidth()*0.5,ofGetHeight()*0.5));
        
        ofLoadImage(img,"03_Nivel/principiante.png");
        principiante.loadData(img);
        principiante.setAnchorPercent(0.5,0.5);
        principiante.setPosition(ofPoint(ofGetWidth()*0.5,ofGetHeight()*0.5-80));
        
        ofLoadImage(img,"03_Nivel/avanzado.png");
        avanzado.loadData(img);
        avanzado.setAnchorPercent(0.5,0.5);
        avanzado.setPosition(ofPoint(ofGetWidth()*0.5,ofGetHeight()*0.5));
        
        ofLoadImage(img,"03_Nivel/experto.png");
        experto.loadData(img);
        experto.setAnchorPercent(0.5,0.5);
        experto.setPosition(ofPoint(ofGetWidth()*0.5,ofGetHeight()*0.5+80));
        
        ofLoadImage(img,"03_Nivel/elegidoBack.png");
        elegidoBack.loadData(img);
        elegidoBack.setAnchorPercent(0.5,0.55);
        elegidoBack.setPosition(ofPoint(ofGetWidth()*0.5,ofGetHeight()*0.5));
        elegidoBack.color.setRepeatType(LOOP_BACK_AND_FORTH_ONCE);
        elegidoBack.color.setDuration(0.5);
        elegidoBack.color.setCurve(EASE_OUT);
    }
    
    // scene setup
    void setup() {
        principiante.setColor(ofColor(255,0));
        principiante.setSize(1.);
        avanzado.setColor(ofColor(255,0));
        avanzado.setSize(1.);
        experto.setColor(ofColor(255,0));;
        experto.setSize(1.);
        
        elegido=&principiante;
        rechazado0=&avanzado;
        rechazado1=&experto;
        
        elegidoBack.setColor(ofColor(255,0));
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
		
        // called on first enter update
        if(isEnteringFirst()) {
            principiante.color.animateToAfterDelay(ofColor(255,255),0.0);
            avanzado.color.animateToAfterDelay(ofColor(255,255),0.5);
            experto.color.animateToAfterDelay(ofColor(255,255),1.0);
            
            ofLogNotice(PROVINCIA_SCENE_NAME) << "update enter";
        }
        
        update();
		
        // call finishedEntering() to indicate scne is done entering
        if(!principiante.isOrWillBeAnimating() && !avanzado.isOrWillBeAnimating() && !experto.isOrWillBeAnimating()) {
            finishedEntering();
            ofLogNotice(PROVINCIA_SCENE_NAME) << "update enter done";
        }
    }
    
    // normal update
    void update() {
        float t = ofGetElapsedTimef();
        float dt = t - time;
        time = t;
        principiante.update(dt);
        avanzado.update(dt);
        experto.update(dt);
        elegidoBack.update(dt);
    }
    
    // called when scene is exiting
    void updateExit() {
		
        // called on first exit update
        if(isExitingFirst()) {            
            //elegido->position.animateTo(ofPoint(ofGetWidth()*0.1,ofGetHeight()*0.55));
            //elegido->size.animateTo(0.5);
            
            elegidoBack.setPosition(elegido->position.getCurrentPosition());
            elegidoBack.color.animateTo(ofColor(255,255));
            
            rechazado0->color.animateTo(ofColor(255,0));
            rechazado1->color.animateTo(ofColor(255,0));

            ofLogNotice(PROVINCIA_SCENE_NAME) << "update exit";
        }
        
        update();
		
        // call finishedExiting() to indicate scene is done exiting
        if(!elegidoBack.isOrWillBeAnimating()) {
            finishedExiting();            
            ofLogNotice(PROVINCIA_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {
        selector.draw();
        elegidoBack.draw();
        principiante.draw();
        avanzado.draw();
        experto.draw();
    }
    
    // cleanup
    void exit() {
        ofLogNotice(PROVINCIA_SCENE_NAME) << "exit";
    }
    
    void mousePressed(int x, int y, int button){
        if(isExiting())
            return;
        if(principiante.inside(ofPoint(x,y))){
            elegido = &principiante;
            rechazado0 = &avanzado;
            rechazado1 = &experto;
            
            sceneManager.gotoScene(INFO_SCENE_NAME);
        }
        else if(avanzado.inside(ofPoint(x,y))){
            rechazado0 = &principiante;
            elegido = &avanzado;
            rechazado1 = &experto;
            
            sceneManager.gotoScene(INFO_SCENE_NAME);
        }
        else if(experto.inside(ofPoint(x,y))){
            rechazado0 = &principiante;
            rechazado1 = &avanzado;
            elegido = &experto;

            sceneManager.gotoScene(INFO_SCENE_NAME);
        }
    }
    
    ofxAnimatableObject<ofTexture> selector,principiante,avanzado,experto;
    ofxAnimatableObject<ofTexture> elegidoBack;
    ofxAnimatableObject<ofTexture> * elegido, * rechazado0, * rechazado1;
    float time;
    
    Data& data;
    ofxSceneManager& sceneManager;
};
