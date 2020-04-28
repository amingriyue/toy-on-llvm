cmake -G "Unix Makefiles" -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;libcxx;libcxxabi;libunwind;lldb;compiler-rt;lld;polly" -DCMAKE_BUILD_TYPE=Debug -DLLVM_CCACHE_BUILD=true ../llvm

