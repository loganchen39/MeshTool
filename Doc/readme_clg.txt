20070515-2255: ����ָ���ܶ������ֻ�ϸ��������Ż�������smoothing��edge swap��
�ֲ����������edge swap���ڵ�Ķ�ֵ��Ϊ��Ҫ���Ż�Ŀ�ꡣ�����һ��
sliver removal���������������Ԫ�������ڲ���f22nobox����ʱ������һЩ���⣬
��ʱ�޸���off�ļ������������

20070503-1024: ��mtoolsurf�еĹ⻬������2��ֲ������������mtoolsurf�еĺܶ���룬
������MeshToolԭ�еķ�װ��OO��񣬱�ıȽ��ѿ�����������
1��MeshTool�е�ba3��mtoolsurf�е�density.dat�ܶȴ������㷽ʽ��ͬ�����ߵ�����
�任�ļ����׼(�Խڵ㻹�ǶԱ߽��м���)����ִ�е����˱任Ҳ����ͬ�����½����ͬ��
mtoolsurf�г����ܶȱ仯�ʽϴ�������У�����ڵ�Ķ�ֵ��������������Ƿȱ����������
�������á���MeshTool������ڵ��ֵ����������Ƿȱ�������⣬�����е�ƫ���е�ƫС��
�ر��������ߡ��߽����ϵĽڵ�Ķ�ֵ�������룬���¹⻬��Ч�����ޣ������ܶȵĴ���
ʽ�д���һ���Ľ������˱任�����׼������ҲҪ�����Ƿ����mtoolsurf�еķ�����
EdgeSwap�Ĵ���ʽҲҪ�Ľ���


20070427-2322: ��mtoolsurf�еĹ⻬������1��ֲ����������2����ֲ��ʵ����
edge swap�������������ֱ���ڴֻ�ϸ�����档

20070419-2250: ���뱳��������ܶȿ���Դ��ba3�ļ��������û��ܶȻ��ƣ�
��remesh��Ľ�����Ǻ����룬���ڵĿ������⣬
1����������д��Ľ���������ܶȹ⻬����������������Ҫ��ԭʼ������
Ϊreference mesh, �кܶദ��Ҫ�����䶯��
2����Щ����(�糤�������)�������Եú�ϡ�裬������һ��cornerNd���ܶ�
ridgeNd�������м��������ڵ�͵�Ԫ������ѵ����û��ܶȱ���������ˣ�����
���˱任ʱ����Լ�����£�Ҫ�Ȱ��������������

20070418-2219: ���¸�дis_collapse_ok(HalfedgeHandle)Ϊ
is_collapse_legal(HalfedgeHandle), ��edge collapseʱ��
�����ķ������ı仯������Ա��ⵥԪ�Խ���������ʱ���µ�Ԫ
�ͽڵ�ķ��������ܱ��ⵥԪ�Խ�����������
1�����������Դ���û��ܶȻ������룻
2��smoothing&swapping&smoothing&"��Ԫ"������
3��edge collapse��edge split����һ��ѭ���п��з�
4����ʼ������Ϊreference mesh�����ڵ������ܶ���Ϣ��
5��ͶӰ����ֵ������
6��vertex split, face split

20070417-2331: ������һ����Ҫbug��ԭ����EdgeIter�Ա߽���ѭ������������
�任�󲢽��е�ʵ�ʵ�Ԫ������ʱ����EdgeIter�ܿ��ܱ����Ч��
edge collapseʱֻ����deleted��ǣ�������Ԫ���������ӹ�ϵ������deleted
��Ԫ�ز����ۼ������Ժ�������˱任��Ӱ�졣��garbage_collection()�����ʵ�ʵ�
Ԫ��ɾ����Ҫ��֤����λ�ðڷ���ȷ��(edge) split Ҳ����ʵ����Ԫ��������
���Զ���������EdgeIter, ������index������ѭ������Ϊindex��һ��ѭ����
���ֲ���(������ΪԪ������push_back()����vector������)�����ڵ����⣬
edge collapseʱ�����Խ���Ԫ�γɣ���������

20070416-2350: ʵ����remesh�㷨��ģ���࣬����Ҫ�����˱任(��ʱ��edge split)
ʱ������Ԫ�ص����ͱ�־(��Ԫ�ص����Ͳ�������)��
������д��split(EdgeHandle, VertexHandle)������
���⣬�����˼���߽��߽�ǵķ���������[0.0, pi]֮���С�ǣ������ܷ���
�������кܶ����⣬�㷨����ܿ����д���ʱ��Ч�������⣬�д���һ���Ľ���

20070407-1106: ��Feature detection�����ݲ����㷨��MeshViewerWidget�Ƴ�����
����װ�ɶ�����ģ���ࡣע�⣬��VS2005�У�ģ����������Ա�����Ķ���Ҫ����
�������ͬһ���ļ��У����������Ա�������õ�����һ���Ա����Ҳһ��������
����֡��޷��������ⲿ���š������Ӵ�����Ӧ���Ǳ�������Ե�ʣ�linux��Ӧ��
���������ġ�

20070405-2240: ��"dynamic properties"���ƻ����ϣ�ʵ����
Feature Detection Basic Algorithm, ʵ����Feature View�еĹ��ܡ�

20070403-2308: ��ʱɾ����"Using traits to extend the mesh"��ش��룬
����"dynamic properties"������ʵ�ִ�ȡԪ��(�ߡ��ڵ�)������������Ϣ��
��ΪOpenMesh1.9.x��֧��mesh entity traits, can only use dynamic 
property to extend the mesh entity.
now so far so good.

