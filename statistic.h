#ifndef STATISTIC_H
#define STATISTIC_H

#include <OpenMesh/Core/Geometry/MathDefs.hh>

#include <math.h>
#include <string>
#include <fstream>
#include <iomanip>

template<class Mesh>
class StatisticT
{
public:
    typedef typename Mesh::Scalar            Scalar;
    typedef typename Mesh::Point             Point;
    typedef typename Mesh::Normal            Normal;
    typedef typename Mesh::VertexHandle      VertexHandle;
	typedef typename Mesh::HalfedgeHandle    HalfedgeHandle;
    typedef typename Mesh::EdgeHandle        EdgeHandle;
	typedef typename Mesh::FaceHandle        FaceHandle;

	// constructor & destructor
    StatisticT(Mesh& _mesh);
    ~StatisticT();

public:
	void calc_edge_length_info();
	Scalar min_edge_length() const { return min_edge_length_; }
	EdgeHandle min_length_edge_handle() const { return min_length_edge_handle_; }
	Scalar max_edge_length() const { return max_edge_length_; }
	EdgeHandle max_length_edge_handle() const { return max_length_edge_handle_; }
	Scalar ave_edge_length() const { return ave_edge_length_; }

	void calc_face_area_info();
	// Scalar face_area(FaceHandle _fh) const;
	Scalar min_face_area() const { return min_face_area_; }
	FaceHandle min_area_face_handle() const { return min_area_face_handle_; }
	Scalar max_face_area() const { return max_face_area_; }
	FaceHandle max_area_face_handle() const { return max_area_face_handle_; }
	Scalar ave_face_area() const { return ave_face_area; }

	void calc_halfedge_angle_info();
	//Vec3f  face_angles(FaceHandle _fh) const;
	Scalar min_halfedge_angle() const { return min_halfedge_angle_; }
	HalfedgeHandle min_angle_halfedge_handle() const { return min_angle_halfedge_handle_; }
	Scalar max_halfedge_angle() const { return max_halfedge_angle_; }
	HalfedgeHandle max_angle_halfedge_handle() const { return max_angle_halfedge_handle_; }

	Scalar calc_face_aspect_ratio(FaceHandle _fh) const;
	void calc_face_aspect_ratio_info();
	Scalar min_face_aspect_ratio() const { return min_face_aspect_ratio_; }
	FaceHandle min_aspect_ratio_face_handle() const { return min_aspect_ratio_face_handle_; }
	Scalar max_face_aspect_ratio() const { return max_face_aspect_ratio_; }
	FaceHandle max_aspect_ratio_face_handle() const { return max_aspect_ratio_face_handle_; }
	Scalar ave_face_aspect_ratio() const { return ave_face_aspect_ratio_; }

	void calc_statistic();
	void output_statistic(std::string _fn);

private: 
	Mesh& mesh_;

	// Should these statistical values be stored for efficiency consideration ? yes !
	Scalar min_edge_length_, max_edge_length_, ave_edge_length_;
	EdgeHandle min_length_edge_handle_, max_length_edge_handle_;

	Scalar min_face_area_, max_face_area_, ave_face_area_;
	FaceHandle min_area_face_handle_, max_area_face_handle_;

	Scalar min_halfedge_angle_, max_halfedge_angle_;
	HalfedgeHandle min_angle_halfedge_handle_, max_angle_halfedge_handle_;

	Scalar min_face_aspect_ratio_, max_face_aspect_ratio_, ave_face_aspect_ratio_;
	FaceHandle min_aspect_ratio_face_handle_, max_aspect_ratio_face_handle_;
};

template<class Mesh>
StatisticT<Mesh>::StatisticT(Mesh& _mesh) : mesh_(_mesh)
{
	min_edge_length_ = 0.0;
	min_length_edge_handle_.reset();
	max_edge_length_ = 0.0;
	max_length_edge_handle_.reset();
	ave_edge_length_ = 0.0;

	min_face_area_ = 0.0;
	min_area_face_handle_.reset();
	max_face_area_ = 0.0;
	max_area_face_handle_.reset();
	ave_face_area_ = 0.0;

	min_halfedge_angle_ = 0.0;
	min_angle_halfedge_handle_.reset();
	max_halfedge_angle_ = 0.0;
	max_angle_halfedge_handle_.reset();

	min_face_aspect_ratio_ = 0.0;
	min_aspect_ratio_face_handle_.reset();
	max_face_aspect_ratio_ = 0.0;
	max_aspect_ratio_face_handle_.reset();
	ave_face_aspect_ratio_ = 0.0;
}

