/**
*class GLWidgetCenter source file
*@author LigangChen
*@version 0.1 2007/02/04
*/

#include <QtGui>
#include <QtOpenGL>
#include <Qt>

#include <GL/glut.h>

#include <OpenMesh/Core/Geometry/VectorT.hh>
#include <OpenMesh/Tools/Utils/Timer.hh>

#include <math.h>

#include "glwidgetcenter.h"

GLWidgetCenter::GLWidgetCenter( QWidget* _parent, const char* _name )
  : QGLWidget( _parent, _name )
{    
  init();
}

GLWidgetCenter::GLWidgetCenter( QGLFormat& _fmt, QWidget* _parent, const char* _name )
  : QGLWidget( _fmt, _parent, _name )
{
  init();
}

GLWidgetCenter::~GLWidgetCenter()
{
	glDeleteLists(coords_display_list_, 1);	 
}

void GLWidgetCenter::init(void)
{
	// qt stuff 
	setFocusPolicy(Qt::StrongFocus); 
	setCursor(Qt::PointingHandCursor);

	objectShowFlags.reset();
	objectShowFlags.set(OSI_Edge);
	objectShowFlags.set(OSI_Light);
	objectShowFlags.set(OSI_ShadeSmooth);

	bbox_.set_min(Vec3f(0.0, 0.0, 0.0)); 
	bbox_.set_max(Vec3f(0.0, 0.0, 0.0)); 

	bbox_color_[0] = 1.0;
	bbox_color_[1] = 1.0;
	bbox_color_[2] = 1.0;
	bbox_color_[3] = 1.0;

	backgroud_color_[0] = 0.0;
	backgroud_color_[1] = 0.0;
	backgroud_color_[2] = 0.0;
	backgroud_color_[3] = 1.0;
}

void GLWidgetCenter::init_light(void)
{
	light0_ambient_[0] = 0.1;  // originally 0.1
	light0_ambient_[1] = 0.1;  // originally 0.1
	light0_ambient_[2] = 0.1;  // originally 0.1
	light0_ambient_[3] = 1.0;  // originally 1.0

	light0_diffuse_[0] = 0.5;  // originally 1.0
	light0_diffuse_[1] = 0.6;  // originally 1.0
	light0_diffuse_[2] = 0.8;  // originally 1.0
	light0_diffuse_[3] = 0.0;  // originally 1.0

	light0_specular_[0] = 0.8;  // originally 1.0
	light0_specular_[1] = 0.8;  // originally 1.0
	light0_specular_[2] = 0.8;  // originally 1.0
	light0_specular_[3] = 1.0;  // originally 1.0

	light0_position_[0] = 1.0;  // originally 1.0
	light0_position_[1] = 1.0;  // originally 1.0
	light0_position_[2] = 0.0; // originally 0.5
	light0_position_[3] = 0.0;

	//glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient_);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse_);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular_);
  
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position_);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1); // originally 0
}

void GLWidgetCenter::init_material(void)
{
	material_ambient_[0] = 0.1;  // originally 0.1
	material_ambient_[1] = 0.1;  // originally 0.1
	material_ambient_[2] = 0.1;  // originally 0.1
	material_ambient_[3] = 1.0;  // originally 1.0

	material_diffuse_[0] = 0.8;  // originally 0.8
	material_diffuse_[1] = 0.8;  // originally 0.8
	material_diffuse_[2] = 0.8;  // originally 0.8
	material_diffuse_[3] = 1.0;  // originally 1.0

	material_specular_[0] = 0.8;  // originally 1.0
	material_specular_[1] = 0.8;  // originally 1.0
	material_specular_[2] = 0.8;  // originally 1.0
	material_specular_[3] = 1.0;  // originally 1.0

	material_shine_ = 100;  // originally 120

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient_);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse_);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular_);
	glMaterialf(GL_FRONT, GL_SHININESS, material_shine_);
}

