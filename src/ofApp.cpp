#include "ofApp.h"

void ofApp::setup(){
    // ofBackground(255);
    ofxConnexion::start();
    
    // if you want to get data events, you can add a listener to ofxConnexion::connexionEvent
    ofAddListener(ofxConnexion::connexionEvent, this, &ofApp::connexionMoved);
    
    ofBackground(20,20,20);
    ofEnableDepthTest();
    light.enable();
    light.setPosition(+500, +500, +500);
    ofSetBackgroundAuto(false);
    
}

void ofApp::exit() {
    ofxConnexion::stop();
}

void ofApp::update(){
}

// get data as soon as it comes in
void ofApp::connexionMoved(ConnexionData& data) {
    // this would be a good place to get data from multiple devices
    cout << data.getButton(0) << " " << data.getButton(1) << endl;
    
    // use the button state to set the LED
    ofxConnexion::setLed(data.getButton(0) || data.getButton(1));
}

void ofApp::draw(){
    ofEnableLighting();
    
    ofPushMatrix();
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2 , 0);
    
    // get the most recent data
    ConnexionData& data = ofxConnexion::connexionData;
    
    
    int colval = (data.rotation[2] + 180)*(255/180);
   //ofSetColor(data.rotation[0]*255/180, data.rotation[1]*255/180, data.rotation[2]*255/180);
    
    
    ofSetColor(colval, abs(127 - colval), abs(colval - 255), 255-data.position[0]);
    
    //ofDrawSphere(data.rotation[1]* 3, data.rotation[0]*3, (data.position[0] + data.position[1]), data.position[2]);
   
    //ofDrawCircle(data.rotation[1]* 2, data.rotation[0]*2, 2 + data.position[2]/2);
    
    
    
    ofNoFill();
    ofDrawTriangle(data.rotation[1]* 3, data.rotation[0]*3, (data.position[0] + data.position[1]), (data.rotation[1]* 3)+data.position[2] , (data.rotation[0]*3) - data.position[2], (data.position[0] + data.position[1]) );

    
    ofBeginShape(); //Begin shape
    ofVertex( data.rotation[0], data.rotation[1], data.rotation[2] ); //The first vertex
    ofVertex( data.rotation[0], data.rotation[1], data.rotation[2] ); //The second vertex//...
    ofVertex( data.rotation[0], data.rotation[1], data.rotation[2] ); //The last vertex
    ofEndShape();
    
    ofPopMatrix();
    
    //-
    
    //ofDisableLighting();
    
    ofPushStyle();
    ofSetColor(255);
    
    stringstream ss;
    ss << endl;
    ss << "POSITION" << endl;
    ss << "data.position[0] : " << data.position[0] << endl;
    ss << "data.position[2] : " << data.position[2] << endl;
    ss << "data.position[1] : " << data.position[1] << endl;
    ss << endl;
    
    ss << "ROTATION" << endl;
    ss << "data.rotation[0] : " << data.rotation[0] << endl;
    ss << "data.rotation[2] : " << data.rotation[2] << endl;
    ss << "data.rotation[1] : " << data.rotation[1] << endl;
    ss << endl;
    
    ofDrawBitmapString(ss.str().c_str(), 10, 20);
    ofPopStyle();
}