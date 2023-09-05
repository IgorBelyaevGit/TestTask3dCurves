// 3DCurvesHierarchyTEST.cpp
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <math.h>
#include <omp.h>
#include <string.h>
#include "3DObjects.h"


using namespace std;

#define T_PARAM M_PI_4
#define OPENMP_THREADS 4





void CreateContainer(vector<std::shared_ptr<Object3D>> &curvesVec);

void PrintPointsAndDerivs(vector< std::shared_ptr<Object3D>> &curvesVec);

void CreateContainerCircles(vector<std::shared_ptr<Circle>>& CirclesOnlyVec, vector<std::shared_ptr<Object3D>>& curvesVec);
void SortCircles(vector< std::shared_ptr<Circle>> &CirclesOnlyVec);
float ComputeRadiusSum(vector<std::shared_ptr<Circle>>& CirclesOnlyVec);
bool СompareCircles(std::shared_ptr<Circle> a, std::shared_ptr<Circle> b);
void FreeResources(vector<std::shared_ptr<Circle>>& CirclesOnlyVec, vector<std::shared_ptr<Object3D>>& curvesVec);




int main()
{
    

    std::cout.precision(2);
    float sum_radiuses = 0;
    std::vector<std::shared_ptr<Object3D>> CurvesVec;
    std::vector<std::shared_ptr<Circle>> CirclesOnlyVec;
    

    CreateContainer( CurvesVec);

    PrintPointsAndDerivs(CurvesVec);

    CreateContainerCircles(CirclesOnlyVec, CurvesVec);

    SortCircles(CirclesOnlyVec);
    
    
    
    std::cout << "\nSort result!\n";
    for (auto& circle : CirclesOnlyVec) {
        cout << "Radius: " << circle->GetRad() << "\n";      
    }

    
    sum_radiuses = ComputeRadiusSum(CirclesOnlyVec);
    cout << "Sum of Radiuses: " << sum_radiuses << "\n";

    
    
    //try with OPEN_MP
    sum_radiuses = 0;
    omp_set_num_threads(OPENMP_THREADS);

    #pragma omp parallel for
    for (int i = 0; i < CirclesOnlyVec.size(); i++)
        sum_radiuses += CirclesOnlyVec[i]->GetRad();
    

    cout << "Sum of Radiuses with OPENMP: " << sum_radiuses << "\n";


    
    FreeResources(CirclesOnlyVec, CurvesVec);
   
}

void CreateContainer( vector<std::shared_ptr<Object3D>> &CurvesVector) {

    int numbercurves = 0;
    int maxvalue = 0;
    int type = 0;

    std::cout << "Enter number of curves!\n";
    cin >> numbercurves;
    std::cout << "Enter max value of parameters of curves!\n";
    cin >> maxvalue;



    random_device rnd_device;   
    mt19937 gen(rnd_device());
    uniform_int_distribution<> distType(1, 3); 
    uniform_int_distribution<> distValue(1, maxvalue);
    

    float valueIN;
    float valueIN2;

    for (int i = 0; i < numbercurves; i++) {

        valueIN = float(distValue(gen));
        valueIN2 = float(distValue(gen));
        
        type = distType(gen);
        


        if (type == 1 && valueIN > 0)               
            CurvesVector.push_back( std::make_shared<Circle>(valueIN));
        
        if(type == 2 && valueIN * valueIN2 > 0)
            CurvesVector.push_back(std::make_shared<Ellips>(valueIN, valueIN2));

        if (type == 3 && valueIN > 0)          
            CurvesVector.push_back(std::make_shared<Helix>(valueIN, valueIN2));
        
    }


    
}
void PrintPointsAndDerivs(vector< std::shared_ptr<Object3D>> &CurvesVector) {

    Point3D point;
    Vector3D vec;
    string typestr;
    cout << "Number of curves: " << CurvesVector.size()<<"\n";

    cout << "Type\t" << "PointX\t" << "PointY\t" << "PointZ\t" << "Derivatives:\t"<<"NormalX\t"<< "NormalY\t"<< "NormalZ\n";

    for (auto& curve : CurvesVector)
    {
        
        point = curve->GetPointByParameter(T_PARAM);
        vec = curve->GetDerivByParameter(T_PARAM);
        typestr.assign(typeid(*curve).name());
        
        

        if (!typestr.compare("class Circle\0")) {
            cout << "Circle " << "\t" << point.x << "\t" << point.y << "\t" << point.z << " \tDerivatives: ";
            cout << "\t" << vec.nrmlX << "\t" << vec.nrmlY << "\t" << vec.nrmlZ << " \n";
        }
            
        if (!typestr.compare("class Ellips\0")) {
            cout << "Ellips " << "\t" << point.x << "\t" << point.y << "\t" << point.z << " \tDerivatives: ";
            cout << "\t" << vec.nrmlX << "\t" << vec.nrmlY << "\t" << vec.nrmlZ << " \n";
        }
        if (!typestr.compare("class Helix\0")) {
            cout << "Helix " << "\t" << point.x << "\t" << point.y << "\t" << point.z << " \tDerivatives: ";
            cout << "\t" << vec.nrmlX << "\t" << vec.nrmlY << "\t" << vec.nrmlZ << " \n";
        }
        
        
    }

}
void CreateContainerCircles(vector<std::shared_ptr<Circle>> &CirclesOnlyVector, vector<std::shared_ptr<Object3D>> &CurvesVector) {

    string typestr;
    for (auto& curve : CurvesVector)
    {
        typestr.assign(typeid(*curve).name());
        if (!typestr.compare( "class Circle\0")) {
            
            CirclesOnlyVector.push_back(dynamic_pointer_cast<Circle>(curve));
        }
    }
    
}



void SortCircles(vector<std::shared_ptr<Circle>> &CirclesOnlyVector) {
    

    sort(CirclesOnlyVector.begin(), CirclesOnlyVector.end(), СompareCircles);

}
float ComputeRadiusSum(vector<std::shared_ptr<Circle>> &CirclesOnlyVector) {
    float RadiusSum = 0;
    
    for (auto& circle : CirclesOnlyVector)
        RadiusSum += circle->GetRad();
    return RadiusSum;
}
void FreeResources(vector<std::shared_ptr<Circle>> &CirclesOnlyVector, vector<std::shared_ptr<Object3D>> &CurvesVector) {

    char val;
    for (auto& curve : CurvesVector) {
         curve.reset();
    }
    
    CurvesVector.clear();
    CirclesOnlyVector.clear();

    cout << "Enter any button" << "\n";
    cin >> val;
    
}

bool СompareCircles(std::shared_ptr<Circle> a, std::shared_ptr<Circle> b) {
    return (a->GetRad() < b->GetRad());
}