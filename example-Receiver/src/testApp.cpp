#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(60);
    receiver.setup(port);
}

//--------------------------------------------------------------
void testApp::update(){
    while (receiver.hasWaitingMessages()) {
        ofxTcpOscMessage m;
        receiver.getNextMessage(&m);
        
        cout << "message from " << m.getRemoteIp() << ", " << m.getRemotePort() << ", " << m.getAddress() << endl;
        
        if (m.getAddress() == "/mousePressed") {
            string strx = m.getArgAsString(0);
            int xpos = m.getArgAsInt32(1);
            string stry = m.getArgAsString(2);
            uint64_t ypos = m.getArgAsInt32(3);
            string strframerate = m.getArgAsString(4);
            float framerate = m.getArgAsFloat(5);
            
            cout << strx << " " << xpos << " " << stry << " " << ypos << " " << strframerate << " " << framerate << endl;
        } else {
            for (int i=0; i<m.getNumArgs(); i++) {
                cout << m.getArgTypeName(i) << ": ";
                ofxTcpOscArgType argType = m.getArgType(i);
                if (argType == OFXTCPOSC_TYPE_INT32) {
                    cout << m.getArgAsInt32(i);
                } else if (argType == OFXTCPOSC_TYPE_INT64) {
                    cout << m.getArgAsInt64(i);
                } else if (argType == OFXTCPOSC_TYPE_FLOAT) {
                    cout << m.getArgAsFloat(i);
                } else if (argType == OFXTCPOSC_TYPE_STRING) {
                    cout << m.getArgAsString(i);
                }
                cout << endl;
            }
        }
        cout << endl;
    }
}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

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