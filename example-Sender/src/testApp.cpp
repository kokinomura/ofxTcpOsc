#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    sender.setup(host, port);
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == OF_KEY_RETURN) {
        sender.setup(host, port);
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    ofxTcpOscMessage m;
    m.setAddress("/mouseDragged");
    m.addStringArg("x, y: ");
    m.addIntArg(x);
    m.addInt64Arg(y);
    m.addFloatArg(ofGetFrameRate());
    
    sender.sendMessage(m);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    ofxTcpOscMessage m;
    m.setAddress("/mousePressed");
    m.addStringArg("x:");
    m.addIntArg(x);
    m.addStringArg("y:");
    m.addIntArg(y);
    m.addStringArg("frameRate:");
    m.addFloatArg(ofGetFrameRate());
    
    sender.sendMessage(m);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}