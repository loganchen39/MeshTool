#ifndef SMOOTHER_H
#define SMOOTHER_H

#include "global.h"

#include <math.h>

#define MALLOC(var, type, size, subr_name) \
   if (((var) = (type *) malloc ((size) * sizeof(type))) == (type *) NULL)
#define ABS(a) ((MACRO_ABS_arg=(a)) >= 0. ? MACRO_ABS_arg : -MACRO_ABS_arg)
#define SQUARE(a) ((a) * (a))
#define SIGN(a,b) (MACRO_SIGN_arg = ABS(a), \
                   (b) >= 0. ? MACRO_SIGN_arg : -MACRO_SIGN_arg)
#define RMAX(a,b) (MACRO_RMAX_arg1=(a), MACRO_RMAX_arg2=(b), \
       (MACRO_RMAX_arg1 > MACRO_RMAX_arg2) ? MACRO_RMAX_arg1 : MACRO_RMAX_arg2)
#define IMIN(a,b) (MACRO_IMIN_arg1=(a), MACRO_IMIN_arg2=(b), \
       (MACRO_IMIN_arg1 < MACRO_IMIN_arg2) ? MACRO_IMIN_arg1 : MACRO_IMIN_arg2)
#define TOL_EQ(a,b,tol) (ABS((b) - (a)) <= (tol))
#define ZERO             (0.0L)
#define ALMOST_ZERO      (1.0e-30L)
#define SQRT_ALMOST_ZERO (1.0e-15L)


template<class Mesh>
class SmootherT
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

	SmootherT(Mesh& _mesh);
	~SmootherT();

public:
	void smooth();
	//void edge_swap();
	//bool is_swap_legal(EdgeHandle _eh) const;

	void set_smmethod(int _smmethod) { smmethod_ = _smmethod; }
	void set_nsmoothsurf(int _nsmoothsurf) { nsmoothsurf_ = _nsmoothsurf; }
	void set_relaxsurf(float _relaxsurf) { relaxsurf_ = _relaxsurf; }

private:
	/** Calculate the closest point at a line segment from the point coord.  Also
	 *  return as the function value the square of the distance between the points.
     *  NOTE: projCoord, distFrom1 and lineLeng can be NULL.
	 */
	Scalar closest_to_line_segment3d(const Point& _pnt, const Point& _ln_pnt1, 
		const Point& _ln_pnt2, Point& _projected_pnt) const;

	/** Compute the area of a 2d triangle, the parameter is in 3d
	*   The sign of the area is used to indicate the location of a point to a line
	*/
	Scalar calc_triangle2d_area(const Point _tri_pnt[]) const;

	/** Determine in 2D whether a point is inside a triangle or not 	
	*   Although the parameter is in 3D, only the first two coordinates are used
	*/
	bool is_inside_triangle2d(const Point& _pnt, const Point _tri_pnt[]) const;

	/** Calculates the closest point to the triangle of coord and returns that
     *  value.  Also returns the square of the distance between coord and the
     *  triangle.
     */
	Scalar closest_to_triangle3d(const Point& _pnt, const Point _tri_pnt[], Point& _projected_pnt) const;

	// solvers
	/**
	*  This is the singular value decomposition routine as found in the book
	*  Numerical Recipes by Press, Flannery, Teukolsky and Vetterling.
	*
	*  Given a matrix a, with logical dimensions m by n and physical
	*  dimensions mp by np, this routine computes its singular value
	*  decomposition, a=u w tran(v).  The matrix u replaces a on output.
	*  The diagonal matrix of singular values, w, is output as a vector.
	*  The matrix v (not its transpose) is output.  m must be greater or
	*  equal to n; if it is smaller, the a should be filled up to square
	*  with zero rows.  rv1 is a work area which should be of size np.
	*
	*  ierr returns the follow values:
	*    0 => everything is ok
	*    1 => dimensions are incorrect (No longer checks this)
	*    2 => procedure did not converge
	*/
	void svdcmp(double *a, int m, int n, int mp, int np, double *w, double *v, int *ierr);
	double LENGTH2D(double a, double b);

	/**
	 *  This is the singular value decomposition back substitution routine as
	 *  found in the book Numerical Recipes by Press, Flannery, Teukolsky and
	 *  Vetterling.
	 *
	 *  Given the matrices u, w and v from a previous singular value
	 *  decomposition with logical dimensions m by n and physical dimensions
	 *  mp by np, this routine does the back substitution for a x = b.  The
	 *  diagonal matrix of singular values, w, is a vector.  The matrix v
	 *  (not its transpose) is input.  m must be greater or equal to n.
	 *  tmp is a work area which must be of size np.
	 */
	void svbksb (double *u, double *w, double *v, int m, int n, int mp, int np, double *b, double *x);

private:
	Mesh& mesh_;

	int smmethod_;
	int nsmoothsurf_;
	float relaxsurf_;
};

template<class Mesh>
SmootherT<Mesh>::SmootherT(Mesh &_mesh) : mesh_(_mesh)
{
}

template<class Mesh>
SmootherT<Mesh>::~SmootherT()
{
}

