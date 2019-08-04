/**
* class Trackball for mouse trackball algorithm
* @origin Intra3D, RuiLin
* @author LigangChen
* @version 0.1 02/27/2007
*/

#include <math.h>		
//#include <assert.h>

#include <OpenMesh/Core/Geometry/VectorT.hh>

#include "trackball.h"

Trackball::Trackball(void)
{
	width_ = height_ = 400;	
	center_x_ = center_y_ = 200;
	radius_ = 200;
	mouse_x_ = mouse_y_ = 1;

	start_ = end_ = Vec3f(0.0, 0.0, 0.0);
}

Trackball::~Trackball(void)
{
}

void Trackball::set_track_window(int _width, int _height)
{
	width_    = _width;
	height_   = _height;
	center_x_ = width_/2;
	center_y_ = height_/2;
	radius_   = (width_ > height_) ? center_y_ : center_x_;
}

void Trackball::set_track_window(int _width, int _height, int _center_x, int _center_y)
{
	width_    = _width;
	height_   = _height;
	center_x_ = _center_x;
	center_y_ = _center_y;
	radius_   = (width_ > height_) ? center_y_ : center_x_;
}

Vec3f Trackball::map_to_sphere(int _mouse_x, int _mouse_y)
{
	Vec3f v(0.0, 0.0, 0.0);

	if(center_x_ >= width_/2)  
		v[0] = 1.0 * (_mouse_x - center_x_) / center_x_;
	else
		v[0] = 1.0 * (_mouse_x - center_x_) / (width_ - center_x_);

	if(center_y_ >= height_ / 2)  
		v[1] = 1.0 * (center_y_ - _mouse_y) / center_y_;
	else
		v[1] = 1.0 * (center_y_ - _mouse_y) / (height_ - center_y_);

	float d = (float)sqrt(v[0] * v[0] + v[1] * v[1]);
	v[2] = (float)(cos((3.14159265 / 2.0) * ((d < 1.0) ? d : 1.0)));
	v.normalize();

	return v;
}

void Trackball::start(int _mouse_x, int _mouse_y)
{
	mouse_x_ = _mouse_x;
	mouse_y_ = _mouse_y;
	start_ = map_to_sphere(mouse_x_, mouse_y_);
}

void Trackball::tracking(int _dx, int _dy, Vec3f *axis, float *angle)
{
	mouse_x_ += _dx;
	mouse_y_ += _dy;
	end_ = map_to_sphere(mouse_x_, mouse_y_);
	*axis = start_ % end_;  // cross product

	const float ANGLE_SCALE = 2.0f;	// given an arbitary angle scale, it must determine the rotating speed
	*angle = (float)(ANGLE_SCALE * acos(start_ | end_) / 3.14159 * 180.0); // make sure start_ and end_ are unit normals
	
	// limit the returning minimum angle, or the rotation might be wrong
	const float	DELTA_ANGLE = 0.00001f;
	if(*angle < DELTA_ANGLE)	
		*angle = DELTA_ANGLE;

	start_ = end_; // do not forget
}
