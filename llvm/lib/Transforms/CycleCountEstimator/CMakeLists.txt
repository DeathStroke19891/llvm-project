add_llvm_component_library(LLVMCycleCountEstimator
  CycleCountEstimator.cpp

  DEPENDS
  intrinsics_gen
  opt)