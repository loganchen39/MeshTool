#ifndef MESHVIEWERWIDGET_H
#define MESHVIEWERWIDGET_H

#include <OpenMesh/Core/IO/Options.hh>
#include <OpenMesh/Core/Utils/Property.hh>

#include "glwidgetcenter.h"  // including global.h

using namespace OpenMesh;
     
class MeshViewerWidget : public GLWidgetCenter
{
	Q_OBJECT

public:
	// default constructor
	MeshViewerWidget(QWidget* _parent = 0, const char* _name = 0, MyMesh* _mesh = 0)
		    : GLWidgetCenter(_parent, _name),
			mesh_(_mesh),
			is_mesh_valid_(false)
	{
		init();
	}

	~MeshViewerWidget()
	{
	}

public:
  // open mesh, should be put in the mainwindow class
  // here only reference the mesh data
  MyMesh* mesh() { return mesh_; }
  const MyMesh* mesh() const { return mesh_; }

  // following functions actually operate on mesh_ data
  // they are actually should not be here, this class only reference the data
  void compute_bbox();

public slots:
	void on_mesh_loaded(void);

	void setObjectShowItems(bitset<OSI_NumObjectShowItems>);

	void setFeatureViewItems(bitset<FV_NumFeatureViewItems>);

protected: 
    // inherited drawing method
	virtual void draw_scene(void);  
  
private:
	void init();

	// for object show
	void draw_objects();
	void draw_vertices();
	void draw_vertex_normals();
	void draw_vertex_indices();
	void draw_edges();
	void draw_hidden_line();
	void draw_edge_indices();
	void draw_faces();
	void draw_face_normals();
	void draw_face_indices();
	//EditLitDir
	//Inertia

	// for feature view
	void draw_boundary_vertices();
	void draw_boundary_vertex_indices();
	void draw_boundary_vertex_normals();
	void draw_corner_vertices();
	void draw_corner_vertex_indices();
	void draw_corner_vertex_normals();
	void draw_ridge_vertices();
	void draw_ridge_vertex_indices();
	void draw_ridge_vertex_normals();
	void draw_flat_vertices();
	void draw_flat_vertex_indices();
	void draw_flat_vertex_normals();
	void draw_boundary_edges();
	void draw_ridge_edges();
	void draw_flat_edges();
	void draw_boundary_edge_indices();
	void draw_ridge_edge_indices();
	void draw_flat_edge_indices();


  void glVertex( const MyMesh::VertexHandle _vh )
  { glVertex3fv( &mesh_->point( _vh )[0] ); }

  void glVertex( const MyMesh::Point& _p )
  { glVertex3fv( &_p[0] ); }
  
  void glNormal( const MyMesh::VertexHandle _vh )
  { glNormal3fv( &mesh_->normal( _vh )[0] ); }

  /**
  void glTexCoord( const MyMesh::VertexHandle _vh )
  { glTexCoord2fv( &mesh_->texcoord(_vh)[0] ); }
  
  void glColor( const MyMesh::VertexHandle _vh )
  { glColor3ubv( &mesh_->color(_vh)[0] ); }
  */
  
  // face properties
  void glNormal( const MyMesh::FaceHandle _fh )
  { glNormal3fv( &mesh_->normal( _fh )[0] ); }

  /**
  void glColor( const MyMesh::FaceHandle _fh )
  { glColor3ubv( &mesh_->color(_fh)[0] ); }

  void glMaterial( const MyMesh::FaceHandle _fh, 
		   int _f=GL_FRONT_AND_BACK, int _m=GL_DIFFUSE )
  { 
    Vec3f c = color_cast<Vec3f>(mesh_->color(_fh));
    Vec4f m( c[0], c[1], c[2], 1.0f );

    glMaterialfv(_f, _m, &m[0]); 
  }
  */

protected:
  OpenMesh::IO::Options  opt_; // mesh file contained texcoords?
  
  MyMesh*                        mesh_; 
  bool                           is_mesh_valid_;
  float                          normal_scale_;
  //FPropHandleT< MyMesh::Point >  fp_normal_base_;
  bitset<FV_NumFeatureViewItems> featureViewFlags;

  // for object show
  GLfloat                        vertices_color_[4];
  GLfloat                        vertices_size_;
  GLfloat                        edges_color_[4];
  GLfloat                        edges_width_;
  GLfloat                        faces_color_[4];

  GLfloat                        vertex_indices_color_[4];
  GLfloat                        edge_indices_color_[4];
  GLfloat                        face_indices_color_[4];

  GLfloat                        vertex_normals_color_[4];
  GLfloat                        face_normals_color_[4];

  // for feature view
  GLfloat                        boundary_vertices_color_[4];
  GLfloat                        boundary_vertices_size_;
  GLfloat                        boundary_vertex_indices_color_[4];
  GLfloat                        boundary_vertex_normals_color_[4];

  GLfloat                        corner_vertices_color_[4];
  GLfloat                        corner_vertices_size_;
  GLfloat                        corner_vertex_indices_color_[4];
  GLfloat                        corner_vertex_normals_color_[4];

  GLfloat                        ridge_vertices_color_[4];
  GLfloat                        ridge_vertices_size_;
  GLfloat                        ridge_vertex_indices_color_[4];
  GLfloat                        ridge_vertex_normals_color_[4];

  GLfloat                        flat_vertices_color_[4];
  GLfloat                        flat_vertices_size_;
  GLfloat                        flat_vertex_indices_color_[4];
  GLfloat                        flat_vertex_normals_color_[4];

  GLfloat                        boundary_edges_color_[4];
  GLfloat                        boundary_edges_width_;
  GLfloat                        ridge_edges_color_[4];
  GLfloat                        ridge_edges_width_;
  GLfloat                        flat_edges_color_[4];
  GLfloat                        flat_edges_width_;

  GLfloat                        boundary_edge_indices_color_[4];
  GLfloat                        ridge_edge_indices_color_[4];
  GLfloat                        flat_edge_indices_color_[4];
};

#endif