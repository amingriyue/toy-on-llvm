//===-- TOYELFObjectWriter.cpp - TOY ELF Writer ---------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/TOYMCTargetDesc.h"
#include "MCTargetDesc/TOYFixupKinds.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCSectionELF.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  class TOYELFObjectWriter : public MCELFObjectTargetWriter {
  public:
    TOYELFObjectWriter(uint8_t OSABI);

    virtual ~TOYELFObjectWriter();

  unsigned getRelocType(MCContext &Ctx,
                        const MCValue &Target,
                        const MCFixup &Fixup,
                        bool IsPCRel) const override;
  };
}

unsigned TOYELFObjectWriter::getRelocType(MCContext &Ctx, const MCValue &Target,
                                          const MCFixup &Fixup,
                                          bool IsPCRel) const {
  if (!IsPCRel) {
    llvm_unreachable("Only dealying with PC-relative fixups for now");
  }

  unsigned Type = 0;
  switch ((unsigned)Fixup.getKind()) {
  default:
    llvm_unreachable("Unimplemented");
  case TOY::fixup_toy_mov_hi16_pcrel:
    Type = ELF::R_ARM_MOVT_PREL;
    break;
  case TOY::fixup_toy_mov_lo16_pcrel:
    Type = ELF::R_ARM_MOVW_PREL_NC;
    break;
  }
  return Type;
}

TOYELFObjectWriter::TOYELFObjectWriter(uint8_t OSABI)
    : MCELFObjectTargetWriter(/*Is64Bit*/ false, OSABI, /*ELF::EM_TOY*/ ELF::EM_ARM,
                              /*HasRelocationAddend*/ false) {}

TOYELFObjectWriter::~TOYELFObjectWriter() {}

std::unique_ptr<MCObjectTargetWriter>
llvm::createTOYELFObjectWriter(uint8_t OSABI) {
  
  return std::make_unique<TOYELFObjectWriter>(OSABI);
  //MCELFObjectTargetWriter *MOTW = new TOYELFObjectWriter(OSABI);
  //return createELFObjectWriter(MOTW, OS, /*IsLittleEndian=*/true);
}
