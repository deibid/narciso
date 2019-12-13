//
//  Calibrator.hpp
//  narciso-4
//
//  Created by David on 11/24/19.
//

#ifndef Calibrator_h
#define Calibrator_h

#include <stdio.h>
#include "ofMain.h"
#include "Keyframe.h"
#include <iostream>
#include <vector>

class Calibrator{
    
public:
    
    void addNewKeyframe(Keyframe k);
    void toString();
    Keyframe getScaleKeyframes(float depth);
    bool readFile();
    void parseDataFromFile(ofFile f);
    void saveDataToFile();
    static bool compareKeyframes(Keyframe k1, Keyframe k2);
    
    
    std::vector<Keyframe> dataKeyframes;
};

#endif /* Calibrator_hpp */
