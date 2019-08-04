#include <OpenMesh/Core/Utils/vector_cast.hh>
#include <OpenMesh/Core/Mesh/Handles.hh>
#include <OpenMesh/Core/Mesh/IteratorsT.hh>
#include <OpenMesh/Core/Geometry/MathDefs.hh>

#include "global.h"
#include "meshviewerwidget.h"
#include <stdlib.h>

void MeshViewerWidget::init()
{
	GLWidgetCenter::init();

	// for object show
	vertices_color_[0] = 1.0;
	vertices_color_[1] = 0.0;
	vertices_color_[2] = 0.0;
	vertices_color_[3] = 0.0;
	vertices_size_     = 2.0;

	edges_color_[0] = 0.0;
	edges_color_[1] = 1.0;
	edges_color_[2] = 0.0;
	edges_color_[3] = 0.0;
	edges_width_    = 1.0;

	faces_color_[0] = 0.0;
	faces_color_[1] = 0.0;
	faces_color_[2] = 1.0;
	faces_color_[3] = 0.0;

	vertex_indices_color_[0] = 1.0;
	vertex_indices_color_[1] = 0.0;
	vertex_indices_color_[2] = 0.0;
	vertex_indices_color_[3] = 0.0;

	edge_indices_color_[0] = 1.0;
	edge_indices_color_[1] = 0.0;
	edge_indices_color_[2] = 0.0;
	edge_indices_color_[3] = 0.0;

	face_indices_color_[0] = 1.0;
	face_indices_color_[1] = 0.0;
	face_indices_color_[2] = 0.0;
	face_indices_color_[3] = 0.0;

	vertex_normals_color_[0] = 1.0;
	vertex_normals_color_[1] = 1.0;
	vertex_normals_color_[2] = 1.0;
	vertex_normals_color_[3] = 0.0;

	face_normals_color_[0] = 1.0;
	face_normals_color_[1] = 1.0;
	face_normals_color_[2] = 1.0;
	face_normals_color_[3] = 0.0;


	// for feature view
	boundary_vertices_color_[0] = 1.0;
	boundary_vertices_color_[1] = 0.0;
	boundary_vertices_color_[2] = 0.0;
	boundary_vertices_color_[3] = 0.0;
	boundary_vertices_size_     = 2.0;

	boundary_vertex_indices_color_[0] = 1.0;
	boundary_vertex_indices_color_[1] = 0.0;
	boundary_vertex_indices_color_[2] = 0.0;
	boundary_vertex_indices_color_[3] = 1.0;

	boundary_vertex_normals_color_[0] = 1.0;
	boundary_vertex_normals_color_[1] = 1.0;
	boundary_vertex_normals_color_[2] = 1.0;
	boundary_vertex_normals_color_[3] = 0.0;

	corner_vertices_color_[0] = 1.0;
	corner_vertices_color_[1] = 0.0;
	corner_vertices_color_[2] = 0.0;
	corner_vertices_color_[3] = 0.0;
	corner_vertices_size_     = 2.0;

	corner_vertex_indices_color_[0] = 1.0;
	corner_vertex_indices_color_[1] = 0.0;
	corner_vertex_indices_color_[2] = 0.0;
	corner_vertex_indices_color_[3] = 1.0;

	corner_vertex_normals_color_[0] = 1.0;
	corner_vertex_normals_color_[1] = 1.0;
	corner_vertex_normals_color_[2] = 1.0;
	corner_vertex_normals_color_[3] = 0.0;

	ridge_vertices_color_[0] = 1.0;
	ridge_vertices_color_[1] = 0.0;
	ridge_vertices_color_[2] = 0.0;
	ridge_vertices_color_[3] = 0.0;
	ridge_vertices_size_     = 2.0;

	ridge_vertex_indices_color_[0] = 1.0;
	ridge_vertex_indices_color_[1] = 0.0;
	ridge_vertex_indices_color_[2] = 0.0;
	ridge_vertex_indices_color_[3] = 1.0;

	ridge_vertex_normals_color_[0] = 1.0;
	ridge_vertex_normals_color_[1] = 1.0;
	ridge_vertex_normals_color_[2] = 1.0;
	ridge_vertex_normals_color_[3] = 0.0;

	flat_vertices_color_[0] = 1.0;
	flat_vertices_color_[1] = 0.0;
	flat_vertices_color_[2] = 0.0;
	flat_vertices_color_[3] = 0.0;
	flat_vertices_size_     = 2.0;

	flat_vertex_indices_color_[0] = 1.0;
	flat_vertex_indices_color_[1] = 0.0;
	flat_vertex_indices_color_[2] = 0.0;
	flat_vertex_indices_color_[3] = 1.0;

	flat_vertex_normals_color_[0] = 1.0;
	flat_vertex_normals_color_[1] = 1.0;
	flat_vertex_normals_color_[2] = 1.0;
	flat_vertex_normals_color_[3] = 0.0;

	boundary_edges_color_[0] = 0.0;
	boundary_edges_color_[1] = 1.0;
	boundary_edges_color_[2] = 0.0;
	boundary_edges_color_[3] = 0.0;
	boundary_edges_width_    = 1.0;

	ridge_edges_color_[0] = 0.0;
	ridge_edges_color_[1] = 1.0;
	ridge_edges_color_[2] = 0.0;
	ridge_edges_color_[3] = 0.0;
	ridge_edges_width_    = 1.0;

	flat_edges_color_[0] = 0.0;
	flat_edges_color_[1] = 1.0;
	flat_edges_color_[2] = 0.0;
	flat_edges_color_[3] = 0.0;
	flat_edges_width_    = 1.0;

	boundary_edge_indices_color_[0] = 1.0;
	boundary_edge_indices_color_[1] = 0.0;
	boundary_edge_indices_color_[2] = 0.0;
	boundary_edge_indices_color_[3] = 1.0;

	ridge_edge_indices_color_[0] = 1.0;
	ridge_edge_indices_color_[1] = 0.0;
	ridge_edge_indices_color_[2] = 0.0;
	ridge_edge_indices_color_[3] = 1.0;

	flat_edge_indices_color_[0] = 1.0;
	flat_edge_indices_color_[1] = 0.0;
	flat_edge_indices_color_[2] = 0.0;
	flat_edge_indices_color_[3] = 1.0;
}

