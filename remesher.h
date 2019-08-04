#ifndef REMESHER_H
#define REMESHER_H

#include "userdensity.h"
#include "global.h"
//#include "statistic.h"

#include <map>

template<class Mesh>
class RemesherT
{
public:
    typedef typename Mesh::Scalar            Scalar;
    typedef typename Mesh::Point             Point;
    typedef typename Mesh::Normal            Normal;
    typedef typename Mesh::VertexHandle      VertexHandle;
	typedef typename Mesh::HalfedgeHandle    HalfedgeHandle;
    typedef typename Mesh::EdgeHandle        EdgeHandle;
	typedef typename Mesh::FaceHandle        FaceHandle;

	// enum/struct definition
	/**
	typedef struct EdgeInfo
	{
		EdgeHandle    eh_;
		Scalar        value_;
	} EdgeInfo;
	*/

	// constructor & destructor
    RemesherT(Mesh& _mesh, UserDensity& _user_density);
    ~RemesherT();

public:
	void remesh();

	void coarsen();
	void refine();
	void optimize(); // by edge swapping
	void eliminate_sliver(); // by edge collapse

	void set_flip_type(FlipType _flip_type) { flip_type_ = _flip_type; }

private:
	Scalar calc_face_aspect_ratio(FaceHandle _fh) const;
	bool is_collapse_legal(HalfedgeHandle _heh) const;
	void collapse(EdgeHandle _eh);

	// Edge split (= 2-to-4 split)
    void split(EdgeHandle _eh, VertexHandle _vh);

	bool is_flip_legal(EdgeHandle _eh) const;
	float calc_edge_swap_ratio(EdgeHandle _eh) const;

	Scalar calc_edge_length_ratio(EdgeHandle _eh) const;
	Scalar calc_node_length_ratio(VertexHandle _vh) const;

	EdgeHandle find_adjacent_boundary_edge(HalfedgeHandle _heh) const; // with the same start node
	EdgeHandle find_adjacent_ridge_edge(HalfedgeHandle _heh) const;

private:
	Mesh& mesh_;
	UserDensity& user_density_;
	FlipType flip_type_;

	const double sqrt2; // or global ?
};

template<class Mesh>
RemesherT<Mesh>::RemesherT(Mesh& _mesh, UserDensity& _user_density) 
		: mesh_(_mesh), user_density_(_user_density), sqrt2(1.41421356)
{
}

template<class Mesh>
RemesherT<Mesh>::~RemesherT()
{
}

template<class Mesh>
typename Mesh::Scalar
RemesherT<Mesh>::calc_edge_length_ratio(EdgeHandle _eh) const
{
	HalfedgeHandle heh0, heh1;
	VertexHandle   vh0, vh1;
	Vec3f p0(0.0, 0.0, 0.0), p1(0.0, 0.0, 0.0);
	Scalar actual_edge_length = 0.0, ideal_edge_length = 0.0;

	heh0   = mesh_.halfedge_handle(_eh, 0);
	heh1   = mesh_.halfedge_handle(_eh, 1);
    vh0    = mesh_.to_vertex_handle(heh0);
	vh1    = mesh_.to_vertex_handle(heh1);

	p0 = mesh_.point(vh0);
	p1 = mesh_.point(vh1);

	actual_edge_length = mesh_.calc_edge_length(_eh);
	ideal_edge_length  = (user_density_.get_user_density(p0) + user_density_.get_user_density(p1)) / 2.0;

	return actual_edge_length / ideal_edge_length;
}

template<class Mesh>
typename Mesh::Scalar
RemesherT<Mesh>::calc_node_length_ratio(VertexHandle _vh) const
{
	Scalar sum_edge_length = 0.0, ave_edge_length = 0.0, ideal_edge_length = 0.0;

	typename Mesh::ConstVertexEdgeIter cve_it = mesh_.cve_iter(_vh);
	for (; cve_it; ++ cve_it)
		sum_edge_length += mesh_.calc_edge_length(cve_it.handle());
	ave_edge_length = sum_edge_length / mesh_.valence(_vh);
	ideal_edge_length = user_density_.get_user_density( vector_cast<Vec3f>(mesh_.point(_vh)) );

	return ave_edge_length / ideal_edge_length; 
}

// would be invalid if topological transformations are used! so not to use it.
template<class Mesh>
typename Mesh::EdgeHandle
RemesherT<Mesh>::find_adjacent_boundary_edge(HalfedgeHandle _heh) const
{
	assert(mesh_.is_boundary(_heh));

	typename Mesh::ConstVertexEdgeIter cve_it = mesh_.cve_iter(mesh_.from_vertex_handle(_heh));
	for (; cve_it; ++cve_it)
		if (cve_it.handle() != mesh_.edge_handle(_heh) && mesh_.is_boundary(cve_it.handle()))
			return cve_it.handle();

	assert(false); // for debugging
	return EdgeHandle();
}

// would be invalid if topological transformations are used! so not to use it.
template<class Mesh>
typename Mesh::EdgeHandle
RemesherT<Mesh>::find_adjacent_ridge_edge(HalfedgeHandle _heh) const
{
	assert( ET_Ridge == mesh_.property(edge_type, mesh_.edge_handle(_heh)) );

	typename Mesh::ConstVertexEdgeIter cve_it = mesh_.cve_iter(mesh_.from_vertex_handle(_heh));
	for (; cve_it; ++cve_it)
	{
		if ( cve_it.handle() != mesh_.edge_handle(_heh) && ET_Ridge == mesh_.property(edge_type, cve_it.handle()) )
			return cve_it.handle();
	}

	assert(false); // for debugging
	return EdgeHandle();
}

