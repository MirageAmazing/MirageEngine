> 连峰去天不盈尺，枯松倒挂倚绝壁
# CrossPlatform Shader
目前关于跨平台的Shader研究已经有了大概的思路，主要是三部分

1. 对应平台的Shader的编译，资源的传递以及状态的设置，比如Windows上的HLSL的各种Shader，VertexShader，HullShader，PixelShader。
2. 以HLSLcc为概念的HLSL交叉编译，用HLSLcc将同一份HLSL代码编译成指定的语言类型的Shader代码，比如GLSL，Metal，SPIR-V。Unity和Unreal都有各家自己的HLSLcc编译器，这部分将来第一步是使用第三方的，第二步是完全自制（这会涉及到编译器相关的东西，比如LLVM）。
3. 一个跨平台的Effect Framework，DX本身的Effect框架是DX独占，所以肯定不能用，做一个跨平台游戏引擎就必须一个跨平台的Effect框架，像Unity，Unreal4都拥有一个自己的跨平台Effect框架，Nvidia的nvFX，cgFX也是一个可以参考的对象。<br>

目前我只需要做第一部分(2018-6-29 11:18:50)

参考链接<br>
Effect Framework相关 [nvFX](https://pdfs.semanticscholar.org/presentation/1c0e/d77b7efdcb34649b801500d65611f70fd7c5.pdf) [nvFX-Git](https://github.com/tlorach/nvFX) <br>
HLSLcc 相关 [Unity-HLSLcc](https://github.com/Unity-Technologies/HLSLcc) [HLSLcc相关讨论](http://www.opengpu.org/forum.php?mod=viewthread&tid=16513)