void MeshViewerWidget::on_mesh_loaded(void)
{
	is_mesh_valid_ = true;

    compute_bbox();
	set_scene_pos(bbox_.center(), bbox_.diagonal() * 0.5);
    
    // for normal display
	normal_scale_ = (bbox_.max() - bbox_.min()).min() * 0.05f;

	updateGL();
}

void MeshViewerWidget::compute_bbox()
{
  if (mesh_->n_vertices())
  {
    MyMesh::ConstVertexIter  vIt(mesh_->vertices_begin());
    MyMesh::ConstVertexIter  vEnd(mesh_->vertices_end());

    MyMesh::Point min(mesh_->point(vIt));
    MyMesh::Point max(mesh_->point(vIt));
                         
    for (++vIt; vIt != vEnd; ++vIt)
    {
      max.maximize(mesh_->point(vIt));
      min.minimize(mesh_->point(vIt));
    }

	bbox_.set_min(Vec3f(min[0], min[1], min[2]));
	bbox_.set_max(Vec3f(max[0], max[1], max[2]));
  }
  else 
  {
	bbox_.set_min(Vec3f(0.0, 0.0, 0.0)); 
	bbox_.set_max(Vec3f(0.0, 0.0, 0.0)); 
  }
}

void MeshViewerWidget::setObjectShowItems(bitset<OSI_NumObjectShowItems> showFlags)
{
	objectShowFlags = showFlags;

	updateGL();
}

void MeshViewerWidget::setFeatureViewItems(bitset<FV_NumFeatureViewItems> viewFlags)
{
	featureViewFlags = viewFlags;

	updateGL();
}

void MeshViewerWidget::draw_scene(void)
{
	draw_objects();
}

