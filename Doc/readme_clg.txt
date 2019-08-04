20070515-2255: 根据指定密度条件粗化细化后进行优化，包括smoothing和edge swap两
种操作，这里的edge swap将节点的度值作为主要的优化目标。最后还有一个
sliver removal操作，以消除极差单元。由于在测试f22nobox例子时，出现一些问题，
暂时修改了off文件的输出函数。

20070503-1024: 将mtoolsurf中的光滑化方法2移植过来，借用了mtoolsurf中的很多代码，
打破了MeshTool原有的封装等OO风格，变的比较难看。接下来，
1、MeshTool中的ba3与mtoolsurf中的density.dat密度处理及计算方式不同，两者的拓扑
变换的计算标准(对节点还是对边进行计算)及所执行的拓扑变换也不相同，导致结果不同。
mtoolsurf中除了密度变化率较大的区域中，网格节点的度值和网格质量有所欠缺，其他区域
表现良好。而MeshTool中网格节点度值整体上有所欠缺，不均衡，总是有的偏大有的偏小，
特别是特征线、边界线上的节点的度值不甚理想，导致光滑化效果有限，并且密度的处理方
式有待进一步改进，拓扑变换计算标准及操作也要考虑是否借用mtoolsurf中的方法。
EdgeSwap的处理方式也要改进。


20070427-2322: 将mtoolsurf中的光滑化方法1移植过来，方法2待移植。实现了
edge swap操作，并将它分别放在粗化细化后面。

20070419-2250: 读入背景网格和密度控制源的ba3文件，引入用户密度机制，
但remesh后的结果不是很理想，存在的可能问题，
1、网格过渡有待改进，需进行密度光滑化操作，这样就需要把原始网格作
为reference mesh, 有很多处理要发生变动。
2、有些区域(如长方体的面)的网格显得很稀疏，经常是一个cornerNd跟很多
ridgeNd相连，中间无其他节点和单元。这个难道是用户密度本来就是如此，还是
拓扑变换时各种约束所致？要先把这个问题搞清楚！

20070418-2219: 重新改写is_collapse_ok(HalfedgeHandle)为
is_collapse_legal(HalfedgeHandle), 在edge collapse时，
检查面的法向量的变化情况，以避免单元自交。仅仅及时更新单元
和节点的法向量不能避免单元自交。接下来，
1、背景网格和源等用户密度机制引入；
2、smoothing&swapping&smoothing&"薄元"消除。
3、edge collapse和edge split合在一个循环中可行否？
4、初始网格作为reference mesh处理，节点上有密度信息。
5、投影到插值曲线上
6、vertex split, face split

20070417-2331: 修正了一个重要bug。原来用EdgeIter对边进行循环，但当拓扑
变换后并进行的实际的元素增减时，该EdgeIter很可能变成无效！
edge collapse时只进行deleted标记，并更新元素拓扑连接关系，所以deleted
的元素不会累加起来对后面的拓扑变换有影响。但garbage_collection()则进行实际的
元素删除，要保证它的位置摆放正确；(edge) split 也进行实际了元素增减，
所以对它不能用EdgeIter, 而改用index来进行循环，因为index在一次循环中
保持不变(这是因为元素是用push_back()加在vector最后面的)。存在的问题，
edge collapse时会有自交单元形成，待改正。

20070416-2350: 实现了remesh算法的模板类，由于要在拓扑变换(暂时是edge split)
时设置新元素的类型标志(新元素的类型不言自明)，
所以重写了split(EdgeHandle, VertexHandle)函数。
另外，改正了计算边界点边界角的方法，返回[0.0, pi]之间的小角，而不管方向。
程序仍有很多问题，算法本身很可能有错误，时空效率有问题，有待进一步改进。

20070407-1106: 将Feature detection等数据操作算法从MeshViewerWidget移出来，
并封装成独立的模板类。注意，在VS2005中，模板类的虚拟成员函数的定义要跟类
定义放在同一个文件中，被该虚拟成员函数调用的其他一般成员函数也一样，否则
会出现“无法解析的外部符号”的链接错误，这应该是编译器的缘故，linux下应该
不是这样的。

