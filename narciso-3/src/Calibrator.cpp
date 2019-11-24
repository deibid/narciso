//
//  Calibrator.cpp
//  narciso-3
//
//  Created by David on 11/23/19.
//

#include "Calibrator.h"


void Calibrator::addNewKeyframe(Keyframe k){
    std::cout << "Adding new keyframe   "<<k.depth <<"  " <<k.scale<<endl;
    dataKeyframes.push_back(k);
    std::sort(dataKeyframes.begin(), dataKeyframes.end(), compareKeyframes);
    cout<<"Ordering keyframes in ASC order"<<endl;
    toString();
}

void Calibrator::toString(){
    
    for(Keyframe k:dataKeyframes){
        std::cout << k.depth <<"   "<<k.scale<<"\n";
    }
    
}

Keyframe Calibrator::getScaleKeyframes(float depth){
    
    int i=0;
    for(Keyframe k: dataKeyframes){
        if(depth >= dataKeyframes[i].depth && depth <= dataKeyframes[i+1].depth){
            break;
        }
        i++;
    }
    std::cout <<"Your keyframe is between "<< i <<" and"<<i+1 <<endl;
    
    float mappedScale = ofMap(depth, dataKeyframes[i].depth, dataKeyframes[i+1].depth, dataKeyframes[i].scale, dataKeyframes[i+1].scale);
    
    float mappedTranslateX = ofMap(depth, dataKeyframes[i].depth,dataKeyframes[i+1].depth, dataKeyframes[i].translateX, dataKeyframes[i+1].translateX);
    
    float mappedTranslateY = ofMap(depth, dataKeyframes[i].depth,dataKeyframes[i+1].depth, dataKeyframes[i].translateY, dataKeyframes[i+1].translateY);
    
    
    
//    float normDepth = ofNormalize(depth, dataKeyshots[i].depth, dataKeyshots[i+1].depth);
//    float lerpDepth = ofLerp(dataKeyshots[i].depth, dataKeyshots[i+1].depth, normDepth);
    
    return Keyframe(depth, mappedScale, mappedTranslateX, mappedTranslateY);
}


/*
 Static comparator function to order calibration keyframes in ASC order
 Invoked by addNewKeyframe
 */
bool Calibrator::compareKeyframes(Keyframe k1, Keyframe k2){
    return (k1.depth < k2.depth);
}