void MeshViewerWidget::draw_objects(void)
{
	if (objectShowFlags.test(OSI_ShadeSmooth))
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);

	// for object show
	if (objectShowFlags.test(OSI_Coords))
		draw_coords_sys();
	if (objectShowFlags.test(OSI_BBox))
		draw_bbox();

	if (objectShowFlags.test(OSI_Vertex))
		draw_vertices();
	if (objectShowFlags[OSI_Edge])
		draw_edges();
	if (objectShowFlags[OSI_Face]) 
		draw_faces();

	if (objectShowFlags[OSI_VIdx])
		draw_vertex_indices();
	if (objectShowFlags[OSI_EIdx])
		draw_edge_indices();
	if (objectShowFlags[OSI_FIdx])
		draw_face_indices();

	if (objectShowFlags[OSI_VNorm])
		draw_vertex_normals();
	if (objectShowFlags[OSI_HiddenLine])
		draw_hidden_line();
	if (objectShowFlags[OSI_FNorm])
		draw_face_normals();

	if (objectShowFlags[OSI_LightDir])
		draw_light_dir();

	// for feature view
	if (featureViewFlags.test(FV_BouNd))
		draw_boundary_vertices();
	if (featureViewFlags.test(FV_BNdIdx))
		draw_boundary_vertex_indices();
	if (featureViewFlags.test(FV_BNdNorm))
		draw_boundary_vertex_normals();
	if (featureViewFlags.test(FV_CornerNd))
		draw_corner_vertices();
	if (featureViewFlags.test(FV_CNdIdx))
		draw_corner_vertex_indices();
	if (featureViewFlags.test(FV_CNdNorm))
		draw_corner_vertex_normals();
	if (featureViewFlags.test(FV_RidgeNd))
		draw_ridge_vertices();
	if (featureViewFlags.test(FV_RNdIdx))
		draw_ridge_vertex_indices();
	if (featureViewFlags.test(FV_RNdNorm))
		draw_ridge_vertex_normals();
	if (featureViewFlags.test(FV_FlatNd))
		draw_flat_vertices();
	if (featureViewFlags.test(FV_FNdIdx))
		draw_flat_vertex_indices();
	if (featureViewFlags.test(FV_FNdNorm))
		draw_flat_vertex_normals();

	if (featureViewFlags.test(FV_BouEd))
		draw_boundary_edges();
	if (featureViewFlags.test(FV_RidgeEd))
		draw_ridge_edges();
	if (featureViewFlags.test(FV_FlatEd))
		draw_flat_edges();

	if (featureViewFlags.test(FV_BEdIdx))
		draw_boundary_edge_indices();
	if (featureViewFlags.test(FV_REdIdx))
		draw_ridge_edge_indices();
	if (featureViewFlags.test(FV_FEdIdx))
		draw_flat_edge_indices();
}

void MeshViewerWidget::draw_vertices()
{
	glColor3f(vertices_color_[0], vertices_color_[1], vertices_color_[2]);
	glPointSize(vertices_size_);

	MyMesh::VertexIter v_it(mesh_->vertices_begin()),
		               v_end(mesh_->vertices_end());
	Vec3f p(0.0, 0.0, 0.0);
	glBegin(GL_POINTS);
		for (; v_it != v_end; ++v_it) 
		{
			p = mesh_->point(v_it);
			glVertex3f(p.values_[0], p.values_[1], p.values_[2]);
		}
	glEnd();

	glFlush();
}

void MeshViewerWidget::draw_edges()
{
    MyMesh::ConstEdgeIter  e_it(mesh_->edges_begin()),  // here it cann't be Mesh::EdgeIter
		                   e_end(mesh_->edges_end());   // or it would have type translation error
    MyMesh::HalfedgeHandle    heh0, heh1;
    MyMesh::VertexHandle      vh0, vh1;
	Vec3f p0(0.0, 0.0, 0.0), p1(0.0, 0.0, 0.0);

	glLineWidth(edges_width_);
	glColor3fv(edges_color_);
	for (; e_it != e_end; ++e_it) 
	{
		heh0   = mesh_->halfedge_handle(e_it.handle(), 0);
	    heh1   = mesh_->halfedge_handle(e_it.handle(), 1);
    	vh0    = mesh_->to_vertex_handle(heh0);
		vh1    = mesh_->to_vertex_handle(heh1);

		p0 = mesh_->point(vh0);
		p1 = mesh_->point(vh1);
	
		glBegin(GL_LINES); // should be put outside the loop for efficiency consideration
	        glVertex3f(p0.values_[0], p0.values_[1], p0.values_[2]);
		    glVertex3f(p1.values_[0], p1.values_[1], p1.values_[2]);
		glEnd();
	}
	
	glFlush();	
}

void MeshViewerWidget::draw_faces()
{
	if (objectShowFlags.test(OSI_Light)) 
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);  // should be here or it will use the default light environment
		glEnable(GL_NORMALIZE);

		if (objectShowFlags.test(OSI_ColorMaterial)) 
		{
			glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
			//glColorMaterial(GL_FRONT, GL_SPECULAR);
			glEnable(GL_COLOR_MATERIAL);	
		}
		else
			glDisable(GL_COLOR_MATERIAL);
	}
	else
		glDisable(GL_LIGHTING);

    glColor3f(faces_color_[0], faces_color_[1], faces_color_[2]);
	
	MyMesh::ConstFaceIter f_it(mesh_->faces_begin()), 
                          f_end(mesh_->faces_end());
	MyMesh::ConstFaceVertexIter fv_it;

	glBegin(GL_TRIANGLES);
        for (; f_it!=f_end; ++f_it)
        {
			glNormal3fv(mesh_->normal(f_it));
            fv_it = mesh_->cfv_iter(f_it.handle()); 
            glVertex3fv( &mesh_->point(fv_it)[0] );
            ++fv_it;
            glVertex3fv( &mesh_->point(fv_it)[0] ); 
	        ++fv_it;
            glVertex3fv( &mesh_->point(fv_it)[0] );
        }
    glEnd();

	// keep the current state not using LIGHTING and COLOR_MATERIAL
	if (objectShowFlags.test(OSI_Light)) 
	{
		glDisable(GL_LIGHTING);
		if (objectShowFlags.test(OSI_ColorMaterial)) 
		{
			glDisable(GL_COLOR_MATERIAL);
			init_material();
		}
	}
	
	glFlush();
}

