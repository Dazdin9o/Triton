//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/pythonUtils.hpp>
#include <triton/api.hpp>



/*! \page py_TritonContext_page TritonContext
    \brief [**python api**] All information about the Triton Context class
    \anchor tritonContext

\section triton_py_description Description
<hr>

The libTriton offers Python bindings on its C++ API which allow you to build analysis in Python as well as in C++.

~~~~~~~~~~~~~{.py}
>>> from triton import TritonContext, ARCH
>>>
>>> ctx = TritonContext()
>>> ctx.setArchitecture(ARCH.X86_64)

~~~~~~~~~~~~~

\section tritonContext_py_api Python API - Methods of the TritonContext class
<hr>

\subsection TritonContext_py_api_methods Methods

- <b>void addCallback(function cb, \ref py_CALLBACK_page kind)</b><br>
Adds a callback at specific internal points. Your callback will be called each time the point is reached.

- <b>void assignSymbolicExpressionToMemory(\ref py_SymbolicExpression_page symExpr, \ref py_MemoryAccess_page mem)</b><br>
Assigns a \ref py_SymbolicExpression_page to a \ref py_MemoryAccess_page area. **Be careful**, use this function only if you know what you are doing.
The symbolic expression (`symExpr`) must be aligned to the memory access.

- <b>void assignSymbolicExpressionToRegister(\ref py_SymbolicExpression_page symExpr, \ref py_Register_page reg)</b><br>
Assigns a \ref py_SymbolicExpression_page to a \ref py_Register_page. **Be careful**, use this function only if you know what you are doing.
The symbolic expression (`symExpr`) must be aligned to the targeted size register. E.g: for SSE registers, the expression must be aligned
to 128-bits. Otherwise, you will probably get a sort mismatch error when you will solve the expression. If you want to assign an
expression to a sub-register like `AX`, `AH` or `AL`, please, craft your expression with the `concat()` and `extract()` ast functions.

- <b>bool buildSemantics(\ref py_Instruction_page inst)</b><br>
Builds the instruction semantics. Returns true if the instruction is supported. You must define an architecture before.

- <b>void clearPathConstraints(void)</b><br>
Clears the logical conjunction vector of path constraints.

- <b>void concretizeAllMemory(void)</b><br>
Concretizes all symbolic memory references.

- <b>void concretizeAllRegister(void)</b><br>
Concretizes all symbolic register references.

- <b>void concretizeMemory(integer addr)</b><br>
Concretizes a specific symbolic memory reference.

- <b>void concretizeMemory(\ref py_MemoryAccess_page mem)</b><br>
Concretizes a specific symbolic memory reference.

- <b>void concretizeRegister(\ref py_Register_page reg)</b><br>
Concretizes a specific symbolic register reference.

- <b>\ref py_SymbolicVariable_page convertExpressionToSymbolicVariable(integer symExprId, integer symVarSize, string comment)</b><br>
Converts a symbolic expression to a symbolic variable. `symVarSize` must be in bits. This function returns the new symbolic variable created.

- <b>\ref py_SymbolicVariable_page convertMemoryToSymbolicVariable(\ref py_MemoryAccess_page mem, string comment)</b><br>
Converts a symbolic memory expression to a symbolic variable. This function returns the new symbolic variable created.

- <b>\ref py_SymbolicVariable_page convertRegisterToSymbolicVariable(\ref py_Register_page reg, string comment)</b><br>
Converts a symbolic register expression to a symbolic variable. This function returns the new symbolic variable created.

- <b>\ref py_SymbolicExpression_page createSymbolicFlagExpression(\ref py_Instruction_page inst, \ref py_AstNode_page node, \ref py_Register_page flag, string comment)</b><br>
Returns the new symbolic register expression and links this expression to the instruction.

- <b>\ref py_SymbolicExpression_page createSymbolicMemoryExpression(\ref py_Instruction_page inst, \ref py_AstNode_page node, \ref py_MemoryAccess_page mem, string comment)</b><br>
Returns the new symbolic memory expression and links this expression to the instruction.

- <b>\ref py_SymbolicExpression_page createSymbolicRegisterExpression(\ref py_Instruction_page inst, \ref py_AstNode_page node, \ref py_Register_page reg, string comment)</b><br>
Returns the new symbolic register expression and links this expression to the instruction.

- <b>\ref py_SymbolicExpression_page createSymbolicVolatileExpression (\ref py_Instruction_page inst, \ref py_AstNode_page node, string comment)</b><br>
Returns the new symbolic volatile expression and links this expression to the instruction.

- <b>void disassembly(\ref py_Instruction_page inst)</b><br>
Disassembles the instruction and setup operands. You must define an architecture before.

- <b>void enableMode(\ref py_MODE_page mode, bool flag)</b><br>
Enables or disables a specific mode.

- <b>void enableSymbolicEngine(bool flag)</b><br>
Enables or disables the symbolic execution engine.

- <b>void enableTaintEngine(bool flag)</b><br>
Enables or disables the taint engine.

- <b>integer evaluateAstViaZ3(\ref py_AstNode_page node)</b><br>
Evaluates an AST via Z3 and returns the symbolic value.

- <b>[\ref py_Register_page, ...] getAllRegisters(void)</b><br>
Returns the list of all registers. Each item of this list is a \ref py_Register_page.

- <b>\ref py_ARCH_page getArchitecture(void)</b><br>
Returns the current architecture used.

- <b>\ref py_AstContext_page getAstContext(void)</b><br>
Returns the AST context to create and modify nodes.

- <b>\ref py_AST_REPRESENTATION_page getAstRepresentationMode(void)</b><br>
Returns the current AST representation mode.

- <b>bytes getConcreteMemoryAreaValue(integer baseAddr, integer size)</b><br>
Returns the concrete value of a memory area.

- <b>integer getConcreteMemoryValue(integer addr)</b><br>
Returns the concrete value of a memory cell.

- <b>integer getConcreteMemoryValue(\ref py_MemoryAccess_page mem)</b><br>
Returns the concrete value of memory cells.

- <b>integer getConcreteRegisterValue(\ref py_Register_page reg)</b><br>
Returns the concrete value of a register.

- <b>integer getConcreteVariableValue(\ref py_SymbolicVariable_page symVar)</b><br>
Returns the concrete value of a symbolic variable.

- <b>integer getGprBitSize(void)</b><br>
Returns the size in bit of the General Purpose Registers.

- <b>integer getGprSize(void)</b><br>
Returns the size in byte of the General Purpose Registers.

- <b>\ref py_AstNode_page getImmediateAst(\ref py_Immediate_page imm)</b><br>
Returns the AST corresponding to the \ref py_Immediate_page.

- <b>\ref py_AstNode_page getMemoryAst(\ref py_MemoryAccess_page mem)</b><br>
Returns the AST corresponding to the \ref py_MemoryAccess_page with the SSA form.

- <b>dict getModel(\ref py_AstNode_page node)</b><br>
Computes and returns a model as a dictionary of {integer symVarId : \ref py_SolverModel_page model} from a symbolic constraint.

- <b>[dict, ...] getModels(\ref py_AstNode_page node, integer limit)</b><br>
Computes and returns several models from a symbolic constraint. The `limit` is the number of models returned.

- <b>\ref py_Register_page getParentRegister(\ref py_Register_page reg)</b><br>
Returns the parent \ref py_Register_page from a \ref py_Register_page.

- <b>[\ref py_Register_page, ...] getParentRegisters(void)</b><br>
Returns the list of parent registers. Each item of this list is a \ref py_Register_page.

- <b>[\ref py_PathConstraint_page, ...] getPathConstraints(void)</b><br>
Returns the logical conjunction vector of path constraints as list of \ref py_PathConstraint_page.

- <b>\ref py_AstNode_page getPathConstraintsAst(void)</b><br>
Returns the logical conjunction AST of path constraints.

- <b>\ref py_Register_page getRegister(\ref py_REG_page id)</b><br>
Returns the \ref py_Register_page class corresponding to a \ref py_REG_page id.

- <b>\ref py_AstNode_page getRegisterAst(\ref py_Register_page reg)</b><br>
Returns the AST corresponding to the \ref py_Register_page with the SSA form.

- <b>\ref py_SymbolicExpression_page getSymbolicExpressionFromId(integer symExprId)</b><br>
Returns the symbolic expression corresponding to an id.

- <b>dict getSymbolicExpressions(void)</b><br>
Returns all symbolic expressions as a dictionary of {integer SymExprId : \ref py_SymbolicExpression_page expr}.

- <b>dict getSymbolicMemory(void)</b><br>
Returns the map of symbolic memory as {integer address : \ref py_SymbolicExpression_page expr}.

- <b>\ref py_SymbolicExpression_page getSymbolicMemory(integer addr)</b><br>
Returns the \ref py_SymbolicExpression_page corresponding to a memory address.

- <b>integer getSymbolicMemoryValue(integer addr)</b><br>
Returns the symbolic memory value.

- <b>integer getSymbolicMemoryValue(\ref py_MemoryAccess_page mem)</b><br>
Returns the symbolic memory value.

- <b>dict getSymbolicRegisters(void)</b><br>
Returns the map of symbolic register as {\ref py_REG_page reg : \ref py_SymbolicExpression_page expr}.

- <b>\ref py_SymbolicExpression_page getSymbolicRegister(\ref py_Register_page reg)</b><br>
Returns the \ref py_SymbolicExpression_page corresponding to the parent register.

- <b>integer getSymbolicRegisterValue(\ref py_Register_page reg)</b><br>
Returns the symbolic register value.

- <b>\ref py_SymbolicVariable_page getSymbolicVariableFromId(integer symVarId)</b><br>
Returns the symbolic variable corresponding to a symbolic variable id.

- <b>\ref py_SymbolicVariable_page getSymbolicVariableFromName(string symVarName)</b><br>
Returns the symbolic variable corresponding to a symbolic variable name.

- <b>dict getSymbolicVariables(void)</b><br>
Returns all symbolic variable as a dictionary of {integer SymVarId : \ref py_SymbolicVariable_page var}.

- <b>[integer, ...] getTaintedMemory(void)</b><br>
Returns the list of all tainted addresses.

- <b>[\ref py_Register_page, ...] getTaintedRegisters(void)</b><br>
Returns the list of all tainted registers.

- <b>[\ref py_SymbolicExpression_page, ...] getTaintedSymbolicExpressions(void)</b><br>
Returns the list of all tainted symbolic expressions.

- <b>bool isArchitectureValid(void)</b><br>
Returns true if the architecture is valid.

- <b>bool isFlag(\ref py_Register_page reg)</b><br>
Returns true if the register is a flag.

- <b>bool isMemoryMapped(integer baseAddr, integer size=1)</b><br>
Returns true if the range `[baseAddr:size]` is mapped into the internal memory representation.

- <b>bool isMemorySymbolized(integer addr)</b><br>
Returns true if the memory cell expression contains a symbolic variable.

- <b>bool isMemorySymbolized(\ref py_MemoryAccess_page mem)</b><br>
Returns true if memory cell expressions contain symbolic variables.

- <b>bool isMemoryTainted(integer addr)</b><br>
Returns true if the address is tainted.

- <b>bool isMemoryTainted(\ref py_MemoryAccess_page mem)</b><br>
Returns true if the memory is tainted.

- <b>bool isModeEnabled(\ref py_MODE_page mode)</b><br>
Returns true if the mode is enabled.

- <b>bool isRegister(\ref py_Register_page reg)</b><br>
Returns true if the register is a register (see also isFlag()).

- <b>bool isRegisterSymbolized(\ref py_Register_page reg)</b><br>
Returns true if the register expression contains a symbolic variable.

- <b>bool isRegisterTainted(\ref py_Register_page reg)</b><br>
Returns true if the register is tainted.

- <b>bool isRegisterValid(\ref py_Register_page reg)</b><br>
Returns true if the register is valid.

- <b>bool isSat(\ref py_AstNode_page node)</b><br>
Returns true if an expression is satisfiable.

- <b>bool isSymbolicEngineEnabled(void)</b><br>
Returns true if the symbolic execution engine is enabled.

- <b>bool isSymbolicExpressionIdExists(integer symExprId)</b><br>
Returns true if the symbolic expression id exists.

- <b>bool isTaintEngineEnabled(void)</b><br>
Returns true if the taint engine is enabled.

- <b>\ref py_SymbolicExpression_page newSymbolicExpression(\ref py_AstNode_page node, string comment)</b><br>
Returns a new symbolic expression. Note that if there are simplification passes recorded, simplifications will be applied.

- <b>\ref py_SymbolicVariable_page newSymbolicVariable(integer varSize, string comment)</b><br>
Returns a new symbolic variable.

- <b>bool processing(\ref py_Instruction_page inst)</b><br>
Processes an instruction and updates engines according to the instruction semantics. Returns true if the instruction is supported. You must define an architecture before.

- <b>void removeAllCallbacks(void)</b><br>
Removes all recorded callbacks.

- <b>void removeCallback(function cb, \ref py_CALLBACK_page kind)</b><br>
Removes a recorded callback.

- <b>void reset(void)</b><br>
Resets everything.

- <b>void setArchitecture(\ref py_ARCH_page arch)</b><br>
Initializes an architecture. This function must be called before any call to the rest of the API.

- <b>void setAstRepresentationMode(\ref py_AST_REPRESENTATION_page mode)</b><br>
Sets the AST representation mode.

- <b>void setConcreteMemoryAreaValue(integer baseAddr, [integer,])</b><br>
Sets the concrete value of a memory area. Note that by setting a concrete value will probably imply a desynchronization with
the symbolic state (if it exists). You should probably use the concretize functions after this.

- <b>void setConcreteMemoryAreaValue(integer baseAddr, bytes opcodes)</b><br>
Sets the concrete value of a memory area. Note that by setting a concrete value will probably imply a desynchronization with
the symbolic state (if it exists). You should probably use the concretize functions after this.

- <b>void setConcreteMemoryValue(integer addr, integer value)</b><br>
Sets the concrete value of a memory cell. Note that by setting a concrete value will probably imply a desynchronization with
the symbolic state (if it exists). You should probably use the concretize functions after this.

- <b>void setConcreteMemoryValue(\ref py_MemoryAccess_page mem, integer value)</b><br>
Sets the concrete value of memory cells. Note that by setting a concrete value will probably imply a desynchronization with
the symbolic state (if it exists). You should probably use the concretize functions after this.

- <b>void setConcreteRegisterValue(\ref py_Register_page reg, integer value)</b><br>
Sets the concrete value of a register. Note that by setting a concrete value will probably imply a desynchronization with
the symbolic state (if it exists). You should probably use the concretize functions after this.

- <b>void setConcreteVariableValue(\ref py_SymbolicVariable_page symVar, integer value)</b><br>
Sets the concrete value of a symbolic variable.

- <b>bool setTaintMemory(\ref py_MemoryAccess_page mem, bool flag)</b><br>
Sets the targeted memory as tainted or not. Returns true if the memory is still tainted.

- <b>bool setTaintRegister(\ref py_Register_page reg, bool flag)</b><br>
Sets the targeted register as tainted or not. Returns true if the register is still tainted.

- <b>\ref py_AstNode_page simplify(\ref py_AstNode_page node, bool z3=False)</b><br>
Calls all simplification callbacks recorded and returns a new simplified node. If the `z3` flag is
set to True, Triton will use z3 to simplify the given `node` before to call its recorded callbacks.

- <b>dict sliceExpressions(\ref py_SymbolicExpression_page expr)</b><br>
Slices expressions from a given one (backward slicing) and returns all symbolic expressions as a dictionary of {integer SymExprId : \ref py_SymbolicExpression_page expr}.

- <b>bool taintAssignmentMemoryImmediate(\ref py_MemoryAccess_page memDst)</b><br>
Taints `memDst` with an assignment - `memDst` is untained. Returns true if the `memDst` is still tainted.

- <b>bool taintAssignmentMemoryMemory(\ref py_MemoryAccess_page memDst, \ref py_MemoryAccess_page memSrc)</b><br>
Taints `memDst` from `memSrc` with an assignment - `memDst` is tainted if `memSrc` is tainted, otherwise
`memDst` is untained. Returns true if `memDst` is tainted.

- <b>bool taintAssignmentMemoryRegister(\ref py_MemoryAccess_page memDst, \ref py_Register_page regSrc)</b><br>
Taints `memDst` from `regSrc` with an assignment - `memDst` is tainted if `regSrc` is tainted, otherwise
`memDst` is untained. Return true if `memDst` is tainted.

- <b>bool taintAssignmentRegisterImmediate(\ref py_Register_page regDst)</b><br>
Taints `regDst` with an assignment - `regDst` is untained. Returns true if `reDst` is still tainted.

- <b>bool taintAssignmentRegisterMemory(\ref py_Register_page regDst, \ref py_MemoryAccess_page memSrc)</b><br>
Taints `regDst` from `MemSrc` with an assignment - `regDst` is tainted if `memSrc` is tainted, otherwise
`regDst` is untained. Return true if `regDst` is tainted.

- <b>bool taintAssignmentRegisterRegister(\ref py_Register_page regDst, \ref py_Register_page regSrc)</b><br>
Taints `regDst` from `regSrc` with an assignment - `regDst` is tainted if `regSrc` is tainted, otherwise
`regDst` is untained. Return true if `regDst` is tainted.

- <b>bool taintMemory(integer addr)</b><br>
Taints an address. Returns true if the address is tainted.

- <b>bool taintMemory(\ref py_MemoryAccess_page mem)</b><br>
Taints a memory. Returns true if the memory is tainted.

- <b>bool taintRegister(\ref py_Register_page reg)</b><br>
Taints a register. Returns true if the register is tainted.

- <b>bool taintUnionMemoryImmediate(\ref py_MemoryAccess_page memDst)</b><br>
Taints `memDst` with an union - `memDst` does not changes. Returns true if `memDst` is tainted.

- <b>bool taintUnionMemoryMemory(\ref py_MemoryAccess_page memDst, \ref py_MemoryAccess_page memSrc)</b><br>
Taints `memDst` from `memSrc` with an union - `memDst` is tainted if `memDst` or `memSrc` are
tainted. Returns true if `memDst` is tainted.

- <b>bool taintUnionMemoryRegister(\ref py_MemoryAccess_page memDst, \ref py_Register_page regSrc)</b><br>
Taints `memDst` from `RegSrc` with an union - `memDst` is tainted if `memDst` or `regSrc` are
tainted. Returns true if `memDst` is tainted.

- <b>bool taintUnionRegisterImmediate(\ref py_Register_page regDst)</b><br>
Taints `regDst` with an union - `regDst` does not changes. Returns true if `regDst` is tainted.

- <b>bool taintUnionRegisterMemory(\ref py_Register_page regDst, \ref py_MemoryAccess_page memSrc)</b><br>
Taints `regDst` from `memSrc` with an union - `regDst` is tainted if `regDst` or `memSrc` are
tainted. Returns true if `regDst` is tainted.

- <b>bool taintUnionRegisterRegister(\ref py_Register_page regDst, \ref py_Register_page regSrc)</b><br>
Taints `regDst` from `regSrc` with an union - `regDst` is tainted if `regDst` or `regSrc` are
tainted. Returns true if `regDst` is tainted.

- <b>void unmapMemory(integer baseAddr, integer size=1)</b><br>
Removes the range `[baseAddr:size]` from the internal memory representation.

- <b>bool untaintMemory(integer addr)</b><br>
Untaints an address. Returns true if the address is still tainted.

- <b>bool untaintMemory(\ref py_MemoryAccess_page mem)</b><br>
Untaints a memory. Returns true if the memory is still tainted.

- <b>bool untaintRegister(\ref py_Register_page reg)</b><br>
Untaints a register. Returns true if the register is still tainted.

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initTritonContextObject(pybind11::module& pyTriton) {

        // TODO: removeCallback
        // TODO: addCallback
        // TODO: getParentRegisters() -> return a clean list of Register. Even in the C++ API?
        // TODO: getAllRegisters() -> return a clean list of Register. Even in the C++ API?
        // TODO: OperandWrapper
        // TODO: Operator ==, >, < pour Imm, Mem, Reg, Ins...
        // TODO: Faire la synchro API <-> doc

        auto ctx = pybind11::class_<triton::API>(pyTriton, "TritonContext", "The TritonContext class")

          .def(pybind11::init<>())

          .def("assignSymbolicExpressionToMemory",    &triton::API::assignSymbolicExpressionToMemory)
          .def("assignSymbolicExpressionToRegister",  &triton::API::assignSymbolicExpressionToRegister)
          .def("buildSemantics",                      &triton::API::buildSemantics)
          .def("clearPathConstraints",                &triton::API::clearPathConstraints)
          .def("concretizeAllMemory",                 &triton::API::concretizeAllMemory)
          .def("concretizeAllRegister",               &triton::API::concretizeAllRegister)
          .def("concretizeRegister",                  &triton::API::concretizeRegister)
          .def("disassembly",                         &triton::API::disassembly)
          .def("enableMode",                          &triton::API::enableMode)
          .def("enableSymbolicEngine",                &triton::API::enableSymbolicEngine)
          .def("enableTaintEngine",                   &triton::API::enableTaintEngine)
          .def("getAllRegisters",                     &triton::API::getAllRegisters, pybind11::return_value_policy::reference_internal)
          .def("getArchitecture",                     &triton::API::getArchitecture)
          .def("getAstContext",                       &triton::API::getAstContext, pybind11::return_value_policy::reference_internal)
          .def("getAstRepresentationMode",            &triton::API::getAstRepresentationMode)
          .def("getGprBitSize",                       &triton::API::getGprBitSize)
          .def("getGprSize",                          &triton::API::getGprSize)
          .def("getModel",                            &triton::API::getModel)
          .def("getModels",                           &triton::API::getModels)
          .def("getParentRegisters",                  &triton::API::getParentRegisters, pybind11::return_value_policy::reference_internal)
          .def("getPathConstraints",                  &triton::API::getPathConstraints, pybind11::return_value_policy::reference_internal)
          .def("getPathConstraintsAst",               &triton::API::getPathConstraintsAst)
          .def("getRegister",                         &triton::API::getRegister, pybind11::return_value_policy::reference_internal)
          .def("getSymbolicExpressionFromId",         &triton::API::getSymbolicExpressionFromId)
          .def("getSymbolicExpressions",              &triton::API::getSymbolicExpressions)
          .def("getSymbolicRegister",                 &triton::API::getSymbolicRegister, pybind11::return_value_policy::reference_internal)
          .def("getSymbolicRegisters",                &triton::API::getSymbolicRegisters)
          .def("getSymbolicVariableFromId",           &triton::API::getSymbolicVariableFromId, pybind11::return_value_policy::reference_internal)
          .def("getSymbolicVariableFromName",         &triton::API::getSymbolicVariableFromName, pybind11::return_value_policy::reference_internal)
          .def("getSymbolicVariables",                &triton::API::getSymbolicVariables, pybind11::return_value_policy::reference_internal)
          .def("getTaintedMemory",                    &triton::API::getTaintedMemory, pybind11::return_value_policy::reference_internal)
          .def("getTaintedRegisters",                 &triton::API::getTaintedRegisters, pybind11::return_value_policy::reference_internal)
          .def("getTaintedSymbolicExpressions",       &triton::API::getTaintedSymbolicExpressions)
          .def("isArchitectureValid",                 &triton::API::isArchitectureValid)
          .def("isModeEnabled",                       &triton::API::isModeEnabled)
          .def("isRegisterSymbolized",                &triton::API::isRegisterSymbolized)
          .def("isRegisterTainted",                   &triton::API::isRegisterTainted)
          .def("isSat",                               &triton::API::isSat)
          .def("isSymbolicEngineEnabled",             &triton::API::isSymbolicEngineEnabled)
          .def("isSymbolicExpressionIdExists",        &triton::API::isSymbolicExpressionIdExists)
          .def("isTaintEngineEnabled",                &triton::API::isTaintEngineEnabled)
          .def("processing",                          &triton::API::processing)
          .def("removeAllCallbacks",                  &triton::API::removeAllCallbacks)
          .def("reset",                               &triton::API::reset)
          .def("setArchitecture",                     &triton::API::setArchitecture)
          .def("setAstRepresentationMode",            &triton::API::setAstRepresentationMode)
          .def("setTaintMemory",                      &triton::API::setTaintMemory)
          .def("setTaintRegister",                    &triton::API::setTaintRegister)
          .def("sliceExpressions",                    &triton::API::sliceExpressions)
          .def("taintAssignmentMemoryImmediate",      &triton::API::taintAssignmentMemoryImmediate)
          .def("taintAssignmentMemoryMemory",         &triton::API::taintAssignmentMemoryMemory)
          .def("taintAssignmentMemoryRegister",       &triton::API::taintAssignmentMemoryRegister)
          .def("taintAssignmentRegisterImmediate",    &triton::API::taintAssignmentRegisterImmediate)
          .def("taintAssignmentRegisterMemory",       &triton::API::taintAssignmentRegisterMemory)
          .def("taintAssignmentRegisterRegister",     &triton::API::taintAssignmentRegisterRegister)
          .def("taintRegister",                       &triton::API::taintRegister)
          .def("taintUnionMemoryImmediate",           &triton::API::taintUnionMemoryImmediate)
          .def("taintUnionMemoryMemory",              &triton::API::taintUnionMemoryMemory)
          .def("taintUnionMemoryRegister",            &triton::API::taintUnionMemoryRegister)
          .def("taintUnionRegisterImmediate",         &triton::API::taintUnionRegisterImmediate)
          .def("taintUnionRegisterMemory",            &triton::API::taintUnionRegisterMemory)
          .def("taintUnionRegisterRegister",          &triton::API::taintUnionRegisterRegister)
          .def("untaintRegister",                     &triton::API::untaintRegister)

          //.def("addCallback",                         &triton::API::addCallback)

          .def("concretizeMemory",
            [] (triton::API& self, const triton::arch::MemoryAccess& mem) {
              self.concretizeMemory(mem);
            })

          .def("concretizeMemory",
            [] (triton::API& self, triton::uint64 addr) {
              self.concretizeMemory(addr);
            })

          .def("convertExpressionToSymbolicVariable",
            [] (triton::API& self, triton::usize id, triton::uint32 size, const std::string& comment) {
              return self.convertExpressionToSymbolicVariable(id, size, comment);
            }, pybind11::return_value_policy::reference_internal)

          .def("convertExpressionToSymbolicVariable",
            [] (triton::API& self, triton::usize id, triton::uint32 size) {
              return self.convertExpressionToSymbolicVariable(id, size);
            }, pybind11::return_value_policy::reference_internal)

          .def("convertMemoryToSymbolicVariable",
            [] (triton::API& self, const triton::arch::MemoryAccess& mem, const std::string& comment) {
              return self.convertMemoryToSymbolicVariable(mem, comment);
            }, pybind11::return_value_policy::reference_internal)

          .def("convertMemoryToSymbolicVariable",
            [] (triton::API& self, const triton::arch::MemoryAccess& mem) {
              return self.convertMemoryToSymbolicVariable(mem);
            }, pybind11::return_value_policy::reference_internal)

          .def("convertRegisterToSymbolicVariable",
            [] (triton::API& self, const triton::arch::Register& reg, const std::string& comment) {
              return self.convertRegisterToSymbolicVariable(reg, comment);
            }, pybind11::return_value_policy::reference_internal)

          .def("convertRegisterToSymbolicVariable",
            [] (triton::API& self, const triton::arch::Register& reg) {
              return self.convertRegisterToSymbolicVariable(reg);
            }, pybind11::return_value_policy::reference_internal)

          .def("createSymbolicFlagExpression",
            [] (triton::API& self, triton::arch::Instruction& inst, const triton::ast::SharedAbstractNode& node, const triton::arch::Register& flag, const std::string& comment) {
              return self.createSymbolicFlagExpression(inst, node, flag, comment);
            }, pybind11::return_value_policy::reference_internal)

          .def("createSymbolicFlagExpression",
            [] (triton::API& self, triton::arch::Instruction& inst, const triton::ast::SharedAbstractNode& node, const triton::arch::Register& flag) {
              return self.createSymbolicFlagExpression(inst, node, flag);
            }, pybind11::return_value_policy::reference_internal)

          .def("createSymbolicMemoryExpression",
            [] (triton::API& self, triton::arch::Instruction& inst, const triton::ast::SharedAbstractNode& node, const triton::arch::MemoryAccess& mem, const std::string& comment) {
              return self.createSymbolicMemoryExpression(inst, node, mem, comment);
            }, pybind11::return_value_policy::reference_internal)

          .def("createSymbolicMemoryExpression",
            [] (triton::API& self, triton::arch::Instruction& inst, const triton::ast::SharedAbstractNode& node, const triton::arch::MemoryAccess& mem) {
              return self.createSymbolicMemoryExpression(inst, node, mem);
            }, pybind11::return_value_policy::reference_internal)

          .def("createSymbolicRegisterExpression",
            [] (triton::API& self, triton::arch::Instruction& inst, const triton::ast::SharedAbstractNode& node, const triton::arch::Register& reg, const std::string& comment) {
              return self.createSymbolicRegisterExpression(inst, node, reg, comment);
            }, pybind11::return_value_policy::reference_internal)

          .def("createSymbolicRegisterExpression",
            [] (triton::API& self, triton::arch::Instruction& inst, const triton::ast::SharedAbstractNode& node, const triton::arch::Register& reg) {
              return self.createSymbolicRegisterExpression(inst, node, reg);
            }, pybind11::return_value_policy::reference_internal)

          .def("createSymbolicVolatileExpression",
            [] (triton::API& self, triton::arch::Instruction& inst, const triton::ast::SharedAbstractNode& node, const std::string& comment) {
              return self.createSymbolicVolatileExpression(inst, node, comment);
            }, pybind11::return_value_policy::reference_internal)

          .def("createSymbolicVolatileExpression",
            [] (triton::API& self, triton::arch::Instruction& inst, const triton::ast::SharedAbstractNode& node) {
              return self.createSymbolicVolatileExpression(inst, node);
            }, pybind11::return_value_policy::reference_internal)

          .def("evaluateAstViaZ3",
            [] (triton::API& self, const triton::ast::SharedAbstractNode& node) -> pybind11::object {
              return pybind11::reinterpret_borrow<pybind11::object>(PyLong_FromUint512(self.evaluateAstViaZ3(node)));
            })

          .def("getConcreteMemoryAreaValue",
            [] (triton::API& self, triton::uint64 addr, triton::usize size) {
              std::vector<triton::uint8> vv = self.getConcreteMemoryAreaValue(addr, size);
              triton::uint8* area = new triton::uint8[vv.size()];

              for (triton::usize index = 0; index < vv.size(); index++)
                area[index] = vv[index];

              std::string s(reinterpret_cast<const char*>(area), vv.size());
              delete[] area;
              return pybind11::bytes(s);
            })

          .def("getConcreteMemoryValue",
            [] (triton::API& self, triton::uint64 addr) -> pybind11::object {
              return pybind11::reinterpret_borrow<pybind11::object>(PyLong_FromUint512(self.getConcreteMemoryValue(addr)));
            })

          .def("getConcreteMemoryValue",
            [] (triton::API& self, const triton::arch::MemoryAccess& mem) -> pybind11::object {
              return pybind11::reinterpret_borrow<pybind11::object>(PyLong_FromUint512(self.getConcreteMemoryValue(mem)));
            })

          .def("getConcreteRegisterValue",
            [] (triton::API& self, const triton::arch::Register& reg) -> pybind11::object {
              return pybind11::reinterpret_borrow<pybind11::object>(PyLong_FromUint512(self.getConcreteRegisterValue(reg)));
            })

          .def("getSymbolicMemoryValue",
            [] (triton::API& self, const triton::arch::MemoryAccess& mem) -> pybind11::object {
              return pybind11::reinterpret_borrow<pybind11::object>(PyLong_FromUint512(self.getSymbolicMemoryValue(mem)));
            })

          .def("getSymbolicRegisterValue",
            [] (triton::API& self, const triton::arch::Register& reg) -> pybind11::object {
              return pybind11::reinterpret_borrow<pybind11::object>(PyLong_FromUint512(self.getSymbolicRegisterValue(reg)));
            })

          .def("getConcreteVariableValue",
            [] (triton::API& self, const triton::engines::symbolic::SharedSymbolicVariable& var) -> pybind11::object {
              return pybind11::reinterpret_borrow<pybind11::object>(PyLong_FromUint512(self.getConcreteVariableValue(var)));
            }, pybind11::return_value_policy::reference_internal)

          .def("getImmediateAst",
            [] (triton::API& self, const triton::arch::Immediate& imm) {
              return self.getImmediateAst(imm);
            })

          .def("getMemoryAst",
            [] (triton::API& self, const triton::arch::MemoryAccess& mem) {
              return self.getMemoryAst(mem);
            })

          .def("getParentRegister",
            [] (triton::API& self, const triton::arch::Register& reg) {
              return self.getParentRegister(reg);
            }, pybind11::return_value_policy::reference_internal)

          .def("getParentRegister",
            [] (triton::API& self, triton::arch::register_e regId) {
              return self.getParentRegister(regId);
            }, pybind11::return_value_policy::reference_internal)

          .def("getRegisterAst",
            [] (triton::API& self, const triton::arch::Register& reg) {
              return self.getRegisterAst(reg);
            })

          .def("getSymbolicMemory",
            [] (triton::API& self) {
              return self.getSymbolicMemory();
            })

          .def("getSymbolicMemory",
            [] (triton::API& self, triton::uint64 addr) {
              return self.getSymbolicMemory(addr);
            })

          .def("isMemoryMapped",
            [] (triton::API& self, triton::uint64 addr) {
              return self.isMemoryMapped(addr);
            })

          .def("isMemoryMapped",
            [] (triton::API& self, triton::uint64 addr, triton::usize size) {
              return self.isMemoryMapped(addr, size);
            })

          .def("isMemorySymbolized",
            [] (triton::API& self, triton::uint64 addr) {
              return self.isMemorySymbolized(addr);
            })

          .def("isMemorySymbolized",
            [] (triton::API& self, triton::uint64 addr, triton::usize size) {
              return self.isMemorySymbolized(addr, size);
            })

          .def("isMemorySymbolized",
            [] (triton::API& self, const triton::arch::MemoryAccess& mem) {
              return self.isMemorySymbolized(mem);
            })

          .def("isMemoryTainted",
            [] (triton::API& self, triton::uint64 addr) {
              return self.isMemoryTainted(addr);
            })

          .def("isMemoryTainted",
            [] (triton::API& self, triton::uint64 addr, triton::usize size) {
              return self.isMemoryTainted(addr, size);
            })

          .def("isMemoryTainted",
            [] (triton::API& self, const triton::arch::MemoryAccess& mem) {
              return self.isMemoryTainted(mem);
            })

          .def("isFlag",
            [] (triton::API& self, triton::arch::register_e regId) {
              return self.isFlag(regId);
            })

          .def("isFlag",
            [] (triton::API& self, const triton::arch::Register& reg) {
              return self.isFlag(reg);
            })

          .def("isRegister",
            [] (triton::API& self, triton::arch::register_e regId) {
              return self.isRegister(regId);
            })

          .def("isRegister",
            [] (triton::API& self, const triton::arch::Register& reg) {
              return self.isRegister(reg);
            })

          .def("isRegisterValid",
            [] (triton::API& self, triton::arch::register_e regId) {
              return self.isRegisterValid(regId);
            })

          .def("isRegisterValid",
            [] (triton::API& self, const triton::arch::Register& reg) {
              return self.isRegisterValid(reg);
            })

          .def("newSymbolicExpression",
            [] (triton::API& self, const triton::ast::SharedAbstractNode& node, const std::string& comment) {
              return self.newSymbolicExpression(node, comment);
            })

          .def("newSymbolicExpression",
            [] (triton::API& self, const triton::ast::SharedAbstractNode& node) {
              return self.newSymbolicExpression(node);
            })

          .def("newSymbolicVariable",
            [] (triton::API& self, triton::uint32 varSize, const std::string& comment) {
              return self.newSymbolicVariable(varSize, comment);
            }, pybind11::return_value_policy::reference_internal)

          .def("newSymbolicVariable",
            [] (triton::API& self, triton::uint32 varSize) {
              return self.newSymbolicVariable(varSize);
            }, pybind11::return_value_policy::reference_internal)

          //.def("removeCallback",                      &triton::API::removeCallback)

          .def("setConcreteMemoryAreaValue",
            [] (triton::API& self, triton::uint64 baseAddr, const std::vector<triton::uint8>& values) {
              self.setConcreteMemoryAreaValue(baseAddr, values);
            })

          .def("setConcreteMemoryAreaValue",
            [] (triton::API& self, triton::uint64 baseAddr, pybind11::bytes area) {
              std::string s = area.cast<std::string>();
              self.setConcreteMemoryAreaValue(baseAddr, reinterpret_cast<const triton::uint8*>(s.data()), s.size());
            })

          .def("setConcreteMemoryValue",
            [] (triton::API& self, triton::uint64 addr, triton::uint8 value) {
              self.setConcreteMemoryValue(addr, value);
            })

          .def("setConcreteMemoryValue",
            [] (triton::API& self, const triton::arch::MemoryAccess& mem, pybind11::int_ value) {
              self.setConcreteMemoryValue(mem, PyLong_AsUint512(value.ptr()));
            })

          .def("setConcreteRegisterValue",
            [] (triton::API& self, const triton::arch::Register& reg, pybind11::int_ value) {
              self.setConcreteRegisterValue(reg, PyLong_AsUint512(value.ptr()));
            })

          .def("setConcreteVariableValue",
            [] (triton::API& self, const triton::engines::symbolic::SharedSymbolicVariable& symVar, pybind11::int_ value) {
              self.setConcreteVariableValue(symVar, PyLong_AsUint512(value.ptr()));
            })

          .def("simplify",
            [] (triton::API& self, const triton::ast::SharedAbstractNode& node, bool z3) {
              return self.processSimplification(node, z3);
            })

          .def("simplify",
            [] (triton::API& self, const triton::ast::SharedAbstractNode& node) {
              return self.processSimplification(node);
            })

          .def("taintMemory",
            [] (triton::API& self, triton::uint64 addr) {
              return self.taintMemory(addr);
            })

          .def("taintMemory",
            [] (triton::API& self, const triton::arch::MemoryAccess& mem) {
              return self.taintMemory(mem);
            })

          .def("unmapMemory",
            [] (triton::API& self, triton::uint64 addr) {
              return self.unmapMemory(addr);
            })

          .def("unmapMemory",
            [] (triton::API& self, triton::uint64 addr, triton::usize size) {
              return self.unmapMemory(addr, size);
            })

          .def("untaintMemory",
            [] (triton::API& self, triton::uint64 addr) {
              return self.untaintMemory(addr);
            })

          .def("untaintMemory",
            [] (triton::API& self, const triton::arch::MemoryAccess& mem) {
              return self.untaintMemory(mem);
            })

          .def_readonly("registers", &triton::API::registers);
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
