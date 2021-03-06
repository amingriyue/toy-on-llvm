//===-- TOYAsmBackend.cpp - TOY Assembler Backend -------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/TOYMCTargetDesc.h"
#include "MCTargetDesc/TOYFixupKinds.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/ADT/Triple.h"
#include "llvm/BinaryFormat/ELF.h"
#include "llvm/BinaryFormat/MachO.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDirectives.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCFixupKindInfo.h"
#include "llvm/MC/MCMachObjectWriter.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSectionELF.h"
#include "llvm/MC/MCSectionMachO.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;


namespace {
class TOYELFObjectWriter : public MCELFObjectTargetWriter {
public:
  TOYELFObjectWriter(uint8_t OSABI)
      : MCELFObjectTargetWriter(/*Is64Bit*/ false, OSABI, /*ELF::EM_TOY*/ ELF::EM_ARM,
                                /*HasRelocationAddend*/ false) {}
};

class TOYAsmBackend : public MCAsmBackend {
public:
  TOYAsmBackend(const Target &T, const StringRef TT) : MCAsmBackend(support::little) {}

  ~TOYAsmBackend() {}

  void adjustFixupValue(const MCFixup &Fixup, const MCValue &Target,
                        uint64_t &Value, MCContext *Ctx = nullptr) const;

//  std::unique_ptr<MCObjectTargetWriter>
  //createObjectTargetWriter() const override;

  void applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                  const MCValue &Target, MutableArrayRef<char> Data,
                  uint64_t Value, bool IsResolved,
                  const MCSubtargetInfo *STI) const override;

  const MCFixupKindInfo &getFixupKindInfo(MCFixupKind Kind) const override {
    const static MCFixupKindInfo Infos[TOY::NumTargetFixupKinds] = {
      // This table *must* be in the order that the fixup_* kinds are defined in
      // TOYFixupKinds.h.
      //
      // Name                      Offset (bits) Size (bits)     Flags
      { "fixup_toy_mov_hi16_pcrel", 0, 32, MCFixupKindInfo::FKF_IsPCRel },
      { "fixup_toy_mov_lo16_pcrel", 0, 32, MCFixupKindInfo::FKF_IsPCRel },
    };

    if (Kind < FirstTargetFixupKind) {
      return MCAsmBackend::getFixupKindInfo(Kind);
    }

    assert(unsigned(Kind - FirstTargetFixupKind) < getNumFixupKinds() &&
           "Invalid kind!");
    return Infos[Kind - FirstTargetFixupKind];
  }

  unsigned getNumFixupKinds() const override {
    return TOY::NumTargetFixupKinds;
  }

  bool mayNeedRelaxation(const MCInst &Inst,
                         const MCSubtargetInfo &STI) const override {
    return false;
  }

  bool fixupNeedsRelaxation(const MCFixup &Fixup, uint64_t Value,
                            const MCRelaxableFragment *DF,
                            const MCAsmLayout &Layout) const override {
    llvm_unreachable("RelaxInstruction() unimplemented");
    return false;
  }

  void relaxInstruction(const MCInst &Inst, const MCSubtargetInfo &STI,
                        MCInst &Res) const override {}

  bool shouldForceRelocation(const MCAssembler &Asm, const MCFixup &Fixup,
                             const MCValue &Target) override {
    switch ((unsigned) Fixup.getKind()) {
    default: return false;
      // Fixups which should always be recorded as relocations.
    //case AVR::fixup_call:
    return true;
  }

  }
  bool writeNopData(raw_ostream &OS, uint64_t Count) const override {
    if (Count == 0) {
      return true;
    }
    return false;
  }

  unsigned getPointerSize() const { return 4; }
};
void TOYAsmBackend::adjustFixupValue(const MCFixup &Fixup, const MCValue &Target,
                        uint64_t &Value, MCContext *Ctx)  const {
 // static unsigned adjustFixupValue(const MCFixup &Fixup, uint64_t Value,
//                                 MCContext *Ctx = NULL) {
  unsigned Kind = Fixup.getKind();
  switch (Kind) {
  default:
    llvm_unreachable("Unknown fixup kind!");
  case TOY::fixup_toy_mov_hi16_pcrel:
    Value >>= 16;
  // Intentional fall-through
  case TOY::fixup_toy_mov_lo16_pcrel:
    unsigned Hi4  = (Value & 0xF000) >> 12;
    unsigned Lo12 = Value & 0x0FFF;
    // inst{19-16} = Hi4;
    // inst{11-0} = Lo12;
    Value = (Hi4 << 16) | (Lo12);
  }
}
void TOYAsmBackend::applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                  const MCValue &Target, MutableArrayRef<char> Data,
                  uint64_t Value, bool IsResolved,
                  const MCSubtargetInfo *STI) const {
//void TOYAsmBackend::processFixupValue(const MCAssembler &Asm,
//                                      const MCAsmLayout &Layout,
//                                      const MCFixup &Fixup,
//                                      const MCFragment *DF,
//                                      const MCValue &Target, uint64_t &Value,
//                                      bool &IsResolved) {
  // We always have resolved fixups for now.
  IsResolved = true;
  // At this point we'll ignore the value returned by adjustFixupValue as
  // we are only checking if the fixup can be applied correctly.
  adjustFixupValue(Fixup, Target, Value, &Asm.getContext());
}


} // end anonymous namespace



#if 0
void TOYAsmBackend::applyFixup(const MCAssembler &Asm, const MCFixup &Fixup,
                  const MCValue &Target, MutableArrayRef<char> Data,
                  uint64_t Value, bool IsResolved,
                  const MCSubtargetInfo *STI) const {
//void TOYAsmBackend::applyFixup(const MCFixup &Fixup, char *Data,
//                               unsigned DataSize, uint64_t Value,
//                               bool isPCRel) const {
  unsigned NumBytes = 4;
  adjustFixupValue(Fixup, Target, Value, &Asm.getContext());
  if (!Value) {
    return; // Doesn't change encoding.
  }

  unsigned Offset = Fixup.getOffset();
  assert(Offset + NumBytes <= Data.size() && "Invalid fixup offset!");

  // For each byte of the fragment that the fixup touches, mask in the bits from
  // the fixup value. The Value has been "split up" into the appropriate
  // bitfields above.
  for (unsigned i = 0; i != NumBytes; ++i) {
    Data[Offset + i] |= uint8_t((Value >> (i * 8)) & 0xff);
  }
}
#endif

namespace {

class ELFTOYAsmBackend : public TOYAsmBackend {
public:
  uint8_t OSABI;
  ELFTOYAsmBackend(const Target &T, const StringRef TT, uint8_t _OSABI)
      : TOYAsmBackend(T, TT), OSABI(_OSABI) {}

  std::unique_ptr<MCObjectTargetWriter>
    createObjectTargetWriter() const override {
    return createTOYELFObjectWriter(OSABI);
  }

};

} // end anonymous namespace

namespace llvm {
MCAsmBackend *createTOYAsmBackend(const Target &T, const MCSubtargetInfo &STI,
                                  const MCRegisterInfo &MRI,
                                  const llvm::MCTargetOptions &TO) {

  const uint8_t ABI = MCELFObjectTargetWriter::getOSABI(STI.getTargetTriple().getOS());
  return new ELFTOYAsmBackend(T, STI.getTargetTriple().getTriple(), ABI);
}
}