template<class Mesh>
typename Mesh::Scalar
RemesherT<Mesh>::calc_face_aspect_ratio(FaceHandle _fh) const
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
bool RemesherT<Mesh>::is_collapse_legal(HalfedgeHandle v0v1) const
{
  HalfedgeHandle  v1v0(mesh_.opposite_halfedge_handle(v0v1));
  VertexHandle    v0(mesh_.to_vertex_handle(v1v0));
  VertexHandle    v1(mesh_.to_vertex_handle(v0v1));

  // are vertices already deleted ?
  if (mesh_.status(v0).deleted() || mesh_.status(v1).deleted())
    return false;


  VertexHandle    vl, vr;
  HalfedgeHandle  h1, h2;


  // the edges v1-vl and vl-v0 must not be both boundary edges
  if (!mesh_.is_boundary(v0v1))
  {
    vl = mesh_.to_vertex_handle(mesh_.next_halfedge_handle(v0v1));

    h1 = mesh_.next_halfedge_handle(v0v1);
    h2 = mesh_.next_halfedge_handle(h1);
    if (mesh_.is_boundary(mesh_.opposite_halfedge_handle(h1)) && 
        mesh_.is_boundary(mesh_.opposite_halfedge_handle(h2)))
    {
      return false;
    }
  }


  // the edges v0-vr and vr-v1 must not be both boundary edges
  if (!mesh_.is_boundary(v1v0))
  {
    vr = mesh_.to_vertex_handle(mesh_.next_halfedge_handle(v1v0));

    h1 = mesh_.next_halfedge_handle(v1v0);
    h2 = mesh_.next_halfedge_handle(h1);
    if (mesh_.is_boundary(mesh_.opposite_halfedge_handle(h1)) &&
        mesh_.is_boundary(mesh_.opposite_halfedge_handle(h2)))
      return false;
  }


  // if vl and vr are equal or both invalid -> fail
  if (vl == vr) return false;


  typename Mesh::VertexVertexIter  vv_it;


  // test intersection of the one-rings of v0 and v1
  for (vv_it = mesh_.vv_iter(v0); vv_it; ++vv_it)
    mesh_.status(vv_it).set_tagged(false);

  for (vv_it = mesh_.vv_iter(v1); vv_it; ++vv_it)
    mesh_.status(vv_it).set_tagged(true);

  for (vv_it = mesh_.vv_iter(v0); vv_it; ++vv_it)
    if (mesh_.status(vv_it).tagged() && vv_it.handle() != vl && vv_it.handle() != vr)
      return false;


  // overlapping test if an edge collapsed
  typename Mesh::VertexFaceIter vf_it = mesh_.vf_iter(v0);
  typename Mesh::ConstFaceVertexIter fv_it;
  FaceHandle fh0 = mesh_.face_handle(v0v1);
  FaceHandle fh1 = mesh_.face_handle(v1v0);
  Normal n0, n1;
  Point p0, p1, p2;
  Scalar denom, cos_a;
  for (; vf_it; ++vf_it)
  {
    if (vf_it.handle() == fh0 || vf_it.handle() == fh1)
		continue;

	n0 = mesh_.calc_face_normal(vf_it.handle());

	fv_it = mesh_.cfv_iter(vf_it.handle());
	if (fv_it.handle() == v0)
		p0 = mesh_.point(v1);
	else
		p0 = mesh_.point(fv_it.handle());
	++fv_it;

    if (fv_it.handle() == v0)
		p1 = mesh_.point(v1);
	else
		p1 = mesh_.point(fv_it.handle());
    ++fv_it;

    if (fv_it.handle() == v0)
		p2 = mesh_.point(v1);
	else
		p2 = mesh_.point(fv_it.handle());

	n1 = mesh_.calc_face_normal(p0, p1, p2);

	denom = n0.norm() * n1.norm();
    if (is_zero(denom))  
      return false;

	cos_a = (n0 | n1) / denom;
	if (cos_a <= 0.0) // face normals in [90d, 180d]
		return false;
  }


  // edge between two boundary vertices should be a boundary edge
  if ( mesh_.is_boundary(v0) && mesh_.is_boundary(v1) &&
       !mesh_.is_boundary(v0v1) && !mesh_.is_boundary(v1v0))
    return false;

  // passed all tests
  return true;
}