void GLWidgetCenter::initializeGL()
{
  // OpenGL state
  glClearColor(backgroud_color_[0], backgroud_color_[1], backgroud_color_[2], backgroud_color_[3]);
  glDisable( GL_DITHER );
  glEnable( GL_DEPTH_TEST );

  init_light();
  init_material();
  
  /** Fog, Not used temporarily
  GLfloat fogColor[4] = { 0.3, 0.3, 0.4, 1.0 };
  glFogi(GL_FOG_MODE,    GL_LINEAR);
  glFogfv(GL_FOG_COLOR,  fogColor);
  glFogf(GL_FOG_DENSITY, 0.35);
  glHint(GL_FOG_HINT,    GL_DONT_CARE);
  glFogf(GL_FOG_START,    5.0f);
  glFogf(GL_FOG_END,     25.0f);
  */

    // scene pos and size and prepare model view matrix
    set_scene_pos(Vec3f(0.0, 0.0, 0.0), 1.0);
	init_modelview_matrices();
	coords_display_list_ = gen_coords_display_list();
}

void GLWidgetCenter::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
	/**
	glPushMatrix();
	glLoadIdentity();
	init_light();
	*/

	update_projection_matrix();  // in case of changing the projection mode
    glMatrixMode( GL_PROJECTION );
    glLoadMatrixd( projection_matrix_ );

    glMatrixMode( GL_MODELVIEW );
	//glPushMatrix();
	//glMultMatrixd(modelview_matrix_);
	glLoadMatrixd(modelview_matrix_);

	//glLightfv(GL_LIGHT0, GL_POSITION, light0_position_);
  
    draw_scene();
}

void GLWidgetCenter::resizeGL(int _w, int _h)
{
	update_projection_matrix();
    glViewport(0, 0, _w, _h);
    updateGL();
}

void GLWidgetCenter::setViewport(QString viewport)
{
	if ("Reset" == viewport) {
		init_modelview_matrices();
		updateGL();

		return;
	}

	glPushMatrix();
	glLoadIdentity();

	if ("Center" == viewport) {
		glTranslated(0.0, 0.0, -3.0*radius_);
		glGetDoublev(GL_MODELVIEW_MATRIX, translate_matrix_);
		goto multmatrix;
	}
	else if ("Isomet" == viewport) {
		Vec3f axis = Vec3f(0.0, 0.0, 1.0) % Vec3f(1.0, 1.0, 1.0);
		float cos_angle = (Vec3f(0.0, 0.0, 1.0) | Vec3f(1.0, 1.0, 1.0)) / Vec3f(1.0, 1.0, 1.0).norm();
		if ( fabs(cos_angle) < 1.0 ) {
			float angle = acos( cos_angle ) * 180.0 / M_PI;
			glRotated( -angle, axis[0], axis[1], axis[2]);
		}
	}
	else if ("X-Y Plane" == viewport) {		
		;
	}
	else if ("Y-X Plane" == viewport) 
		glRotatef(180.0, 1.0, 1.0, 0.0);
	else if ("Y-Z Plane" == viewport) {
		glRotatef(-90.0, 0.0, 0.0, 1.0);    
		glRotatef(-90.0, 0.0, 1.0, 0.0);
	}
	else if ("Z-Y Plane" == viewport)
		glRotatef(90.0, 0.0, 1.0, 0.0);
	else if ("X-Z Plane" == viewport)
		glRotatef(-90.0, 1.0, 0.0, 0.0);
	else if ("Z-X Plane" == viewport) {
		glRotatef(90.0, 0.0, 0.0f, 1.0f);    
		glRotatef(90.0, 1.0f, 0.0f, 0.0f); 
	}

	glGetDoublev(GL_MODELVIEW_MATRIX, rotate_matrix_);

multmatrix: glLoadIdentity();
    glMultMatrixd(lookat_matrix_);
    glMultMatrixd(translate_matrix_);
	glMultMatrixd(scale_matrix_);
    glMultMatrixd(rotate_matrix_);
    glMultMatrixd(center_matrix_);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview_matrix_);

	glPopMatrix();

	updateGL();
}

void GLWidgetCenter::updateView()
{
	updateGL();
}

void GLWidgetCenter::draw_scene()
{ 
}

void GLWidgetCenter::mousePressEvent(QMouseEvent *_event)
{
	last_point_ok_ = map_to_sphere(last_point_2D_=_event->pos(),
			last_point_3D_);
}

