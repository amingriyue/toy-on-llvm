#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/LoopInfo.h"

using namespace llvm;

namespace {

struct CountOpcode : public FunctionPass {
  std::map<std::string, int> opcodeCounter;
  static char ID;
  CountOpcode() : FunctionPass(ID) {}
  void countBlocksInLoop(Loop *L, unsigned nest) {

    unsigned num_Blocks = 0;

    Loop::block_iterator bb;
    for (bb = L->block_begin(); bb != L->block_end(); ++bb)
      num_Blocks++;
    errs() << "Loop level " << nest << " has " << num_Blocks << " blocks\n";
    std::vector<Loop*> subLoops = L->getSubLoops();
    Loop::iterator j, f;
    for (j = subLoops.begin(), f = subLoops.end(); j != f; ++j)
      countBlocksInLoop(*j, nest + 1);
  }
  bool runOnFunction(Function &F) override {
    LoopInfo *LI = &getAnalysis<LoopInfoWrapperPass>().getLoopInfo();

    errs() << "Function name is " << F.getName() << '\n';
    for (Loop *L : *LI)
      countBlocksInLoop(L, 0);

    for (Function::iterator bb = F.begin(), e = F.end(); bb != e; ++bb) {
      for (BasicBlock::iterator i = bb->begin(), e = bb->end(); i != e; ++i) {
        if (opcodeCounter.find(i->getOpcodeName()) == opcodeCounter.end()) {
          opcodeCounter[i->getOpcodeName()] = 1;
        } else {
          opcodeCounter[i->getOpcodeName()] += 1;
        }
      }
    }

    std::map<std::string, int>::iterator i = opcodeCounter.begin();
    std::map<std::string, int>::iterator e = opcodeCounter.end();

    opcodeCounter.end();
    while (i != e) {
      llvm::outs() << i->first << ": " << i->second << "\n";
      i++;
    }
    llvm::outs() << "\n";

    opcodeCounter.clear();

    return false;
  }
  void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.addRequired<LoopInfoWrapperPass>();
                    //AU.setPreservesAll();
  }
};

}

char CountOpcode::ID = 0;
static RegisterPass<CountOpcode> X("countopcode", "Opcode Count", false, false);