template<class Mesh>
void RemesherT<Mesh>::collapse(EdgeHandle _eh)
{
	if (mesh_.status(_eh).deleted())
		return;

	HalfedgeHandle                   heh0 = mesh_.halfedge_handle(_eh, 0), heh1 = mesh_.halfedge_handle(_eh, 1);
	VertexHandle                     vh0 = mesh_.to_vertex_handle(heh0), vh1 = mesh_.to_vertex_handle(heh1);
	typename Mesh::VertexFaceIter    vf_it;
	typename Mesh::VertexVertexIter  vv_it;

	if (mesh_.face_handle(heh0).is_valid() && mesh_.status(mesh_.face_handle(heh0)).deleted())
		return;
	if (mesh_.face_handle(heh1).is_valid() && mesh_.status(mesh_.face_handle(heh1)).deleted())
		return;

	// boundary edge and ridge edge are much alike
	if (ET_Boundary == mesh_.property(edge_type, _eh) || ET_Ridge == mesh_.property(edge_type, _eh))
	{
		if (mesh_.property(node_type, vh0).is_corner() && mesh_.property(node_type, vh1).is_corner())
		{
			// return; // originally

			if (is_collapse_legal(heh1))
			{
				mesh_.collapse(heh1);
							
				vf_it = mesh_.vf_iter(vh1);
				for (; vf_it; ++vf_it)
					if (!mesh_.status(vf_it).deleted())
						mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
				vv_it = mesh_.vv_iter(vh1);
				for (; vv_it; ++vv_it)
					if (!mesh_.status(vv_it).deleted())
						mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));							
			}
			else if (is_collapse_legal(heh0))
			{
				mesh_.collapse(heh0);
							
				vf_it = mesh_.vf_iter(vh0);
				for (; vf_it; ++vf_it)
					if (!mesh_.status(vf_it).deleted())
						mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
				vv_it = mesh_.vv_iter(vh0);
				for (; vv_it; ++vv_it)
					if (!mesh_.status(vv_it).deleted())
						mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));						
			}

			else // actually shouldn't have this code segment
			{
				mesh_.collapse(heh1);
							
				vf_it = mesh_.vf_iter(vh1);
				for (; vf_it; ++vf_it)
					if (!mesh_.status(vf_it).deleted())
						mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
				vv_it = mesh_.vv_iter(vh1);
				for (; vv_it; ++vv_it)
					if (!mesh_.status(vv_it).deleted())
						mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));
			}
		}
		else if (mesh_.property(node_type, vh0).is_corner()) // vh1->vh0
		{				
			// if (is_collapse_legal(heh0)) // mesh_.is_collapse_ok(heh0)
			// {
				mesh_.collapse(heh0);
							
				// update adjacent face/vertex normals
				vf_it = mesh_.vf_iter(vh0);
				for (; vf_it; ++vf_it)
					if (!mesh_.status(vf_it).deleted())
						mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
				vv_it = mesh_.vv_iter(vh0);
				for (; vv_it; ++vv_it)
					if (!mesh_.status(vv_it).deleted())
						mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));
			// }

		}
		else if (mesh_.property(node_type, vh1).is_corner()) // vh0->vh1
		{
			// if (is_collapse_legal(heh1)) // mesh_.is_collapse_ok(heh1)
			// {
				mesh_.collapse(heh1);
							
				vf_it = mesh_.vf_iter(vh1);
				for (; vf_it; ++vf_it)
					if (!mesh_.status(vf_it).deleted())
						mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
				vv_it = mesh_.vv_iter(vh1);
					for (; vv_it; ++vv_it)
						if (!mesh_.status(vv_it).deleted())
							mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));
			// }

		}
		else // no corner node
		{
			if (is_collapse_legal(heh1))
			{
				mesh_.collapse(heh1);
							
				vf_it = mesh_.vf_iter(vh1);
				for (; vf_it; ++vf_it)
					if (!mesh_.status(vf_it).deleted())
						mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
				vv_it = mesh_.vv_iter(vh1);
				for (; vv_it; ++vv_it)
					if (!mesh_.status(vv_it).deleted())
						mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));							
			}
			else if (is_collapse_legal(heh0))
			{
				mesh_.collapse(heh0);
							
				vf_it = mesh_.vf_iter(vh0);
				for (; vf_it; ++vf_it)
					if (!mesh_.status(vf_it).deleted())
						mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
				vv_it = mesh_.vv_iter(vh0);
				for (; vv_it; ++vv_it)
					if (!mesh_.status(vv_it).deleted())
						mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));						
			}

			else // shouldn't have this code segment
			{
				mesh_.collapse(heh1);
							
				vf_it = mesh_.vf_iter(vh1);
				for (; vf_it; ++vf_it)
					if (!mesh_.status(vf_it).deleted())
						mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
				vv_it = mesh_.vv_iter(vh1);
				for (; vv_it; ++vv_it)
					if (!mesh_.status(vv_it).deleted())
						mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));
			}
		}
	}
	else // ET_Flat
	{
		// if ( !mesh_.property(node_type, vh0).is_flat() && !mesh_.property(node_type, vh1).is_flat()) // shouldn't happen
			// return;
		if ( mesh_.property(node_type, vh0).is_flat() && mesh_.property(node_type, vh1).is_flat() ) // else
		{
			if (is_collapse_legal(heh1))
			{
				mesh_.collapse(heh1);
							
				vf_it = mesh_.vf_iter(vh1);
				for (; vf_it; ++vf_it)
					if (!mesh_.status(vf_it).deleted())
						mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
				vv_it = mesh_.vv_iter(vh1);
				for (; vv_it; ++vv_it)
					if (!mesh_.status(vv_it).deleted())
						mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));							
			}
			else if (is_collapse_legal(heh0))
			{
				mesh_.collapse(heh0);
					
				vf_it = mesh_.vf_iter(vh0);
				for (; vf_it; ++vf_it)
					if (!mesh_.status(vf_it).deleted())
						mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
				vv_it = mesh_.vv_iter(vh0);
				for (; vv_it; ++vv_it)
					if (!mesh_.status(vv_it).deleted())
						mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));
			}

			else // shouldn't have this code segment
			{
				mesh_.collapse(heh1);
							
				vf_it = mesh_.vf_iter(vh1);
				for (; vf_it; ++vf_it)
					if (!mesh_.status(vf_it).deleted())
						mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
				vv_it = mesh_.vv_iter(vh1);
				for (; vv_it; ++vv_it)
					if (!mesh_.status(vv_it).deleted())
						mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));
			}
		}
		else if ( mesh_.property(node_type, vh0).is_flat() )
		{
			// if (is_collapse_legal(heh1))
			// {
				mesh_.collapse(heh1);
						
				vf_it = mesh_.vf_iter(vh1);
				for (; vf_it; ++vf_it)
					if (!mesh_.status(vf_it).deleted())
						mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
				vv_it = mesh_.vv_iter(vh1);
				for (; vv_it; ++vv_it)
					if (!mesh_.status(vv_it).deleted())
						mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));
			// }						
		}
		else // vh1 is flat
		{
			// if (is_collapse_legal(heh0))
			// {
				mesh_.collapse(heh0);
							
				vf_it = mesh_.vf_iter(vh0);
				for (; vf_it; ++vf_it)
					if (!mesh_.status(vf_it).deleted())
						mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
				vv_it = mesh_.vv_iter(vh0);
				for (; vv_it; ++vv_it)
					if (!mesh_.status(vv_it).deleted())
						mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));
			// }
		}
	} // end of "else // ET_Flat"
			
}

