//
//  ofxTcpOscSender.cpp
//
//  Created by Koki Nomura on 2014/06/12.
//

/*
    The function isLittleEndian() is from
    http://forums.devshed.com/programming-42/printing-float-hex-567826.html .
    Thank you, @clifford!
*/

#include <iostream>
#include <vector>

#pragma once

using namespace std;

namespace ofxTcpOsc {

    static bool isLittleEndian()
    {
        static bool little_endian ;
        static bool endian_checked = false ;
        // runtime endianness check (once only)
        if( !endian_checked )
        {
            const short endian_test_pattern = 0x00ff ;
            little_endian = *(reinterpret_cast<const char*>(&endian_test_pattern)) == '\xff' ;
            endian_checked = true ;
        }
        
        return little_endian ;
    }

    static void float_to_chars(float f, vector<char>& c) {
        union {
            float f;
            char c[4];
        } u;
        u.f = f;
        if (isLittleEndian()) {
            for (int i=4-1; i>=0; i--) {
                c.push_back(u.c[i]);
            }
        } else {
            for (int i=0; i<4; i++) {
                c.push_back(u.c[i]);
            }
        }
    }

    static void int32_to_chars(int32_t i32, vector<char>& c) {
        union {
            int32_t i;
            char c[4];
        } u;
        u.i = i32;
        if (isLittleEndian()) {
            for (int i=4-1; i>=0; i--) {
                c.push_back(u.c[i]);
            }
        } else {
            for (int i=0; i<4; i++) {
                c.push_back(u.c[i]);
            }
        }
    }

    static void int64_to_chars(uint64_t i64, vector<char>& c) {
        union {
            uint64_t h;
            char c[8];
        } u;
        u.h = i64;
        if (isLittleEndian()) {
            for (int i=8-1; i>=0; i--) {
                c.push_back(u.c[i]);
            }
        } else {
            for (int i=0; i<8; i++) {
                c.push_back(u.c[i]);
            }
        }
    }
    
    static float chars_to_float(char* c) {
        union {
            float f;
            char c[4];
        } u;
        if (isLittleEndian()) {
            u.c[0] = c[3];
            u.c[1] = c[2];
            u.c[2] = c[1];
            u.c[3] = c[0];
            
        } else {
            u.c[0] = c[0];
            u.c[1] = c[1];
            u.c[2] = c[2];
            u.c[3] = c[3];
        }
        return u.f;
    }
    
    static int chars_to_int32(char* c) {
        union {
            int32_t i;
            char c[4];
        } u;
        if (isLittleEndian()) {
            u.c[0] = c[3];
            u.c[1] = c[2];
            u.c[2] = c[1];
            u.c[3] = c[0];
            
        } else {
            u.c[0] = c[0];
            u.c[1] = c[1];
            u.c[2] = c[2];
            u.c[3] = c[3];
        }
        return u.i;
    }
    
    static uint64_t chars_to_int64(char* c) {
        union {
            uint64_t i;
            char c[8];
        } u;
        if (isLittleEndian()) {
            u.c[0] = c[7];
            u.c[1] = c[6];
            u.c[2] = c[5];
            u.c[3] = c[4];
            u.c[4] = c[3];
            u.c[5] = c[2];
            u.c[6] = c[1];
            u.c[7] = c[0];
        } else {
            u.c[0] = c[0];
            u.c[1] = c[1];
            u.c[2] = c[2];
            u.c[3] = c[3];
            u.c[4] = c[4];
            u.c[5] = c[5];
            u.c[6] = c[6];
            u.c[7] = c[7];        
        }
        return u.i;
    }

//    int main() {
//        vector<char> c;
//        int32_to_chars(65535, c);
//        for (int i=0; i<c.size(); i++) {
//            printf("%d\n", (unsigned char)c[i]);
//        }
//        
//        c.clear();
//        int64_to_chars(65535, c);
//        for (int i=0; i<c.size(); i++) {
//            printf("%d\n", (unsigned char)c[i]);
//        }
//        
//        c.clear();
//        float_to_chars(0.123, c);
//        for (int i=0; i<c.size(); i++) {
//            printf("%d\n", (unsigned char)c[i]);
//        }
//    }
        
}
