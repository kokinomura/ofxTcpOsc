//
//  ofxTcpOscMessage.h
//
//  Created by Koki Nomura on 2014/06/12.
//
//

#pragma once

#include "ofMain.h"
#include "ofxTcpOscArg.h"

class ofxTcpOscMessage {
public:
    ofxTcpOscMessage();
    ~ofxTcpOscMessage();
    ofxTcpOscMessage(const ofxTcpOscMessage & other) { copy(other); }
    ofxTcpOscMessage & operator=(const ofxTcpOscMessage & other) { return copy(other); }
    ofxTcpOscMessage & copy(const ofxTcpOscMessage & other);
    
    void clear();
    string getAddress() const { return address; }
    string getRemoteIp() const { return remote_host; }
    int getRemotePort() const { return remote_port; }
    
    int getNumArgs() const;
    ofxTcpOscArgType getArgType(int index) const;
    string getArgTypeName(int index) const;
    
    int32_t getArgAsInt32(int index) const;
    uint64_t getArgAsInt64(int index) const;
    float getArgAsFloat(int index) const;
    string getArgAsString(int index) const;
    
    void setAddress(string _address) { address = _address; };
    void setRemoteEndpoint(string host, int port) { remote_host = host; remote_port = port; }
    void addIntArg(int32_t argument);
    void addInt64Arg(uint64_t argument);
    void addFloatArg(float argument);
    void addStringArg(string argument);
    
private:
    string address;
    vector<ofxTcpOscArg*> args;
    
    string remote_host;
    int remote_port;
};