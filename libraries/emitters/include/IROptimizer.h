////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     IROptimizer.h (emitters)
//  Authors:  Umesh Madan
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "LLVMInclude.h"

namespace ell
{
namespace emitters
{
    ///<summary>Class to manage optimizations for functions</summary>
    class IRFunctionOptimizer
    {
    public:
        /// <summary> Function optimizer for functions in this module. </summary>
        ///
        /// <param name="pModule"> pointer to an LLVM module. </param>
        IRFunctionOptimizer(llvm::Module* pModule);

        /// <summary> Add common optimizations to the optimizer pipeline. </summary>
        void AddStandardPasses();

        /// <summary> Add an optimization pass to simplify instructions. </summary>
        void AddInstructionCombiner();

        /// <summary> Add an optimization pass for dead code elimination. </summary>
        void AddDeadCodeEliminator();

        /// <summary> Adds reassociation. </summary>
        void AddReassociation();

        /// <summary> Add an optimization pass to turn stack variables into SSA registers. </summary>
        void AddMemoryToRegisterPass();

        /// <summary> Add an optimization pass to eliminate sub-expressions. </summary>
        void AddCommonSubexpressionEliminator();

        /// <summary> Add an optimization pass to simplify control flow. </summary>
        void AddControlFlowSimplification();

        /// <summary> Optimize the given function. </summary>
        ///
        /// <param name="pFunction"> pointer to an llvm function. </param>
        void Run(llvm::Function* pFunction);

    private:
        std::unique_ptr<llvm::legacy::FunctionPassManager> _pPasses;
        bool _initialized = false;
    };

    ///<summary>Class to apply module-wide optimizations</summary>
    class IRModuleOptimizer
    {
    public:
        /// <summary> Add common optimizations to the optimizer pipeline. </summary>
        void AddStandardPasses();

        /// <summary> Optimize a given module. </summary>
        ///
        /// <param name="pModule"> pointer to an llvm module. </param>
        void Run(llvm::Module* pModule);

    private:
        llvm::ModulePassManager _passes;
        llvm::ModuleAnalysisManager _analysis;
    };
}
}