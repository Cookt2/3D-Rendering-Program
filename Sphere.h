//  Sphere.h
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
#include <math.h>
#include "glm/glm.hpp"					// NOTE: Need to compile, hence the quotes
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"
#include "HitRecord.h"

using namespace std;

#ifndef Sphere_h
#define Sphere_h

class Sphere {
    
private:
    int materialIndex = -1;
    double radius = 1;
    
    glm::vec3 pos = glm::vec3(0,0,0);
    
public:
    Sphere(void){
        
    };
    
    Sphere(glm::vec3 center1, double radius1){
        pos.x=center1.x;
        pos.y=center1.y;
        pos.z=center1.z;
        radius=radius1;
    };
    
    void setMaterialIndex(int matIndex){
        materialIndex=matIndex;
    };
    
    int getMaterialIndex(){
        return(materialIndex);
    };
    
    glm::vec3 getCenter(){
        return(pos);
    };
    
    double getRadius(){
        return(radius);
    };
    
    void read(string data){
        stringstream ss (data);
        char dummy[80];
        
        ss>>dummy;
        ss>>pos.x>>pos.y>>pos.z;
        ss>>radius;
    };
    
    string toString(){
        string posandrad = "s " + to_string(pos.x) +" "+ to_string(pos.y) +" "+ to_string(pos.z) +" "+ to_string(radius);
        return (posandrad);
    };
    
    bool getIntersection(glm::vec3 E, glm::vec3 D, HitRecord &record){
        float g = pow(glm::dot(D,E-pos),2.0) - glm::dot(D,D)*(glm::dot((E-pos),(E-pos))-pow(radius, 2.0));
        
        if (g < 0) {
            return false;
        }
/*        else if ( g == 0 ){
            float t = -glm::dot(D,(E-pos))/glm::dot(D,D);
            record.setT(t);
            record.setMatIndex(materialIndex);
            record.setNormal(glm::normalize(pos-(E+(t*D))));
            record.setPoint(E+(t*D));
            return true;
        }*/
        else {
           // float tt = -glm::dot(D,(E-pos))+sqrt(pow(glm::dot(D,E-pos),2.0) - glm::dot(D,D)*(glm::dot((E-pos),(E-pos))-pow(radius, 2.0)))/glm::dot(D,D);
            float t = (-glm::dot(D,(E-pos))-sqrt(g))/glm::dot(D,D);
           /* if (tt < t){
                record.setT(tt);
                record.setPoint(E+(tt*D));
                record.setNormal(glm::normalize(pos-(E+(tt*D))));
                record.setMatIndex(materialIndex);
                return true;
                }*/
            
                record.setT(t);
                record.setPoint(E+(t*D));
                record.setNormal(glm::normalize((E+(t*D))-pos));
                record.setMatIndex(materialIndex);
                return true;
            
        }
    };
};

#endif /* Sphere_h */
