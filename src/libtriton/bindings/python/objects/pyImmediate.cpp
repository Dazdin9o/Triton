//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/cpuSize.hpp>
#include <triton/immediate.hpp>



/* setup doctest context

>>> from triton import TritonContext, ARCH, Instruction, Immediate, CPU_SIZE

>>> ctxt = TritonContext()
>>> ctxt.setArchitecture(ARCH.X86_64)

>>> inst = Instruction()
>>> inst.setOpcode("\xB8\x14\x00\x00\x00")

*/

/*! \page py_Immediate_page Immediate
    \brief [**python api**] All information about the Immediate python object.

\tableofcontents

\section py_Immediate_description Description
<hr>

This object is used to represent an immediate.

\subsection py_Immediate_example Example

~~~~~~~~~~~~~{.py}
>>> ctxt.processing(inst)
True
>>> print inst
0x0: mov eax, 0x14

>>> op1 = inst.getOperands()[1]
>>> print op1
0x14:32 bv[31..0]

>>> print hex(op1.getValue())
0x14L

>>> print op1.getBitSize()
32

~~~~~~~~~~~~~

\subsection py_Immediate_constructor Constructor

~~~~~~~~~~~~~{.py}
>>> imm = Immediate(0x1234, CPU_SIZE.WORD)
>>> print imm
0x1234:16 bv[15..0]
>>> imm.getValue()
4660L
>>> imm.getSize()
2L
>>> imm.getBitSize()
16L

~~~~~~~~~~~~~

\section Immediate_py_api Python API - Methods of the Immediate class
<hr>

- <b>integer getBitSize(void)</b><br>
Returns the size (in bits) of the immediate.<br>
e.g: `64`

- <b>\ref py_BitsVector_page getBitvector(void)</b><br>
Returns the bitvector.

- <b>\ref py_SHIFT_page getShiftType(void)</b><br>
Returns the shift type of the operand. Mainly used for AArch64.<br>
e.g: `SHIFT.AARCH64.LSL`

- <b>integer getShiftValue(void)</b><br>
Returns the shift value of the operand. Mainly used for AArch64.<br>
e.g: `2`

- <b>integer getSize(void)</b><br>
Returns the size (in bytes) of the immediate.<br>
e.g: `8`

- <b>\ref py_OPERAND_page getType(void)</b><br>
Returns the type of the immediate. In this case this function returns `OPERAND.IMM`.

- <b>integer getValue(void)</b><br>
Returns the immediate value.

- <b>void setValue(integer value, integer size)</b><br>
Sets the immediate value.

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initImmediateObject(pybind11::module& pyTriton) {
        pybind11::class_<triton::arch::Immediate>(pyTriton, "Immediate", "The Immediate class")
          .def(pybind11::init<>())
          .def(pybind11::init<triton::sint64, triton::uint32>())
          .def(pybind11::init<pybind11::int_, triton::uint32>())

          .def("getBitSize",    &triton::arch::Immediate::getBitSize)
          .def("getShiftType",  &triton::arch::Immediate::getShiftType)
          .def("getShiftValue", &triton::arch::Immediate::getShiftValue)
          .def("getSize",       &triton::arch::Immediate::getSize)
          .def("getType",       &triton::arch::Immediate::getType)
          .def("getValue",      &triton::arch::Immediate::getValue)
          .def("setValue",      &triton::arch::Immediate::setValue)

          .def("getBitvector",
            [] (const triton::arch::Immediate& self) -> triton::arch::BitsVector {
              return static_cast<triton::arch::BitsVector>(self);
            })

          .def("__repr__",
            [] (const triton::arch::Immediate& imm) {
              std::ostringstream stream;
              stream << imm;
              return stream.str();
            })

          .def("__str__",
            [] (const triton::arch::Immediate& imm) {
              std::ostringstream stream;
              stream << imm;
              return stream.str();
            });
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
