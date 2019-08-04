#include "userdensity.h"

#include <math.h>
#include <fstream>
#include <iostream>

UserDensity::UserDensity() : uniform_spacing_(0.0),
		use_uniform_density_(false), use_user_density_(false),
		use_geometric_density_(false)
{
	point_source_.clear();
	line_source_.clear();
	triangle_source_.clear();

	bkg_node_.clear();
	bkg_elem_.clear();
}

UserDensity::~UserDensity()
{
	point_source_.clear();
	line_source_.clear();
	triangle_source_.clear();

	bkg_node_.clear();
	bkg_elem_.clear();
}

bool UserDensity::read_ba3(string _fn)
{
	ifstream ba3_file(_fn.c_str());
	if (!ba3_file)
	{
		cerr << "error: unable to open ba3 file: " << _fn << endl;
		return false;
	}

	int np, ne, nps, nls, nts;
	int i, j, idummy;
	float fdummy;
	char cdummy[1024];
	Node nd;
	Elem el;
	PointSource    pnts;
	LineSource     lins;
	TriangleSource tris;

	ba3_file.getline(cdummy, 512);
	ba3_file >> np >> ne >> nps >> nls >> nts;
	cout << "#P #E #PS #LS #TS: " << np << " " << ne << " " << nps << " " << nls << " " << nts << endl; 
	
	for (i = 0; i < np; i++)
	{
		ba3_file >> idummy >> nd.pt[0] >> nd.pt[1] >> nd.pt[2];
		ba3_file >> fdummy >> fdummy >> fdummy >> nd.spacing;
		ba3_file.getline(cdummy, 1024);

		ba3_file.getline(cdummy, 1024);
		ba3_file.getline(cdummy, 1024);
		bkg_node_.push_back(nd);
	}

	for (i = 0; i < ne; i++)
	{
		ba3_file >> idummy >> el.nodes[0] >> el.nodes[1] >> el.nodes[2] >> el.nodes[3];
		for (j = 0; j < 4; j++)
			el.nodes[j]--;
		bkg_elem_.push_back(el);
	}
	ba3_file.getline(cdummy, 1024);

	ba3_file.getline(cdummy, 256);
	for (i = 0; i < nps; i++)
	{
		ba3_file >> idummy;
		ba3_file >> pnts.center[0] >> pnts.center[1] >> pnts.center[2] >> pnts.spacing 
			>> pnts.inner_radius >> pnts.outer_radius;
		point_source_.push_back(pnts);
	}
	ba3_file.getline(cdummy, 1024);

	ba3_file.getline(cdummy, 256);
	for (i = 0; i < nls; i++)
	{
		ba3_file >> idummy;
		for (j = 0; j < 2; j++)
		{
			ba3_file >> lins.point_sources[j].center[0] >> lins.point_sources[j].center[1]  
				>> lins.point_sources[j].center[2]  >> lins.point_sources[j].spacing 
				>> lins.point_sources[j].inner_radius >> lins.point_sources[j].outer_radius;
		}
		line_source_.push_back(lins);
	}
	ba3_file.getline(cdummy, 1024);

	ba3_file.getline(cdummy, 256);
	for (i = 0; i < nts; i++)
	{
		ba3_file >> idummy;
		for (j = 0; j < 3; j++)
		{
			ba3_file >> tris.point_sources[j].center[0] >> tris.point_sources[j].center[1]  
				>> tris.point_sources[j].center[2]  >> tris.point_sources[j].spacing 
				>> tris.point_sources[j].inner_radius >> tris.point_sources[j].outer_radius;
		}
		triangle_source_.push_back(tris);
	}
	ba3_file.getline(cdummy, 1024);

	ba3_file.close();

	return true;
}

float UserDensity::get_user_density(Vec3f _p) const
{
	// to be enhanced

	float den = 1.0e10, tmp_den = 0.0;

	if (use_uniform_density_)
	{
		if (uniform_spacing_ <= 0.0)
			return -1.0;
		else
			den = uniform_spacing_;
	}
		
	if (use_user_density_)
		tmp_den = spacing_from_source(_p);
	if (tmp_den > 0.0 && tmp_den < den)
		den = tmp_den;

	if (1.0e10 == den || den <= 0.0)
		return -1.0;
	else
		return den;
}

float UserDensity::spacing_from_source(Vec3f _p) const
{
	int j;
	float den = 1.e10, spac;

	PointSource pnt_src0, pnt_src1, pnt_src2;

	// point source control 
	//std::vector<PointSource>::iterator pnt_iter;
	for (j = 0; j < point_source_.size(); j++)
	{
		pnt_src0 = point_source_[j];
		spac = spacing_from_point_source(pnt_src0, _p);
		if (spac < den)
			den = spac;
	}

	// line source control 
	for (j = 0; j < line_source_.size(); j++)
	{
		pnt_src0 = line_source_[j].point_sources[0];
		pnt_src1 = line_source_[j].point_sources[1];
		spac = spacing_from_line_source(pnt_src0, pnt_src1, _p);
		if (spac < den)
			den = spac;
	}	

	// triangle source control
	for (j = 0; j < triangle_source_.size(); j++)
	{
		pnt_src0 = triangle_source_[j].point_sources[0];
		pnt_src1 = triangle_source_[j].point_sources[1];
		pnt_src2 = triangle_source_[j].point_sources[2];
		spac = spacing_from_triangle_source(pnt_src0,
					   	  pnt_src1,
			              pnt_src2,
						  _p);
		if (spac < den)
			den = spac;
	}

	return den;
}