template<class Mesh>
void RemesherT<Mesh>::split(EdgeHandle _eh, VertexHandle _vh)
{
  EdgeType et = mesh_.property(edge_type, _eh);

  HalfedgeHandle h0 = mesh_.halfedge_handle(_eh, 0);
  HalfedgeHandle o0 = mesh_.halfedge_handle(_eh, 1);

  VertexHandle   v2 = mesh_.to_vertex_handle(o0);

  HalfedgeHandle e1 = mesh_.new_edge(_vh, v2);
  HalfedgeHandle t1 = mesh_.opposite_halfedge_handle(e1);
  if (ET_Boundary == et)
  {
	  mesh_.property(edge_type, mesh_.edge_handle(e1)) = ET_Boundary;
	  mesh_.property(edge_type, mesh_.edge_handle(h0)) = ET_Boundary;
	  mesh_.property(node_type, _vh).set_boundary(true);
	  
  }
  else if (ET_Ridge == et)
  {
	  mesh_.property(edge_type, mesh_.edge_handle(e1)) = ET_Ridge;
	  mesh_.property(edge_type, mesh_.edge_handle(h0)) = ET_Ridge;
	  mesh_.property(node_type, _vh).set_ridge(true);
  }
  else if (ET_Flat == et)
  {
	  mesh_.property(edge_type, mesh_.edge_handle(e1)) = ET_Flat;
	  mesh_.property(edge_type, mesh_.edge_handle(h0)) = ET_Flat;
	  mesh_.property(node_type, _vh).set_flat(true);
  }

  FaceHandle     f0 = mesh_.face_handle(h0);
  FaceHandle     f3 = mesh_.face_handle(o0);

  mesh_.set_halfedge_handle(_vh, h0);
  mesh_.set_vertex_handle(o0, _vh);

  if (!mesh_.is_boundary(h0))
  {
    HalfedgeHandle h1 = mesh_.next_halfedge_handle(h0);
    HalfedgeHandle h2 = mesh_.next_halfedge_handle(h1);

    VertexHandle v1 = mesh_.to_vertex_handle(h1);

    HalfedgeHandle e0 = mesh_.new_edge(_vh, v1);
    HalfedgeHandle t0 = mesh_.opposite_halfedge_handle(e0);
	mesh_.property(edge_type, mesh_.edge_handle(e0)) = ET_Flat;

    FaceHandle f1 = mesh_.new_face();
    mesh_.set_halfedge_handle(f0, h0);
    mesh_.set_halfedge_handle(f1, h2);

    mesh_.set_face_handle(h1, f0);
    mesh_.set_face_handle(t0, f0);
    mesh_.set_face_handle(h0, f0);

    mesh_.set_face_handle(h2, f1);
    mesh_.set_face_handle(t1, f1);
    mesh_.set_face_handle(e0, f1);

    mesh_.set_next_halfedge_handle(h0, h1);
    mesh_.set_next_halfedge_handle(h1, t0);
    mesh_.set_next_halfedge_handle(t0, h0);

    mesh_.set_next_halfedge_handle(e0, h2);
    mesh_.set_next_halfedge_handle(h2, t1);
    mesh_.set_next_halfedge_handle(t1, e0);
  }
  else
  {
    mesh_.set_next_halfedge_handle(mesh_.prev_halfedge_handle(h0), t1);
    mesh_.set_next_halfedge_handle(t1, h0);
    // halfedge handle of _vh already is h0
  }

  if (!mesh_.is_boundary(o0))
  {
    HalfedgeHandle o1 = mesh_.next_halfedge_handle(o0);
    HalfedgeHandle o2 = mesh_.next_halfedge_handle(o1);

    VertexHandle v3 = mesh_.to_vertex_handle(o1);

    HalfedgeHandle e2 = mesh_.new_edge(_vh, v3);
    HalfedgeHandle t2 = mesh_.opposite_halfedge_handle(e2);
	mesh_.property(edge_type, mesh_.edge_handle(e2)) = ET_Flat;

    FaceHandle f2 = mesh_.new_face();
    mesh_.set_halfedge_handle(f2, o1);
    mesh_.set_halfedge_handle(f3, o0);

    mesh_.set_face_handle(o1, f2);
    mesh_.set_face_handle(t2, f2);
    mesh_.set_face_handle(e1, f2);

    mesh_.set_face_handle(o2, f3);
    mesh_.set_face_handle(o0, f3);
    mesh_.set_face_handle(e2, f3);

    mesh_.set_next_halfedge_handle(e1, o1);
    mesh_.set_next_halfedge_handle(o1, t2);
    mesh_.set_next_halfedge_handle(t2, e1);

    mesh_.set_next_halfedge_handle(o0, e2);
    mesh_.set_next_halfedge_handle(e2, o2);
    mesh_.set_next_halfedge_handle(o2, o0);
  }
  else
  {
    mesh_.set_next_halfedge_handle(e1, mesh_.next_halfedge_handle(o0));
    mesh_.set_next_halfedge_handle(o0, e1);
    mesh_.set_halfedge_handle(_vh, e1);
  }

  if (mesh_.halfedge_handle(v2) == h0)
    mesh_.set_halfedge_handle(v2, t1);
}

