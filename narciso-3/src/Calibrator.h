//
//  Calibrator.hpp
//  narciso-3
//
//  Created by David on 11/23/19.
//

#ifndef Calibrator_h
#define Calibrator_h

#include "ofMain.h"
#include "Keyshot.h"
#include <stdio.h>
#include <iostream>
#include <vector>

class Calibrator{
    
public:
    
    void addNewKeyshot(Keyshot k);
    void toString();
    Keyshot getScaleKeyshot(float depth);
    std::vector<Keyshot> dataKeyshots;
};


#endif /* Calibrator_hpp */
