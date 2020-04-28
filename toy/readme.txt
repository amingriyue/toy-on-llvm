graphviz:
It needs a debug build of llvm

../build/bin/llc -fast-isel=false -view-dag-combine1-dags example4.ll

dot test.dot -Tpng -o test.png

TableGen Language:
https://blog.csdn.net/SiberiaBear/article/details/103539530?depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-2&utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-2

build issue:
1. error: invalid static_cast from type 'const llvm::TargetFrameLowering*' to type 'const llvm::ToyFrameLowering*' MF.getSubtarget().getFrameLowering());
fix: include TOYFrameLowering.h before TOYGenRegisterInfo.inc in .cpp