template<class Mesh>
typename Mesh::Scalar 
SmootherT<Mesh>::closest_to_line_segment3d(const Point& _pnt, const Point& _ln_pnt1, 
		const Point& _ln_pnt2, Point& _projected_pnt) const
{
	Scalar dist_from_pnt1;
	Point ln_vec = _ln_pnt2 - _ln_pnt1;
	Scalar ln_length = ln_vec.norm();
	Point delta_vec = _pnt - _ln_pnt1;

	if (ln_length <=  1.0e-6) // the tolerance should actually be determined by BBox
	{
		// 将节点还原为原始位置
		_projected_pnt = _ln_pnt1;
		return delta_vec.sqrnorm();
	}

	dist_from_pnt1 = ln_vec | delta_vec / ln_length;

	if (dist_from_pnt1 < 0.0)
	{
		// 投影在反向延长线上，取_ln_pnt1
		_projected_pnt = _ln_pnt1;
		return delta_vec.sqrnorm();
	}

	if (dist_from_pnt1 > ln_length)
	{
		// 投影在正向延长线上，取_ln_pnt2
		_projected_pnt = _ln_pnt2;
		return (_pnt - _ln_pnt2).sqrnorm();
	}

	// 投影到线段内部
	_projected_pnt = _ln_pnt1 + ln_vec * (dist_from_pnt1 / ln_length);
	Point norm = ln_vec % delta_vec;
	return norm.sqrnorm() / ln_vec.sqrnorm();
}

template<class Mesh>
typename Mesh::Scalar 
SmootherT<Mesh>::calc_triangle2d_area(const Point _tri_pnt[]) const
{
	Scalar area2 = (_tri_pnt[1][0] - _tri_pnt[0][0]) * (_tri_pnt[2][1] - _tri_pnt[0][1])
					- (_tri_pnt[2][0] - _tri_pnt[0][0]) * (_tri_pnt[1][1] - _tri_pnt[0][1]);

	return area2 / 2.0;
}

template<class Mesh>
bool SmootherT<Mesh>::is_inside_triangle2d(const Point& _pnt, const Point _tri_pnt[]) const
{
	Scalar tri_area = calc_triangle2d_area(_tri_pnt); // must be wrong

	Point pnt[3] = {_tri_pnt[0], _tri_pnt[1], _tri_pnt[2]};
	Scalar area;
	int i;

	for (i = 0; i < 3; ++i)
	{
		pnt[i] = _pnt;
		area = calc_triangle2d_area(pnt);
		if (tri_area * area < 0.0)
			return false;

		pnt[i] = _tri_pnt[i];
	}

	return true;
}

template<class Mesh>
typename Mesh::Scalar 
SmootherT<Mesh>::closest_to_triangle3d(const Point& _pnt, const Point _tri_pnt[], Point& _projected_pnt) const
{
	Scalar dist, dist_square, tmp_dist_square;
	Point origin, xaxis, yaxis, zaxis, vec[3], pnt2d;

	Point tmp_vec;
	int i, j, use_as_x;

	// First, calculate a new coordinate system based on the three points and put
    // all the points into that coordinate system.
	dist_square = -1.0e20;
	for (i = 0, j = 1; i < 3; ++i, ++j)
	{
		if (j >= 3)
			j = 0;

		vec[i] = _tri_pnt[j] - _tri_pnt[i];
		tmp_dist_square = vec[i].sqrnorm();

		if (tmp_dist_square < 1.0e-12) // should be determined by BBox 
			goto UseEdges;

		if (tmp_dist_square > dist_square)
		{
			dist_square = tmp_dist_square;
			use_as_x = i;
			origin = _tri_pnt[i];
		}
	}

	xaxis = vec[use_as_x] / vec[use_as_x].norm();

	j = use_as_x + 1;
	if (3 == j)
		j = 0;
	zaxis = xaxis % vec[j];
	if (zaxis.norm() < 1.0e-6)
		goto UseEdges;
	zaxis.normalize_cond();

	yaxis = zaxis % xaxis;
	yaxis.normalize_cond();

	// Project all the points into this new coordinate system.
	vec[0] = _pnt - origin;
	pnt2d[0] = vec[0] | xaxis;
	pnt2d[1] = vec[0] | yaxis;
	pnt2d[2] = vec[0] | zaxis;

	for (i = 0; i < 3; ++i)
	{
		tmp_vec = _tri_pnt[i] - origin;
		vec[i][0] = tmp_vec | xaxis;
		vec[i][1] = tmp_vec | yaxis;
		vec[i][2] = 0.0;
	}

	/** See if the point is inside the triangle.  If it is inside, the projection
     *  point becomes the closest point and the distance is the distance between
     *  the point and the project point.  If the point is outside, the distance
     *  is the closest distance to any of the triangle sides.
	 */
	if (!is_inside_triangle2d(pnt2d, vec))
		goto UseEdges;

	_projected_pnt[0] = origin[0] + pnt2d[0]*xaxis[0] + pnt2d[1]*yaxis[0];
	_projected_pnt[1] = origin[1] + pnt2d[0]*xaxis[1] + pnt2d[1]*yaxis[1];
	_projected_pnt[2] = origin[2] + pnt2d[0]*xaxis[2] + pnt2d[1]*yaxis[2];

	return pnt2d[2] * pnt2d[2];

	/**
    *  The triangle is degenerate or the projection point is outside the
    *  triangle.  Calculate the distance to the triangle edges and return the
    *  smallest value is the distance to this triangle.
    */
UseEdges:
	dist_square = 1.0e20;
	for (i = 0, j = 1; i < 3; ++i, ++j)
	{
		if (j >= 3)
			j = 0;

		tmp_dist_square = closest_to_line_segment3d(_pnt, _tri_pnt[i], _tri_pnt[j], tmp_vec);
		if (tmp_dist_square < dist_square)
		{
			dist_square = tmp_dist_square;
			_projected_pnt = tmp_vec;
		}
	}

	return dist_square;
}