template<class Mesh>
bool RemesherT<Mesh>::is_flip_legal(EdgeHandle _eh) const
{
  // boundary edges cannot be flipped
  if (mesh_.is_boundary(_eh)) return false;

  HalfedgeHandle hh = mesh_.halfedge_handle(_eh, 0);
  HalfedgeHandle oh = mesh_.halfedge_handle(_eh, 1);

  // check if the flipped edge is already present
  // in the mesh
  VertexHandle ah = mesh_.to_vertex_handle(mesh_.next_halfedge_handle(hh));
  VertexHandle bh = mesh_.to_vertex_handle(mesh_.next_halfedge_handle(oh));
  if (ah == bh)   // this is generally a bad sign !!!
    return false;

  typename Mesh::ConstVertexVertexIter vvi = mesh_.cvv_iter(ah);
  for (; vvi; ++vvi) // ConstVertexVertexIter vvi(*this, ah)
    if (vvi.handle() == bh)
      return false;

  //ridge edges cannot be flipped
  if (ET_Ridge == mesh_.property(edge_type, _eh))
	  return false;

  // check if it is curved
  FaceHandle afh = mesh_.face_handle(hh);
  FaceHandle bfh = mesh_.face_handle(oh);
  Normal afn = mesh_.normal(afh);
  Normal bfn = mesh_.normal(bfh);

  Scalar denom, cos_a, angle;
  denom = afn.norm() * bfn.norm();
  if (is_zero(denom))  
      return false;

  cos_a = (afn | bfn) / denom;
  if (cos_a < 0.99)
	  return false;

  // check if it would be overlapped, and whether the mesh quality will be improved 
  // maybe later aspect ratio etc. as mesh quality criteria will be used
  Scalar ang_1, ang_2, ang_3, ang_4;
  ang_1 = mesh_.calc_sector_angle(mesh_.prev_halfedge_handle(hh));
  ang_2 = mesh_.calc_sector_angle(hh);
  ang_3 = mesh_.calc_sector_angle(mesh_.prev_halfedge_handle(oh));
  ang_4 = mesh_.calc_sector_angle(oh);

  // the last two inequalities also include the concave quadrilateral case, which guarantees
  // to avoid the formation of invalid elements
  if (FT_TopoTrans == flip_type_)
  {
      if (ang_1 >= M_PI / 2.0 || ang_2 >= M_PI / 2.0 || ang_3 >= M_PI / 2.0 || ang_4 >= M_PI / 2.0
	          || ang_1+ang_4 >= 3.0*M_PI/4.0 || ang_2+ang_3 >= 3.0*M_PI/4.0)
	      return false;
  }
  else // FT_Smoothing
  {
	if (ang_1 + ang_4 >= 5.0*M_PI/6.0 || ang_2 + ang_3 >= 5.0*M_PI/6.0)
		return false;
	
	if (!mesh_.property(node_type, ah).is_flat() || !mesh_.property(node_type, bh).is_flat())
		return false;

	VertexHandle aah, bbh;
	aah = mesh_.to_vertex_handle(hh);
	bbh = mesh_.to_vertex_handle(oh);
	int valence_1, valence_2, valence_3, valence_4;
	valence_1 = mesh_.valence(bbh);
	valence_2 = mesh_.valence(bh);
	valence_3 = mesh_.valence(ah);
	valence_4 = mesh_.valence(aah);	
	
	if (valence_1 < 6 || valence_4 < 6 || valence_1 + valence_4 <= valence_2 + valence_3 + 2)
		return false;
  }	

  // passes all tests, the edge flip should be constrained outside by other conditions, like valence
  // or element quality, here it is too relaxed
  return true;
}

template<class Mesh>
float RemesherT<Mesh>::calc_edge_swap_ratio(EdgeHandle _eh) const
{
	assert(ET_Boundary != mesh_.property(edge_type, _eh) && ET_Ridge != mesh_.property(edge_type, _eh));

	float distd = (float)mesh_.calc_edge_length(_eh);
	if (distd == 0.0)
	{
		cerr << "error: zero length edge found" << endl;
		return 2.0;
	}

	HalfedgeHandle hh = mesh_.halfedge_handle(_eh, 0);
	HalfedgeHandle oh = mesh_.halfedge_handle(_eh, 1);
	VertexHandle vh0 = mesh_.to_vertex_handle(mesh_.next_halfedge_handle(hh));
	VertexHandle vh1 = mesh_.to_vertex_handle(mesh_.next_halfedge_handle(oh));
	
	float distu = (float)(mesh_.point(vh0) - mesh_.point(vh1)).length();

	return distu / distd;
}

