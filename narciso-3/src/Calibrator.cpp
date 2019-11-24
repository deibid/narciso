//
//  Calibrator.cpp
//  narciso-3
//
//  Created by David on 11/23/19.
//

#include "Calibrator.h"


void Calibrator::addNewKeyshot(Keyshot k){
    std::cout << "Adding new keyshow   "<<k.depth <<"  " <<k.scale;
    dataKeyshots.push_back(k);
}

void Calibrator::toString(){
    
    for(Keyshot k:dataKeyshots){
        std::cout << k.depth <<"   "<<k.scale<<"\n";
    }
    
}

Keyshot Calibrator::getScaleKeyshot(float depth){
    
    int i=0;
    for(Keyshot k: dataKeyshots){
        if(depth >= dataKeyshots[i].depth && depth <= dataKeyshots[i+1].depth){
            break;
        }
        i++;
    }
    std::cout <<"Your keyshot is between "<< i <<" and"<<i+1;
    
    float mappedScale = ofMap(depth, dataKeyshots[i].depth, dataKeyshots[i+1].depth, dataKeyshots[i].scale, dataKeyshots[i+1].scale);
    
    
//    float normDepth = ofNormalize(depth, dataKeyshots[i].depth, dataKeyshots[i+1].depth);
//    float lerpDepth = ofLerp(dataKeyshots[i].depth, dataKeyshots[i+1].depth, normDepth);
    
    return Keyshot(depth, mappedScale);
    
    //map de la depth a los keyshots en rango
    
    //hacer lerp de atributos
    //armar un nuevo keyshot y regresarlo
    
    
    
    
}

