#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/User.h"
#include "llvm/InitializePasses.h"
#include "llvm/Support/Casting.h"
#include "llvm/Transforms/Scalar.h"


#define DEBUG_TYPE "func-block-count2"
using namespace llvm;

namespace {

struct FuncBlockCount2 : public FunctionPass {
  static char ID;
  FuncBlockCount2() : FunctionPass(ID) {
    initializeFuncBlockCount2Pass(*PassRegistry::getPassRegistry());
  }
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
    return false;
  }
  void getAnalysisUsage(AnalysisUsage &AU) const override {
    AU.addRequired<LoopInfoWrapperPass>();
    //AU.setPreservesAll();
  }
};

}

char FuncBlockCount2::ID = 0;
//static RegisterPass<FuncBlockCount2> X("funcblockcount2", "Function Block Count 2", false, false);
INITIALIZE_PASS_BEGIN(FuncBlockCount2, "funcblockcount2", "Function Block Count 2", false, false)
INITIALIZE_PASS_DEPENDENCY(LoopInfoWrapperPass)
INITIALIZE_PASS_END(FuncBlockCount2, "funcblockcount2", "Function Block Count 2", false, false)

Pass *llvm::createFuncBlockCountPass() { return new FuncBlockCount2(); }