void MeshViewerWidget::draw_vertex_indices()
{
	MyMesh::ConstVertexIter v_it(mesh_->vertices_begin()),
		               v_end(mesh_->vertices_end());
	Vec3f p(0.0, 0.0, 0.0);
	char index[32];

	glColor3f(vertex_indices_color_[0], vertex_indices_color_[1], vertex_indices_color_[2]);
	for (; v_it != v_end; ++v_it) 
	{
		p = mesh_->point(v_it);
		sprintf(index, "%d", v_it.handle().idx());
		renderText(p[0], p[1], p[2], index);
	}
}

void MeshViewerWidget::draw_edge_indices()
{
	MyMesh::ConstEdgeIter  e_it(mesh_->edges_begin()), 
		              e_end(mesh_->edges_end());  
    MyMesh::HalfedgeHandle    heh0, heh1, heh2;
    MyMesh::VertexHandle      v0, v1;
	Vec3f p0(0.0, 0.0, 0.0), p1(0.0, 0.0, 0.0);
	char index[32];

	glColor3f(edge_indices_color_[0], edge_indices_color_[1], edge_indices_color_[2]);
	for (; e_it != e_end; ++e_it) 
	{
		heh0   = mesh_->halfedge_handle(e_it.handle(), 0);
	    heh1   = mesh_->halfedge_handle(e_it.handle(), 1);
    	v0     = mesh_->to_vertex_handle(heh0);
		v1     = mesh_->to_vertex_handle(heh1);

		p0 = mesh_->point(v0);
		p1 = mesh_->point(v1);

		sprintf(index, "%d", e_it.handle().idx());
	
		renderText((p0[0] + p1[0]) / 2, (p0[1] + p1[1]) / 2, (p0[2] + p1[2]) / 2, index);
	}
}

void MeshViewerWidget::draw_face_indices()
{
	MyMesh::ConstFaceIter f_it(mesh_->faces_begin()), 
                          f_end(mesh_->faces_end());
	MyMesh::ConstFaceVertexIter fv_it;
	Vec3f p0, p1, p2, p;
	char index[32];

	glColor3f(face_indices_color_[0], face_indices_color_[1], face_indices_color_[2]);
    for (; f_it!=f_end; ++f_it)
	{
        fv_it = mesh_->cfv_iter(f_it.handle()); 
		p0 = mesh_->point(fv_it);
        ++fv_it;
        p1 = mesh_->point(fv_it);
	    ++fv_it;
        p2 = mesh_->point(fv_it);
		p = (p0 + p1 + p2) / 3;
		
		sprintf(index, "%d", f_it.handle().idx());

		renderText(p[0], p[1], p[2], index);
    }

	glFlush();
}

void MeshViewerWidget::draw_vertex_normals()
{
	MyMesh::ConstVertexIter v_it(mesh_->vertices_begin()),
		               v_end(mesh_->vertices_end());
	Vec3f p(0.0, 0.0, 0.0);
	MyMesh::Normal n(0.0, 0.0, 0.0);

	glColor3f(vertex_normals_color_[0], vertex_normals_color_[1], vertex_normals_color_[2]);
	glLineWidth(1.0);
	glBegin(GL_LINES);
		for (; v_it != v_end; ++v_it) 
		{
			p = mesh_->point(v_it);
			n = mesh_->normal(v_it);
			glVertex3fv(p);
			glVertex3fv(p + n);
		}
	glEnd();

	glFlush();
}

