/**
* class Trackball for mouse trackball algorithm
* @origin Intra3D, RuiLin
* @author LigangChen
* @version 0.1 02/27/2007
*/

#ifndef TRACKBALL_H
#define TRACKBALL_H

#include <OpenMesh/Core/Geometry/VectorT.hh>

using namespace OpenMesh; // can not find Vec3f without this directive

class Trackball
{
public:
	Trackball(void);
    ~Trackball(void);

public:
	// the center of Trackball is the center of the window 
	void set_track_window(int _width, int _height);

	// the center of Trackball is the window coordinate(_center_x, _center_y) 
	void set_track_window(int _width, int _height, int _center_x, int _center_y);

	// set the coordinate when the mouse is pressed (_mouse_x, _mouse_y)
	void start(int _mouse_x, int _mouse_y);

	// move mouse (dx,dy), compute the axis and the angle of rotation 
	void tracking(int _dx, int _dy, Vec3f *_axis, float *_angle);

protected:
	// project the mouse coordinate to the trackball
	// return the vector from the ball-center to the projection-point
	Vec3f map_to_sphere(int _mouse_x, int _mouse_y);

	int width_, height_;	        // width and height of window
	int center_x_, center_y_;	    // center of trackball
	int radius_;				    // radius of trackball
	int mouse_x_,  mouse_y_;	    // coordinate of mouse

	Vec3f start_;	// the projected vector when mouse is pressed
	Vec3f end_;	    // the projected vector when mouse is dragged
};

#endif