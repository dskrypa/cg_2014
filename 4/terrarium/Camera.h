/**
	Camera in a 3D environment
	@author Douglas Skrypa
	@version 2014.05.09
*/
#ifndef CAMERA_H
#define CAMERA_H

#include "Env3D.h"

class Camera{
	private:
		//float w, x, y, z;
		float radius, angleXY, angleZW;
		float zoomSpeed, spinSpeed;
		Position pos, focus, up;
	public:
		Camera();
		Camera(Position focusPoint, Position upPoint, float distance, float angXY, float angZW);
		void refresh();
		void setSpeed(float, float);
		void setZoomSpeed(float);
		void setSpinSpeed(float);
		void zoomIn(int);
		void zoomOut(int);
		void spin(float, float);
		void spinXY(float);
		void spinZW(float);
		void changeTarget(float, float, float);
		void shiftTarget(float, float, float);
		void changeUp(Position);
		void moveCam(float, float, float);
		void setRadius(float);
		void setAngles(float, float);
		Position getPosition();
		Position getTarget();
		Position getUp();
		float getRadius();
		float getAngleXY();
		float getAngleZW();
};
#endif