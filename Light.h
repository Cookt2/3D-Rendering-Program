//  Light.h
//  Assignment 4
//
//  Created by Taylor Cook on 9/13/17.

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
#include "glm/glm.hpp"					// NOTE: Need to compile, hence the quotes
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

using namespace std;

#ifndef Light_h
#define Light_h

class Light {
    
private:
    glm::vec3 pos = glm::vec3(0,0,0);
    glm::vec3 color = glm::vec3(1,1,1);
    
public:
    Light(void){
        
    };
    
    Light(glm::vec3 pos1){
        pos.x=pos1.x;
        pos.y=pos1.y;
        pos.z=pos1.z;
        color.r = 1;
        color.g = 1;
        color.b = 1;
        
    };
    
    Light(glm::vec3 pos1, glm::vec3 color1){
        pos.x=pos1.x;
        pos.y=pos1.y;
        pos.z=pos1.z;
        color.r=color1.r;
        color.g=color1.g;
        color.b=color1.b;
    };
    
    glm::vec3 getPos(){
        return (pos);
    };
    glm::vec3 getColor(){
        return (color);
    };
    
    void read(string data){
        stringstream ss (data);
        char dummy[80];
        
        ss>>dummy;
        ss>>pos.x>>pos.y>>pos.z;
        
        if (ss >> color.r){
            ss >> color.g >> color.b;
        }
        else {
            color.r = 1;
            color.g = 1;
            color.b = 1;
            
        }
        
    };
    
    string toString(){
        string posandcolor = "l " + to_string(pos.x) +" "+ to_string(pos.y) +" "+ to_string(pos.z) +" "+ to_string(color.r)+" "+ to_string(color.g) +" "+ to_string(color.b);
        return (posandcolor);
    };
    
};


#endif /* Light_h */
