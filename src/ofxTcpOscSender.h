//
//  ofxTcpOscSender.h
//
//  Created by Koki Nomura on 2014/06/12.
//
//

// ofxTcpOsc is an addon for OSC-like communication over TCP.
//
// Protocol:
//      (size means a number of chars)
//      4 bytes: size of the address
//      n bytes: address
//      4 bytes: size of arg1
//      n bytes: arg1
//      ...

#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"

#include "ofxTcpOscMessage.h"
#include "ofxTcpOscUtils.h"


class ofxTcpOscSender {
public:
    ofxTcpOscSender();
    ~ofxTcpOscSender();
    
    void setup(string hostname, int port);
    void sendMessage(ofxTcpOscMessage & message);
    
private:
    void shutdown();
    void appendMessage(ofxTcpOscMessage & message);
    
    ofxTCPClient tcpClient;
    string _hostname;
    int _port;
    
    // helper methods
    string makeOscTypeTagString(ofxTcpOscMessage & message);
        
    void appendStringToOscString(string input, vector<char> & output);
    void makeOscString(string input, vector<char> & output);
};