template<class Mesh>
StatisticT<Mesh>::~StatisticT()
{
}

template<class Mesh>
void StatisticT<Mesh>::calc_edge_length_info()
{
	typename Mesh::ConstEdgeIter e_it(mesh_.edges_begin()),
	                             e_end(mesh_.edges_end());

	Scalar edge_length = 0.0, edge_length_sum = 0.0;
	min_edge_length_ = 2.0e30; // ok ?
	max_edge_length_ = 0.0;
	ave_edge_length_ = 0.0;

	for (; e_it != e_end; ++e_it)
	{
		edge_length = mesh_.calc_edge_length(e_it.handle());
		edge_length_sum += edge_length;
		if (edge_length < min_edge_length_)
		{
			min_edge_length_ = edge_length;
			min_length_edge_handle_ = e_it.handle();
		}
		if (edge_length > max_edge_length_)
		{
			max_edge_length_ = edge_length;
			max_length_edge_handle_ = e_it.handle();
		}
	}
	ave_edge_length_ = edge_length_sum / (Scalar)mesh_.n_edges();

	return;
}

template<class Mesh>
void StatisticT<Mesh>::calc_face_area_info()
{
	typename Mesh::ConstFaceIter cf_it(mesh_.faces_begin()),
		                         cf_end(mesh_.faces_end());
	HalfedgeHandle heh;

	Scalar face_area = 0.0, face_area_sum = 0.0;
	min_face_area_ = 2.0e30;
	max_face_area_ = 0.0;
	ave_face_area_ = 0.0;

	for (; cf_it != cf_end; ++cf_it)
	{
		heh = mesh_.halfedge_handle(cf_it.handle());
		face_area = mesh_.calc_sector_area(heh);
		face_area_sum += face_area;

		if (face_area < min_face_area_)
		{
			min_face_area_ = face_area;
			min_area_face_handle_ = cf_it.handle();
		}
		if (face_area > max_face_area_)
		{
			max_face_area_ = face_area;
			max_area_face_handle_ = cf_it.handle();
		}
	}

	ave_face_area_ = face_area_sum / (Scalar)mesh_.n_faces();
}

template<class Mesh>
void StatisticT<Mesh>::calc_halfedge_angle_info()
{
	typename Mesh::ConstFaceIter cf_it(mesh_.faces_begin()),
		                         cf_end(mesh_.faces_end());
	typename Mesh::ConstFaceHalfedgeIter cfh_it;

	Scalar angle = 0.0;
	min_halfedge_angle_ = 2.0e30;
	max_halfedge_angle_ = 0.0;

	for (; cf_it != cf_end; ++cf_it)
	{
		for (cfh_it = mesh_.cfh_iter(cf_it.handle()); cfh_it; ++cfh_it)
		{
			angle = mesh_.calc_sector_angle(cfh_it.handle());
			if (angle < min_halfedge_angle_)
			{
				min_halfedge_angle_ = angle;
				min_angle_halfedge_handle_ = cfh_it.handle();
			}
			if (angle > max_halfedge_angle_)
			{
				max_halfedge_angle_ = angle;
				max_angle_halfedge_handle_ = cfh_it.handle();
			}
		}
	}
}