void MeshViewerWidget::draw_hidden_line()
{
	MyMesh::ConstFaceIter f_it(mesh_->faces_begin()), 
                          f_end(mesh_->faces_end());
	MyMesh::ConstFaceVertexIter fv_it;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(edges_color_[0], edges_color_[1], edges_color_[2]);
	glLineWidth(1.0);
	glBegin(GL_TRIANGLES);
        for (; f_it!=f_end; ++f_it)
        {
            fv_it = mesh_->cfv_iter(f_it.handle()); 
            glVertex3fv( &mesh_->point(fv_it)[0] );
            ++fv_it;
            glVertex3fv( &mesh_->point(fv_it)[0] ); 
	        ++fv_it;
            glVertex3fv( &mesh_->point(fv_it)[0] );
        }
    glEnd();
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0, 1.0);
	glColor3f(backgroud_color_[0], backgroud_color_[1], backgroud_color_[2]);
	glLineWidth(1.0);
	glBegin(GL_TRIANGLES);
        for (f_it = mesh_->faces_begin(); f_it!=f_end; ++f_it)
        {
            fv_it = mesh_->cfv_iter(f_it.handle()); 
            glVertex3fv( &mesh_->point(fv_it)[0] );
            ++fv_it;
            glVertex3fv( &mesh_->point(fv_it)[0] ); 
	        ++fv_it;
            glVertex3fv( &mesh_->point(fv_it)[0] );
        }
    glEnd();

	glFlush();
}

void MeshViewerWidget::draw_face_normals()
{
	MyMesh::ConstFaceIter f_it(mesh_->faces_begin()), 
                          f_end(mesh_->faces_end());
	MyMesh::ConstFaceVertexIter fv_it;
	MyMesh::Point centroid(0.0, 0.0, 0.0);

	glColor3f(face_normals_color_[0], face_normals_color_[1], face_normals_color_[2]);
	glLineWidth(1.0);
	glBegin(GL_LINES);
        for (; f_it!=f_end; ++f_it)
        {
			mesh_->calc_face_centroid(f_it.handle(), centroid);
			glVertex3fv(centroid);
			glVertex3fv(centroid + mesh_->normal(f_it.handle()));
        }
    glEnd();
	
	glFlush();
}


// for feature view
void MeshViewerWidget::draw_boundary_vertices()
{
	MyMesh::ConstVertexIter v_it(mesh_->vertices_begin()),
	                        v_end(mesh_->vertices_end());

	glColor4fv(boundary_vertices_color_);
	glPointSize(boundary_vertices_size_);
	glBegin(GL_POINTS);
		for (; v_it != v_end; ++v_it)
			if (mesh_->property(node_type, v_it).is_boundary())
				glVertex3fv(&mesh_->point(v_it)[0]);
	glEnd();

	glFlush();
}

void MeshViewerWidget::draw_boundary_vertex_indices()
{
	MyMesh::ConstVertexIter v_it(mesh_->vertices_begin()),
		                    v_end(mesh_->vertices_end());

	Vec3f p(0.0, 0.0, 0.0);
	char index[32];
	glColor4fv(boundary_vertex_indices_color_);
	for (; v_it != v_end; ++v_it) 
		if (mesh_->property(node_type, v_it).is_boundary())
		{
			p = mesh_->point(v_it);
			sprintf(index, "%d", v_it.handle().idx());
			renderText(p[0], p[1], p[2], index);
		}
}

void MeshViewerWidget::draw_boundary_vertex_normals()
{
	MyMesh::ConstVertexIter v_it(mesh_->vertices_begin()),
		                    v_end(mesh_->vertices_end());
	Vec3f p(0.0, 0.0, 0.0);
	MyMesh::Normal n(0.0, 0.0, 0.0);
	glColor4fv(boundary_vertex_normals_color_);
	glLineWidth(1.0);
	glBegin(GL_LINES);
		for (; v_it != v_end; ++v_it) 
			if (mesh_->property(node_type, v_it).is_boundary())
			{
				p = mesh_->point(v_it);
				n = mesh_->normal(v_it);
				glVertex3fv(p);
				glVertex3fv(p + n);
			}
	glEnd();

	glFlush();
}

void MeshViewerWidget::draw_corner_vertices()
{
	MyMesh::ConstVertexIter v_it(mesh_->vertices_begin()),
	                        v_end(mesh_->vertices_end());

	glColor4fv(corner_vertices_color_);
	glPointSize(corner_vertices_size_);
	glBegin(GL_POINTS);
		for (; v_it != v_end; ++v_it)
			if (mesh_->property(node_type, v_it).is_corner())
				glVertex3fv(&mesh_->point(v_it)[0]);
	glEnd();

	glFlush();
}

void MeshViewerWidget::draw_corner_vertex_indices()
{
	MyMesh::ConstVertexIter v_it(mesh_->vertices_begin()),
		                    v_end(mesh_->vertices_end());

	Vec3f p(0.0, 0.0, 0.0);
	char index[32];
	glColor4fv(corner_vertex_indices_color_);
	for (; v_it != v_end; ++v_it) 
		if (mesh_->property(node_type, v_it).is_corner())
		{
			p = mesh_->point(v_it);
			sprintf(index, "%d", v_it.handle().idx());
			renderText(p[0], p[1], p[2], index);
		}
}

