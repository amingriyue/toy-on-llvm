LLVM_DIR = /home/zhoucm1/freedesktop/llvm-project/
LLVM_INC = ${LLVM_DIR}/llvm/include/
LLVM_BIN_DIR = ${LLVM_DIR}/build/
CXXFLAGS = -g -std=c++11 -Wall -Wno-deprecated -Wno-unused -fpermissive -Wno-write-strings
CXXFLAGS += `${LLVM_BIN_DIR}/bin/llvm-config --cxxflags`
LDFLAGS += `${LLVM_BIN_DIR}/bin/llvm-config --ldflags`
LLVMLIBS = `${LLVM_BIN_DIR}/bin/llvm-config --libs core mcjit native`
LLVMLIBS += `${LLVM_BIN_DIR}/bin/llvm-config --system-libs`
CXX = clang++

all:
	${CXX} toy.cpp ${CXXFLAGS} ${LDFLAGS} ${LLVMLIBS} -I${LLVM_INC} -o toy
