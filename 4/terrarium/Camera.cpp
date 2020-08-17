/**
	Camera that exists in a 3D environment.
	While the camera's position can be set explicitly, the primary method of
	movement is along the surface of an imaginary sphere around the focal point.
	The radius of the sphere is specified, as well as angles of rotation 
	in the X-Y direction and in the Z-W direction, where W is an imaginary axis
	along the line Y = X.
	
	Author: Douglas Skrypa
	Version: 2014.05.09
*/
#include "Camera.h"
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Camera::Camera(){}

/**
	Construct a Camera that exists in a 3D environment.  
	@param focusVec array/vector representing the focal point
	@param upVec array/vector representing the up direction
	@param distance the distance between the Camera and the focal point
	@param angXY angle on the XY plane (Y axis + X axis)
	@param angZW angle on the ZW plane (Z axis + imaginary axis along line Y = X)
*/
Camera::Camera(Position focusPoint, Position upPoint, float distance, float angXY, float angZW){
	focus = focusPoint;
	changeUp(upPoint);
	radius = distance;
	angleXY = angXY;
	angleZW = angZW;
	spin(0, 0);								//Initalize camera position
	setSpeed(0.1f, 3.14159f / 360.0f);		//Default zoom: 10%; spin: 0.5°
}

/**
	Refresh the camera orientation with GLU
*/
void Camera::refresh(){
	glLoadIdentity();
	gluLookAt(pos.x, pos.y, pos.z, focus.x, focus.y, focus.z, up.x, up.y, up.z);
}

/**
	Set the speed at which this Camera zooms and spins
	@param zoom multiplier for zoom steps (%)
	@param spin multiplier for spin steps (radians)
*/
void Camera::setSpeed(float zoom, float spin){
	zoomSpeed = zoom;
	spinSpeed = spin;
}

/**
	Set the speed at which this Camera zooms
	@param speed multiplier for zoom steps (%)
*/
void Camera::setZoomSpeed(float speed){
	zoomSpeed = speed;
}

/**
	Set the speed at which this Camera spins
	@param speed multiplier for spin steps (radians)
*/
void Camera::setSpinSpeed(float speed){
	spinSpeed = speed;
}

/**
	Zoom in at the previously set speed
	@param steps (optional) number of steps to zoom in (default 1)
*/
void Camera::zoomIn(int steps){
	radius -= radius * zoomSpeed;
	spin(0, 0);
}

/**
	Zoom out at the previously set speed
	@param steps (optional) number of steps to zoom out (default 1)
*/
void Camera::zoomOut(int steps){
	radius += radius * zoomSpeed;
	spin(0, 0);
}

/**
	Rotate the camera position at the previously set speed
	@param stepsXY number of steps to rotate in the XY direction
	@param stepsZW number of steps to rotate in the ZW direction
*/
void Camera::spin(float stepsXY, float stepsZW){
	angleXY += spinSpeed * stepsXY;
	angleZW += spinSpeed * stepsZW;
	pos.z = radius * sin(angleZW) + focus.z;
	pos.w = radius * cos(angleZW);
	pos.x = pos.w * cos(angleXY) + focus.x;
	pos.y = pos.w * sin(angleXY) + focus.y;
}

/**
	Rotate the camera position at the previously set speed
	@param steps number of steps to rotate in the XY direction
*/
void Camera::spinXY(float steps){
	spin(steps, 0);
}

/**
	Rotate the camera position at the previously set speed
	@param steps number of steps to rotate in the ZW direction
*/
void Camera::spinZW(float steps){
	spin(0, steps);
}

/**
	Change the focal point of this Camera
	@param pos array/vector representing the focal point
*/
void Camera::changeTarget(float x, float y, float z){
	focus.x = x;
	focus.y = y;
	focus.y = z;
}

/**
	Shift the focal point of this Camera by the specified amount in
	each direction
	@param amnt array/vector containing the distances by which to move
*/
void Camera::shiftTarget(float x, float y, float z){
	focus.x += x;
	focus.y += y;
	focus.z += z;
}

/**
	Change the direction that this Camera treats as up
	@param pos array/vector representing the up direction
*/
void Camera::changeUp(Position pos){
	up = pos;
}

/**
	Change the position of this Camera
	@param pos array/vector representing the new position
*/
void Camera::moveCam(float dx, float dy, float dz){
	shiftTarget(dx, dy, dz);
	pos.x += dx;
	pos.y += dy;
	pos.z += dz;
}

/**
	Change the distance between this Camera and its focal point
	@param r the new radius (distance)
*/
void Camera::setRadius(float r){
	radius = r;
}

/**
	Change the angle between each axis and the camera
	@param xy the new XY angle
	@param zw the new ZW angle
*/
void Camera::setAngles(float xy, float zw){
	angleXY = xy;
	angleZW = zw;
}

/**
	Get the coordinates of this Camera's position
	@return array/vector representing this Camera's position
*/
Position Camera::getPosition(){
	return pos;
}

/**
	Get the coordinates of this Camera's target
	@return array/vector representing this Camera's target's position
*/
Position Camera::getTarget(){
	return focus;
}

/**
	Get the coordinates of this Camera's up direction
	@return array/vector representing this Camera's up direction
*/
Position Camera::getUp(){
	return up;
}

/**
	Get the current radius (distance from focal point)
	@return radius of sphere of camera movement
*/
float Camera::getRadius(){
	return radius;
}

/**
	Get the current angle in the XY direction
	@return current angle in the XY direction in radians
*/
float Camera::getAngleXY(){
	return angleXY;
}

/**
	Get the current angle in the ZW direction
	@return current angle in the ZW direction in radians
*/
float Camera::getAngleZW(){
	return angleZW;
}