void MeshViewerWidget::draw_corner_vertex_normals()
{
	MyMesh::ConstVertexIter v_it(mesh_->vertices_begin()),
		                    v_end(mesh_->vertices_end());
	Vec3f p(0.0, 0.0, 0.0);
	MyMesh::Normal n(0.0, 0.0, 0.0);
	glColor4fv(corner_vertex_normals_color_);
	glLineWidth(1.0);
	glBegin(GL_LINES);
		for (; v_it != v_end; ++v_it) 
			if (mesh_->property(node_type, v_it).is_corner())
			{
				p = mesh_->point(v_it);
				n = mesh_->normal(v_it);
				glVertex3fv(p);
				glVertex3fv(p + n);
			}
	glEnd();

	glFlush();
}

void MeshViewerWidget::draw_ridge_vertices()
{
	MyMesh::ConstVertexIter v_it(mesh_->vertices_begin()),
	                        v_end(mesh_->vertices_end());

	glColor4fv(ridge_vertices_color_);
	glPointSize(ridge_vertices_size_);
	glBegin(GL_POINTS);
		for (; v_it != v_end; ++v_it)
			if (mesh_->property(node_type, v_it).is_ridge())
				glVertex3fv(&mesh_->point(v_it)[0]);
	glEnd();

	glFlush();
}

void MeshViewerWidget::draw_ridge_vertex_indices()
{
	MyMesh::ConstVertexIter v_it(mesh_->vertices_begin()),
		                    v_end(mesh_->vertices_end());

	Vec3f p(0.0, 0.0, 0.0);
	char index[32];
	glColor4fv(ridge_vertex_indices_color_);
	for (; v_it != v_end; ++v_it) 
		if (mesh_->property(node_type, v_it).is_ridge())
		{
			p = mesh_->point(v_it);
			sprintf(index, "%d", v_it.handle().idx());
			renderText(p[0], p[1], p[2], index);
		}
}

void MeshViewerWidget::draw_ridge_vertex_normals()
{
	MyMesh::ConstVertexIter v_it(mesh_->vertices_begin()),
		                    v_end(mesh_->vertices_end());
	Vec3f p(0.0, 0.0, 0.0);
	MyMesh::Normal n(0.0, 0.0, 0.0);
	glColor4fv(ridge_vertex_normals_color_);
	glLineWidth(1.0);
	glBegin(GL_LINES);
		for (; v_it != v_end; ++v_it) 
			if (mesh_->property(node_type, v_it).is_ridge())
			{
				p = mesh_->point(v_it);
				n = mesh_->normal(v_it);
				glVertex3fv(p);
				glVertex3fv(p + n);
			}
	glEnd();

	glFlush();
}

void MeshViewerWidget::draw_flat_vertices()
{
	MyMesh::ConstVertexIter v_it(mesh_->vertices_begin()),
	                        v_end(mesh_->vertices_end());

	glColor4fv(flat_vertices_color_);
	glPointSize(flat_vertices_size_);
	glBegin(GL_POINTS);
		for (; v_it != v_end; ++v_it)
			if (mesh_->property(node_type, v_it).is_flat())
				glVertex3fv(&mesh_->point(v_it)[0]);
	glEnd();

	glFlush();
}

void MeshViewerWidget::draw_flat_vertex_indices()
{
	MyMesh::ConstVertexIter v_it(mesh_->vertices_begin()),
		                    v_end(mesh_->vertices_end());

	Vec3f p(0.0, 0.0, 0.0);
	char index[32];
	glColor4fv(flat_vertex_indices_color_);
	for (; v_it != v_end; ++v_it) 
		if (mesh_->property(node_type, v_it).is_flat())
		{
			p = mesh_->point(v_it);
			sprintf(index, "%d", v_it.handle().idx());
			renderText(p[0], p[1], p[2], index);
		}

	glFlush();
}

void MeshViewerWidget::draw_flat_vertex_normals()
{
	MyMesh::ConstVertexIter v_it(mesh_->vertices_begin()),
		                    v_end(mesh_->vertices_end());
	Vec3f p(0.0, 0.0, 0.0);
	MyMesh::Normal n(0.0, 0.0, 0.0);
	glColor4fv(flat_vertex_normals_color_);
	glLineWidth(1.0);
	glBegin(GL_LINES);
		for (; v_it != v_end; ++v_it) 
			if (mesh_->property(node_type, v_it).is_flat())
			{
				p = mesh_->point(v_it);
				n = mesh_->normal(v_it);
				glVertex3fv(p);
				glVertex3fv(p + n);
			}
	glEnd();

	glFlush();
}