float UserDensity::spacing_from_point_source(PointSource& _pnt_src, Vec3f _p) const
{
	float diff, ae;
	const float BIG = 50.0;
	const float CLG2 = log(2.0);
	Vec3f dist_vec = _pnt_src.center - _p;
	float dist = dist_vec.norm();
	if (dist <= _pnt_src.inner_radius)
		return _pnt_src.spacing;
	else
	{
		dist = dist - _pnt_src.inner_radius;
		diff = _pnt_src.outer_radius - _pnt_src.inner_radius;
		if (diff <= 0.0)
		{
			cerr << "Error point source" << endl;
			return 1.0e10;
		}
		else
		{
			diff = CLG2 / diff;
			ae = dist * diff < BIG ? dist * diff : BIG;
			return _pnt_src.spacing * exp(ae);
		}
	}
}

float UserDensity::spacing_from_line_source(PointSource& _pnt_src1, PointSource& _pnt_src2, Vec3f _p) const
{
	float sca = 0.0;
	float w1, w2;
	// REAL tolg = 1e-5;
	Vec3f v12, line = _pnt_src1.center - _pnt_src2.center;
	PointSource pnt_src3;
	int i;

	float dist = line.norm(); 
	if (dist < 1.0e-6)  
	{
		cerr << "Error line source" <<endl;
		return 1.0e10;
	}
	v12 = (_pnt_src2.center - _pnt_src1.center) / dist;

	sca = (_p - _pnt_src1.center) | v12;
	if (sca <= 0.0)
		return spacing_from_point_source(_pnt_src1, _p);
	else if (sca >= dist)
		return spacing_from_point_source(_pnt_src2, _p);
	else
	{
		w2 = sca / dist;
		w1 = 1.0 - w2;

		pnt_src3.center = w1 * _pnt_src1.center + w2 * _pnt_src2.center;
		pnt_src3.inner_radius = w1 * _pnt_src1.inner_radius + w2 * _pnt_src2.inner_radius;
		pnt_src3.outer_radius = w1 * _pnt_src1.outer_radius + w2 * _pnt_src2.outer_radius;
		pnt_src3.spacing = w1 * _pnt_src1.spacing + w2 * _pnt_src2.spacing;
		return spacing_from_point_source(pnt_src3, _p);
	}
}

float UserDensity::spacing_from_triangle_source(PointSource& _pnt_src1, PointSource& _pnt_src2, 
			PointSource& _pnt_src3, Vec3f _p) const
{
	float sca = 0;
	float w1, w2, w3, sh1=0.0, sh3=0.0, h1=0.0, h3=0.0;
	// REAL tolg = 1e-5;
	PointSource pnt_src4;
	Vec3f v12, v23, v31;
	Vec3f nt, n12, n23; 
	Vec3f v2p;
	int i;
	float dist;

#define  EPS_ZERO_SQ  1.e-12

	v12 = _pnt_src2.center - _pnt_src1.center;
	dist = v12.sqrnorm(); 
	if (dist < EPS_ZERO_SQ) 
	{
		cerr << "Error triangle source" << endl;
		return 1.0e10;
	}

	v23 = _pnt_src3.center - _pnt_src2.center;
	dist = v23.sqrnorm(); 
	if (dist < EPS_ZERO_SQ)
	{
		cerr << "Error triangle source" << endl;
		return 1.0e10;
	}

	v31 = _pnt_src1.center - _pnt_src3.center;
	dist = v31.sqrnorm(); 
	if (dist < EPS_ZERO_SQ)
	{
		cerr << "Error triangle source" << endl;
		return 1.0e10;
	}

#undef EPS_ZERO_SQ

	nt = v12 % v23;
	
	// normal to side 1-2 n12=nt^v12 
	// crossVect(nt, v12, &n12);
	n12 = nt % v12;

	n23 = nt % v23;

	v2p = _p - _pnt_src2.center;
	
	// compute area weights, using the point projected to the triangle 
	h1  =  v2p | n23;
	sh1 = -v12 | n23;
	h3  =  v2p | n12;
	sh3 =  v23 | n12;

	w1 = h1 / sh1;
	w3 = h3 / sh3;
	w2 = 1.0 - w1 - w3;
	
	if (w1 <= 0.0)
		return spacing_from_line_source(_pnt_src2, _pnt_src3, _p);
	else if (w2 <= 0.0)
		return spacing_from_line_source(_pnt_src1, _pnt_src3, _p);
	else if (w3 <= 0.0)
		return spacing_from_line_source(_pnt_src1, _pnt_src2, _p);
	else
	{
		pnt_src4.center = w1 * _pnt_src1.center + w2 * _pnt_src2.center + w3 * _pnt_src3.center;
		pnt_src4.inner_radius = w1 * _pnt_src1.inner_radius + w2 * _pnt_src2.inner_radius + w3 * _pnt_src3.inner_radius;
		pnt_src4.outer_radius = w1 * _pnt_src1.outer_radius + w2 * _pnt_src2.outer_radius + w3 * _pnt_src3.outer_radius;
		pnt_src4.spacing      = w1 * _pnt_src1.spacing + w2 * _pnt_src2.spacing + w3 * _pnt_src3.spacing;

		return spacing_from_point_source(pnt_src4, _p);
	}
}