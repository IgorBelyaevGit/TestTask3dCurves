#pragma once

struct Point3D {
	float x;
	float y;
	float z;
};
struct Vector3D {
	float nrmlX = 0;
	float nrmlY = 0;
	float nrmlZ = 0;
};

class Object3D {

public:
	Object3D();
	~Object3D();
	virtual Point3D GetPointByParameter(float t);
	virtual Vector3D GetDerivByParameter(float t);
	virtual int GetType();	
	virtual Object3D* GetThis();


	Vector3D ResultVec;
	Point3D ResultPnt;
	float  Ky, Kz;
};

class Circle : public Object3D {
public:
	Circle(float rad);
	Point3D GetPointByParameter(float t);
	Vector3D GetDerivByParameter(float t);
	int GetType();
	float GetRad();
	~Circle();
private:
	float Rad;

};

class Ellips : public Object3D {
public:
	Ellips(float radA, float radB);
	Point3D GetPointByParameter(float t);
	Vector3D GetDerivByParameter(float t);
	int GetType();
	~Ellips();
private:
	float RadA;
	float RadB;

};

class Helix : public Object3D {
public:
	Helix(float rad,float step);
	Point3D GetPointByParameter(float t);
	Vector3D GetDerivByParameter(float t);
	int GetType();
	
	~Helix();
private:
	float Rad;
	float Step;

};