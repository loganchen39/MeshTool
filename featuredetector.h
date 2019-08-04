#ifndef FEATUREDETECTOR_H
#define FEATUREDETECTOR_H

#include <OpenMesh/Core/Geometry/MathDefs.hh>

// Base class for feature detection algorithms
template<class Mesh>
class FeatureDetectorT
{
public:
    typedef typename Mesh::Scalar            Scalar;
    typedef typename Mesh::Point             Point;
    typedef typename Mesh::Normal            Normal;
    typedef typename Mesh::VertexHandle      VertexHandle;
	typedef typename Mesh::HalfedgeHandle    HalfedgeHandle;
    typedef typename Mesh::EdgeHandle        EdgeHandle;

	//enum

	// constructor & destructor
    FeatureDetectorT(Mesh& _mesh);
    virtual ~FeatureDetectorT();

public:
	virtual void detect_feature() const { } // is const ok ?

	virtual void classify_nodes() const { }
	virtual void classify_edges() const { }

protected:
	// return the smaller angle between [0.0, pi]
	Scalar calc_cutting_angle(VertexHandle vh, HalfedgeHandle heh0, HalfedgeHandle heh1) const;

protected:
	Mesh& mesh_;
};

// Basic feature detection algorithm
template<class Mesh>
class BasicFeatureDetectorT : public FeatureDetectorT<Mesh>
{
private: 
	typedef FeatureDetectorT<Mesh>    Base;

public:
	typedef typename FeatureDetectorT<Mesh>::Scalar            Scalar;
    typedef typename FeatureDetectorT<Mesh>::Point             Point;
    typedef typename FeatureDetectorT<Mesh>::Normal            Normal;
    typedef typename FeatureDetectorT<Mesh>::VertexHandle      VertexHandle;
	typedef typename FeatureDetectorT<Mesh>::HalfedgeHandle    HalfedgeHandle;
    typedef typename FeatureDetectorT<Mesh>::EdgeHandle        EdgeHandle;

	// constructor & destructor
	BasicFeatureDetectorT(Mesh& _mesh, Scalar _ridge_edge_angle_thresh = OpenMesh::deg_to_rad(45.0), 
			Scalar _corner_node_promotion_angle_thresh = OpenMesh::deg_to_rad(120.0));
	~BasicFeatureDetectorT();

public:
	void detect_feature() const; // is const ok ?

	void classify_edges() const;
	void classify_vertices() const;

	Scalar ridge_edge_angle_thresh() const 
	{ return ridge_edge_angle_thresh_; }

	void set_ridge_edge_angle_thresh( Scalar _ridge_edge_angle_thresh) 
	{ ridge_edge_angle_thresh_ = _ridge_edge_angle_thresh; }

	Scalar corner_node_promotion_angle_thresh() const 
	{ return corner_node_promotion_angle_thresh_; }

	void set_corner_node_promotion_angle_thresh( Scalar _corner_node_promotion_angle_thresh) 
	{ corner_node_promotion_angle_thresh_ = _corner_node_promotion_angle_thresh; }

private:
	// Algorithmic parameters
	Scalar    ridge_edge_angle_thresh_;
	Scalar    corner_node_promotion_angle_thresh_;
};


template<class Mesh>
FeatureDetectorT<Mesh>::FeatureDetectorT(Mesh& _mesh)
		: mesh_(_mesh)
{
}

template<class Mesh>
FeatureDetectorT<Mesh>::~FeatureDetectorT()
{
}

template<class Mesh>
typename Mesh::Scalar
FeatureDetectorT<Mesh>::calc_cutting_angle(VertexHandle vh, HalfedgeHandle heh0, HalfedgeHandle heh1) const
{
	Normal v0, v1;
	mesh_.calc_edge_vector(heh0, v0);
	mesh_.calc_edge_vector(heh1, v1);

	Scalar denom, cos_a, angle;
	denom = v0.norm() * v1.norm();
    if (is_zero(denom))  
      return 0;

	cos_a = (v0 | v1) / denom;

	angle = acos(sane_aarg(cos_a));

	return angle;
}


template<class Mesh>
BasicFeatureDetectorT<Mesh>::BasicFeatureDetectorT(Mesh &_mesh, Scalar _ridge_edge_angle_thresh, 
		Scalar _corner_node_promotion_angle_thresh)
	: FeatureDetectorT<Mesh>(_mesh), 
	  ridge_edge_angle_thresh_(_ridge_edge_angle_thresh),
	  corner_node_promotion_angle_thresh_(_corner_node_promotion_angle_thresh)
{
}

template<class Mesh>
BasicFeatureDetectorT<Mesh>::~BasicFeatureDetectorT()
{
}

