//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/version.hpp>

#include <string>



/*! \page py_triton_page Python bindings of the libTriton
    \brief [**python api**] All information about the libTriton's Python API.
    \anchor triton

\section triton_py_api Python API - Methods and namespaces of the triton module
<hr>

This project work using a `TritonContext` which contains all the required internal state
to simulate your instructions. You may also find [helpers](https://github.com/JonathanSalwan/Triton/tree/master/src/examples/python)
to wrap more generic concepts.

\subsection triton_py_api_classes Classes

- \ref py_AstContext_page
- \ref py_AstNode_page
- \ref py_BitsVector_page
- \ref py_Immediate_page
- \ref py_Instruction_page
- \ref py_MemoryAccess_page
- \ref py_PathConstraint_page
- \ref py_Register_page
- \ref py_SolverModel_page
- \ref py_SymbolicExpression_page
- \ref py_SymbolicVariable_page
- \ref py_TritonContext_page


\subsection triton_py_api_namespaces Namespaces

- \ref py_ARCH_page
- \ref py_AST_NODE_page
- \ref py_AST_REPRESENTATION_page
- \ref py_CALLBACK_page
- \ref py_CONDITION_page
- \ref py_CPUSIZE_page
- \ref py_EXTEND_page
- \ref py_MODE_page
- \ref py_OPCODE_page
- \ref py_OPERAND_page
- \ref py_PREFIX_page
- \ref py_REG_page
- \ref py_SHIFT_page
- \ref py_SYMBOLIC_page
- \ref py_SYSCALL_page
- \ref py_VERSION_page

*/



namespace triton {
  namespace bindings {
    namespace python {

      pybind11::module pyTriton("triton", "Triton Python API");

      PYBIND11_MODULE(triton, pyTriton) {
        pyTriton.attr("__version__") = pybind11::str(std::to_string(triton::MAJOR)
          + "."
          + std::to_string(triton::MINOR)
          + "."
          + std::to_string(triton::BUILD));

        /* Enums */
        initArchEnum(pyTriton);
        initAstNodeEnum(pyTriton);
        initAstRepresentationEnum(pyTriton);
        initCallbackEnum(pyTriton);
        initConditionEnum(pyTriton);
        initCpuSizeEnum(pyTriton);
        initExtendEnum(pyTriton);
        initModeEnum(pyTriton);
        initOpcodeEnum(pyTriton);
        initOperandEnum(pyTriton);
        initPrefixEnum(pyTriton);
        initRegisterEnum(pyTriton);
        initShiftEnum(pyTriton);
        initSymbolicEnum(pyTriton);
        #if defined(__unix__) || defined(__APPLE__)
        initSyscallEnum(pyTriton);
        #endif
        initVersionEnum(pyTriton);

        /* Objects */
        initAstContextObject(pyTriton);
        initAstNodeObject(pyTriton);
        initBitsVectorObject(pyTriton);
        initImmediateObject(pyTriton);
        initInstructionObject(pyTriton);
        initMemoryAccessObject(pyTriton);
        initPathConstraintObject(pyTriton);
        initRegisterObject(pyTriton);
        initShortcutRegisterObject(pyTriton);
        initSolverModelObject(pyTriton);
        initSymbolicExpressionObject(pyTriton);
        initSymbolicVariableObject(pyTriton);
        initTritonContextObject(pyTriton);
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
