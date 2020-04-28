//===-- TOYAsmPrinter.cpp - TOY LLVM assembly writer ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains a printer that converts from our internal representation
// of machine-dependent LLVM code to the XAS-format TOY assembly language.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "asm-printer"
#include "TOY.h"
#include "InstPrinter/TOYInstPrinter.h"
#include "TOYInstrInfo.h"
#include "TOYMCInstLower.h"
#include "TOYSubtarget.h"
#include "TOYTargetMachine.h"
#include "llvm/ADT/SmallString.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineJumpTableInfo.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Mangler.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetLoweringObjectFile.h"
#include <algorithm>
#include <cctype>
using namespace llvm;

namespace {
class TOYAsmPrinter : public AsmPrinter {
//  const TOYSubtarget &Subtarget;
  TOYMCInstLower MCInstLowering;

public:
  explicit TOYAsmPrinter(TargetMachine &TM, std::unique_ptr<MCStreamer>Streamer)
      : AsmPrinter(TM, std::move(Streamer)), //Subtarget(TM.getSubtarget<TOYSubtarget>()),
        MCInstLowering(*this) {}

  StringRef getPassName() const { return "TOY Assembly Printer"; }

  void EmitFunctionEntryLabel();
  void EmitInstruction(const MachineInstr *MI);
  void EmitFunctionBodyStart();
};
} // end of anonymous namespace

void TOYAsmPrinter::EmitFunctionBodyStart() {
  MCInstLowering.Initialize(&MF->getContext());
}

void TOYAsmPrinter::EmitFunctionEntryLabel() {
  //OutStreamer.EmitLabel(CurrentFnSym);
}

void TOYAsmPrinter::EmitInstruction(const MachineInstr *MI) {
  MCInst TmpInst;
  MCInstLowering.Lower(MI, TmpInst);

  EmitToStreamer(*OutStreamer.get(), TmpInst);
}

// Force static initialization.
extern "C" void LLVMInitializeTOYAsmPrinter() {
  RegisterAsmPrinter<TOYAsmPrinter> X(TheTOYTarget);
}
