//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/instruction.hpp>

#include <string>



/*! \page py_Instruction_page Instruction
    \brief [**python api**] All information about the Instruction python object.

\tableofcontents

\section py_Instruction_description Description
<hr>

This object is used to represent an Instruction.

~~~~~~~~~~~~~{.py}
>>> from triton import TritonContext, ARCH, Instruction, OPERAND

>>> trace = [
...     (0x400000, "\x48\x8b\x05\xb8\x13\x00\x00"), # mov        rax, QWORD PTR [rip+0x13b8]
...     (0x400007, "\x48\x8d\x34\xc3"),             # lea        rsi, [rbx+rax*8]
...     (0x40000b, "\x67\x48\x8D\x74\xC3\x0A"),     # lea        rsi, [ebx+eax*8+0xa]
...     (0x400011, "\x66\x0F\xD7\xD1"),             # pmovmskb   edx, xmm1
...     (0x400015, "\x89\xd0"),                     # mov        eax, edx
...     (0x400017, "\x80\xf4\x99"),                 # xor        ah, 0x99
... ]

>>> ctxt = TritonContext()

# Set the arch
>>> ctxt.setArchitecture(ARCH.X86_64)

>>> for (addr, opcode) in trace:
...
...     # Build an instruction
...     inst = Instruction()
...
...     # Setup opcode
...     inst.setOpcode(opcode)
...
...     # Setup Address
...     inst.setAddress(addr)
...
...     # Process everything
...     if not ctxt.processing(inst):
...         print "Fail an instruction"
...
...     print inst
...     for op in inst.getOperands():
...         print '   ', op
...         if op.getType() == OPERAND.MEM:
...             print '         base  : ', op.getBaseRegister()
...             print '         index : ', op.getIndexRegister()
...             print '         disp  : ', op.getDisplacement()
...             print '         scale : ', op.getScale()
...     print
0x400000: mov rax, qword ptr [rip + 0x13b8]
    rax:64 bv[63..0]
    [@0x4013bf]:64 bv[63..0]
         base  :  rip:64 bv[63..0]
         index :  unknown:1 bv[0..0]
         disp  :  0x13b8:64 bv[63..0]
         scale :  0x1:64 bv[63..0]
<BLANKLINE>
0x400007: lea rsi, [rbx + rax*8]
    rsi:64 bv[63..0]
    [@0x0]:64 bv[63..0]
         base  :  rbx:64 bv[63..0]
         index :  rax:64 bv[63..0]
         disp  :  0x0:64 bv[63..0]
         scale :  0x8:64 bv[63..0]
<BLANKLINE>
0x40000b: lea rsi, [ebx + eax*8 + 0xa]
    rsi:64 bv[63..0]
    [@0xa]:64 bv[63..0]
         base  :  ebx:32 bv[31..0]
         index :  eax:32 bv[31..0]
         disp  :  0xa:32 bv[31..0]
         scale :  0x8:32 bv[31..0]
<BLANKLINE>
0x400011: pmovmskb edx, xmm1
    edx:32 bv[31..0]
    xmm1:128 bv[127..0]
<BLANKLINE>
0x400015: mov eax, edx
    eax:32 bv[31..0]
    edx:32 bv[31..0]
<BLANKLINE>
0x400017: xor ah, 0x99
    ah:8 bv[15..8]
    0x99:8 bv[7..0]
<BLANKLINE>

~~~~~~~~~~~~~

\subsection py_Instruction_constructor Constructor

~~~~~~~~~~~~~{.py}
>>> inst = Instruction("\x48\xC7\xC0\x01\x00\x00\x00")
>>> inst.setAddress(0x40000)
>>> ctxt.processing(inst)
True
>>> print inst
0x40000: mov rax, 1

~~~~~~~~~~~~~

~~~~~~~~~~~~~{.py}
>>> inst = Instruction()
>>> inst.setAddress(0x40000)
>>> inst.setOpcode("\x48\xC7\xC0\x01\x00\x00\x00")
>>> ctxt.processing(inst)
True
>>> print inst
0x40000: mov rax, 1

~~~~~~~~~~~~~

\section Instruction_py_api Python API - Methods of the Instruction class
<hr>

- <b>integer getAddress(void)</b><br>
Returns the address of the instruction.

- <b>integer getCodeCondition(void)</b><br>
Returns the code condition of the instruction (mainly used for AArch64).

- <b>string getDisassembly(void)</b><br>
Returns the disassembly of the instruction.

- <b>[tuple, ...] getLoadAccess(void)</b><br>
Returns the list of all implicit and explicit LOAD access as list of tuple <\ref py_MemoryAccess_page, \ref py_AstNode_page>.

- <b>integer getNextAddress(void)</b><br>
Returns the next address of the instruction.

- <b>bytes getOpcode(void)</b><br>
Returns the opcode of the instruction.

- <b>[\ref py_Immediate_page, \ref py_MemoryAccess_page, \ref py_Register_page, ...] getOperands(void)</b><br>
Returns the operands of the instruction as list of \ref py_Immediate_page, \ref py_MemoryAccess_page or \ref py_Register_page.

- <b>\ref py_PREFIX_page getPrefix(void)</b><br>
Returns the instruction prefix. Mainly used for X86.

- <b>[tuple, ...] getReadImmediates(void)</b><br>
Returns a list of tuple <\ref py_Immediate_page, \ref py_AstNode_page> which represents all implicit and explicit immediate inputs.

- <b>[tuple, ...] getReadRegisters(void)</b><br>
Returns a list of tuple <\ref py_Register_page, \ref py_AstNode_page> which represents all implicit and explicit register (flags includes) inputs.

- <b>integer getSize(void)</b><br>
Returns the size of the instruction.

- <b>[tuple, ...] getStoreAccess(void)</b><br>
Returns the list of all implicit and explicit STORE access as list of tuple <\ref py_MemoryAccess_page, \ref py_AstNode_page>.

- <b>[\ref py_SymbolicExpression_page, ...] getSymbolicExpressions(void)</b><br>
Returns the list of symbolic expressions of the instruction.

- <b>integer getThreadId(void)</b><br>
Returns the thread id of the instruction.

- <b>\ref py_OPCODE_page getType(void)</b><br>
Returns the type of the instruction.

- <b>[\ref py_Register_page, ...] getUndefinedRegisters(void)</b><br>
Returns a list \ref py_Register_page which represents all implicit and explicit undefined registers.

- <b>[tuple, ...] getWrittenRegisters(void)</b><br>
Returns a list of tuple <\ref py_Register_page, \ref py_AstNode_page> which represents all implicit and explicit register (flags includes) outputs.

- <b>bool isBranch(void)</b><br>
Returns true if the instruction is a branch (i.e x86: JUMP, JCC).

- <b>bool isConditionTaken(void)</b><br>
Returns true if the condition is taken (i.e x86: JCC, CMOVCC, SETCC, ...).

- <b>bool isControlFlow(void)</b><br>
Returns true if the instruction modifies the control flow (i.e x86: JUMP, JCC, CALL, RET).

- <b>bool isMemoryRead(void)</b><br>
Returns true if the instruction contains an expression which reads the memory.

- <b>bool isMemoryWrite(void)</b><br>
Returns true if the instruction contains an expression which writes into the memory.

- <b>bool isPrefixed(void)</b><br>
Returns true if the instruction has a prefix.

- <b>bool isSymbolized(void)</b><br>
Returns true if at least one of its \ref py_SymbolicExpression_page contains a symbolic variable.

- <b>bool isTainted(void)</b><br>
Returns true if at least one of its \ref py_SymbolicExpression_page is tainted.

- <b>bool isWriteBack(void)</b><br>
Returns true if the instruction performs a write back. Mainly used for AArch64 instructions like LDR.

- <b>void setAddress(integer addr)</b><br>
Sets the address of the instruction.

- <b>void setOpcode(bytes opcode)</b><br>
Sets the opcode of the instruction.

- <b>void setThreadId(integer tid)</b><br>
Sets the thread id of the instruction.

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initInstructionObject(pybind11::module& pyTriton) {
        pybind11::class_<triton::arch::Instruction>(pyTriton, "Instruction", "The Instruction class")

          .def(pybind11::init<>())
          .def("__init__",
            [] (triton::arch::Instruction& inst, pybind11::bytes opcode) {
              std::string s = opcode.cast<std::string>();
              new (&inst) triton::arch::Instruction(reinterpret_cast<const triton::uint8*>(s.data()), s.size());
            })

          .def("getAddress",                &triton::arch::Instruction::getAddress)
          .def("getCodeCondition",          &triton::arch::Instruction::getCodeCondition)
          .def("getDisassembly",            &triton::arch::Instruction::getDisassembly)
          .def("getLoadAccess",             &triton::arch::Instruction::getLoadAccess, pybind11::return_value_policy::reference_internal)
          .def("getNextAddress",            &triton::arch::Instruction::getNextAddress)
          .def("getPrefix",                 &triton::arch::Instruction::getPrefix)
          .def("getReadImmediates",         &triton::arch::Instruction::getReadImmediates, pybind11::return_value_policy::reference_internal)
          .def("getReadRegisters",          &triton::arch::Instruction::getReadRegisters, pybind11::return_value_policy::reference_internal)
          .def("getSize",                   &triton::arch::Instruction::getSize)
          .def("getStoreAccess",            &triton::arch::Instruction::getStoreAccess, pybind11::return_value_policy::reference_internal)
          .def("getThreadId",               &triton::arch::Instruction::getThreadId)
          .def("getType",                   &triton::arch::Instruction::getType)
          .def("getUndefinedRegisters",     &triton::arch::Instruction::getUndefinedRegisters, pybind11::return_value_policy::reference_internal)
          .def("getWrittenRegisters",       &triton::arch::Instruction::getWrittenRegisters, pybind11::return_value_policy::reference_internal)
          .def("isBranch",                  &triton::arch::Instruction::isBranch)
          .def("isConditionTaken",          &triton::arch::Instruction::isConditionTaken)
          .def("isControlFlow",             &triton::arch::Instruction::isControlFlow)
          .def("isMemoryRead",              &triton::arch::Instruction::isMemoryRead)
          .def("isMemoryWrite",             &triton::arch::Instruction::isMemoryWrite)
          .def("isPrefixed",                &triton::arch::Instruction::isPrefixed)
          .def("isSymbolized",              &triton::arch::Instruction::isSymbolized)
          .def("isTainted",                 &triton::arch::Instruction::isTainted)
          .def("isWriteBack",               &triton::arch::Instruction::isWriteBack)
          .def("setAddress",                &triton::arch::Instruction::setAddress)
          .def("setThreadId",               &triton::arch::Instruction::setThreadId)

          .def("getOpcode",
            [] (const triton::arch::Instruction& self) -> pybind11::bytes {
              return std::string(reinterpret_cast<const char*>(self.getOpcode()), self.getSize());
            })

          .def("getOperands",
            [] (const triton::arch::Instruction& self) {
              return self.operands;
            }, pybind11::return_value_policy::reference_internal)

          .def("getSymbolicExpressions",
            [] (const triton::arch::Instruction& self) {
              return self.symbolicExpressions;
            }, pybind11::return_value_policy::reference_internal)

          .def("setOpcode",
            [] (triton::arch::Instruction& self, pybind11::bytes opcode) {
              std::string s = opcode.cast<std::string>();
              self.setOpcode(reinterpret_cast<const triton::uint8*>(s.data()), s.size());
            })

          .def("__repr__",
            [] (const triton::arch::Instruction& inst) {
              std::ostringstream stream;
              stream << inst;
              return stream.str();
            })

          .def("__str__",
            [] (const triton::arch::Instruction& inst) {
              std::ostringstream stream;
              stream << inst;
              return stream.str();
            });
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