template<class Mesh>
double SmootherT<Mesh>::LENGTH2D(double a, double b)
{
  // Local variables needed for macro definitions. 
  double MACRO_SQUARE_arg;

  if (a < ZERO) a = -a;
  if (b < ZERO) b = -b;
  if (a > b)    return a * sqrt((1.0) + SQUARE(b/a));
  if (b > ZERO) return b * sqrt(SQUARE(a/b) + (1.0));
  return ZERO;
}

template<class Mesh>
void SmootherT<Mesh>::svdcmp (double *a, int m, int n, int mp, int np, double *w, double *v, int *ierr)
{
  // Local variables needed for macro definitions.
  double MACRO_ABS_arg;
  int MACRO_IMIN_arg1, MACRO_IMIN_arg2;
  double MACRO_RMAX_arg1, MACRO_RMAX_arg2;
  double MACRO_SQUARE_arg;
  double MACRO_SIGN_arg;

/*
 * DIMENSION A(MP,NP), W(NP), V(NP,NP), RV1(NP)
 */
#define A(i,j) (a[(i)*np + (j)])
#define V(i,j) (v[(i)*np + (j)])
#define MAXITERS 30

  int svdcmp_fix = 0; // extern 
  int i, j, jj, k, l, its, nm, flag;
  double g, scale, anorm, s, f, h, tmp, c, y, z, x, *rv1=NULL, localTol;
  static char *name = "svdcmp";

/*
 *  Householder reduction to bidiagonal form.
 *
 *  There is a bug in the SGI compiler supplied with IRIX 5.3 that causes this
 *  alloca to generate code that generates a SIGTRAP signal.  SGI was not able
 *  to provide a fix for the problem at this level of the operating system so
 *  the alloca is replaced with malloc.
 */
  /*ALLOCA (rv1, REAL, n, name);*/
  MALLOC (rv1, double, n, name); //rv1[n]用来存放Householder reduction后的bidiagonal matrix的上次对角线元素吧
  g = 0.0;
  scale = 0.0;
  anorm = 0.0;
  for (i=0; i<n; i++)
  {
    l = i + 1;
    rv1[i] = scale * g;
    g = 0.0;
    s = 0.0;
    scale = 0.0;
    if (i < m)
    {
      for (k=i; k<m; k++)
        scale += ABS(A(k,i));
      if (scale != 0.0)
      {
        for (k=i; k<m; k++)
        {
          A(k,i) /= scale;
          s += SQUARE(A(k,i));
        }
        f = A(i,i);
        g = -SIGN(sqrt(s), f);
        h = f*g - s;
        A(i,i) = f - g;
        for (j=l; j<n; j++)
        {
          s = 0.0;
          for (k=i; k<m; k++)
            s += A(k,i) * A(k,j);
          f = s / h;
          for (k=i; k<m; k++)
            A(k,j) += f * A(k,i);
        }
        for (k=i; k<m; k++)
          A(k,i) *= scale;
      }
    }
    w[i] = scale * g;
    g = 0.0;
    s = 0.0;
    scale = 0.0;
    if (i < m && i+1 != n)
    {
      for (k=l; k<n; k++)
        scale += ABS(A(i,k));
      if (scale != 0.0)
      {
        for (k=l; k<n; k++)
        {
          A(i,k) /= scale;
          s += SQUARE(A(i,k));
        }
        f = A(i,l);
        g = -SIGN(sqrt(s), f);
        h = f*g - s;
        A(i,l) = f - g;
        for (k=l; k<n; k++)
          rv1[k] = A(i,k) / h;
        for (j=l; j<m; j++)
        {
          s = 0.0;
          for (k=l; k<n; k++)
            s += A(j,k) * A(i,k);
          for (k=l; k<n; k++)
            A(j,k) += s * rv1[k];
        }
        for (k=l; k<n; k++)
          A(i,k) *= scale;
      }
    }
    anorm = RMAX (anorm, (ABS(w[i]) + ABS(rv1[i])));
  }
  /* Needed if svdcmp_fix is TRUE. */
  localTol = anorm * 1.0e-6;
  if (localTol < ALMOST_ZERO) localTol = ALMOST_ZERO;

/*
 *  Accumulation of right-hand transformations.
 */
  for (i=n-1; i>=0; i--)
  {
    if (i+1 < n)
    {
      if (g != 0.0)
      {
        for (j=l; j<n; j++)
        {
          /*
           * Order is important in following statement to avoid possible
           * underflow.
           */
          tmp = A(i,j) / A(i,l);
          V(j,i) = tmp / g;
        }
        for (j=l; j<n; j++)
        {
          s = 0.0;
          for (k=l; k<n; k++)
            s += A(i,k) * V(k,j);
          for (k=l; k<n; k++)
            V(k,j) += s * V(k,i);
        }
      }
      for (j=l; j<n; j++)
      {
        V(i,j) = 0.0;
        V(j,i) = 0.0;
      }
    }
    V(i,i) = 1.0;
    g = rv1[i];
    l = i;
  }

/*
 *  Accumulation of left-hand transformations.
 */
  for (i=IMIN(m,n)-1; i>=0; i--)
  {
    l = i + 1;
    g = w[i];
    for (j=l; j<n; j++)
      A(i,j) = 0.0;
    if (g != 0.0)
    {
      g = 1.0 / g;
      for (j=l; j<n; j++)
      {
        s = 0.0;
        for (k=l; k<m; k++)
          s += A(k,i) * A(k,j);
        tmp = s / A(i,i);
        f = tmp * g;
        for (k=i; k<m; k++)
          A(k,j) += f * A(k,i);
      }
      for (j=i; j<m; j++)
        A(j,i) *= g;
    }
    else
    {
      for (j=i; j<m; j++)
        A(j,i) = 0.0;
    }
    A(i,i)++;
  }

/*
 *  Diagonalization of the bidiagonal form.
 *  Loop over singular values.
 */
  for (k=n-1; k>=0; k--)
  {
    /*
     * Loop over allowed iterations.
     */
    for (its=1; its<=MAXITERS; its++)
    {
      flag = 1;
      for (l=k; l>=0; l--)
      {
        nm = l - 1;
        if (!svdcmp_fix)
        {
          if ((ABS(rv1[l]) + anorm) == anorm) { flag = 0; break; }
          if ((ABS(w[nm]) + anorm) == anorm)  break;
        }
        else
        {
          if (TOL_EQ (rv1[l], 0.0, localTol)) { flag = 0; break; }
          if (TOL_EQ (w[nm],  0.0, localTol)) break;
        }
      }

      if (flag)
      {
        c = 0.0;
        s = 1.0;
        for (i=l; i<=k; i++)
        {
          f = s * rv1[i];
          rv1[i] *= c;
          if (!svdcmp_fix)
          {
            if ((ABS(f) + anorm) == anorm) break;
          }
          else
          {
            if (TOL_EQ (f, 0.0, localTol)) break;
          }
          g = w[i];
          h = LENGTH2D (f, g);
          w[i] = h;
          h = (1.0) / h;
          c = (g * h);
          s = -(f * h);
          for (j=0; j<m; j++)
          {
            y = A(j,nm);
            z = A(j,i);
            A(j,nm) = (y * c) + (z * s);
            A(j,i) = -(y * s) + (z * c);
          }
        }
      }

      z = w[k];
      if (l == k)
      {
        if (z < ZERO)
        {
          w[k] = -z;
          for (j=0; j<n; j++)
            V(j,k) = -V(j,k);
        }
        break;
      }
      if (its == MAXITERS)
      {
        *ierr = 2;
        goto FreeAndReturn;
      }
      x = w[l];
      nm = k - 1;
      y = w[nm];
      g = rv1[nm];
      h = rv1[k];
      f = ((y - z) * (y + z) + (g - h) * (g + h)) / ((2.0) * h * y);
      g = LENGTH2D (f, (1.0));
      f = ((x - z) * (x + z) + h * ((y / (f + SIGN (g, f))) - h)) / x;
/*
 *  Next qr transformation.
 */
      c = (1.0);
      s = (1.0);
      for (j=l; j<=nm; j++)
      {
        i = j + 1;
        g = rv1[i];
        y = w[i];
        h = s * g;
        g = c * g;
        z = LENGTH2D (f, h);
        rv1[j] = z;
        c = f / z;
        s = h / z;
        f =  (x * c) + (g * s);
        g = -(x * s) + (g * c);
        h = y * s;
        y *= c;
        for (jj=0; jj<n; jj++)
        {
          x = V(jj,j);
          z = V(jj,i);
          V(jj,j) =  (x * c) + (z * s);
          V(jj,i) = -(x * s) + (z * c);
        }
        z = LENGTH2D (f, h);
        w[j] = z;
        /*
         * Rotation can be arbitrary if z = 0.
         */
        if (z != 0.0)
        {
          c = f / z;
          s = h / z;
        }
        f =  (c * g) + (s * y);
        x = -(s * g) + (c * y);
        for (jj=0; jj<m; jj++)
        {
          y = A(jj,j);
          z = A(jj,i);
          A(jj,j) =  (y * c) + (z * s);
          A(jj,i) = -(y * s) + (z * c);
        }
      }
      rv1[l] = 0.0;
      rv1[k] = f;
      w[k] = x;
    }
  }

  *ierr = 0;

FreeAndReturn:
  if (rv1) 
	  free(rv1);
  return;

#undef A
#undef V
#undef MAXITERS
}

