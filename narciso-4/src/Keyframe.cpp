//
//  Keyframe.cpp
//  narciso-4
//
//  Created by David on 11/24/19.
//

#include "Keyframe.h"

using namespace std;

Keyframe::Keyframe(float d,float s, float tX, float tY){
    depth = d;
    scale = s;
    translateX = tX;
    translateY = tY;
}

void Keyframe::toString(){
    cout << "Keyframe - Depth: "<<depth<<", Scale: "<<scale<<", TranslateX: "<<translateX<<", TransalteY: "<<translateY<<endl;
}
