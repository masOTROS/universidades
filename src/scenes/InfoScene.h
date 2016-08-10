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
        ofLoadImage(img,"05_Info/background.png");
        background.loadData(img);
        background.color.setDuration(1.0f);
        
        ofLoadImage(img,"05_Info/titulo.png");
        title.loadData(img);
        title.setAnchorPercent(0.0f,0.0f);
    }
    
    // scene setup
    void setup() {
        background.setColor(ofColor(255,0));
        title.setPosition(ofPoint(0,-title.getHeight()));
        
        rama = ofPtr< ofxAnimatableObject<ofTrueTypeFont> >( new ofxAnimatableObject<ofTrueTypeFont> );
        rama->ofTrueTypeFont::load("DINBold.otf",32);
        rama->ofTrueTypeFont::setLineHeight(32);
        rama->setText(data.filteredRamas[0]->nombre);
        rama->setAnchorPercent(0.0,0.5);
        rama->setSize(1.);
        rama->setPosition(ofGetWidth()*0.5, 200);
        rama->setColor(ofColor(255,0));
        
        provincia = ofPtr< ofxAnimatableObject<ofTrueTypeFont> >( new ofxAnimatableObject<ofTrueTypeFont> );
        provincia->ofTrueTypeFont::load("DINRegular.otf",32);
        provincia->ofTrueTypeFont::setLineHeight(32);
        provincia->setText(data.filteredProvincias[0]->nombre);
        provincia->setAnchorPercent(0.0,0.5);
        provincia->setSize(1.);
        provincia->setPosition(ofGetWidth()*0.5, 250);
        provincia->setColor(ofColor(255,0));
        
        universidad = ofPtr< ofxAnimatableObject<ofTrueTypeFont> >( new ofxAnimatableObject<ofTrueTypeFont> );
        universidad->ofTrueTypeFont::load("DINRegular.otf",32);
        universidad->ofTrueTypeFont::setLineHeight(32);
        universidad->setText(data.filteredUniversidades[0]->nombre);
        universidad->setAnchorPercent(0.0,0.5);
        universidad->setSize(1.);
        universidad->setPosition(ofGetWidth()*0.5, 300);
        universidad->setColor(ofColor(255,0));
        
        discipline = ofPtr< ofxAnimatableObject<ofTexture> >( new ofxAnimatableObject<ofTexture> );
        ofPixels img;
        if(data.filteredRamas[0]->nombre.find("Social")!=std::string::npos){
            ofLoadImage(img,"05_Info/Sociales.png");
            discipline->loadData(img);
        }
        else if(data.filteredRamas[0]->nombre.find("Humanas")!=std::string::npos){
            ofLoadImage(img,"05_Info/Humanas.png");
            discipline->loadData(img);
        }
        else if(data.filteredRamas[0]->nombre.find("Aplicadas")!=std::string::npos){
            ofLoadImage(img,"05_Info/Aplicadas.png");
            discipline->loadData(img);
        }
        else if(data.filteredRamas[0]->nombre.find("Salud")!=std::string::npos){
            ofLoadImage(img,"05_Info/Salud.png");
            discipline->loadData(img);
        }
        else{
            ofLoadImage(img,"05_Info/Basicas.png");
            discipline->loadData(img);
        }
        discipline->setAnchorPercent(0.5,0.5);
        discipline->setPosition(ofGetWidth()*0.5,ofGetHeight()*0.65);
        discipline->setColor(ofColor(255,0));
        discipline->setSize(0.5);
        
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
		
        // called on first enter update
        if(isEnteringFirst()) {
            background.color.animateTo(ofColor(255,255));
            title.position.animateTo(ofPoint(0,0));
            
            rama->color.animateTo(ofColor(255,255));
            provincia->color.animateTo(ofColor(255,255));
            universidad->color.animateTo(ofColor(255,255));
            
            discipline->color.animateTo(ofColor(255,255));
            discipline->size.animateTo(1.0f);
            
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
        
        rama->update(dt);
        provincia->update(dt);
        universidad->update(dt);
        
        discipline->update(dt);
        
        background.update(dt);
        title.update(dt);
    }
    
    // called when scene is exiting
    void updateExit() {
		
        // called on first exit update
        if(isExitingFirst()) {
            background.color.animateTo(ofColor(255,0));
            title.position.animateTo(ofPoint(0,-title.getHeight()));
            
            rama->color.animateTo(ofColor(255,0));
            provincia->color.animateTo(ofColor(255,0));
            universidad->color.animateTo(ofColor(255,0));
            
            discipline->color.animateTo(ofColor(255,0));
            
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
        background.draw();
        title.draw();
        discipline->draw();
        rama->draw();
        provincia->draw();
        universidad->draw();
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
    
    ofxAnimatableObject<ofTexture> background;
    ofxAnimatableObject<ofTexture> title;
    ofPtr< ofxAnimatableObject<ofTexture> > discipline;
    ofPtr< ofxAnimatableObject<ofTrueTypeFont> > rama;
    ofPtr< ofxAnimatableObject<ofTrueTypeFont> > provincia;
    ofPtr< ofxAnimatableObject<ofTrueTypeFont> > universidad;
    float time;
    
    Data& data;
    ofxSceneManager& sceneManager;
};
