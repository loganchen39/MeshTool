#ifndef DENSITY_H
#define DENSITY_H

#include <OpenMesh/Core/Geometry/VectorT.hh>
#include <string>
#include <vector>

using namespace std;
using namespace OpenMesh;

class UserDensity
{
public:
	// structure definition
	// point source
	typedef struct PointSource
	{
		Vec3f center;				        // center position
		float outer_radius, inner_radius;	// outer & inner radius
		float spacing;                      // space value 
		Vec3f bmin, bmax;		            // box of the impacted region
	} PointSource;

	// line source
	typedef struct LineSource
	{
		PointSource point_sources[2];		// two point sources
		Vec3f       bmin, bmax;     	    // box of the impacted region
	} LineSource;

	// triangle source
	typedef struct TriangleSource
	{
		PointSource point_sources[3];		// three point sources
		Vec3f     bmin, bmax;	            // box of the impacted region
	} TriangleSource;

	// Node for background
	typedef struct Node
	{
		Vec3f pt;			// coords
		float spacing;		// space control
	} Node;

    // element (triangle in 2D & tetrahedral in 3D), here it is only used for background mesh 
	typedef struct Elem
	{
		int nodes[4];
	} Elem;

	UserDensity();
	~UserDensity();

public:
	bool read_ba3(string _fn);

	float get_user_density(Vec3f _p) const;

	void set_uniform_spacing(double _us) 
	{ 
		assert(_us >= 0.0); 
		uniform_spacing_ = _us; 
	}

	void set_use_uniform_density(bool _b) { use_uniform_density_ = _b; }
	void set_use_user_density(bool _b) { use_user_density_ = _b; }
	void set_use_geometric_density(bool _b) { use_geometric_density_ = _b; }

private:
	float spacing_from_source(Vec3f _p) const;
	float spacing_from_point_source(PointSource& _pnt_src, Vec3f _p) const; // previously PointSource&, but can't do type transformation
	float spacing_from_line_source(PointSource& _pnt_src1, PointSource& _pnt_src2, Vec3f _p) const;
	float spacing_from_triangle_source(PointSource& _pnt_src1, PointSource& _pnt_src2, 
			PointSource& _pnt_src3, Vec3f _p) const;

	bool use_uniform_density_, use_user_density_, use_geometric_density_;

	// uniform spacing
	float uniform_spacing_;

	// user density
	// source
	std::vector<PointSource>    point_source_;
	std::vector<LineSource>     line_source_;
	std::vector<TriangleSource> triangle_source_;
	// background mesh
	std::vector<Node> bkg_node_;
	std::vector<Elem> bkg_elem_;

	// geometric density

};

#endif 