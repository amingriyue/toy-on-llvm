//===-- TOYRegisterInfo.h - TOY Register Information Impl ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the TOY implementation of the MRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef TOYREGISTERINFO_H
#define TOYREGISTERINFO_H

#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "TOYGenRegisterInfo.inc"

namespace llvm {

class TargetInstrInfo;

struct TOYRegisterInfo : public TOYGenRegisterInfo {
public:
  TOYRegisterInfo();

  /// Code Generation virtual methods...
  const uint16_t *getCalleeSavedRegs(const MachineFunction *MF = 0) const
      override;

  const uint32_t *getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID CC) const override;

  BitVector getReservedRegs(const MachineFunction &MF) const override;

  bool requiresRegisterScavenging(const MachineFunction &MF) const override;

  bool trackLivenessAfterRegAlloc(const MachineFunction &MF) const override;

  bool useFPForScavengingIndex(const MachineFunction &MF) const override;

  void eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                           unsigned FIOperandNum, RegScavenger *RS = NULL) const
      override;

  // Debug information queries.
  Register getFrameRegister(const MachineFunction &MF) const override;

};

} // end namespace llvm

#endif