20070405-2240: 在"dynamic properties"机制基础上，实现了
Feature Detection Basic Algorithm, 实现了Feature View中的功能。

20070403-2308: 暂时删除了"Using traits to extend the mesh"相关代码，
采用"dynamic properties"机制来实现存取元素(边、节点)的特征类型信息。
因为OpenMesh1.9.x不支持mesh entity traits, can only use dynamic 
property to extend the mesh entity.
now so far so good.

20070403-1706: 正在实现Feature Detection部分内容，设计了界面，编写了部分
代码，出现的一个问题是，把元素(边、节点)的特征类型信息作为
"static configuration"存储在相关元素中的，即采用了
"Using traits to extend the mesh", 但在编译时没通过，以OpenMesh自带
的例子说明如下。接下来，要么解决这个问题(等作者回复)，要么采用
"dynamic properties"机制来实现。先备份一下。

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
error C2039: “set_cog”: is not the member of "OpenMesh::ArrayItems::Vertex"
error C2039: “cog”: is not the member of "OpenMesh::ArrayItems::Vertex”



20070327-1648: 实现了Quick Set Viewport功能，Objects Show功能中，除了Inertia
和EditLitDir外都已实现，这两个功能以后看情况再去实现。

20070320-2312: 将netgen中用多个矩阵(如lookatmat, transmat, rotmat, 
transformationmat等)分别存储平移、旋转等变换成功实现。这样下面可以
继续实现setViewport、画坐标系等功能了。

20070320-1031: 这个作为version1.0, 不再删除它，接下来将做大的变动，要引入
其他matrix，如lookatmatrix, rotatematrix, translatematrix, centerscalematrix
transformationmatrix, projectionmatrix等


20070320-0954: 在原来基础上，实现了两种投影方式的切换，并且其他功能照样完好。
主要是将非虚函数void GLWidgetCenter::paintGL()中前面那段代码放到了虚拟继承
函数void MeshViewerWidget::draw_scene(void)中去，并在前面调用
update_projection_matrix()函数，如下。
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
这样，当通过控制面板修改投影方式并通知重画时，可实现投影方式（矩阵）的改变。
或者如下也可以。一般情况下投影方式初始化时指定后将不再改变。
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

另外，通过鼠标中键的缩放操作，原来在透视投影方式下是通过沿z轴平移来实现的，
现在在两种投影方式下，在平移到原点后，统一用
  glScalef(1.0 + _scale, 1.0 + _scale, 1.0 + _scale);
其中_scale为 (float)dy / (float)h, 参数中的1.0代表原来的缩放大小。 



20070319: 实现了Object Show中以下功能，Vertex, Edge, Face, Light, ShadeSmooth,
ColorMaterial, BBox. 投影采用perspective方式，这样模型的缩放可通过向z轴平移来
实现，若是用平行投影则不行！Perspective Check Box的功能没能实现，暂时还不知道
如何实现投影方式的切换，update_projection_matrix等都试过了，行不通，鼠标操作
（旋转、平移等）不行了。接下来改成在平行投影方式下处理。



20070308: 使用OpenMesh的模板类，由于Qt的消息机制一定要有Q_OBJECT支持，而Q_OBJECT不支持
模板类，所以相应的消息机制实现起来比较麻烦，处理办法如下。
本程序实现了方法1，结果很理想，模型视图效果也很理想，原来没有执行
compute_bbox()和set_scene_pos()方法，没有进行归一化处理，模型视图效果很差，像是没
没经过变换而直接显示物体坐标得到的。

1、原来的模板类声明如下，
template <class M>
class MeshViewerWidgetT : public GLWidgetCenter 
{
    //没有Q_OBJECT, 不能跟它进行通信
    ......

private:
    const Mesh*            mesh_;
}
将模板类改成非模板类，其中原来的模板参数用一个具体的Mesh类代入。
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

2、由模板类实例化所得到的具体类基础上再进行继承，并带有Q_OBJECT，使之具有通信的能力。