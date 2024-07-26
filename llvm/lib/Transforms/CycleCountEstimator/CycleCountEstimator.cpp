#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/BranchProbabilityInfo.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm;

namespace {
  struct CycleCountEstimator : public FunctionPass {
    static char ID;
    CycleCountEstimator() : FunctionPass(ID) {}

    // bool runOnFunction(Function &F) override {
    //   return false;
    // }
    bool runOnFunction(Function &F) {
      errs() << "Estimating cycles for function: " << F.getName() << "\n";

      LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
      TargetTransformInfo &TTI = getAnalysis<TargetTransformInfoWrapperPass>().getTTI(F);

      for (auto &BB : F) {
        int cycleCount = 0;

        for (auto &I : BB) {
          cycleCount += 1;
        }

        errs() << "Basic Block: " << BB.getName() << " Cycles: " << cycleCount << "\n";
      }

  return false;
}
    
    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
      AU.addRequired<LoopInfoWrapperPass>();
      AU.addRequired<TargetTransformInfoWrapperPass>();
      AU.addRequired<TargetLibraryInfoWrapperPass>();
      AU.addRequired<BranchProbabilityInfoWrapperPass>();
    }
  };
}

char CycleCountEstimator::ID = 0;

static RegisterPass<CycleCountEstimator> X("cycle-count-estimator", "Cycle Count Estimation Pass", false, false);