template<class Mesh>
typename Mesh::Scalar
StatisticT<Mesh>::calc_face_aspect_ratio(FaceHandle _fh) const
{
	typename Mesh::ConstFaceEdgeIter cfe_it = mesh_.cfe_iter(_fh);
	int i;
	Scalar len[3], hp, ll, area, ar;
	const Scalar sqrt3 = 1.73205080757;

	for (i = 0, cfe_it = mesh_.cfe_iter(_fh); i < 3; ++i, ++cfe_it)
		len[i] = mesh_.calc_edge_length(cfe_it.handle());
	
	hp = (len[0] + len[1] + len[2]) / 2.0;
	ll = len[1] > len[0] ? len[1] : len[0];
	ll = ll > len[2] ? ll : len[2];
	
	area = sqrt(hp * (hp - len[0]) * (hp - len[1]) * (hp - len[2]));
	ar = (2 * sqrt3 * area) / (hp * ll);
	if (ar > 1.0)
		ar = 1.0;
	else if (ar < 0.0)
		ar = 0.0;

	return ar;
}

template<class Mesh>
void StatisticT<Mesh>::calc_face_aspect_ratio_info()
{
	typename Mesh::ConstFaceIter cf_it(mesh_.faces_begin()),
		                         cf_end(mesh_.faces_end());

	Scalar face_aspect_ratio = 0.0, face_aspect_ratio_sum = 0.0;
	min_face_aspect_ratio_ = 2.0e30;
	max_face_aspect_ratio_ = 0.0;
	ave_face_aspect_ratio_ = 0.0;

	for (; cf_it != cf_end; ++cf_it)
	{
		face_aspect_ratio = calc_face_aspect_ratio(cf_it.handle());
		face_aspect_ratio_sum += face_aspect_ratio;

		if (face_aspect_ratio < min_face_aspect_ratio_)
		{
			min_face_aspect_ratio_ = face_aspect_ratio;
			min_aspect_ratio_face_handle_ = cf_it.handle();
		}
		if (face_aspect_ratio > max_face_aspect_ratio_)
		{
			max_face_aspect_ratio_ = face_aspect_ratio;
			max_aspect_ratio_face_handle_ = cf_it.handle();
		}
	}

	 ave_face_aspect_ratio_ = face_aspect_ratio_sum / (Scalar)mesh_.n_faces();
}

template<class Mesh>
void StatisticT<Mesh>::calc_statistic()
{
	calc_edge_length_info();
	calc_face_area_info();
	calc_halfedge_angle_info();
	calc_face_aspect_ratio_info();
}

template<class Mesh>
void StatisticT<Mesh>::output_statistic(std::string _fn)
{
	ofstream sta_file(_fn.c_str());
	sta_file << "minimal edge length and its index: " << setw(15) << min_edge_length_ << "  " 
		<< setw(10) << min_length_edge_handle_.idx() << endl;
	sta_file << "maximum edge length and its index: " << setw(15) << max_edge_length_ << "  " 
		<< setw(10) << max_length_edge_handle_.idx() << endl;
	sta_file << "average edge length: " << setw(15) << ave_edge_length_ << endl;

	sta_file << endl;

	sta_file << "minimal face area and its index: " << setw(15) << min_face_area_ << "  " 
		<< setw(10) << min_area_face_handle_.idx() << endl;
	sta_file << "maximum edge length and its index: " << setw(15) << max_face_area_ << "  " 
		<< setw(10) << max_area_face_handle_.idx() << endl;
	sta_file << "average face area: " << setw(15) << ave_face_area_ << endl;

	sta_file << endl;

	sta_file << "minimal halfedge angle and its index: " << setw(15) << min_halfedge_angle_ << "  " 
		<< setw(10) << min_angle_halfedge_handle_.idx() << endl;
	sta_file << "maximum halfedge angle and its index: " << setw(15) << max_halfedge_angle_ << "  " 
		<< setw(10) << max_angle_halfedge_handle_.idx() << endl;
	
	sta_file << endl;

	sta_file << "minimal face aspect ratio and its index: " << setw(15) << min_face_aspect_ratio_ << "  " 
		<< setw(10) << min_aspect_ratio_face_handle_.idx() << endl;
	sta_file << "maximum face aspect ratio and its index: " << setw(15) << max_face_aspect_ratio_ << "  " 
		<< setw(10) << max_aspect_ratio_face_handle_.idx() << endl;
	sta_file << "average face aspect ratio: " << setw(15) << ave_face_aspect_ratio_ << endl;

	sta_file.close();
}

#endif 