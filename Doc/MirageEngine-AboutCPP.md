> 蜀道之难，难于上青天，使人听此凋朱颜
# About CPP
基于C++需要使用很多有用的必要的技术来增加引擎功能，有些是必要的，有些事锦上添花。比如MetaObjectSystem, 各种C++反射技术，HotLoad等等，关于C++的一些技术点我在该文档做一个备忘。</br>

1. MetaObjectSystem 元数据系统，参考Qt的QObject, UE4的UObject，以及其他。元数据系统为实现万物可追踪（比如可以很方便的展示各个对象的引用关系），垃圾回收（GC），反射，序列化，统一的内存管理，统计，编辑器的更好的支持。所以对于ME来说，一套属于自己的元数据系统是基础设施。</br>

2. 反射技术.据说C++20可能会加入反射特性，值得期待。[RTTR](https://github.com/rttrorg/rttr)这个C++反射技术可以尝试引入，另外可以关注研究[CryEngine](https://github.com/CRYTEK/CRYENGINE)的反射技术,因为ME将来可能会倾向于CryEngine和FrostbiteEngine这种风格。</br>

3. Hotload.关于C++Hotload技术是一个很有吸引力的技术，为实现在引擎编辑器中在不关闭运行状态的的时候动态修改代码调试，即改即看铺垫基础。这个在其他的基础设施建设完成后一定要加入，相关技术引用[RuntimeCompiledC++](https://github.com/RuntimeCompiledCPlusPlus/RuntimeCompiledCPlusPlus)。