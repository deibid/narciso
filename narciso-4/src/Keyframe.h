//
//  Keyframe.hpp
//  narciso-4
//
//  Created by David on 11/24/19.
//

#ifndef Keyframe_h
#define Keyframe_h

#include <stdio.h>

class Keyframe{
    
public:
    float depth;
    float scale;
    float translateX;
    float translateY;
    
    Keyframe(float,float,float,float);
};


#endif /* Keyframe_h */
