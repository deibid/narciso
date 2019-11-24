//
//  Keyshot.h
//  narciso-3
//
//  Created by David on 11/23/19.
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


#endif /* Keyshot_h */