/**
* Left button: rotate around center_
* Middle button: zoom in/out 
* Right button: translate object
*/
void GLWidgetCenter::mouseMoveEvent(QMouseEvent *_event)
{
  QPoint newPoint2D = _event->pos(); 
 
  double value_y;
  Vec3f  newPoint3D;
  bool   newPoint_hitSphere = map_to_sphere( newPoint2D, newPoint3D );

  float dx = newPoint2D.x() - last_point_2D_.x();
  float dy = newPoint2D.y() - last_point_2D_.y();
  
  float w  = width();
  float h  = height();

  //glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  if (_event->state() & MidButton) // scale from the center of the model
  {
    value_y = 1.0 * dy / h;
	glScaled(1.0 + value_y, 1.0 + value_y, 1.0 + value_y); 
	glMultMatrixd(scale_matrix_);
	glGetDoublev(GL_MODELVIEW_MATRIX, scale_matrix_);
  }  
  else if (_event->state() & RightButton)  // translate in x,y direction
  {
	  /** from netgen, too slow when translating in perspective projection mode, don't understand these codes yet!
	  GLdouble projmat[16], modelviewmat[16];
	  GLint viewport[4];
	  glGetDoublev(GL_PROJECTION_MATRIX, projmat);
	  glGetDoublev(GL_MODELVIEW_MATRIX, modelviewmat);
	  glGetIntegerv(GL_VIEWPORT, viewport);
	
	  // vorher pvz1/2 = 0
	  GLdouble pvx1 = 0, pvy1 = 0, pvz1 = 0.95;
	  GLdouble pvx2 = dx, pvy2 = -dy, pvz2 = 0.95;

	  GLdouble px1, py1, pz1;
	  GLdouble px2, py2, pz2;
	
	  gluUnProject (pvx1, pvy1, pvz1, 
			modelviewmat, projmat, viewport,
			&px1, &py1, &pz1);
	  gluUnProject (pvx2, pvy2, pvz2, 
			modelviewmat, projmat, viewport,
			&px2, &py2, &pz2);

	  glTranslated(px2-px1, py2-py1, pz2-pz1);
	  //glTranslated(5.0*(px2-px1), 5.0*(py2-py1), 5.0*(pz2-pz1)); // too fast for ortho projection
	  glMultMatrixd(translate_matrix_);
	  glGetDoublev(GL_MODELVIEW_MATRIX, translate_matrix_);
	  */

    float z = - (modelview_matrix_[ 2]*center_[0] + 
			modelview_matrix_[ 6]*center_[1] + 
			modelview_matrix_[10]*center_[2] + 
			modelview_matrix_[14]) 
			/ (modelview_matrix_[ 3]*center_[0] + 
	        modelview_matrix_[ 7]*center_[1] + 
	        modelview_matrix_[11]*center_[2] + 
	        modelview_matrix_[15]);
    float aspect     = 1.0 * w / h;
    float near_plane = 0.01 * radius_;
    float top        = tan(fovy()/2.0*M_PI/180.0f) * near_plane;
    float right      = aspect*top;

	glTranslated(2.0*dx/w*right/near_plane*z, -2.0*dy/h*top/near_plane*z, 0.0);
	glMultMatrixd(translate_matrix_);
	glGetDoublev(GL_MODELVIEW_MATRIX, translate_matrix_);	
  }
  else if (_event->state() & LeftButton)  // rotate
  {
	  if (last_point_ok_) 
	  {
		  if (newPoint_hitSphere = map_to_sphere(newPoint2D, newPoint3D)) {
			  Vec3f axis = last_point_3D_ % newPoint3D;
	          float cos_angle = (last_point_3D_ | newPoint3D);
			  if ( fabs(cos_angle) < 1.0 ) {
				  float angle = 2.0 * acos( cos_angle ) * 180.0 / M_PI;
				  glRotated( angle, axis[0], axis[1], axis[2]);
				  glMultMatrixd(rotate_matrix_);
				  glGetDoublev (GL_MODELVIEW_MATRIX, rotate_matrix_);
			  }
		  }
	  }
  }

  // remember this point
  last_point_2D_ = newPoint2D;
  last_point_3D_ = newPoint3D;
  last_point_ok_ = newPoint_hitSphere;

    glLoadIdentity();
    glMultMatrixd(lookat_matrix_);
    glMultMatrixd(translate_matrix_);
	glMultMatrixd(scale_matrix_);
    glMultMatrixd(rotate_matrix_);
    glMultMatrixd(center_matrix_);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview_matrix_);

	glPopMatrix();

  // trigger redraw
  updateGL();
}

