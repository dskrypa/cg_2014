#include "Env3D.h"

Env3D::Env3D(){}

/**
	Construct a new 3D environment with all parameters set
	@param fps target frams per second for animation
	@param wWidth window width
	@param wHeight window height
	@param pMin minimum X/Y/Z bounds for this environment
	@param pMax maximum X/Y/Z bounds for this environment
*/
Env3D::Env3D(float fps, float wWidth, float wHeight, Position pMin, Position pMax){
	targetFps = fps;
	windowWidth = wWidth;
	windowHeight = wHeight;
	min = pMin;
	max = pMax;
}

/**
	Determines whether or not a given point is within the bounds of this 3D
	environment.
	@param p the position to test
	@return true if the given position is between min & max points
*/
bool Env3D::isInBounds(Position p){
	bool minCheck = (p.x >= min.x) && (p.y >= min.y) && (p.z >= min.z);
	bool maxCheck = (p.x <= max.x) && (p.y <= max.y) && (p.z <= max.z);
	return minCheck && maxCheck;
}






/*	Self-explanatory setters	*/
void Env3D::setWinSize(float w, float h){
	windowWidth = w;
	windowHeight = h;
}
void Env3D::setTargetFps(float fps){		targetFps = fps;}
void Env3D::setMinPoint(Position p){		min = p;}
void Env3D::setMaxPoint(Position p){		max = p;}
/*	Self-explanatory getters	*/
float Env3D::getTargetFps(){	return targetFps;}
float Env3D::getWinWidth(){		return windowWidth;}
float Env3D::getWinHeight(){	return windowHeight;}
Position Env3D::getMinPoint(){	return min;}
Position Env3D::getMaxPoint(){	return max;}
float Env3D::getBoundedWidth(){		return max.x - min.x;}
float Env3D::getBoundedLength(){	return max.y - min.y;}
float Env3D::getBoundedHeight(){	return max.z - min.z;}
