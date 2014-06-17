//
//  ofxTcpOscMessage.cpp
//
//  Created by Koki Nomura on 2014/06/12.
//
//

#include "ofxTcpOscMessage.h"

ofxTcpOscMessage::ofxTcpOscMessage() {
    
}

ofxTcpOscMessage::~ofxTcpOscMessage() {
    clear();
}

void ofxTcpOscMessage::clear() {
    args.clear();
    address = "";
}

//----------------------------
#pragma mark - Get Methods

int ofxTcpOscMessage::getNumArgs() const {
    return args.size();
}

ofxTcpOscArgType ofxTcpOscMessage::getArgType(int index) const {
    if (index >= args.size()) {
        ofLogError("ofxTcpOscMessage") << "getArgType(): index " << index << " out of bounds";
        return OFXTCPOSC_TYPE_INDEXOUTOFBOUNDS;
    } else {
        return args[index]->getType();
    }
}

string ofxTcpOscMessage::getArgTypeName(int index) const {
    if (index >= args.size()) {
        ofLogError("ofxTcpOscMessage") << "getArgTypeName(): index " << index << " out of bounds";
        return "INDEX OUT OF BOUNDS";
    } else {
        return args[index]->getTypeName();
    }
}

int32_t ofxTcpOscMessage::getArgAsInt32(int index) const {
    if (getArgType(index) != OFXTCPOSC_TYPE_INT32) {
        if (getArgType(index) == OFXTCPOSC_TYPE_FLOAT) {
            ofLogError("ofxTcpOscMessage") << "getArgAsInt32(): converting int32 to float for argument " << index;
            return((ofxTcpOscArgFloat*)args[index])->get();
        } else {
            ofLogError("ofxTcpOscMessage") << "getArgAsInt32(): arguent " << index << " is not a number";
            return 0;
        }
    } else {
        return ((ofxTcpOscArgInt32*)args[index])->get();
    }
}

uint64_t ofxTcpOscMessage::getArgAsInt64(int index) const {
    if (getArgType(index) != OFXTCPOSC_TYPE_INT64) {
        if (getArgType(index) == OFXTCPOSC_TYPE_FLOAT) {
            ofLogError("ofxTcpOscMessage") << "getArgAsInt64(): converting int64 to float for argument " << index;
            return((ofxTcpOscArgFloat*)args[index])->get();
        } else {
            ofLogError("ofxTcpOscMessage") << "getArgAsInt64(): arguent " << index << " is not a number";
            return 0;
        }
    } else {
        return ((ofxTcpOscArgInt64*)args[index])->get();
    }
}

float ofxTcpOscMessage::getArgAsFloat(int index) const {
    if (getArgType(index) != OFXTCPOSC_TYPE_FLOAT) {
        if (getArgType(index) == OFXTCPOSC_TYPE_INT32) {
            ofLogError("ofxTcpOscMessage") << "getArgAsFloat(): converting float to int32 for argument " << index;
            return((ofxTcpOscArgInt32*)args[index])->get();
        } else {
            ofLogError("ofxTcpOscMessage") << "getArgAsFloat(): arguent " << index << " is not a number";
            return 0;
        }
    } else {
        return ((ofxTcpOscArgFloat*)args[index])->get();
    }
}

string ofxTcpOscMessage::getArgAsString(int index) const {
    if (getArgType(index) != OFXTCPOSC_TYPE_STRING) {
        if (getArgType(index) == OFXTCPOSC_TYPE_FLOAT) {
            string str = ofToString(((ofxTcpOscArgFloat*)args[index])->get());
            ofLogWarning("ofxTcpOscMessage") << "getArgAsString(): converting float to string for argument " << index;
            return str;
        } else if (getArgType(index) == OFXTCPOSC_TYPE_INT32) {
            string str = ofToString(((ofxTcpOscArgInt32*)args[index])->get());
            ofLogWarning("ofxTcpOscMessage") << "getArgAsString(): converting int32 to string for argument " << index;
            return str;
        } else {
            ofLogError("ofxTcpOscMessage") << "getArgAsString(): argument " << index << " is not a string";
            return "";
        }
    } else {
        return ((ofxTcpOscArgString *)args[index])->get();
    }
}


//------------------------------------------------------------
#pragma mark - Set Methods

void ofxTcpOscMessage::addIntArg(int32_t argument) {
    args.push_back(new ofxTcpOscArgInt32(argument));
}

void ofxTcpOscMessage::addInt64Arg(uint64_t argument) {
    args.push_back(new ofxTcpOscArgInt64(argument));
}

void ofxTcpOscMessage::addFloatArg(float argument) {
    args.push_back(new ofxTcpOscArgFloat(argument));
}

void ofxTcpOscMessage::addStringArg(string argument) {
    args.push_back(new ofxTcpOscArgString(argument));
}


//------------------------------------------------------------
#pragma mark - housekeeping

ofxTcpOscMessage& ofxTcpOscMessage::copy(const ofxTcpOscMessage &other) {
    clear();
    address = other.address;
    
    remote_host = other.remote_host;
    remote_port = other.remote_port;
    
    // copy arguments
    for (int i=0; i<other.args.size(); i++) {
        ofxTcpOscArgType argType = other.getArgType(i);
        if (argType == OFXTCPOSC_TYPE_INT32) {
            args.push_back(new ofxTcpOscArgInt32(other.getArgAsInt32(i)));
        } else if (argType == OFXTCPOSC_TYPE_INT64) {
            args.push_back(new ofxTcpOscArgInt64(other.getArgAsInt64(i)));
        } else if (argType == OFXTCPOSC_TYPE_FLOAT) {
            args.push_back(new ofxTcpOscArgFloat(other.getArgAsFloat(i)));
        } else if (argType == OFXTCPOSC_TYPE_STRING) {
            args.push_back(new ofxTcpOscArgString(other.getArgAsString(i)));
        } else {
            assert(false && "bad argument type");
        }
    }
    return *this;
}
