void GLWidgetCenter::mouseReleaseEvent(QMouseEvent* _event)
{  
   last_point_ok_ = false;
}

bool GLWidgetCenter::map_to_sphere( const QPoint& _v2D, Vec3f& _v3D )
{
  if ( (_v2D.x() >= 0) && (_v2D.x() <= width()) &&
       (_v2D.y() >= 0) && (_v2D.y() <= height()) ) 
  {
    double x  = (double)(_v2D.x() - 0.5*width())  / (double)width();
    double y  = (double)(0.5*height() - _v2D.y()) / (double)height();
    double sinx         = sin(M_PI * x * 0.5);
    double siny         = sin(M_PI * y * 0.5);
    double sinx2siny2   = sinx * sinx + siny * siny;
    
    _v3D[0] = sinx;
    _v3D[1] = siny;
    _v3D[2] = sinx2siny2 < 1.0 ? sqrt(1.0 - sinx2siny2) : 0.0;
    
    return true;
  }
  
  return false;
}

void GLWidgetCenter::update_projection_matrix()
{
  // enable GL context
  makeCurrent();
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  
  if (objectShowFlags.test(OSI_Perspective)) {
	gluPerspective(45.0, (GLfloat) width() / (GLfloat) height(),
		0.01*radius_, 100.0*radius_); 
  }
  else 
  {	 
	  float width = this->width();
	  float height = this->height();
	  float x_ratio, y_ratio;

	  width = width > 0? width : 1;
	  height = height >0 ? height : 1;
	  if (  width < height) {
	      x_ratio = 1.0;
		  y_ratio = height / width;
	  }
	  else {
	      x_ratio = width / height;
		  y_ratio = 1.0f;
	  }

	  glOrtho(-x_ratio*radius_, x_ratio*radius_, -y_ratio*radius_, y_ratio*radius_, 
			0.01*radius_, 100.0*radius_); // originally 0.01*radius_, diag*scale
  }
  
  glGetDoublev( GL_PROJECTION_MATRIX, projection_matrix_);
  glMatrixMode( GL_MODELVIEW );
}

void GLWidgetCenter::init_modelview_matrices()
{
	// prepare model view matrix
    glPushMatrix(); // default current matrix mode is modelview

    glLoadIdentity();
    gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
    glGetDoublev(GL_MODELVIEW_MATRIX, lookat_matrix_);

    glLoadIdentity();
    glTranslated(0.0, 0.0, -3.0*radius_);
    glGetDoublev(GL_MODELVIEW_MATRIX, translate_matrix_);
  
    glLoadIdentity();
	glGetDoublev(GL_MODELVIEW_MATRIX, scale_matrix_);
    glGetDoublev(GL_MODELVIEW_MATRIX, rotate_matrix_);

    // in netgen glScalef (1/rad, 1/rad, 1/rad); the model must be normalized
    glTranslated(-center_[0], -center_[1], -center_[2]);
	glGetDoublev(GL_MODELVIEW_MATRIX, center_matrix_);

    glLoadIdentity();
    glMultMatrixd(lookat_matrix_);
    glMultMatrixd(translate_matrix_);
	glMultMatrixd(scale_matrix_);
    glMultMatrixd(rotate_matrix_);
    glMultMatrixd(center_matrix_);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview_matrix_);

    glPopMatrix();
}

void GLWidgetCenter::set_scene_pos( const Vec3f& _cog, float _radius )
{
	if ((center_-_cog).norm() < 1.0e-6 && fabs(radius_-_radius) < 1.0e-6) // regard as the same model
		return;

    center_ = _cog;
    radius_ = _radius;
    //glFogf( GL_FOG_START,      1.5*_radius );  //temporarily not used
    //glFogf( GL_FOG_END,        3.0*_radius );

    update_projection_matrix();
    init_modelview_matrices(); // the same as view_all()
}