void MeshViewerWidget::draw_boundary_edges()
{
	MyMesh::ConstEdgeIter e_it(mesh_->edges_begin()),
	                      e_end(mesh_->edges_end());
	MyMesh::HalfedgeHandle    heh0, heh1;
    MyMesh::VertexHandle      vh0, vh1;
	Vec3f p0(0.0, 0.0, 0.0), p1(0.0, 0.0, 0.0);
	
	glColor4fv(boundary_edges_color_);
	glLineWidth(boundary_edges_width_);
	glBegin(GL_LINES);
		for (; e_it != e_end; ++e_it)
			if (ET_Boundary == mesh_->property(edge_type, e_it))
			{
				heh0   = mesh_->halfedge_handle(e_it.handle(), 0);
				heh1   = mesh_->halfedge_handle(e_it.handle(), 1);
    			vh0     = mesh_->to_vertex_handle(heh0);
				vh1     = mesh_->to_vertex_handle(heh1);

				p0 = mesh_->point(vh0);
				p1 = mesh_->point(vh1);

				//glVertex3fv(&mesh_->point(v0)[0]); // it's wrong, why ?
				//glVertex3fv(&mesh_->point(v1)[1]);
				glVertex3f(p0.values_[0], p0.values_[1], p0.values_[2]);
				glVertex3f(p1.values_[0], p1.values_[1], p1.values_[2]);
			}
	glEnd();

	glFlush();
}

void MeshViewerWidget::draw_ridge_edges()
{
	/** for testing assignment, succeed
	MyMesh ref_mesh;
	ref_mesh = *mesh_;

	MyMesh::ConstEdgeIter e_it(ref_mesh.edges_begin()),
	                      e_end(ref_mesh.edges_end());
	MyMesh::HalfedgeHandle    heh0, heh1;
    MyMesh::VertexHandle      vh0, vh1;
	Vec3f p0(0.0, 0.0, 0.0), p1(0.0, 0.0, 0.0);
	
	glColor4fv(ridge_edges_color_);
	glLineWidth(ridge_edges_width_);
	glBegin(GL_LINES);
		for (; e_it != e_end; ++e_it)
			if (ET_Ridge == ref_mesh.property(edge_type, e_it))
			{
				heh0   = ref_mesh.halfedge_handle(e_it.handle(), 0);
				heh1   = ref_mesh.halfedge_handle(e_it.handle(), 1);
    			vh0     = ref_mesh.to_vertex_handle(heh0);
				vh1     = ref_mesh.to_vertex_handle(heh1);

				p0 = ref_mesh.point(vh0);
				p1 = ref_mesh.point(vh1);

				//glVertex3fv(&mesh_->point(v0)[0]); // it's wrong, why ?
				//glVertex3fv(&mesh_->point(v1)[1]);
				glVertex3f(p0.values_[0], p0.values_[1], p0.values_[2]);
				glVertex3f(p1.values_[0], p1.values_[1], p1.values_[2]);
			}
	glEnd();

	glFlush();
	*/

	MyMesh::ConstEdgeIter e_it(mesh_->edges_begin()),
	                      e_end(mesh_->edges_end());
	MyMesh::HalfedgeHandle    heh0, heh1;
    MyMesh::VertexHandle      vh0, vh1;
	Vec3f p0(0.0, 0.0, 0.0), p1(0.0, 0.0, 0.0);
	
	glColor4fv(ridge_edges_color_);
	glLineWidth(ridge_edges_width_);
	glBegin(GL_LINES);
		for (; e_it != e_end; ++e_it)
			if (ET_Ridge == mesh_->property(edge_type, e_it))
			{
				heh0   = mesh_->halfedge_handle(e_it.handle(), 0);
				heh1   = mesh_->halfedge_handle(e_it.handle(), 1);
    			vh0     = mesh_->to_vertex_handle(heh0);
				vh1     = mesh_->to_vertex_handle(heh1);

				p0 = mesh_->point(vh0);
				p1 = mesh_->point(vh1);

				//glVertex3fv(&mesh_->point(v0)[0]); // it's wrong, why ?
				//glVertex3fv(&mesh_->point(v1)[1]);
				glVertex3f(p0.values_[0], p0.values_[1], p0.values_[2]);
				glVertex3f(p1.values_[0], p1.values_[1], p1.values_[2]);
			}
	glEnd();

	glFlush();
}

