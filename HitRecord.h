//  HitRecord.h
//  Assignment 4
//
//  Created by Taylor Cook on 11/1/17.

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

#ifndef HitRecord_h
#define HitRecord_h


#define MIN_DISTANCE_T 0.001

class HitRecord {

    
private:
    double t = -1;
    glm::vec3 interpoint = glm::vec3(0,0,0);
    glm::vec3 normalinter = glm::vec3(0,0,1);
    int matindexinter = 0;
    
public:

    
    HitRecord(void){
    
    };
    
    HitRecord(double T, glm::vec3 point, glm::vec3 normal, int matindex){
        t = T;
        interpoint = point;
        normalinter = normal;
        matindexinter = matindex;
    };
    
    double getT(){
        return(t);
    };
    
    glm::vec3 getPoint(){
        return(interpoint);
    };
    
    glm::vec3 getNormal(){
        return(normalinter);
    };
    
    int getMatIndex(){
        return(matindexinter);
    };
    
    void setT(double T){
        t=T;
    };
    
    void setPoint(glm::vec3 point){
        interpoint=point;
    };
    
    void setNormal(glm::vec3 normal){
        normalinter = normal;
    };
    
    void setMatIndex(int index){
        matindexinter = index;
    };
    
};
#endif /* HitRecord_h */