template<class Mesh>
void RemesherT<Mesh>::coarsen()
{
	typename Mesh::EdgeIter          e_it; // e_end, add/delete operations, iterators may become invalid or wrong
	HalfedgeHandle                   heh0, heh1;
	VertexHandle                     vh0, vh1;
	EdgeHandle                       eh0, eh1;
	typename Mesh::VertexFaceIter    vf_it;
	typename Mesh::VertexVertexIter  vv_it; 
	Scalar node_ratio_0 = 0.0, node_ratio_1 = 0.0;

	Point p(0.0, 0.0, 0.0);
	Scalar edge_length_ratio = 0.0;
	bool go_on;

	do
	{
		go_on = false;

		for (e_it = mesh_.edges_begin(); e_it != mesh_.edges_end(); ++e_it) // if use e_end, then assertion failed
		{
			if (mesh_.status(e_it.handle()).deleted())
				continue;

			heh0   = mesh_.halfedge_handle(e_it.handle(), 0);
			heh1   = mesh_.halfedge_handle(e_it.handle(), 1);
			vh0    = mesh_.to_vertex_handle(heh0);
			vh1    = mesh_.to_vertex_handle(heh1);

			if (mesh_.face_handle(heh0).is_valid() && mesh_.status(mesh_.face_handle(heh0)).deleted())
				continue;
			if (mesh_.face_handle(heh1).is_valid() && mesh_.status(mesh_.face_handle(heh1)).deleted())
				continue;

			edge_length_ratio = calc_edge_length_ratio(e_it.handle());

			if (edge_length_ratio < sqrt2 / 2.0) // original sqrt2 / 2.0, derefine by edge collapsing
			{
				// these codes should be packaged into one independent function, whick could be reused easily

				// boundary edge and ridge edge are much alike
				if (ET_Boundary == mesh_.property(edge_type, e_it) || ET_Ridge == mesh_.property(edge_type, e_it))
				{
					if (mesh_.property(node_type, vh0).is_corner() && mesh_.property(node_type, vh1).is_corner())
						continue;
					else if (mesh_.property(node_type, vh0).is_corner()) // vh1->vh0
					{				
						if (is_collapse_legal(heh0)) // mesh_.is_collapse_ok(heh0)
						{
							mesh_.collapse(heh0);

							
							// update adjacent face/vertex normals
							vf_it = mesh_.vf_iter(vh0);
							for (; vf_it; ++vf_it)
								if (!mesh_.status(vf_it).deleted())
									mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
							vv_it = mesh_.vv_iter(vh0);
							for (; vv_it; ++vv_it)
								if (!mesh_.status(vv_it).deleted())
									mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));
							

							if (!go_on)
								go_on = true;
						}

					}
					else if (mesh_.property(node_type, vh1).is_corner()) // vh0->vh1
					{
						if (is_collapse_legal(heh1)) // mesh_.is_collapse_ok(heh1)
						{
							mesh_.collapse(heh1);

							
							vf_it = mesh_.vf_iter(vh1);
							for (; vf_it; ++vf_it)
								if (!mesh_.status(vf_it).deleted())
									mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
							vv_it = mesh_.vv_iter(vh1);
							for (; vv_it; ++vv_it)
								if (!mesh_.status(vv_it).deleted())
									mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));
							

							if (!go_on)
								go_on = true;
						}

					}
					else // no corner node
					{
						if (is_collapse_legal(heh1))
						{
							mesh_.collapse(heh1);
							
							vf_it = mesh_.vf_iter(vh1);
							for (; vf_it; ++vf_it)
								if (!mesh_.status(vf_it).deleted())
									mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
							vv_it = mesh_.vv_iter(vh1);
							for (; vv_it; ++vv_it)
								if (!mesh_.status(vv_it).deleted())
									mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));
							

							if (!go_on)
								go_on = true;
						}
						else if (is_collapse_legal(heh0))
						{
							mesh_.collapse(heh0);

							
							vf_it = mesh_.vf_iter(vh0);
							for (; vf_it; ++vf_it)
								if (!mesh_.status(vf_it).deleted())
									mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
							vv_it = mesh_.vv_iter(vh0);
							for (; vv_it; ++vv_it)
								if (!mesh_.status(vv_it).deleted())
									mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));
							

							if (!go_on)
								go_on = true;
						}
					}
				}
				else // ET_Flat
				{
					if ( !mesh_.property(node_type, vh0).is_flat() && !mesh_.property(node_type, vh1).is_flat())
						continue;
					else if ( mesh_.property(node_type, vh0).is_flat() && mesh_.property(node_type, vh1).is_flat() )
					{
						if (is_collapse_legal(heh1))
						{
							mesh_.collapse(heh1);

							
							vf_it = mesh_.vf_iter(vh1);
							for (; vf_it; ++vf_it)
								if (!mesh_.status(vf_it).deleted())
									mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
							vv_it = mesh_.vv_iter(vh1);
							for (; vv_it; ++vv_it)
								if (!mesh_.status(vv_it).deleted())
									mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));
							

							if (!go_on)
								go_on = true;
						}
						else if (is_collapse_legal(heh0))
						{
							mesh_.collapse(heh0);

						
							vf_it = mesh_.vf_iter(vh0);
							for (; vf_it; ++vf_it)
								if (!mesh_.status(vf_it).deleted())
									mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
							vv_it = mesh_.vv_iter(vh0);
							for (; vv_it; ++vv_it)
								if (!mesh_.status(vv_it).deleted())
									mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));
							

							if (!go_on)
								go_on = true;
						}
					}
					else if ( mesh_.property(node_type, vh0).is_flat() )
					{
						if (is_collapse_legal(heh1))
						{
							mesh_.collapse(heh1);

						
							vf_it = mesh_.vf_iter(vh1);
							for (; vf_it; ++vf_it)
								if (!mesh_.status(vf_it).deleted())
									mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
							vv_it = mesh_.vv_iter(vh1);
							for (; vv_it; ++vv_it)
								if (!mesh_.status(vv_it).deleted())
									mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));
							

							if (!go_on)
								go_on = true;
						}						
					}
					else // vh1 is flat
					{
						if (is_collapse_legal(heh0))
						{
							mesh_.collapse(heh0);

							
							vf_it = mesh_.vf_iter(vh0);
							for (; vf_it; ++vf_it)
								if (!mesh_.status(vf_it).deleted())
									mesh_.set_normal(vf_it, mesh_.calc_face_normal(vf_it.handle()));
							vv_it = mesh_.vv_iter(vh0);
							for (; vv_it; ++vv_it)
								if (!mesh_.status(vv_it).deleted())
									mesh_.set_normal(vv_it, mesh_.calc_vertex_normal(vv_it.handle()));
							

							if (!go_on)
								go_on = true;
						}
					}
				} // end of "else // ET_Flat"

				//mesh_.garbage_collection(); // put it below ? then assertion failed, invalid halfedge handle, here would make e_it invalid

			} // end of derefinement, end of "if (edge_length_ratio < sqrt2 / 2.0) // derefine by edge collapsing"

		} // end of for loop 

		mesh_.garbage_collection(); // ok ? here or above, or even below ? better than above
		mesh_.update_face_normals();
		mesh_.update_vertex_normals(); // should be put here for checking is_collapse_ok(HalfedgeHandle _heh)

	}while (go_on);
}

