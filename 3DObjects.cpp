#include "3DObjects.h"
#define _USE_MATH_DEFINES
#include <math.h>

Object3D::Object3D() {
	Ky = 0 ,Kz = 0;
	ResultPnt = { 0, 0, 0 };
	ResultVec = { 0, 0, 0 };
}


Point3D Object3D::GetPointByParameter(float t) {
	//realize for the object
	return ResultPnt;
}
Vector3D Object3D::GetDerivByParameter(float t) {
	//realize for the object
	return ResultVec;
}
Object3D* Object3D::GetThis() {

	return this;

}
Object3D::~Object3D(){
	
}


//CIRCLE
Circle::Circle(float rad) {
	Rad = rad;
}
Point3D Circle::GetPointByParameter(float t) {
	

	ResultPnt.x = Rad * cos (t);
	ResultPnt.y = Rad * sin (t);
	ResultPnt.z = 0;

	return ResultPnt;
}

Vector3D Circle::GetDerivByParameter(float t) {

	

	if (sin(t) != 0) {
		Ky = -cos(t) / sin(t);

		ResultVec.nrmlX = 1.0 / sqrt(1.0 + Ky * Ky);
		ResultVec.nrmlY = Ky / sqrt(1.0 + Ky * Ky);
	}
	else {
		ResultVec.nrmlX = 0;
		ResultVec.nrmlY = 1;
	}


	ResultVec.nrmlZ = 0;

	return ResultVec;
}


float Circle::GetRad() {
	return Rad;
}
Circle::~Circle() {
	
}


//ELLIPS
Ellips::Ellips(float radA, float radB) {
	
	RadA = radA;
	RadB = radB;
	
}
Point3D Ellips::GetPointByParameter(float t) {
	
	
	ResultPnt.x = RadA * cos(t);
	ResultPnt.y = RadB * sin(t);
	ResultPnt.z = 0;

	return ResultPnt;
}
Vector3D Ellips::GetDerivByParameter(float t) {
	
	if (sin(t) != 0) {
		Ky = -(RadB*cos(t)) / (RadA*sin(t));

		ResultVec.nrmlX = 1.0 / sqrt(1.0 + Ky * Ky);
		ResultVec.nrmlY = Ky / sqrt(1.0 + Ky * Ky);
	}
	else {
		ResultVec.nrmlX = 0;
		ResultVec.nrmlY = 1.0;
	}

	ResultVec.nrmlZ = 0;

	return ResultVec;

	
}


Ellips::~Ellips() {
	
}



//HELIX
Helix::Helix(float rad, float step) {
	
	Rad = rad;
	Step = step;
	
}
Point3D Helix::GetPointByParameter(float t) {
	
	
	ResultPnt.x = Rad * cos(t);
	ResultPnt.y = Rad * sin(t);
	ResultPnt.z =  Step * t;

	return ResultPnt;
}
Vector3D Helix::GetDerivByParameter(float t) {
	

	if (sin(t) != 0) {
		Ky = -cos(t) / sin(t);

		ResultVec.nrmlX = 1.0 / sqrt(1.0 + Ky * Ky);
		ResultVec.nrmlY = Ky / sqrt(1.0 + Ky * Ky);
	}
	else {
		ResultVec.nrmlX = 0;
		ResultVec.nrmlY = 1;
	}

	Kz = Step / sqrt(Rad * Rad + Step * Step);

	ResultVec.nrmlZ = Kz;

	return ResultVec;
}


Helix::~Helix() {
	
}