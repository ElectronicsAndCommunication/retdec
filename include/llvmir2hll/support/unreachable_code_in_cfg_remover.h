/*
* @file include/llvmir2hll/support/unreachable_code_in_cfg_remover.h
* @brief Removes code that is unreachable in a CFG.
* @copyright (c) 2017 Avast Software, licensed under the MIT license
*/

#ifndef LLVMIR2HLL_SUPPORT_UNREACHABLE_CODE_IN_CFG_REMOVER_H
#define LLVMIR2HLL_SUPPORT_UNREACHABLE_CODE_IN_CFG_REMOVER_H

#include "llvmir2hll/support/smart_ptr.h"
#include "llvmir2hll/support/visitors/ordered_all_visitor.h"
#include "tl-cpputils/non_copyable.h"

namespace llvmir2hll {

class CFG;
class CFGBuilder;
class Module;

/**
* @brief Removes code that is unreachable in a CFG.
*
* For more information, see the description of removeCode().
*
* This class implements the "static helper" (or "library") design pattern (it
* has just static functions and no public instances can be created).
*/
class UnreachableCodeInCFGRemover: private OrderedAllVisitor,
		private tl_cpputils::NonCopyable {
public:
	// It needs to be public so it can be called in ShPtr's destructor.
	virtual ~UnreachableCodeInCFGRemover() override;

	static void removeCode(ShPtr<Module> module);

private:
	UnreachableCodeInCFGRemover(ShPtr<Module> module);

	void performRemoval();
	void performRemovalInFunc(ShPtr<Function> func);

	/// @name Visitor Interface
	/// @{
	using OrderedAllVisitor::visit;
	virtual void visitStmt(ShPtr<Statement> stmt, bool visitSuccessors = true,
		bool visitNestedStmts = true) override;
	/// @}

private:
	/// Module in which the code is removed.
	ShPtr<Module> module;

	/// The CFG of the current function.
	ShPtr<CFG> cfg;

	/// The used builder of CFGs.
	ShPtr<CFGBuilder> cfgBuilder;
};

} // namespace llvmir2hll

#endif