20070403-1706: ����ʵ��Feature Detection�������ݣ�����˽��棬��д�˲���
���룬���ֵ�һ�������ǣ���Ԫ��(�ߡ��ڵ�)������������Ϣ��Ϊ
"static configuration"�洢�����Ԫ���еģ���������
"Using traits to extend the mesh", ���ڱ���ʱûͨ������OpenMesh�Դ�
������˵�����¡���������Ҫô����������(�����߻ظ�)��Ҫô����
"dynamic properties"������ʵ�֡��ȱ���һ�¡�

struct MyTraits : public OpenMesh::DefaultTraits
{
  // store barycenter of neighbors in this member
  VertexTraits
  {
  private:
    Point  cog_;
  public:

    VertexT() : cog_( Point(0.0f, 0.0f, 0.0f ) ) { }

    const Point& cog() const { return cog_; }
    void set_cog(const Point& _p) { cog_ = _p; }
  };
};

compile error:
error C2039: ��set_cog��: is not the member of "OpenMesh::ArrayItems::Vertex"
error C2039: ��cog��: is not the member of "OpenMesh::ArrayItems::Vertex��



20070327-1648: ʵ����Quick Set Viewport���ܣ�Objects Show�����У�����Inertia
��EditLitDir�ⶼ��ʵ�֣������������Ժ������ȥʵ�֡�

20070320-2312: ��netgen���ö������(��lookatmat, transmat, rotmat, 
transformationmat��)�ֱ�洢ƽ�ơ���ת�ȱ任�ɹ�ʵ�֡������������
����ʵ��setViewport��������ϵ�ȹ����ˡ�

20070320-1031: �����Ϊversion1.0, ����ɾ������������������ı䶯��Ҫ����
����matrix����lookatmatrix, rotatematrix, translatematrix, centerscalematrix
transformationmatrix, projectionmatrix��


20070320-0954: ��ԭ�������ϣ�ʵ��������ͶӰ��ʽ���л���������������������á�
��Ҫ�ǽ����麯��void GLWidgetCenter::paintGL()��ǰ���Ƕδ���ŵ�������̳�
����void MeshViewerWidget::draw_scene(void)��ȥ������ǰ�����
update_projection_matrix()���������¡�
void GLWidgetCenter::paintGL()
{
  /**
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode( GL_PROJECTION );
  glLoadMatrixd( projection_matrix_ );
  glMatrixMode( GL_MODELVIEW );
  glLoadMatrixd( modelview_matrix_ );
  */

  draw_scene();
}
void MeshViewerWidget::draw_scene(void)
{
    update_projection_matrix();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadMatrixd( projection_matrix_ );
    glMatrixMode( GL_MODELVIEW );
    glLoadMatrixd( modelview_matrix_ );

    draw_objects();
}
��������ͨ����������޸�ͶӰ��ʽ��֪ͨ�ػ�ʱ����ʵ��ͶӰ��ʽ�����󣩵ĸı䡣
��������Ҳ���ԡ�һ�������ͶӰ��ʽ��ʼ��ʱָ���󽫲��ٸı䡣
void GLWidgetCenter::paintGL()
{
  update_projection_matrix();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode( GL_PROJECTION );
  glLoadMatrixd( projection_matrix_ );
  glMatrixMode( GL_MODELVIEW );
  glLoadMatrixd( modelview_matrix_ );

  draw_scene();
}
void MeshViewerWidget::draw_scene(void)
{
    draw_objects();
}

���⣬ͨ������м������Ų�����ԭ����͸��ͶӰ��ʽ����ͨ����z��ƽ����ʵ�ֵģ�
����������ͶӰ��ʽ�£���ƽ�Ƶ�ԭ���ͳһ��
  glScalef(1.0 + _scale, 1.0 + _scale, 1.0 + _scale);
����_scaleΪ (float)dy / (float)h, �����е�1.0����ԭ�������Ŵ�С�� 



20070319: ʵ����Object Show�����¹��ܣ�Vertex, Edge, Face, Light, ShadeSmooth,
ColorMaterial, BBox. ͶӰ����perspective��ʽ������ģ�͵����ſ�ͨ����z��ƽ����
ʵ�֣�������ƽ��ͶӰ���У�Perspective Check Box�Ĺ���û��ʵ�֣���ʱ����֪��
���ʵ��ͶӰ��ʽ���л���update_projection_matrix�ȶ��Թ��ˣ��в�ͨ��������
����ת��ƽ�Ƶȣ������ˡ��������ĳ���ƽ��ͶӰ��ʽ�´���



20070308: ʹ��OpenMesh��ģ���࣬����Qt����Ϣ����һ��Ҫ��Q_OBJECT֧�֣���Q_OBJECT��֧��
ģ���࣬������Ӧ����Ϣ����ʵ�������Ƚ��鷳������취���¡�
������ʵ���˷���1����������룬ģ����ͼЧ��Ҳ�����룬ԭ��û��ִ��
compute_bbox()��set_scene_pos()������û�н��й�һ������ģ����ͼЧ���ܲ����û
û�����任��ֱ����ʾ��������õ��ġ�

1��ԭ����ģ�����������£�
template <class M>
class MeshViewerWidgetT : public GLWidgetCenter 
{
    //û��Q_OBJECT, ���ܸ�������ͨ��
    ......

private:
    const Mesh*            mesh_;
}
��ģ����ĳɷ�ģ���࣬����ԭ����ģ�������һ�������Mesh����롣
class MeshViewerWidget : public GLWidgetCenter
{
    Q_OBJECT

public:
    ......

public slots:
    void on_mesh_loaded(void);

private:
    MyMesh*                mesh_;
    ......
}

2����ģ����ʵ�������õ��ľ�����������ٽ��м̳У�������Q_OBJECT��ʹ֮����ͨ�ŵ�������