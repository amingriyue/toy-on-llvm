//===-- TOYMCTargetDesc.cpp - TOY Target Descriptions -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides TOY specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "TOYMCTargetDesc.h"
#include "InstPrinter/TOYInstPrinter.h"
#include "TOYMCAsmInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "TOYGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "TOYGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "TOYGenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createTOYMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitTOYMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createTOYMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitTOYMCRegisterInfo(X, 0);

  return X;
}

static MCSubtargetInfo *createTOYMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
  return createTOYMCSubtargetInfoImpl(TT, CPU, FS);
}

static MCInstPrinter *createTOYMCInstPrinter(const Triple &T,
                                             unsigned SyntaxVariant,
                                             const MCAsmInfo &MAI,
                                             const MCInstrInfo &MII,
                                             const MCRegisterInfo &MRI) {
  if (SyntaxVariant == 0) {
    return new TOYInstPrinter(MAI, MII, MRI);
  }

  return nullptr;
}

static MCAsmInfo *createTOYMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TheTriple,
                                     const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new TOYMCAsmInfo(TheTriple.getTriple());
  return MAI;
}


static MCStreamer *createMCStreamer(const Triple &T, MCContext &Context,
                                    std::unique_ptr<MCAsmBackend> &&MAB,
                                    std::unique_ptr<MCObjectWriter> &&OW,
                                    std::unique_ptr<MCCodeEmitter> &&Emitter,
                                    bool RelaxAll) {
  return createELFStreamer(Context, std::move(MAB), std::move(OW),
                           std::move(Emitter), RelaxAll);
}
#if 0
static MCTargetStreamer *createMCAsmTargetStreamer(MCStreamer &S,
                                                   formatted_raw_ostream &OS,
                                                   MCInstPrinter *InstPrint,
                                                   bool isVerboseAsm) {
  return new TOYTargetAsmStreamer(S);
}
#endif
extern "C" void LLVMInitializeTOYTargetMC() {
  // Register the MC asm info.
  //RegisterMCAsmInfo<TOYMCAsmInfo> X(TheTOYTarget);
  RegisterMCAsmInfoFn X(TheTOYTarget, createTOYMCAsmInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheTOYTarget, createTOYMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheTOYTarget, createTOYMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheTOYTarget,
                                          createTOYMCSubtargetInfo);

  // Register the MCInstPrinter.
  TargetRegistry::RegisterMCInstPrinter(TheTOYTarget,
                                        createTOYMCInstPrinter);

  // Register the MC Code Emitter
  TargetRegistry::RegisterMCCodeEmitter(TheTOYTarget, createTOYMCCodeEmitter);

  // Register the obj streamer
  TargetRegistry::RegisterELFStreamer(TheTOYTarget, createMCStreamer);

#if 0
  // Register the asm target streamer.
  TargetRegistry::RegisterAsmTargetStreamer(TheTOYTarget,
                                            createMCAsmTargetStreamer);
#endif
  // Register the asm backend (as little endian).
  TargetRegistry::RegisterMCAsmBackend(TheTOYTarget, createTOYAsmBackend);
}

