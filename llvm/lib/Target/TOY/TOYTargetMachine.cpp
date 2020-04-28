//===-- TOYTargetMachine.cpp - Define TargetMachine for TOY -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "TOYTargetMachine.h"
#include "TOY.h"
#include "TOYFrameLowering.h"
#include "TOYInstrInfo.h"
#include "TOYISelLowering.h"
#include "TOYSelectionDAGInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

static Reloc::Model getEffectiveRelocModel(const Triple &TT,
                                           Optional<Reloc::Model> RM) {
  // AArch64 Darwin and Windows are always PIC.
  if (TT.isOSDarwin() || TT.isOSWindows())
    return Reloc::PIC_;
  // On ELF platforms the default static relocation model has a smart enough
  // linker to cope with referencing external symbols defined in a shared
  // library. Hence DynamicNoPIC doesn't need to be promoted to PIC.
  if (!RM.hasValue() || *RM == Reloc::DynamicNoPIC)
    return Reloc::Static;
  return *RM;
}

static std::string computeDataLayout(const Triple &TT, StringRef CPU,
                                     const TargetOptions &Options,
                                     bool isLittle) {
  std::string Ret;

  if (isLittle)
    // Little endian.
    Ret += "e";
  else
    // Big endian.
    Ret += "E";

  Ret += DataLayout::getManglingComponent(TT);

  // Pointers are 32 bits and aligned to 32 bits.
  Ret += "-p:32:32";

  // Try to align aggregates to 32 bits (the default is 64 bits, which has no
  // particular hardware support on 32-bit ARM).
  Ret += "-a:0:32";

  // Integer registers are 32 bits.
  Ret += "-n32";


  return Ret;
}
TOYTargetMachine::TOYTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                                   StringRef FS, const TargetOptions &Options,
                                   Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                                   CodeGenOpt::Level OL, bool isLittle)
    : LLVMTargetMachine(T, computeDataLayout(TT, CPU, Options, isLittle), TT,
                        CPU, FS, Options, getEffectiveRelocModel(TT, RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      Subtarget(TT, CPU, FS, *this) {
  initAsmInfo();
}

namespace {
/// TOY Code Generator Pass Configuration Options.
class TOYPassConfig : public TargetPassConfig {
public:
  TOYPassConfig(TOYTargetMachine& TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  TOYTargetMachine &getTOYTargetMachine() const {
    return getTM<TOYTargetMachine>();
  }

  virtual bool addPreISel();
  virtual bool addInstSelector();
  virtual void addPreEmitPass();
};
} // namespace

TargetPassConfig *TOYTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new TOYPassConfig(*this, PM);
}

bool TOYPassConfig::addPreISel() { return false; }

bool TOYPassConfig::addInstSelector() {
  addPass(createTOYISelDag(getTOYTargetMachine(), getOptLevel()));
  return false;
}

void TOYPassConfig::addPreEmitPass() { return; }

// Force static initialization.
extern "C" void LLVMInitializeTOYTarget() {
  RegisterTargetMachine<TOYTargetMachine> X(TheTOYTarget);
}

void TOYTargetMachine::addAnalysisPasses(PassManagerBase &PM) {}
