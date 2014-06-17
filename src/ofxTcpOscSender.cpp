//
//  ofxTcpOscSender.cpp
//
//  Created by Koki Nomura on 2014/06/12.
//
//

#include "ofxTcpOscSender.h"

ofxTcpOscSender::ofxTcpOscSender() {
    
}

ofxTcpOscSender::~ofxTcpOscSender() {
    tcpClient.close();
}

void ofxTcpOscSender::setup(string hostname, int port) {
    tcpClient.close();
    bool success = tcpClient.setup(hostname, port);
    if (success) {
        ofLog() << "successfully connected! at " << hostname << ", " << port;
    }
    tcpClient.setMessageDelimiter("\n");
    _hostname = hostname;
    _port = port;
}

void ofxTcpOscSender::shutdown() {
    tcpClient.close();
}

void ofxTcpOscSender::sendMessage(ofxTcpOscMessage &message) {

    using namespace ofxTcpOsc;
    
    vector<char> output;
    
    // add address
    appendStringToOscString(message.getAddress(), output);

    // add Osc Type Tag String
    string oscTypeTagString = makeOscTypeTagString(message);
    appendStringToOscString(oscTypeTagString, output);

    // add arguments
    using namespace ofxTcpOsc;
    for (int i=0; i<message.getNumArgs(); i++) {
        vector<char> buf;
        if (message.getArgType(i) == OFXTCPOSC_TYPE_INT32) {
            int32_to_chars(message.getArgAsInt32(i), buf);
        } else if (message.getArgType(i) == OFXTCPOSC_TYPE_INT64) {
            int64_to_chars(message.getArgAsInt64(i), buf);
        } else if (message.getArgType(i) == OFXTCPOSC_TYPE_FLOAT) {
            float_to_chars(message.getArgAsFloat(i), buf);
        } else if (message.getArgType(i) == OFXTCPOSC_TYPE_STRING) {
            makeOscString(message.getArgAsString(i), buf);
            
        } else {
            ofLogError("ofxTcpOscSender") << "sendMessage(): bad argument type " << message.getArgType(i);
            assert(false);
        }
        for (int i=0; i<buf.size(); i++) {
            output.push_back(buf[i]);
        }
    }
    
    // add size of the packet
    int numInt32 = 4;
    int32_t size = output.size() + numInt32;
    vector<char> sizeStr;
    int32_to_chars(size, sizeStr);
    
    // prepend the size string
    for (int i=sizeStr.size()-1; i>=0; i--) {
        vector<char>::iterator it = output.begin();
        output.insert(it, sizeStr[i]);
    }
    
    if (!tcpClient.isConnected()) {
        tcpClient.setup(_hostname, _port);
    }
    tcpClient.sendRawBytes(output.data(), output.size());
}

void ofxTcpOscSender::appendStringToOscString(string input, vector<char> &output) {
    int numNulls = 4 - input.size() % 4;
    if (numNulls == 0) {
        numNulls = 4;
    }
    for (int i=0; i<input.size(); i++) {
        output.push_back(input[i]);
    }
    for (int i=0; i<numNulls; i++) {
        output.push_back(0);
    }
}

void ofxTcpOscSender::makeOscString(string input, vector<char> &output) {
    int numNulls = input.size() % 4;
    if (numNulls == 0) {
        numNulls = 4;
    }
    for (int i=0; i<input.size(); i++) {
        output.push_back(input[i]);
    }
    for (int i=0; i<numNulls; i++) {
        output.push_back(0);
    }
    return output;
}

string ofxTcpOscSender::makeOscTypeTagString(ofxTcpOscMessage &message) {
    string oscTypeTagString = ",";
    
    for (int i=0; i<message.getNumArgs(); i++) {
        if (message.getArgType(i) == OFXTCPOSC_TYPE_INT32) {
            oscTypeTagString.append("i");
        } else if (message.getArgType(i) == OFXTCPOSC_TYPE_INT64) {
            oscTypeTagString.append("h");
        } else if (message.getArgType(i) == OFXTCPOSC_TYPE_FLOAT) {
            oscTypeTagString.append("f");
        } else if (message.getArgType(i) == OFXTCPOSC_TYPE_STRING) {
            oscTypeTagString.append("s");
        } else {
            ofLogError("ofxTcpOscSender") << "makeOscTypeTagString(): bad argument type " << message.getArgType(i);
            assert(false);
        }
    }
    return oscTypeTagString;
}