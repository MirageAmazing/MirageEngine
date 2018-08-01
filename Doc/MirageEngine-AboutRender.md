> 欲穷千里目，更上一层楼
# About Render
渲染系统的设计是MirageEngine各个系统中最为复杂的部分，渲染管线，渲染资源，渲染效率，跨平台特性，高中低质量兼容，开发性（最新的启发SRP）等等都要权衡考虑。
## 渲染资源
vertexbuff, indexbuff, Shader，Shader params，texture
## 渲染管线
forward, deferred, SRP(scriptable render pipeline), HDR pipeline </br>
lighting, shadowmap, global illumation, post-process(HDR, AA, AO, etc) </br>
pysically based rendering, custom-material