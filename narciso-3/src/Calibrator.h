//
//  Calibrator.hpp
//  narciso-3
//
//  Created by David on 11/23/19.
//

#ifndef Calibrator_h
#define Calibrator_h

#include "ofMain.h"
#include "Keyframe.h"
#include <stdio.h>
#include <iostream>
#include <vector>

class Calibrator{
    
public:
    
    void addNewKeyframe(Keyframe k);
    void toString();
    Keyframe getScaleKeyframes(float depth);
    static bool compareKeyframes(Keyframe k1, Keyframe k2);
    
    
    std::vector<Keyframe> dataKeyframes;
};


#endif /* Calibrator_hpp */
