#ifndef COMMON_H
#define COMMON_H

//Structs to be used by objects in a 3D environment
typedef struct Position{
	float x, y, z, w;
} Position;
typedef struct Dimensions{
	float w, l, h;
} Dimensions;

//MS Visual Studio Pro 2013 was having issues with math.h
#define PI 3.141592653589793238

/**
	Convert an angle from degrees to radians
	@param degrees an angle measured in degrees
	@return the given angle measures in radians
*/
static float degToRad(float degrees){
	return degrees * PI / 180.0f;
}

/**
	Convert an angle from radians to degrees
	@param radians an angle measured in radians
	@return the given angle measured in degrees
	*/
static float radToDeg(float radians){
	return radians * 180.0f / PI;
}

#endif