template<class Mesh>
void SmootherT<Mesh>::svbksb (double *u, double *w, double *v, int m, int n, int mp, int np, double *b, double *x)
{
 // DIMENSION U(MP,NP), W(NP), V(NP,NP), B(MP), X(NP), TMP(NP)

#define U(i,j) (u[(i)*np + (j)])
#define V(i,j) (v[(i)*np + (j)])

  int i, j, jj;
  double s, *tmp;
  static char *name = "svbksb";

  MALLOC (tmp, double, n, name);

  //  Calculate tran(u) b.
  for (j=0; j<n; j++)
  {
    s = ZERO;
    if (w[j] != ZERO)
    {
      for (i=0; i<m; i++)
        s += U(i,j) * b[i];
      s /= w[j];
    }
    tmp[j] = s;
  }


 //  Matrix multiply by v to get answer.

  for (j=0; j<n; j++)
  {
    s = ZERO;
    for (jj=0; jj<n; jj++)
      s += V(j,jj) * tmp[jj];
    x[j] = s;
  }

#undef U
#undef V
}

/**
// copied and modified from RemesherT<class Mesh>
template<class Mesh>
bool SmootherT<Mesh>::is_swap_legal(EdgeHandle _eh) const
{
 
}

template<class Mesh>
void SmootherT<Mesh>::edge_swap()
{

}
*/

