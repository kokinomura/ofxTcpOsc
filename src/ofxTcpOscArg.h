//
//  ofxTcpOscArg.h
//
//  Created by Koki Nomura on 2014/06/12.
//
//

#pragma once

typedef enum _ofxTcpOscArgType {
    OFXTCPOSC_TYPE_INT32,
    OFXTCPOSC_TYPE_INT64,    
    OFXTCPOSC_TYPE_FLOAT,
    OFXTCPOSC_TYPE_STRING,
    OFXTCPOSC_TYPE_NONE,
    OFXTCPOSC_TYPE_INDEXOUTOFBOUNDS
} ofxTcpOscArgType;

class ofxTcpOscArg {
public:
    ofxTcpOscArg() {};
    virtual ~ofxTcpOscArg() {};
    virtual ofxTcpOscArgType getType() { return OFXTCPOSC_TYPE_NONE; }
    virtual string getTypeName() { return "none"; }
};

class ofxTcpOscArgInt32 : public ofxTcpOscArg {
public:
    ofxTcpOscArgInt32(int32_t _value) { value = _value; }
    ~ofxTcpOscArgInt32() {}
    
    ofxTcpOscArgType getType() { return OFXTCPOSC_TYPE_INT32; }
    string getTypeName() { return "int32"; }
    
    int32_t get() const { return value; }
    void set(int32_t _value) { value = _value; }
private:
    int32_t value;
};

class ofxTcpOscArgInt64 : public ofxTcpOscArg {
public:
    ofxTcpOscArgInt64(uint64_t _value) { value = _value; }
    ~ofxTcpOscArgInt64() {}
    
    ofxTcpOscArgType getType() { return OFXTCPOSC_TYPE_INT64; }
    string getTypeName() { return "int64"; }
    
    uint64_t get() const { return value; }
    void set(uint64_t _value) { value = _value; }
private:
    uint64_t value;
};

class ofxTcpOscArgFloat : public ofxTcpOscArg {
public:
    ofxTcpOscArgFloat(float _value) { value = _value; }
    ~ofxTcpOscArgFloat() {}
    
    ofxTcpOscArgType getType() { return OFXTCPOSC_TYPE_FLOAT; }
    string getTypeName() { return "float"; }
    
    float get() const { return value; }
    void set(float _value) { value = _value; }
private:
    float value;
};

class ofxTcpOscArgString : public ofxTcpOscArg {
public:
    ofxTcpOscArgString(string _value) { value = _value; }
    ~ofxTcpOscArgString() {}
    
    ofxTcpOscArgType getType() { return OFXTCPOSC_TYPE_STRING; }
    string getTypeName() { return "string"; }
    
    string get() const { return value; }
    void set(float _value) { value = _value; }
private:
    string value;
};