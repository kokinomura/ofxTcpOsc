//
//  ofxTcpOscReceiver.h
//
//  Created by Koki Nomura on 2014/06/13.
//
//

#pragma once

#include "ofMain.h"
#include "ofxNetwork.h"

#include "ofxTcpOscMessage.h"
#include "ofxTcpOscUtils.h"

class ofxTcpOscReceiver {
public:
    ofxTcpOscReceiver();
    ~ofxTcpOscReceiver();
    
    void setup(int listen_port);
    void update(ofEventArgs & args);
    bool hasWaitingMessages();
    bool getNextMessage(ofxTcpOscMessage *);

    ofxTCPServer server;
    
private:
    void _receiveOscMessages(int clientId, deque<ofPtr<ofxTcpOscMessage> > & messages);
    
    // parse functions
    // those return an offset.
    int _parsePacketSize(char* packet, int& output);
    int _parsePacketAddress(char* packet, string& output);
    int _parsePacketTypes(char* packet, string& output, int offset);
    void _parsePacketArgs(char* packet, ofPtr<ofxTcpOscMessage> m, int offset, string typeString);
    
    deque<ofPtr<ofxTcpOscMessage> > _messages;
    
    int nBytes = 4096;
    char packet[4096];
};