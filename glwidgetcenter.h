/**
* class GLWidgetCenter header file
* @author LigangChen
* @version 0.1 2007/02/04
*/


#ifndef GLWIDGETCENTER_H
#define GLWIDGETCENTER_H

#include <QGLWidget>
#include <QPoint>

#include <OpenMesh/Core/Geometry/VectorT.hh>

#include "global.h"

using namespace Qt;
using namespace OpenMesh; // can not find Vec3f without this directive

class GLWidgetCenter : public QGLWidget
{
    Q_OBJECT

public:
    // Default constructor.
    GLWidgetCenter(QWidget* _parent = NULL, const char* _name = NULL);
    GLWidgetCenter(QGLFormat& _fmt, QWidget* _parent = NULL, const char* _name = NULL);

    ~GLWidgetCenter();

protected:
	void init(void);
	void init_light(void);
	void init_material(void);

public:
  /* Sets the center and size of the whole scene. 
     The _center is used as fixpoint for rotations and for adjusting
     the camera/viewer. */
  void set_scene_pos( const Vec3f& _center, float _radius );  

  const Vec3f& center() const { return center_; }
  float radius() const { return radius_; }
  
  const GLdouble* modelview_matrix() const  { return modelview_matrix_;  }
  const GLdouble* projection_matrix() const { return projection_matrix_; }

  float fovy() const { return 45.0f; }


public slots:
	void setViewport(QString);

	void updateView();

signals:
	void outputMessage(QString);


protected:
  // draw the scene: will be called by the painGL() method.
  virtual void draw_scene();

protected: // inherited
  // initialize OpenGL states (triggered by Qt)
  void initializeGL();

  // draw the scene (triggered by Qt)
  void paintGL();

  // handle resize events (triggered by Qt)
  void resizeGL(int, int);

protected:
	// Qt mouse events
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);

protected: // originally private
  // updates projection matrix
  void update_projection_matrix();

  // calculate matrices for building scene
  void init_modelview_matrices();

  // draw coordinate system
  void draw_coords_sys();

  void draw_bbox();

  void draw_light_dir();

  // virtual trackball: map 2D screen point to unit sphere, temporarily use OpenMesh's method
  bool map_to_sphere(const QPoint& _point, Vec3f& _result);

  QPoint           last_point_2D_;
  Vec3f            last_point_3D_;
  bool             last_point_ok_;
  
private:
	GLuint      coords_display_list_; //gen_coords_list();
	GLuint      gen_coords_display_list();

protected:
	Vec3f       center_;  // can't be accessed by MeshViewerWidget if use private 
    float       radius_;
	BBox        bbox_;

	bitset<OSI_NumObjectShowItems>  objectShowFlags;

	GLfloat     bbox_color_[4];
	
	GLfloat     backgroud_color_[4];

	GLfloat     light0_ambient_[4];
	GLfloat     light0_diffuse_[4];
	GLfloat     light0_specular_[4];
	GLfloat     light0_position_[4];

	GLfloat     material_ambient_[4];
	GLfloat     material_diffuse_[4];
	GLfloat     material_specular_[4];
	GLfloat     material_shine_;
	      
    GLdouble    projection_matrix_[16],
		        
		        lookat_matrix_[16],
				translate_matrix_[16],
				scale_matrix_[16],
				rotate_matrix_[16],
				center_matrix_[16],
                modelview_matrix_[16];
};

#endif