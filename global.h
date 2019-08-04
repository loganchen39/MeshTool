#ifndef GLOBAL_H
#define GLOBAL_H

#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/Attributes.hh>
#include <OpenMesh/Core/Geometry/VectorT.hh>

#include <bitset>

//#include "featuredetector.h"
#include "userdensity.h"

using namespace std;
using namespace OpenMesh;

struct MyTraits : public OpenMesh::DefaultTraits
{
  VertexAttributes  ( OpenMesh::Attributes::Normal       |
	                  OpenMesh::Attributes::Status       );
  EdgeAttributes    ( OpenMesh::Attributes::Status       );
  HalfedgeAttributes( OpenMesh::Attributes::PrevHalfedge );
  FaceAttributes    ( OpenMesh::Attributes::Normal       |
	                  OpenMesh::Attributes::Status       );
};

typedef OpenMesh::TriMesh_ArrayKernelT<MyTraits> MyMesh;

extern MyMesh       mesh;
extern UserDensity  user_density;

extern int smooth_time;

// Forward declaration
enum  EdgeType;
class NodeTypeInfo;

extern EPropHandleT<EdgeType>         edge_type;
extern VPropHandleT<NodeTypeInfo>     node_type;
//extern MPropHandleT<StatisticT<MyMesh> > statistic;


// global functions or algorithms, they actually should take the "Mesh" as 
// some kind of template parameters, and the algorithms themselves should 
// be packaged as template classes, just like SmootherT<Mesh>


class BBox
{
public:
	Vec3f min() const { return min_; } 
	Vec3f max() const { return max_; }
	void set_min(Vec3f _min) { min_ = _min; }
	void set_max(Vec3f _max) { max_ = _max; }

	Vec3f center() { return (min_ + max_) * 0.5; }
	float diagonal() { return (min_ - max_).norm(); }

private:
	Vec3f min_;
	Vec3f max_;
};

// MeshViewer flags, used to transfer the signals between ControlPanel and MeshViewerWidget
enum ObjectShowItem
{
	OSI_Vertex = 0  ,
	OSI_VNorm       ,
	OSI_VIdx        ,
	OSI_Edge        ,
	OSI_HiddenLine  ,
	OSI_EIdx        ,
	OSI_Face        ,
	OSI_FNorm       ,
	OSI_FIdx        ,
	OSI_Light       ,
	OSI_LightDir    ,
	OSI_EditLitDir  ,
	OSI_ShadeSmooth ,
	OSI_ColorMaterial,
	OSI_Perspective ,
	OSI_Inertia     ,
	OSI_Coords      ,
	OSI_BBox        ,
	OSI_NumObjectShowItems
};


// Feature edge and node, for feature detection
// Mutually exclusive 
enum EdgeType {
	ET_Boundary = 1,
	ET_Ridge,
	ET_Flat
};

// Not mutually exclusive
enum NodeType {
	NT_Boundary = 1,
	NT_Ridge    = 2,
	NT_Corner   = 4,
	NT_Flat     = 8
};

class NodeTypeInfo
{
public:

	typedef unsigned int value_type;

	NodeTypeInfo() : node_type_(0) {}

	// is boundary ?
	bool is_boundary() const { return is_bit_set(NT_Boundary); }
	// set boundary
	void set_boundary(bool _b) { change_bit(NT_Boundary, _b); }

	// is ridge ?
	bool is_ridge() const { return is_bit_set(NT_Ridge); }
	// set ridge
	void set_ridge(bool _b) { change_bit(NT_Ridge, _b); }

	// is corner ?
	bool is_corner() const { return is_bit_set(NT_Corner); }
	// set corner
	void set_corner(bool _b) { change_bit(NT_Corner, _b); }

	// is flat ?
	bool is_flat() const { return is_bit_set(NT_Flat); }
	// set flat
	void set_flat(bool _b) { change_bit(NT_Flat, _b); }

private:
	
	/// is a certain bit set ?
    bool is_bit_set(unsigned int _s) const { return (node_type_ & _s) > 0; }
    /// set a certain bit
    void set_bit(unsigned int _s) { node_type_ |= _s; }
    /// unset a certain bit
    void unset_bit(unsigned int _s) { node_type_ &= ~_s; }
    /// set or unset a certain bit
    void change_bit(unsigned int _s, bool _b) {  if (_b) node_type_ |= _s; else node_type_ &= ~_s; }

	value_type node_type_;
};

// Feature View flags, used to transfer the signals between ControlPanel and MeshViewerWidget
enum FeatureViewItem
{
	FV_BouNd = 0  ,
	FV_BNdIdx     ,
	FV_BNdNorm    ,
	FV_CornerNd   ,
	FV_CNdIdx     ,
	FV_CNdNorm    ,
	FV_RidgeNd    ,
	FV_RNdIdx     ,
	FV_RNdNorm    ,
	FV_FlatNd     ,
	FV_FNdIdx     ,
	FV_FNdNorm    ,
	FV_BouEd      ,
	FV_RidgeEd    ,
	FV_FlatEd     ,
	FV_BEdIdx     ,
	FV_REdIdx     ,
	FV_FEdIdx     ,
	//FV_Properties ,
	FV_NumFeatureViewItems
};

// for edge flip
enum FlipType
{
	FT_TopoTrans = 0,
	FT_Smoothing
};

#endif 
