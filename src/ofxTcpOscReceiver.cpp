//
//  ofxTcpOscReceiver.cpp
//
//  Created by Koki Nomura on 2014/06/13.
//
//

#include "ofxTcpOscReceiver.h"

using namespace ofxTcpOsc;

ofxTcpOscReceiver::ofxTcpOscReceiver() {
    
}

ofxTcpOscReceiver::~ofxTcpOscReceiver() {
    
}

void ofxTcpOscReceiver::setup(int listen_port) {
    server.setup(listen_port, true);
    ofAddListener(ofEvents().update, this, &ofxTcpOscReceiver::update);
}

void ofxTcpOscReceiver::update(ofEventArgs & args) {
    // allows multiple connections
    // though it is intended to have only one connection
    for (int i=0; i<server.getLastID(); i++) {
        if (server.isClientConnected(i)) {
            _receiveOscMessages(i, _messages);
        }
    }
}

bool ofxTcpOscReceiver::hasWaitingMessages() {
    return !_messages.empty();
}

bool ofxTcpOscReceiver::getNextMessage(ofxTcpOscMessage & m) {
    ofPtr<ofxTcpOscMessage> p = _messages.front();
    _messages.pop_front();
    m = *(p.get());
    return true;
}

#pragma mark - Private Methods

void ofxTcpOscReceiver::_receiveOscMessages(int clientId, deque<ofPtr<ofxTcpOscMessage> > &messages) {
    
    int received = server.receiveRawBytes(clientId, packet, nBytes);
    
    if (received == 0) {
        return;
    }

    // parse
    ofPtr<ofxTcpOscMessage> m = ofPtr<ofxTcpOscMessage>(new ofxTcpOscMessage);
    
    int packetSize;
    _parsePacketSize(packet, packetSize);

    string address;
    int offset = _parsePacketAddress(packet, address);
    m->setAddress(address);
    
    string typeString;
    offset = _parsePacketTypes(packet, typeString, offset);
    
    _parsePacketArgs(packet, m, offset, typeString);
    
    string host = server.getClientIP(clientId);
    int port = server.getClientPort(clientId);
    m->setRemoteEndpoint(host, port);
    
    _messages.push_back(m);
}

int ofxTcpOscReceiver::_parsePacketSize(char *packet, int &output) {
    int int32Size = 4;
    int sum = 0;
    for (int i=0; i<int32Size; i++) {
        int power = int32Size - i - 1;
        sum += packet[i] * ::pow(256, power);
    }
    output = sum;
    
    return int32Size;
}

int ofxTcpOscReceiver::_parsePacketAddress(char *packet, string &output) {
    int int32Size = 4;
    int maxAddressLen = 1024;
    
    output.clear();
    output.append(&packet[int32Size]);
    int i;
    for (i=int32Size; i<maxAddressLen; i++) {
        if (packet[i] == ',') {
            return i;
        }
    }
    return i;
}

int ofxTcpOscReceiver::_parsePacketTypes(char *packet, string &output, int offset) {
    int maxLen = 1024;
    output.clear();
    output.append(&packet[offset+1]);
    
    int size = output.size();
    size += 4 - size % 4;
    return offset + size;
}

void ofxTcpOscReceiver::_parsePacketArgs(char *packet, ofPtr<ofxTcpOscMessage> m, int offset, string typeString) {

    int size;
    for (int i=0; i<typeString.size(); i++) {
        if (typeString[i] == 'i') {
            size = 4;
            int32_t arg = chars_to_int32(&packet[offset]);
            m->addIntArg(arg);
        } else if (typeString[i] == 'f') {
            size = 4;
            float arg = chars_to_float(&packet[offset]);
            m->addFloatArg(arg);
        } else if (typeString[i] == 'h') {
            size = 8;
            uint64_t arg = chars_to_int64(&packet[offset]);
            m->addInt64Arg(arg);
        } else if (typeString[i] == 's') {
            string arg = "";
            arg.append(&packet[offset]);
            m->addStringArg(arg);
            size = arg.size();
            size += 4 - size % 4;
        }
        offset += size;
    }
}