void GLWidgetCenter::draw_coords_sys()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glViewport(10, 10, 50, 50);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1.3, 1.3, -1.3, 1.3, 0.1, 10.0);
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslated(0.0, 0.0, -2.0);
	glMultMatrixd(rotate_matrix_);
	glCallList(coords_display_list_);
	glColor3f(1.0 - backgroud_color_[0], 1.0 - backgroud_color_[1], 1.0 - backgroud_color_[2]);
	renderText(1.1, 0.0, 0.0, "x");
	renderText(0.0, 1.1, 0.0, "y");
	renderText(0.0, 0.0, 1.1, "z");
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glPopAttrib();

	glMatrixMode(GL_MODELVIEW);
}

GLuint GLWidgetCenter::gen_coords_display_list()
{
	GLuint coords_display_list = glGenLists(1);

	glNewList(coords_display_list, GL_COMPILE);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glColor3f(1.0 - backgroud_color_[0], 1.0 - backgroud_color_[1], 1.0 - backgroud_color_[2]);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.0);
	glEnd();
	glEndList();

	return coords_display_list;
}

void GLWidgetCenter::draw_bbox()
{
	glColor3f(bbox_color_[0], bbox_color_[1], bbox_color_[2]);
	glLineWidth(1.0);

	glBegin(GL_LINES);
		glVertex3f(bbox_.min()[0], bbox_.min()[1], bbox_.min()[2]);
		glVertex3f(bbox_.max()[0], bbox_.min()[1], bbox_.min()[2]);
		glVertex3f(bbox_.max()[0], bbox_.min()[1], bbox_.min()[2]);
		glVertex3f(bbox_.max()[0], bbox_.max()[1], bbox_.min()[2]);
		glVertex3f(bbox_.max()[0], bbox_.max()[1], bbox_.min()[2]);
		glVertex3f(bbox_.min()[0], bbox_.max()[1], bbox_.min()[2]);
		glVertex3f(bbox_.min()[0], bbox_.max()[1], bbox_.min()[2]);
		glVertex3f(bbox_.min()[0], bbox_.min()[1], bbox_.min()[2]);

		glVertex3f(bbox_.min()[0], bbox_.min()[1], bbox_.min()[2]);
		glVertex3f(bbox_.min()[0], bbox_.min()[1], bbox_.max()[2]);
		glVertex3f(bbox_.max()[0], bbox_.min()[1], bbox_.min()[2]);
		glVertex3f(bbox_.max()[0], bbox_.min()[1], bbox_.max()[2]);
		glVertex3f(bbox_.max()[0], bbox_.max()[1], bbox_.min()[2]);
		glVertex3f(bbox_.max()[0], bbox_.max()[1], bbox_.max()[2]);
		glVertex3f(bbox_.min()[0], bbox_.max()[1], bbox_.min()[2]);
		glVertex3f(bbox_.min()[0], bbox_.max()[1], bbox_.max()[2]);

		glVertex3f(bbox_.min()[0], bbox_.min()[1], bbox_.max()[2]);
		glVertex3f(bbox_.max()[0], bbox_.min()[1], bbox_.max()[2]);
		glVertex3f(bbox_.max()[0], bbox_.min()[1], bbox_.max()[2]);
		glVertex3f(bbox_.max()[0], bbox_.max()[1], bbox_.max()[2]);
		glVertex3f(bbox_.max()[0], bbox_.max()[1], bbox_.max()[2]);
		glVertex3f(bbox_.min()[0], bbox_.max()[1], bbox_.max()[2]);
		glVertex3f(bbox_.min()[0], bbox_.max()[1], bbox_.max()[2]);
		glVertex3f(bbox_.min()[0], bbox_.min()[1], bbox_.max()[2]);
	glEnd();

	glFlush();
}

void GLWidgetCenter::draw_light_dir()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);
	glTranslatef(-center_[0], -center_[1], -center_[2]);
	glTranslatef(0.0, 0.0, -3.0 * radius_);

	glColor3ub(255, 255, 255);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    if (0.0 == light0_position_[3])        // 10000.0 = 'infinite' light
		glVertex3f(light0_position_[0]*1000.0, light0_position_[1]*1000.0, light0_position_[2]*1000.0);
    else 
        glVertex3f(light0_position_[0], light0_position_[1], light0_position_[2]);
    glEnd();

	glPointSize(4.0);
	glBegin(GL_POINTS);
		glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glPopMatrix();
	glPointSize(1.0);

	glFlush();
}