template<class Mesh>
void RemesherT<Mesh>::refine()
{
	typename Mesh::EdgeIter e_it; // e_end, add/delete operations, iterators may become invalid or wrong
	unsigned int e_idx, e_num;
	HalfedgeHandle heh0, heh1;
	VertexHandle   vh0, vh1;
	EdgeHandle     eh, eh0, eh1;
	Scalar node_ratio_0 = 0.0, node_ratio_1 = 0.0;

	Point p(0.0, 0.0, 0.0);
	Scalar edge_length_ratio = 0.0;
	bool go_on;

	do
	{
		go_on = false;
		e_num = mesh_.n_edges();

		for (e_idx = 0; e_idx < e_num; e_idx++)
		{
			eh = mesh_.edge_handle(e_idx);

			if (mesh_.status(eh).deleted())
				continue;

			edge_length_ratio = calc_edge_length_ratio(eh);

			if (edge_length_ratio > sqrt2) // originally sqrt2, refine by edge/vertex splitting
			{
				heh0   = mesh_.halfedge_handle(eh, 0);
				heh1   = mesh_.halfedge_handle(eh, 1);
				vh0    = mesh_.to_vertex_handle(heh0);
				vh1    = mesh_.to_vertex_handle(heh1);

				p = (mesh_.point(vh0) + mesh_.point(vh1)) / 2.0; // todo: to use interpolating curve
				//mesh_.split(e_it.handle(), p);
				split(eh, mesh_.add_vertex(p));

				if (!go_on)
					go_on = true;
			}
		}

	} while (go_on);

	mesh_.garbage_collection();
	mesh_.update_face_normals();
	mesh_.update_vertex_normals();
}

template<class Mesh>
void RemesherT<Mesh>::optimize()
{
	typename Mesh::EdgeIter e_it;
	float edge_swap_ratio;
	EdgeHandle eh;
	HalfedgeHandle hh, oh;
	EdgeHandle eh1, eh2, eh3, eh4;
	FaceHandle fh0, fh1;
	const int max_iter_num = 20;
	int i;
	bool go_on = true;

	for (i = 0; i < max_iter_num && go_on; i++) 
	{
		go_on = false;

		for (e_it = mesh_.edges_begin(); e_it != mesh_.edges_end(); ++e_it)
		{
			if (ET_Boundary == mesh_.property(edge_type, e_it.handle()) 
					|| ET_Ridge == mesh_.property(edge_type, e_it.handle()))
				continue;

			edge_swap_ratio = calc_edge_swap_ratio(e_it.handle());
			if (FT_TopoTrans == flip_type_)
			{
				if (edge_swap_ratio >= 1.0)
					continue;
			}
			else // FT_Smoothing
			{
				if (edge_swap_ratio >= 1.5)
					continue;
			}

			eh = e_it.handle();
			if (is_flip_legal(eh))
			{
				hh = mesh_.halfedge_handle(eh, 0);
				oh = mesh_.halfedge_handle(eh, 1);
				eh1 = mesh_.edge_handle(mesh_.prev_halfedge_handle(hh));
				eh2 = mesh_.edge_handle(mesh_.next_halfedge_handle(hh));
				eh3 = mesh_.edge_handle(mesh_.prev_halfedge_handle(oh));
				eh4 = mesh_.edge_handle(mesh_.next_halfedge_handle(oh));

				// flip
				mesh_.flip(eh);
				fh0 = mesh_.face_handle(mesh_.halfedge_handle(eh, 0));
				fh1 = mesh_.face_handle(mesh_.halfedge_handle(eh, 1));
				mesh_.set_normal(fh0, mesh_.calc_face_normal(fh0));
				mesh_.set_normal(fh1, mesh_.calc_face_normal(fh1));

				if (!go_on)
					go_on = true;

			} // end of "if (is_flip_legal(eh))"
		}
	}

	mesh_.garbage_collection();
	mesh_.update_face_normals();
	mesh_.update_vertex_normals();

	/** original code
	std::multimap<float, EdgeHandle> edge_info;

	// compute the edge information
	typename Mesh::EdgeIter e_it;
	float edge_swap_ratio;

	for (e_it = mesh_.edges_begin(); e_it != mesh_.edges_end(); ++e_it)
	{
		if (ET_Boundary == mesh_.property(edge_type, e_it.handle()) || ET_Ridge == mesh_.property(edge_type, e_it.handle()))
			continue;

		edge_swap_ratio = calc_edge_swap_ratio(e_it.handle());
		edge_info.insert(std::make_pair(edge_swap_ratio, e_it.handle()));
	}

	std::multimap<float, EdgeHandle>::iterator iter, temp_iter;
	EdgeHandle eh;
	HalfedgeHandle hh, oh;
	EdgeHandle eh1, eh2, eh3, eh4;
	FaceHandle fh0, fh1;
	const int max_iter_num = 20;
	int i;
	bool go_on = true;

	for (i = 0; i < max_iter_num && go_on; i++) 
	{
		go_on = false;

		for (iter = edge_info.begin(); iter != edge_info.end();) // ++iter
		{
			if (FT_TopoTrans == flip_type_)
			{
				if (iter->first >= 1.0)
					break;
			}
			else // FT_Smoothing
			{
				if (iter->first >= 1.5)
					break;
			}

			eh = iter->second;
			if (is_flip_legal(eh))
			{
				hh = mesh_.halfedge_handle(eh, 0);
				oh = mesh_.halfedge_handle(eh, 1);
				eh1 = mesh_.edge_handle(mesh_.prev_halfedge_handle(hh));
				eh2 = mesh_.edge_handle(mesh_.next_halfedge_handle(hh));
				eh3 = mesh_.edge_handle(mesh_.prev_halfedge_handle(oh));
				eh4 = mesh_.edge_handle(mesh_.next_halfedge_handle(oh));

				// flip
				mesh_.flip(eh);
				fh0 = mesh_.face_handle(mesh_.halfedge_handle(eh, 0));
				fh1 = mesh_.face_handle(mesh_.halfedge_handle(eh, 1));
				mesh_.set_normal(fh0, mesh_.calc_face_normal(fh0));
				mesh_.set_normal(fh1, mesh_.calc_face_normal(fh1));

				
				// update, need erase and insert, will the iterator still be valid ?
				// first update adjacent edge's information
				for (temp_iter = edge_info.begin(); temp_iter != edge_info.end();) // ++temp_iter
				{
					if (temp_iter->second == eh1)
					{
						edge_swap_ratio = calc_edge_swap_ratio(eh1);
						edge_info.erase(temp_iter++);
						edge_info.insert(std::make_pair(edge_swap_ratio, eh1));
					}
					else if (temp_iter->second == eh2)
					{
						edge_swap_ratio = calc_edge_swap_ratio(eh2);
						edge_info.erase(temp_iter++);
						edge_info.insert(std::make_pair(edge_swap_ratio, eh2));
					}
					else if (temp_iter->second == eh3)
					{
						edge_swap_ratio = calc_edge_swap_ratio(eh3);
						edge_info.erase(temp_iter++);
						edge_info.insert(std::make_pair(edge_swap_ratio, eh3));
					}
					else if (temp_iter->second == eh4)
					{
						edge_swap_ratio = calc_edge_swap_ratio(eh4);
						edge_info.erase(temp_iter++);
						edge_info.insert(std::make_pair(edge_swap_ratio, eh4));
					}
					else
						temp_iter++;
				}
				// second update flipped edge's information
				edge_swap_ratio = calc_edge_swap_ratio(eh);
				edge_info.erase(iter++);
				edge_info.insert(std::make_pair(edge_swap_ratio, eh));

				if (!go_on)
					go_on = true;

			} // end of "if (is_flip_legal(eh))"
		
			else
				iter++;

		} // end of the main loop, "for (iter = edge_info.begin(); iter != edge_info.end();) // ++iter"

	};

	mesh_.update_face_normals();
	mesh_.update_vertex_normals();
	*/

}

