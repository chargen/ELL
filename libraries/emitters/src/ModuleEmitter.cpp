////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     ModuleEmitter.cpp (emitters)
//  Authors:  Umesh Madan, Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ModuleEmitter.h"
#include "EmitterException.h"

// utilities
#include "Files.h"

// stl
#include <cassert>

namespace ell
{
namespace emitters
{
    static const std::string c_literalVar = "c_";
    static const std::string c_globalVar = "g_";
    static const std::string c_localVar = "t_";
    static const std::string c_fnVar = "Fn";
    static const std::string c_nodeVar = "Node";
    static const std::string c_inputVar = "input";
    static const std::string c_outputVar = "output";

    void ModuleEmitter::SetCompilerParameters(const CompilerParameters& parameters)
    {
        _parameters = parameters;
    }

    void ModuleEmitter::WriteToFile(const std::string& filePath)
    {
        WriteToFile(filePath, GetFormatFromExtension(utilities::GetFileExtension(filePath, true)));
    }

    void ModuleEmitter::WriteToFile(const std::string& filePath, ModuleOutputFormat format)
    {
        auto stream = utilities::OpenOfstream(filePath);
        WriteToStream(stream, format);
    }

    ModuleOutputFormat ModuleEmitter::GetFormatFromExtension(const std::string& extension)
    {
        if (extension == "ll")
        {
            return ModuleOutputFormat::ir;
        }
        else if (extension == "bc")
        {
            return ModuleOutputFormat::bitcode;
        }
        else if (extension == "asm")
        {
            return ModuleOutputFormat::assembly;
        }
        else
        {
            return ModuleOutputFormat::ir; // default
        }
    }

    void ModuleEmitter::Reset()
    {
    }

    void ModuleEmitter::AllocateVariable(Variable& var)
    {
        if (var.HasEmittedName())
        {
            return;
        }

        EmittedVar emittedVar;
        const std::string* pPrefix = nullptr;
        switch (var.Scope())
        {
            case VariableScope::literal:
                emittedVar = _literalVars.Allocate();
                pPrefix = &c_literalVar;
                break;
            case VariableScope::local:
                emittedVar = _localVars.Allocate();
                pPrefix = &c_localVar;
                break;
            case VariableScope::global:
                emittedVar = _globalVars.Allocate();
                pPrefix = &c_globalVar;
                break;
            case VariableScope::rValue:
                emittedVar = _rValueVars.Allocate();
                pPrefix = &c_fnVar;
                break;
            case VariableScope::input:
                emittedVar = _inputVars.Allocate();
                pPrefix = &c_inputVar;
                break;
            case VariableScope::output:
                emittedVar = _outputVars.Allocate();
                pPrefix = &c_outputVar;
                break;
            default:
                throw EmitterException(EmitterError::variableScopeNotSupported);
        }
        var.AssignVar(emittedVar);
        var.SetEmittedName(*pPrefix + std::to_string(emittedVar.varIndex));
    }

    void ModuleEmitter::FreeVar(Variable& var)
    {
        if (!var.HasEmittedName())
        {
            return;
        }
        VariableScope scope = var.Scope();
        switch (scope)
        {
            case VariableScope::local:
            {
                auto v = var.GetAssignedVar();
                _localVars.Free(v);
            }
            break;
            case VariableScope::global:
            {
                auto v = var.GetAssignedVar();
                _globalVars.Free(v);
            }
            break;
            default:
                // We never free other types
                assert(scope != VariableScope::local && scope != VariableScope::global);
                break;
        }
    }
}
}
