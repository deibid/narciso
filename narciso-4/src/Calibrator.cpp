/**
 
 Calibrator
 Create by David Azar
 
 */


#include "Calibrator.h"
#include "ofJson.h"


void Calibrator::addNewKeyframe(Keyframe k){
    dataKeyframes.push_back(k);
    std::sort(dataKeyframes.begin(), dataKeyframes.end(), compareKeyframes);
}

void Calibrator::toString(){
    
    for(Keyframe k:dataKeyframes){
        k.toString();
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
        
    float mappedScale = ofMap(depth, dataKeyframes[i].depth, dataKeyframes[i+1].depth, dataKeyframes[i].scale, dataKeyframes[i+1].scale);
    
    float mappedTranslateX = ofMap(depth, dataKeyframes[i].depth,dataKeyframes[i+1].depth, dataKeyframes[i].translateX, dataKeyframes[i+1].translateX);
    
    float mappedTranslateY = ofMap(depth, dataKeyframes[i].depth,dataKeyframes[i+1].depth, dataKeyframes[i].translateY, dataKeyframes[i+1].translateY);
    
    //Object containing the appropriate parameters to scale the video feed to match the mirrors reflection.
    return Keyframe(depth, mappedScale, mappedTranslateX, mappedTranslateY);
}


/*
 Static comparator function to order calibration keyframes in ASC order
 Invoked by addNewKeyframe
 */
bool Calibrator::compareKeyframes(Keyframe k1, Keyframe k2){
    return (k1.depth < k2.depth);
}

bool Calibrator::readFile(){
    
    std::string path = ofToDataPath("calibration.json");
    ofFile f(path);
    
    if(f.exists()){
        parseDataFromFile(f);
        return true;
    }else{
        return false;
    }
}

void Calibrator::parseDataFromFile(ofFile f){
    
    ofJson jsonData = ofLoadJson(f.path());
    cout << "JSON DATA:>>   "<<jsonData.dump()<<endl;
    
    
//    dataKeyframes.clear();
    for(int i =0; i<jsonData["data"].size(); i++){
        ofJson j = jsonData["data"][i];
        Keyframe k(j["depth"],j["scale"],j["translateX"],j["translateY"]);
        addNewKeyframe(k);
    }
    toString();
}

void Calibrator::saveDataToFile(){
    
    std::string path = ofToDataPath("calibration.json");
    ofFile f(path);
    
    if(!f.exists()){
        f.create();
    }
    
    ofJson jsonObject = ofLoadJson(path);
    
    for(int i=0; i<dataKeyframes.size(); i++){
        
        Keyframe k = dataKeyframes[i];
        ofJson jsonK = {
            {"depth",k.depth},
            {"scale",k.scale},
            {"translateX",k.translateX},
            {"translateY",k.translateY}
        };
//        jsonObject[ofToString(i)] = jsonK;
        jsonObject["data"].push_back(jsonK);
    }
    
    
    ofSavePrettyJson("calibration.json", jsonObject);
}