template<class Mesh>
void BasicFeatureDetectorT<Mesh>::detect_feature() const
{
	classify_edges();
	classify_vertices();
}

template<class Mesh>
void BasicFeatureDetectorT<Mesh>::classify_edges() const
{
	typename Mesh::ConstEdgeIter e_it(mesh_.edges_begin()),
	                             e_end(mesh_.edges_end());

	for (; e_it != e_end; ++e_it)
	{
		// didn't use find_feature_edges(...)
		if (mesh_.is_boundary(e_it)) 
			mesh_.property(edge_type, e_it) = ET_Boundary;
		else if (fabs(mesh_.calc_dihedral_angle(e_it)) > ridge_edge_angle_thresh_) 
			mesh_.property(edge_type, e_it) = ET_Ridge;
		else
			mesh_.property(edge_type, e_it) = ET_Flat;
	}
}

template<class Mesh>
void BasicFeatureDetectorT<Mesh>::classify_vertices() const
{
	typename Mesh::ConstVertexIter  v_it(mesh_.vertices_begin()),
								    v_end(mesh_.vertices_end());

	typename Mesh::ConstVertexOHalfedgeIter cvoh_it;

	HalfedgeHandle  first_ridge_outgoing_halfedge_handle, 
		            second_ridge_outgoing_halfedge_handle;
	HalfedgeHandle  first_boundary_outgoing_halfedge_handle, 
		            second_boundary_outgoing_halfedge_handle;
	HalfedgeHandle  in_heh;

	int adj_ridge_outgoing_halfedges, adj_boundary_outgoing_halfedges;
	Scalar angle;
	Scalar corner_node_angle;

	for (; v_it != v_end; ++v_it)
	{
		// first compute the number of adjacent ridge edges
		adj_ridge_outgoing_halfedges = 0;
		adj_boundary_outgoing_halfedges = 0;
		corner_node_angle = 0.0;
		for (cvoh_it = mesh_.cvoh_iter(v_it.handle()); cvoh_it; ++cvoh_it) 
		{
			if ( ET_Ridge == mesh_.property(edge_type, mesh_.edge_handle(cvoh_it.handle())) )  
			{
				adj_ridge_outgoing_halfedges++;
				if (1 == adj_ridge_outgoing_halfedges)
					first_ridge_outgoing_halfedge_handle = cvoh_it.handle();
				else if (2 == adj_ridge_outgoing_halfedges)
					second_ridge_outgoing_halfedge_handle = cvoh_it.handle();
			}
			else if ( ET_Boundary == mesh_.property(edge_type, mesh_.edge_handle(cvoh_it.handle())) ) 
			{
				// mush be boundary node, record the two adjacent boundary edges
				adj_boundary_outgoing_halfedges++;
				if (1 == adj_boundary_outgoing_halfedges)
					first_boundary_outgoing_halfedge_handle = cvoh_it.handle();
				else if (2 == adj_boundary_outgoing_halfedges)
					second_boundary_outgoing_halfedge_handle = cvoh_it.handle();
			}
            
			in_heh = mesh_.opposite_halfedge_handle(cvoh_it.handle());
            corner_node_angle += mesh_.calc_sector_angle(in_heh);
		}

		// then set the node type
		if (mesh_.is_boundary(v_it)) 
		{
			mesh_.property(node_type, v_it).set_boundary(true);

			// check if it is corner node, first compute the angle formed by two adjacent boundary edges
			angle = Base::calc_cutting_angle(v_it.handle(), first_boundary_outgoing_halfedge_handle, 
						second_boundary_outgoing_halfedge_handle);
			if (adj_ridge_outgoing_halfedges > 0 || angle < corner_node_promotion_angle_thresh_)
				mesh_.property(node_type, v_it).set_corner(true);
		}
		else if (0 == adj_ridge_outgoing_halfedges)
			mesh_.property(node_type, v_it).set_flat(true);
		else if (2 != adj_ridge_outgoing_halfedges)
			mesh_.property(node_type, v_it).set_corner(true);
		else
		{
			mesh_.property(node_type, v_it).set_ridge(true);

			angle = Base::calc_cutting_angle(v_it.handle(), first_ridge_outgoing_halfedge_handle, 
						second_ridge_outgoing_halfedge_handle);
			if (angle < corner_node_promotion_angle_thresh_) // || angle > 2*M_PI - corner_node_promotion_angle_thresh_
				mesh_.property(node_type, v_it).set_corner(true);
		}

		// identify a special corner node case by the algorithm presented in 
		// "Surface remeshing by local hermite diffuse interpolation", added on 20080720
        if (!mesh_.is_boundary(v_it))
			if (corner_node_angle < 3.1415926 / 1.0)
				mesh_.property(node_type, v_it).set_corner(true);
	}
}

#endif