template<class Mesh>
void RemesherT<Mesh>::eliminate_sliver()
{
	typename Mesh::EdgeIter e_it;
	Scalar face_aspect_ratio = 0.0, min_edge_length = 0.0, edge_length = 0.0, face_area = 0.0;
	int i;
	const int max_iter = 10;
	bool go_on = true;

	/**
	for (i = 0; i < max_iter && go_on; ++i)
	{
		go_on = false;

		for (e_it = mesh_.edges_begin(); e_it != mesh_.edges_end(); ++e_it)
		{
			if (mesh_.status(e_it.handle()).deleted())
				continue;

			edge_length = mesh_.calc_edge_length(e_it.handle());
			if (edge_length < 1.0e-8)
			{
				collapse(e_it.handle());
				if (!go_on)
					go_on = true;
			}
		}
	}
	mesh_.garbage_collection();
	mesh_.update_face_normals();
	mesh_.update_vertex_normals();
	*/


	typename Mesh::FaceIter f_it;
	typename Mesh::FaceEdgeIter fe_it;
	EdgeHandle min_length_edge_handle;
	HalfedgeHandle heh;

	/**
	go_on = true;
	for (i = 0; i < max_iter && go_on; ++i)
	{
		go_on = false;

		for (f_it = mesh_.faces_begin(); f_it != mesh_.faces_end(); ++f_it)
		{
			if (mesh_.status(f_it.handle()).deleted())
				continue;

			heh = mesh_.halfedge_handle(f_it.handle());
			face_area = mesh_.calc_sector_area(heh);
			if (face_area < 1.0e-8)
			{
				collapse(mesh_.edge_handle(heh)); // handle very simply, need to enhance
				if (!go_on)
					go_on = true;
			}
		}
	}
	mesh_.garbage_collection();
	mesh_.update_face_normals();
	mesh_.update_vertex_normals();
	*/

	go_on = true;
	for (i = 0; i < max_iter && go_on; ++i)
	{
		go_on = false;

		for (f_it = mesh_.faces_begin(); f_it != mesh_.faces_end(); ++f_it)
		{
			if (mesh_.status(f_it.handle()).deleted())
				continue;

			face_aspect_ratio = calc_face_aspect_ratio(f_it.handle());
			if (face_aspect_ratio < 0.001) // sliver, collapse the shortest edge
			{	
				min_edge_length = 2.0e30;
				for (fe_it = mesh_.fe_iter(f_it.handle()), i = 0; fe_it && i < 3; ++fe_it, ++i)
				{
					edge_length = mesh_.calc_edge_length(fe_it.handle());
					if (edge_length < min_edge_length)
					{
						min_edge_length = edge_length;
						min_length_edge_handle = fe_it.handle();
					}
				}

				collapse(min_length_edge_handle);

				if (!go_on)
					go_on = true;
			}
		}
	}
	mesh_.garbage_collection();
	mesh_.update_face_normals();
	mesh_.update_vertex_normals();
}

// first do coarsen, then refine
template<class Mesh>
void RemesherT<Mesh>::remesh()
{
	coarsen();
	optimize();
	refine();
	optimize();
}

#endif