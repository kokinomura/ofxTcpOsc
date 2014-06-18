ofxTcpOsc
=========

A lightweight reliable OSC library over TCP for openFrameworks.

It's as easy as ofxOsc!


Dependency
-----------
- ofxNetwork


Usage
---------------------------

### 1. Sender

testApp.h
```cpp
#include "ofxTcpOsc.h"

const string host = "localhost";
const int port = 50000;

class testApp : public ofBaseApp{
	// definitions
	ofxTcpOscSender sender;
}
```

testApp.cpp
```cpp
void testApp::setup() {
    sender.setup(host, port);
}

void testApp::sendMessage {
    ofxTcpOscMessage m;
    m.setAddress("/testAddress");
    m.addStringArg("test message");
    m.addIntArg(0);
    m.addInt64Arg(123);
    m.addFloatArg(0.123);
    
    sender.sendMessage(m);
}

```

### 2. Receiver

testApp.h
```cpp
#include "ofxTcpOsc.h"

const int port = 50000;

class testApp : public ofBaseApp{
    // definitions
    ofxTcpOscReceiver receiver;
}

```

testApp.cpp
```cpp
void testApp::setup() {
    receiver.setup(port);
}

void testApp::update() {
    while (receiver.hasWaitingMessages()) {
        ofxTcpOscMessage m;
        receiver.getNextMessage(&m);
        
        if (m.getAddress() == "/testAddress") {
            string message = m.getArgAsString(0);
            int i = m.getArgAsInt32(1);
            uint64_t j = m.getArgAsInt64(2);
            float f = m.getArgAsFloat(3);
        }
    }
}
```

Support
-------------------------------
- Tested on OS X 10.9.3 + oF v0.8.0
- No bundle support
- Supported OSC types
  - int32
  - int64
  - float32
  - string
