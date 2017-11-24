//  Scene.h
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
#include "Material.h"
#include "Light.h"
#include "Sphere.h"

using namespace std;

#ifndef Scene_h
#define Scene_h

class Scene {
private:
    vector<Light*> allLights;
    vector<Material*> allMaterials;
    vector<Sphere*> allSpheres;
    float* imageBuffer = NULL;
    int bufferWidth = 0;
    int bufferHeight = 0;
    glm::vec3 bgcolor = glm::vec3(0,0,0);
    
    void cleanup(){
        for (int i = 0; i < allLights.size(); i++) {
            delete allLights[i];
            allLights[i] = NULL;
        }
        for (int i = 0; i < allMaterials.size(); i++) {
            delete allLights[i];
            allMaterials[i] = NULL;
        }
        for (int i = 0; i < allSpheres.size(); i++) {
            delete allSpheres[i];
            allSpheres[i] = NULL;
        }
        
        if (imageBuffer != NULL) {
            delete imageBuffer;
            imageBuffer = NULL;
        }
    };
    
public:

    Scene(void){
        
    };
    
    ~Scene(){
        
    };
    
    int getLightCnt(){
        return(allLights.size());
    };

    int getSurfaceCnt(){
        return(allSpheres.size());
    };
    
    int getMaterialCnt(){
        return(allMaterials.size());
    };
    
    float* getImageBuffer(){
        return(imageBuffer);
    };
    
    int getBufferWidth(){
        return(bufferWidth);
    };
    
    int getBufferHeight(){
        return(bufferHeight);
    };
    
    void clearImageBuffer(glm::vec3 color) {
        int i,j;
        for (i = 0; i < bufferHeight; i++) {
            for (j = 0; j < bufferWidth; j++) {
                imageBuffer [( i * bufferWidth + j) *3] = color.r;
                imageBuffer [( i * bufferWidth + j) *3+1] = color.g;
                imageBuffer [( i * bufferWidth + j) *3+2] = color.b;
            }
        }
    }
    
    void setPixelinImageBuffer(int x, int y, glm::vec3 color) {
        int index = ( y * bufferWidth + x ) * 3;
        imageBuffer [index] = color.r;
        imageBuffer [index + 1] = color.g;
        imageBuffer [index + 2] = color.b;
    }
    
    bool intersectRayWithScene(glm::vec3 rayStart,glm::vec3 rayDir, double minDist, HitRecord &bestRecord){
        bool anyHit = false;
        for (int i = 0; i < allSpheres.size(); i++) {
            HitRecord temprecord;
            if (allSpheres[i]->getIntersection(rayStart, rayDir, temprecord) == true){
                if (temprecord.getT() > minDist) {
                    if (anyHit == false) {
                        anyHit = true;
                        bestRecord=temprecord;
                    }
                    else if ( temprecord.getT() < bestRecord.getT()){
                        bestRecord=temprecord;
                    }
                }
            }
        }
        return anyHit;
    }
    
    void raytrace(){
        clearImageBuffer(glm::vec3(0,0,0));
        int nx,ny;
        int nearDist = 0;
        float aspectratio, imagePlaneHeight, imagePlaneWidth;
        float left, right, bottom, top;
        glm::vec3 U = glm::vec3(1,0,0);
        glm::vec3 V = glm::vec3(0,1,0);
        glm::vec3 W = glm::vec3(0,0,1);
        glm::vec3 E = glm::vec3(0,0,1.5);
        float d = 1.0;
        glm::vec3 raystart = glm::vec3(0,0,0);
        glm::vec3 raydir = glm::vec3(0,0,0);
        
        nx = bufferWidth;
        ny = bufferHeight;
        aspectratio = nx/ny;
        imagePlaneHeight = 2.0;
        imagePlaneWidth = imagePlaneHeight*aspectratio;
        left = -imagePlaneWidth/2.0;
        right = imagePlaneWidth/2.0;
        bottom = -imagePlaneHeight/2.0;
        top = imagePlaneHeight/2.0;
        
        for (int j = 0; j < bufferWidth; j++) {
            for (int i = 0; i < bufferHeight; i++) {
                float u = left + (right - left)*(i+0.5)/nx;
                float v = bottom + (top - bottom)*(j+0.5)/ny;
                raystart = E;
                raydir = (u*U) + (v*V) - (d*W);
                HitRecord bestRecord;
                if (intersectRayWithScene(raystart, raydir, nearDist, bestRecord) == true){
                    setPixelinImageBuffer(j, i, allMaterials[bestRecord.getMatIndex()]->getColor());
                }
                else {
                    setPixelinImageBuffer(j, i, bgcolor);
                }
            }
        }
        
    };
    
    string toString(){
        string finalstring;
        finalstring = "b "+ to_string(bgcolor.r)+" "+to_string(bgcolor.g)+" "+to_string(bgcolor.b)+"\n";
        for (int i = 0; i < allLights.size(); i++) {
            finalstring = finalstring + allLights[i]->toString() + "\n";
        }
        for (int j = 0; j < allMaterials.size(); j++) {
            finalstring = finalstring + allMaterials[j]->toString() + "\n";
        }
        for (int k = 0; k < allSpheres.size(); k++) {
            finalstring = finalstring + allSpheres[k]->toString() + "\n";
        }
        return(finalstring);
    };
    
    bool loadNFF(string filename, int windowWidth, int windowHeight){
        ifstream file;
        file.open(filename);
        
        if (!file) {
            return(false);
        }
        
        cleanup();
        bufferWidth = windowWidth;
        bufferHeight = windowHeight;
        
        int MaterialIndex = -1;
        
        //for (string line; getline(file,line); ){
        while (!file.eof()){
            string line;
            getline(file,line);
            stringstream ss (line);
            
            if (line[0] == 'b') {
                char dummy[5];
                ss>>dummy;
                ss>>bgcolor.r>>bgcolor.g>>bgcolor.b;
            }
            if (line[0] == 'l'){
                Light *l = new Light();
                l->read(line);
                allLights.push_back(l);
                
            }
            if (line[0] == 's'){
                Sphere *s = new Sphere();
                s->read(line);
                allSpheres.push_back(s);
                s->setMaterialIndex(MaterialIndex);
            }
            if (line[0] == 'f' && line[1] != 'r') {
                MaterialIndex++;
                Material *m = new Material();
                m->read(line);
                allMaterials.push_back(m);
            }
            
        }
        file.close();
        //cout<<"number of spheres: "<< allSpheres.size()<<endl;
        
        
        imageBuffer = new float[3*bufferWidth*bufferHeight];
        
        //clearImageBuffer(glm::vec3 (1,0,0));
        return(true);
    }
};

#endif /* Scene_h */