template<class Mesh>
void SmootherT<Mesh>::smooth()
{
	MyMesh ref_mesh;
	ref_mesh = mesh_; // seems ok

	// setup and initialization
	const int max_global_iter_num = 10;
	const int max_smooth_iter_num = 50;
	const int max_min_func_iter_num = 50;
	float relax1 = 0.1;
	float relax2 = 0.1; // ?
	float mu = 0.01;
	float wl = 0.1;
	float wa = 0.9;
	float wmax, epsw;

	float epsres = 5.0e-1; 
	float rden, rnum, residual, residual0; // for residual
	float dist, dist_square, weight, weight_sum, fac;
	int step, iter;
	Point dc_vec, cg_vec, cur_pnt, vec1, vd1, delta_vec, normal;
	Point *initial_vertex_displacement  =  new Point[mesh_.n_vertices()];
	Point *vertex_displacement          =  new Point[mesh_.n_vertices()];
	Point *smooth_vertex_displacement   =  new Point[mesh_.n_vertices()];


	int i, num;
	bool ended;
	typename Mesh::VertexIter v_it;
	typename Mesh::VertexVertexIter vv_it;
	typename Mesh::VertexOHalfedgeIter voh_it;
	EdgeHandle   eh;
	VertexHandle vh;
	HalfedgeHandle heh;
	
	// evaluate initial cell normal and area
	
	// check for possible overlaps

	// evaluate vertex normal using singular value decomposition

	// finding discontinuity points

	// finding corners 

	// stepping toward the final surface
	for (step = 0; step < max_global_iter_num; step++)
	{
		// evaluate new cell normal and area
		mesh_.update_face_normals();

		// check for possible overlaps

		// evaluate guess vertex displacement
		rden = 0.0; // //如6748.6946, 所有节点的偏移向量长度平方的累加，下面作为指示器有用

		// 对所有节点循环,计算其偏移向量
		for (v_it = mesh_.vertices_begin(); v_it != mesh_.vertices_end(); ++v_it)
		{
			cg_vec = (Point)(0.0, 0.0, 0.0);
			dc_vec = (Point)(0.0, 0.0, 0.0);

			if (mesh_.property(node_type, v_it).is_boundary() || mesh_.property(node_type, v_it).is_corner())
				goto skip;
			else if (mesh_.property(node_type, v_it).is_ridge()) // && mesh_.property(node_type, v_it).is_corner()
			{
				num = 0;
				for (voh_it = mesh_.voh_iter(v_it); voh_it; ++voh_it)
				{
					if (ET_Ridge == mesh_.property(edge_type, mesh_.edge_handle(voh_it)))
					{
						num++;
						cg_vec += mesh_.point(mesh_.to_vertex_handle(voh_it));
					}
				}

				if (2 != num)
				{
					cerr << "Error in function smooth: the number of adjacent ridge edges of a ridge node is not 2!";
					// todo: use UI to inform users

				}

				// cg_vec /= num;
			}
			else if (mesh_.property(node_type, v_it).is_flat()) // only "else" should be ok
			{
				for (voh_it = mesh_.voh_iter(v_it), num = 0; voh_it; ++voh_it, ++num)
					cg_vec += mesh_.point(mesh_.to_vertex_handle(voh_it));
			}

			cg_vec /= (float)num;
			dc_vec = cg_vec - mesh_.point(v_it);

		skip:
			vertex_displacement[v_it.handle().idx()] = dc_vec; // is here idx() in squential order ?!
			rden += dc_vec.sqrnorm();
			
			if (0 == step)
				initial_vertex_displacement[v_it.handle().idx()] = vertex_displacement[v_it.handle().idx()];
		}

		// evaluate vertex normal using single value decomposition, is it ok not to use it ?
		mesh_.update_vertex_normals();
		
		// deal with points on edges first (ridge nodes)
		ended = false;
		for (iter = 0; iter < max_smooth_iter_num && !ended; iter++) // // 等于50，50次循环, 每一个step中都这样循环一遍
		{
			rnum = 0.0;

			// 对每个point on edges节点，计算其新的偏移向量，即其新的位置
			for (v_it = mesh_.vertices_begin(); v_it != mesh_.vertices_end(); ++v_it)
			{
				dist_square = vertex_displacement[v_it.handle().idx()].sqrnorm();
				if (mesh_.property(node_type, v_it).is_ridge() && dist_square > 0.0)
				{
					weight_sum = 0.0;

					cur_pnt = mesh_.point(v_it);
					vd1 = (Point)(0.0, 0.0, 0.0);

					num = 0;
					for (voh_it = mesh_.voh_iter(v_it); voh_it; ++voh_it)
					{
						eh = mesh_.edge_handle(voh_it);
						if (ET_Ridge == mesh_.property(edge_type, eh))
						{
							++num;

							vh = mesh_.to_vertex_handle(voh_it);
							if (mesh_.property(node_type, vh).is_ridge() || mesh_.property(node_type, vh).is_corner())
							{
								delta_vec = mesh_.point(vh) - cur_pnt;
								weight = 1.0 / (delta_vec.norm() + 1.0e-20);
								weight_sum += weight;

								delta_vec = vertex_displacement[vh.idx()];
								vd1 += weight*delta_vec;
							}
						}
					}

					if (2 != num)
					{
						cerr << "Error in function smooth: the number of adjacent ridge edges is not 2!";
						// todo: to inform users this situation

					}

					fac = 1.0 / (weight_sum + 1.0e-20);
					vec1 = vd1 * fac;

					delta_vec = vec1 - vertex_displacement[v_it.handle().idx()];
					rnum += delta_vec.sqrnorm();

					delta_vec = vec1 * relax1 + vertex_displacement[v_it.handle().idx()] * (1.0 - relax1);
					vertex_displacement[v_it.handle().idx()] = delta_vec;
				}

			} // end of "for (v_it = mesh_.vertices_begin(); v_it != mesh_.vertices_end(); ++v_it)"

			residual = sqrt(rnum / rden);
			if (residual < epsres)
				ended = true;

		} // end of computing displacements for ridge nodes, "for (iter = 0; iter < max_smooth_iter_num && !ended; iter++)"

		// deal with continuous points 
		ended = false;
		for (iter = 0; iter < max_smooth_iter_num && !ended; iter++) // // 等于50，50次循环, 每一个step中都这样循环一遍
		{
			rnum = 0.0;

			// 对每个point on edges节点，计算其新的偏移向量，即其新的位置
			for (v_it = mesh_.vertices_begin(); v_it != mesh_.vertices_end(); ++v_it)
			{
				if (mesh_.property(node_type, v_it).is_flat())
				{
					weight_sum = 0.0;
					cur_pnt = mesh_.point(v_it);
					vd1 = (Point)(0.0, 0.0, 0.0);

					for (voh_it = mesh_.voh_iter(v_it); voh_it; ++voh_it)
					{
						eh = mesh_.edge_handle(voh_it);
						vh = mesh_.to_vertex_handle(voh_it);

						delta_vec = mesh_.point(vh) - cur_pnt;
						weight = 1.0 / (delta_vec.norm() + 1.0e-20);
						weight_sum += weight;

						delta_vec = vertex_displacement[vh.idx()];
						vd1 += weight*delta_vec;
					}

					fac = 1.0 / (weight_sum + 1.0e-20);
					vec1 = vd1 * fac;

					delta_vec = vec1 - vertex_displacement[v_it.handle().idx()];
					rnum += delta_vec.sqrnorm();

					delta_vec = vec1 * relax1 + vertex_displacement[v_it.handle().idx()] * (1.0 - relax1);
					vertex_displacement[v_it.handle().idx()] = delta_vec;
				}

			} // end of "for (v_it = mesh_.vertices_begin(); v_it != mesh_.vertices_end(); ++v_it)"

			//residual check
			residual = sqrt(rnum / rden);
			if (residual < epsres)
				ended = true;

		} // end of computing displacements for ridge nodes, "for (iter = 0; iter < max_smooth_iter_num && !ended; iter++)"

		// copy and save, 当上面两种类型节点都处理以后(经过了50次循环后的结果)，得到所有节点新的偏移向量
		for (i = 0; i < mesh_.n_vertices(); ++i)
			smooth_vertex_displacement[i] = vertex_displacement[i];


		// MINIMIZING FUNCTIONALS
		// todo: to be continued
		if (2 != smmethod_)
			goto skip3;

		float reducfac = 0.50;
        // relax    = relax_functional; relax2
		float areafac, fac;
		float rho, length2;

        int nreduc   = 0;
        int nincre   = 0;
        int maxreduc = 5;
        int maxincre = 1;
		int k, valence, ierr;

		double daa[9], dbb[3], c[3][3];
		double w[3], v[3][3];
		double bb[3], xx[3];

		Point p0_old, p2_old, p1_new, p2_new, p_res;
		

minimize:
		ended    = false;
        float resold   = 1.0;
        residual = 0.0;

		for (iter = 0; iter < max_min_func_iter_num && !ended; ++iter) // 外层50次循环，中间可根据情况中断
		{
			rnum = 0.0;

			for (v_it = mesh_.vertices_begin(); v_it != mesh_.vertices_end(); ++v_it) // 对所有节点循环
			{
				if (!mesh_.property(node_type, v_it).is_flat()) // 只处理flat node
					continue;

				for (i = 0; i < 9; i++)
					daa[i] = 0.0;
				for (i = 0; i < 3; i++)
					dbb[i] = 0.0;

				valence = mesh_.valence(v_it);

				for (voh_it = mesh_.voh_iter(v_it); voh_it; ++voh_it)
				{
					heh = mesh_.next_halfedge_handle(voh_it);
					vh = mesh_.to_vertex_handle(heh);

					p0_old = mesh_.point(v_it);
					p2_old = mesh_.point(mesh_.to_vertex_handle(voh_it));
					p1_new = mesh_.point(vh) + vertex_displacement[vh.idx()];
					p2_new = p2_old + vertex_displacement[mesh_.to_vertex_handle(voh_it).idx()];
					delta_vec = p1_new - p2_new;

					// matrix for area functional
					areafac = wa / (float)mesh_.calc_sector_area(voh_it);
					c[0][0] = delta_vec[1]*delta_vec[1] + delta_vec[2]*delta_vec[2];
					c[0][1] = -delta_vec[0]*delta_vec[1];
					c[0][2] = -delta_vec[0]*delta_vec[2];
					c[1][0] = -delta_vec[1]*delta_vec[0];
					c[1][1] = delta_vec[2]*delta_vec[2] + delta_vec[0]*delta_vec[0];
					c[1][2] = -delta_vec[1]*delta_vec[2];
					c[2][0] = -delta_vec[2]*delta_vec[0];
					c[2][1] = -delta_vec[2]*delta_vec[1];
					c[2][2] = delta_vec[0]*delta_vec[0] + delta_vec[1]*delta_vec[1];

					daa[0] += areafac * c[0][0];
					daa[1] += areafac * c[0][1];
					daa[2] += areafac * c[0][2];
					daa[3] += areafac * c[1][0];
					daa[4] += areafac * c[1][1];
					daa[5] += areafac * c[1][2];
					daa[6] += areafac * c[2][0];
					daa[7] += areafac * c[2][1];
					daa[8] += areafac * c[2][2];

					dbb[0] += areafac*(c[0][0]*p2_new[0] + c[0][1]*p2_new[1] + c[0][2]*p2_new[2]);
					dbb[1] += areafac*(c[1][0]*p2_new[0] + c[1][1]*p2_new[1] + c[1][2]*p2_new[2]);
					dbb[2] += areafac*(c[2][0]*p2_new[0] + c[2][1]*p2_new[1] + c[2][2]*p2_new[2]);

					// matrix for length functional
					fac = wl / valence;
					daa[0] += 1.0*fac;
					daa[4] += 1.0*fac;
					daa[8] += 1.0*fac;
					dbb[0] += 1.0*p2_new[0];
					dbb[1] += 1.0*p2_new[1];
					dbb[2] += 1.0*p2_new[2];
				}

				// modification for solving for displacements
				dbb[0] = dbb[0] - (daa[0]*p0_old[0] + daa[1]*p0_old[1] + daa[2]*p0_old[2]);
				dbb[1] = dbb[1] - (daa[3]*p0_old[0] + daa[4]*p0_old[1] + daa[5]*p0_old[2]);
				dbb[2] = dbb[2] - (daa[6]*p0_old[0] + daa[7]*p0_old[1] + daa[8]*p0_old[2]);

				// constraining solution to be on surface 
				// using a quadratic penalty approach
				rho = 1.0e+2;
				delta_vec = vertex_displacement[v_it.handle().idx()];
				length2 = delta_vec.sqrnorm();
				if (length2 > 0.0)
				{
					daa[0] += rho*delta_vec[0]*delta_vec[0];
					daa[1] += rho*delta_vec[0]*delta_vec[1];
					daa[2] += rho*delta_vec[0]*delta_vec[2];
					daa[3] += rho*delta_vec[1]*delta_vec[0];
					daa[4] += rho*delta_vec[1]*delta_vec[1];
					daa[5] += rho*delta_vec[1]*delta_vec[2];
					daa[6] += rho*delta_vec[2]*delta_vec[0];
					daa[7] += rho*delta_vec[2]*delta_vec[1];
					daa[8] += rho*delta_vec[2]*delta_vec[2];
					dbb[0] += rho*length2*delta_vec[0];
					dbb[1] += rho*length2*delta_vec[1];
					dbb[2] += rho*length2*delta_vec[2];
				}
				else 
				{
					normal = mesh_.normal(v_it);
					daa[0] += rho * normal[0]*normal[0];
					daa[1] += rho * normal[0]*normal[1];
					daa[2] += rho * normal[0]*normal[2];
					daa[3] += rho * normal[1]*normal[0];
					daa[4] += rho * normal[1]*normal[1];
					daa[5] += rho * normal[1]*normal[2];
					daa[6] += rho * normal[2]*normal[0];
					daa[7] += rho * normal[2]*normal[1];
					daa[8] += rho * normal[2]*normal[2];
				}

				// from double to single precision

				// solve, to be continued
				ierr = 0;
				svdcmp(daa, 3, 3, 3, 3, w, (double*)v, &ierr);
				if (ierr != 0) 
				{
					// fprintf(STDOUT,"error in sv decomposition for vertex=%5d\n",vertex);
					cerr << "error in sv decomposition" << endl;
					// todo, to notify user this bad situation
					return;
				}

				wmax=-1.0e+30;
				for (k=0;k<3;k++)  
					if (w[k]>wmax) 
						wmax=w[k];
                
                epsw=wmax * 1.0e-4;

				double MACRO_ABS_arg; // temprorily used
                for (k = 0; k < 3; k++)  //同前处理，<<nr>>有说明
					if (ABS(w[k]) < epsw) 
						w[k]=0.0;
                svbksb(daa, w, (double*)v, 3, 3, 3, 3, bb, xx);

                p_res[0] = xx[0];
				p_res[1] = xx[1];
				p_res[2] = xx[2];

				delta_vec = p_res - vertex_displacement[v_it.handle().idx()];

				rnum += delta_vec.sqrnorm();

				delta_vec = p_res*relax2 + vertex_displacement[v_it.handle().idx()]*(1.0-relax2);

				vertex_displacement[v_it.handle().idx()] = delta_vec;

			} // 内层对所有节点循环

			residual = sqrt(rnum/rden);
			if (iter == 0) 
				residual0 = residual;

			// check if it is converging
			if (residual>resold) // // resold = 1.0
			{ 
				nincre +=1;
				if (nincre>maxincre) 
				{
					for (v_it = mesh_.vertices_begin(); v_it != mesh_.vertices_end(); ++v_it) 
						vertex_displacement[v_it.handle().idx()] = smooth_vertex_displacement[v_it.handle().idx()];
					
					if (nreduc<maxreduc) 
					{
						wa = wa * reducfac;
						wl = 1.0 - wa;
						nreduc += 1;
						nincre = 0;
						goto minimize;
					} 
					else 
					{
						/**
						fprintf(STDOUT,"functional minimization is diverging\n");
						fprintf(STDOUT,"surface restored from method 1\n");
						fflush(STDOUT);
						*/
						// notice user this situation

						ended = true;
					}
				}
			} 
			else 
				nincre = 0;

			resold = residual;
			if (residual<epsres) 
				ended = true; //终止外层的50次循环
      
		} // 外层50次循环


		// update surface points, outside the max_smooth_iter_num, inside the max_global_iter_num
	skip3:
		for (v_it = mesh_.vertices_begin(); v_it != mesh_.vertices_end(); ++v_it)
			mesh_.point(v_it) += vertex_displacement[v_it.handle().idx()];
	
		// project points onto original surface
		// iterate over all vertices
		for (i = 0; i < mesh_.n_vertices(); ++i) 
		{
			if (mesh_.property(node_type, mesh_.vertex_handle(i)).is_boundary() 
					|| mesh_.property(node_type, mesh_.vertex_handle(i)).is_corner())
				continue;

			Point adj_pnt, old_pnt = ref_mesh.point(ref_mesh.vertex_handle(i)), 
				  new_pnt = mesh_.point(mesh_.vertex_handle(i)); // 当前节点新的位置向量
			Point projected_pnt, tmp_point;
			bool projected = false;
			float tmp_dist = 1.0e20;
			
			if (mesh_.property(node_type, mesh_.vertex_handle(i)).is_ridge() && !mesh_.property(node_type, mesh_.vertex_handle(i)).is_corner())
			{
				//projected = false;
				//tmp_dist = 1.0e20;
				//old_pnt = ref_mesh.point(ref_mesh.vertex_handle(i));

				// It is assumed that position adjustment is such small
                // that the new location of a vertex is near its original
				num = 0;
				for (voh_it = ref_mesh.voh_iter(ref_mesh.vertex_handle(i)); voh_it; ++voh_it)
				{
					eh = ref_mesh.edge_handle(voh_it);
					if (ET_Ridge == ref_mesh.property(edge_type, eh))
					{
						++num;

						vh = ref_mesh.to_vertex_handle(voh_it);
						adj_pnt = ref_mesh.point(vh);
						dist_square = closest_to_line_segment3d(new_pnt, old_pnt, adj_pnt, projected_pnt);
						dist = sqrt(dist_square);
						if (dist < tmp_dist)
						{
							projected = true;
							tmp_dist = dist;
							tmp_point = projected_pnt;
						}
					}
				}

				if (2 != num)
				{
					cerr << "Error in function smooth: the number of adjacent ridge edges is not 2!";
					// todo: to inform the user this situation
				}
			}
			else if (mesh_.property(node_type, mesh_.vertex_handle(i)).is_flat())
			{
				typename Mesh::VertexFaceIter vf_it;
				Point tri_pnt[3];
				typename Mesh::FaceVertexIter fv_it;

				for (vf_it = ref_mesh.vf_iter(ref_mesh.vertex_handle(i)); vf_it; ++vf_it)
				{
					fv_it = ref_mesh.fv_iter(vf_it.handle());
					tri_pnt[0] = ref_mesh.point(fv_it.handle());
					++fv_it;
					tri_pnt[1] = ref_mesh.point(fv_it.handle());
					++fv_it;
					tri_pnt[2] = ref_mesh.point(fv_it.handle());
					
					dist_square = closest_to_triangle3d(new_pnt, tri_pnt, projected_pnt);
					dist = sqrt(dist_square);
					if (dist < tmp_dist)
					{
						projected = true;
						tmp_dist = dist;
						tmp_point = projected_pnt;
					}
				}

				if (projected)
					mesh_.point(mesh_.vertex_handle(i)) = tmp_point;
			}

		} // end of "project points onto original surface", "for (i = 0; i < mesh_.n_vertices(); ++i)"

		mesh_.update_face_normals();
		mesh_.update_vertex_normals();

	} // end of global iteration "for (step = 0; step < max_global_iter_num; step++)"


	// free all memory 

	// copy surfVerts to coordsurf, and free memory

}

#endif 