void MeshViewerWidget::draw_flat_edges()
{
	MyMesh::ConstEdgeIter e_it(mesh_->edges_begin()),
	                      e_end(mesh_->edges_end());
	MyMesh::HalfedgeHandle    heh0, heh1;
    MyMesh::VertexHandle      vh0, vh1;
	Vec3f p0(0.0, 0.0, 0.0), p1(0.0, 0.0, 0.0);
	
	glColor4fv(flat_edges_color_);
	glLineWidth(flat_edges_width_);
	glBegin(GL_LINES);
		for (; e_it != e_end; ++e_it)
			if (ET_Flat == mesh_->property(edge_type, e_it))
			{
				heh0   = mesh_->halfedge_handle(e_it.handle(), 0);
				heh1   = mesh_->halfedge_handle(e_it.handle(), 1);
    			vh0     = mesh_->to_vertex_handle(heh0);
				vh1     = mesh_->to_vertex_handle(heh1);

				p0 = mesh_->point(vh0);
				p1 = mesh_->point(vh1);

				//glVertex3fv(&mesh_->point(v0)[0]); // it's wrong, why ?
				//glVertex3fv(&mesh_->point(v1)[1]);
				glVertex3f(p0.values_[0], p0.values_[1], p0.values_[2]);
				glVertex3f(p1.values_[0], p1.values_[1], p1.values_[2]);
			}
	glEnd();

	glFlush();
}

void MeshViewerWidget::draw_boundary_edge_indices()
{
	MyMesh::ConstEdgeIter  e_it(mesh_->edges_begin()), 
		                   e_end(mesh_->edges_end());  
    MyMesh::HalfedgeHandle    heh0, heh1, heh2;
    MyMesh::VertexHandle      v0, v1;
	Vec3f p0(0.0, 0.0, 0.0), p1(0.0, 0.0, 0.0);
	char index[32];

	glColor4fv(boundary_edge_indices_color_);
	for (; e_it != e_end; ++e_it) 	
		if (ET_Boundary == mesh_->property(edge_type, e_it))
		{
			heh0   = mesh_->halfedge_handle(e_it.handle(), 0);
			heh1   = mesh_->halfedge_handle(e_it.handle(), 1);
    		v0     = mesh_->to_vertex_handle(heh0);
			v1     = mesh_->to_vertex_handle(heh1);

			p0 = mesh_->point(v0);
			p1 = mesh_->point(v1);

			sprintf(index, "%d", e_it.handle().idx());
	
			renderText((p0[0] + p1[0]) / 2, (p0[1] + p1[1]) / 2, (p0[2] + p1[2]) / 2, index);
		}
}

void MeshViewerWidget::draw_ridge_edge_indices()
{
	MyMesh::ConstEdgeIter  e_it(mesh_->edges_begin()), 
		                   e_end(mesh_->edges_end());  
    MyMesh::HalfedgeHandle    heh0, heh1, heh2;
    MyMesh::VertexHandle      v0, v1;
	Vec3f p0(0.0, 0.0, 0.0), p1(0.0, 0.0, 0.0);
	char index[32];

	glColor4fv(ridge_edge_indices_color_);
	for (; e_it != e_end; ++e_it) 	
		if (ET_Ridge == mesh_->property(edge_type, e_it))
		{
			heh0   = mesh_->halfedge_handle(e_it.handle(), 0);
			heh1   = mesh_->halfedge_handle(e_it.handle(), 1);
    		v0     = mesh_->to_vertex_handle(heh0);
			v1     = mesh_->to_vertex_handle(heh1);

			p0 = mesh_->point(v0);
			p1 = mesh_->point(v1);

			sprintf(index, "%d", e_it.handle().idx());
	
			renderText((p0[0] + p1[0]) / 2, (p0[1] + p1[1]) / 2, (p0[2] + p1[2]) / 2, index);
		}

	glFlush();
}

void MeshViewerWidget::draw_flat_edge_indices()
{
	MyMesh::ConstEdgeIter  e_it(mesh_->edges_begin()), 
		                   e_end(mesh_->edges_end());  
    MyMesh::HalfedgeHandle    heh0, heh1, heh2;
    MyMesh::VertexHandle      v0, v1;
	Vec3f p0(0.0, 0.0, 0.0), p1(0.0, 0.0, 0.0);
	char index[32];

	glColor4fv(flat_edge_indices_color_);
	for (; e_it != e_end; ++e_it) 	
		if (ET_Flat == mesh_->property(edge_type, e_it))
		{
			heh0   = mesh_->halfedge_handle(e_it.handle(), 0);
			heh1   = mesh_->halfedge_handle(e_it.handle(), 1);
    		v0     = mesh_->to_vertex_handle(heh0);
			v1     = mesh_->to_vertex_handle(heh1);

			p0 = mesh_->point(v0);
			p1 = mesh_->point(v1);

			sprintf(index, "%d", e_it.handle().idx());
	
			renderText((p0[0] + p1[0]) / 2, (p0[1] + p1[1]) / 2, (p0[2] + p1[2]) / 2, index);
		}
}