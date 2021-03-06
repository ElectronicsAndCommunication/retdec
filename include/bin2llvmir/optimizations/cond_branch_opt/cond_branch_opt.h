/**
* @file include/bin2llvmir/optimizations/cond_branch_opt/cond_branch_opt.h
* @brief Conditional branch optimization.
* @copyright (c) 2017 Avast Software, licensed under the MIT license
*/

#ifndef BIN2LLVMIR_OPTIMIZATIONS_COND_BRANCH_OPT_COND_BRANCH_OPT_H
#define BIN2LLVMIR_OPTIMIZATIONS_COND_BRANCH_OPT_COND_BRANCH_OPT_H

#include <llvm/IR/Module.h>
#include <llvm/Pass.h>

#include "bin2llvmir/providers/config.h"

namespace bin2llvmir {

class CondBranchOpt : public llvm::ModulePass
{
	public:
		static char ID;
		CondBranchOpt();
		virtual bool runOnModule(llvm::Module& m) override;
		bool runOnModuleCustom(llvm::Module& m, Config* c);

	private:
		bool run();
		bool runOnFunction(ReachingDefinitionsAnalysis& RDA, llvm::Function* f);

	private:
		llvm::Module* _module = nullptr;
		Config* _config = nullptr;
};

} // namespace bin2llvmir

#endif
