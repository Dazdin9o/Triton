//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/register.hpp>



/* setup doctest context

>>> from triton import ARCH, TritonContext, Instruction, REG
>>> ctxt = TritonContext()
>>> ctxt.setArchitecture(ARCH.X86_64)

>>> inst = Instruction("\x8A\xA4\x4A\x00\x01\x00\x00")
>>> inst.setAddress(0x40000)

*/

/*! \page py_Register_page Register
    \brief [**python api**] All information about the Register python object.

\tableofcontents

\section py_Register_description Description
<hr>

This object is used to represent a register operand according to the CPU architecture.


\subsection py_Register_example Example

~~~~~~~~~~~~~{.py}
>>> ctxt.processing(inst)
True
>>> print inst
0x40000: mov ah, byte ptr [rdx + rcx*2 + 0x100]

>>> op0 = inst.getOperands()[0]
>>> print op0
ah:8 bv[15..8]

>>> op0.getName()
'ah'

>>> op0.getSize()
1L

>>> op0.getBitSize()
8L

>>> ctxt.getParentRegister(op0).getName()
'rax'

~~~~~~~~~~~~~

\subsection py_Register_constructor Constructor

~~~~~~~~~~~~~{.py}
>>> ah = ctxt.getRegister(REG.X86_64.AH)
>>> print ah
ah:8 bv[15..8]

>>> print ah.getBitSize()
8

>>> print ctxt.registers.rax
rax:64 bv[63..0]

~~~~~~~~~~~~~

\section Register_py_api Python API - Methods of the Register class
<hr>

- <b>integer getBitSize(void)</b><br>
Returns the size (in bits) of the register.<br>
e.g: `64`

- <b>\ref py_BitsVector_page getBitvector(void)</b><br>
Returns the bitvector of the register.

- <b>\ref py_EXTEND_page getExtendSize(void)</b><br>
Returns the size (in bits) of the extend. Mainly used for AArch64.<br>
e.g: `16`

- <b>\ref py_EXTEND_page getExtendType(void)</b><br>
Returns the extend type of the operand. Mainly used for AArch64.<br>
e.g: `EXTEND.AARCH64.UXTW`

- <b>\ref py_REG_page getId(void)</b><br>
Returns the enum of the register.<br>
e.g: `REG.X86_64.RBX`

- <b>string getName(void)</b><br>
Returns the name of the register.<br>
e.g: `rbx`

- <b>\ref py_SHIFT_page getShiftType(void)</b><br>
Returns the shift type of the operand. Mainly used for AArch64.<br>
e.g: `SHIFT.AARCH64.LSL`

- <b>integer getShiftValue(void)</b><br>
Returns the shift value of the operand. Mainly used for AArch64.<br>
e.g: `2`

- <b>integer getSize(void)</b><br>
Returns the size (in bytes) of the register.<br>
e.g: `8`

- <b>\ref py_OPERAND_page getType(void)</b><br>
Returns type of the register. In this case this function returns `OPERAND.REG`.

- <b>bool isMutable(void)</b><br>
Returns true if this register is mutable. Mainly used in AArch64 to define that some registers like XZR are immutable.

- <b>bool isOverlapWith(\ref py_Register_page other)</b><br>
Returns true if `other` and `self` overlap.

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initRegisterObject(pybind11::module& pyTriton) {
        pybind11::class_<triton::arch::Register>(pyTriton, "Register", "The Register class")

          .def("getBitSize",                &triton::arch::Register::getBitSize)
          .def("getExtendSize",             &triton::arch::Register::getExtendSize)
          .def("getExtendType",             &triton::arch::Register::getExtendType)
          .def("getId",                     &triton::arch::Register::getId)
          .def("getName",                   &triton::arch::Register::getName)
          .def("getShiftType",              &triton::arch::Register::getShiftType)
          .def("getShiftValue",             &triton::arch::Register::getShiftValue)
          .def("getSize",                   &triton::arch::Register::getSize)
          .def("getType",                   &triton::arch::Register::getType)
          .def("isMutable",                 &triton::arch::Register::isMutable)
          .def("isOverlapWith",             &triton::arch::Register::isOverlapWith)

          .def("getBitvector",
            [] (const triton::arch::Register& self) -> triton::arch::BitsVector {
              return static_cast<triton::arch::BitsVector>(self);
            })

          .def("__repr__",
            [] (const triton::arch::Register& reg) {
              std::ostringstream stream;
              stream << reg;
              return stream.str();
            })

          .def("__str__",
            [] (const triton::arch::Register& reg) {
              std::ostringstream stream;
              stream << reg;
              return stream.str();
            });
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
