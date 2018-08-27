> 念天地之悠悠，独怆然而涕下

# About Architecture
MirageEngine 将会加入现代引擎必备的元素，比如并行架构最大化利用最新的硬件设计。
# Parallel architecture
[Threading Building Blocks (TBB)](https://github.com/01org/tbb) is a C++ template library developed by Intel for parallel programming on multi-core processors. Using TBB, a computation is broken down into tasks that can run in parallel. The library manages and schedules threads to execute these tasks.