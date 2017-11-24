//  Material.h
//  Assignment 4
//
//  Created by Taylor Cook on 10/18/17.

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>
#include <cstring>
#include <sstream>
#include "glm/glm.hpp"                    // NOTE: Need to compile, hence the quotes
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

using namespace std;

#ifndef Material_h
#define Material_h

class Material {
private:
    glm::vec3 diffcolor = glm::vec3(1,1,1);
    string linedata;
    float Kd = 1.0;
    float Ks = 0.0;
    float Shine = 1.0;
    float T = 0.0;
    float index_of_refraction = 1.0;
    
public:
    Material(void){
        
    };
    
    glm::vec3 getColor(){
        return(diffcolor);
    };
    
    float getKd(){
        return(Kd);
    };
    
    float getKs(){
        return(Ks);
    };
    
    float getShine(){
        return(Shine);
    };
    
    float getTransmittance(){
        return(T);
    };
    
    float getIndexRefraction(){
        return(index_of_refraction);
    };
    
    void read(string data){
        stringstream ss (data);
        char dummy[80];
        ss>>dummy;
        ss>>diffcolor.x>>diffcolor.y>>diffcolor.z>>Kd>>Ks>>Shine>>T>>index_of_refraction;
    };
    
    string toString(){
        linedata = "f "+ to_string(diffcolor.x)+" "+to_string(diffcolor.y)+" "+to_string(diffcolor.z)+" "+to_string(Kd)+" "+to_string(Ks)+" "+to_string(Shine)+" "+to_string(T)+" "+to_string(index_of_refraction);
        return(linedata);
    };
    
};


#endif /* Material_h */
