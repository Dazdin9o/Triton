//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/memoryAccess.hpp>



/* setup doctest context

>>> from triton import TritonContext, ARCH, Instruction, MemoryAccess
>>> ctxt = TritonContext()
>>> ctxt.setArchitecture(ARCH.X86_64)

>>> inst = Instruction("\x8A\xA4\x4A\x00\x01\x00\x00")
>>> inst.setAddress(0x40000)

*/

/*! \page py_MemoryAccess_page MemoryAccess
    \brief [**python api**] All information about the memory access python object.

\tableofcontents

\section py_Memory_description Description
<hr>

This object is used to represent a memory access.

\subsection py_MemoryAccess_example Example

~~~~~~~~~~~~~{.py}
>>> ctxt.processing(inst)
True
>>> print inst
0x40000: mov ah, byte ptr [rdx + rcx*2 + 0x100]

>>> op1 = inst.getOperands()[1]
>>> print op1
[@0x100]:8 bv[7..0]

>>> print op1.getBaseRegister()
rdx:64 bv[63..0]

>>> print op1.getIndexRegister()
rcx:64 bv[63..0]

>>> print op1.getScale()
0x2:64 bv[63..0]

>>> print op1.getDisplacement()
0x100:64 bv[63..0]

>>> print op1.getLeaAst()
(bvadd (_ bv0 64) (bvadd (bvmul (_ bv0 64) (_ bv2 64)) (_ bv256 64)))

>>> print hex(op1.getLeaAst().evaluate())
0x100L

>>> print hex(op1.getAddress())
0x100L

>>> print op1.getSize()
1

~~~~~~~~~~~~~

\subsection py_MemoryAccess_constructor Constructor

~~~~~~~~~~~~~{.py}
>>> mem = MemoryAccess(0x400f4d3, 8)
>>> print mem
[@0x400f4d3]:64 bv[63..0]

>>> hex(mem.getAddress())
'0x400f4d3L'

>>> mem.getSize()
8L

~~~~~~~~~~~~~

\section MemoryAccess_py_api Python API - Methods of the MemoryAccess class
<hr>

- <b>integer getAddress(void)</b><br>
Returns the target address of the memory access.<br>
e.g: `0x7fffdd745ae0`

- <b>\ref py_Register_page getBaseRegister(void)</b><br>
Returns the base register (if exists) of the memory access<br>

- <b>integer getBitSize(void)</b><br>
Returns the size (in bits) of the memory access.<br>
e.g: `64`

- <b>\ref py_BitsVector_page getBitvector(void)</b><br>
Returns the bitvector of the memory cells.

- <b>\ref py_Immediate_page getDisplacement(void)</b><br>
Returns the displacement (if exists) of the memory access.

- <b>\ref py_Register_page getIndexRegister(void)</b><br>
Returns the index register (if exists) of the memory access.<br>

- <b>\ref py_AstNode_page getLeaAst(void)</b><br>
Returns the AST of the memory access (LEA).

- <b>\ref py_Immediate_page getScale(void)</b><br>
Returns the scale (if exists) of the  memory access.

- <b>\ref py_Register_page getSegmentRegister(void)</b><br>
Returns the segment register (if exists) of the memory access. Note that to be user-friendly, the
segment register is used as base register and not as a selector into the GDT.<br>

- <b>integer getSize(void)</b><br>
Returns the size (in bytes) of the  memory access.<br>
e.g: `8`

- <b>\ref py_OPERAND_page getType(void)</b><br>
Returns type of the memory access. In this case this function returns `OPERAND.MEM`.

- <b>bool isOverlapWith(\ref py_MemoryAccess_page other)</b><br>
Returns true if `other` and `self` overlap.

- <b>void setBaseRegister(\ref py_Register_page reg)</b><br>
Sets the base register of the memory access.

- <b>void setDisplacement(\ref py_Immediate_page imm)</b><br>
Sets the displacement of the memory access.

- <b>void setIndexRegister(\ref py_Register_page reg)</b><br>
Sets the index register of the memory' access.

- <b>void setScale(\ref py_Immediate_page imm)</b><br>
Sets the scale of the memory access.

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initMemoryAccessObject(pybind11::module& pyTriton) {
        pybind11::class_<triton::arch::MemoryAccess>(pyTriton, "MemoryAccess", "The MemoryAccess class")

          .def(pybind11::init<>())
          .def(pybind11::init<triton::uint64, triton::uint32>())

          .def("getAddress",          &triton::arch::MemoryAccess::getAddress)
          .def("getBaseRegister",     &triton::arch::MemoryAccess::getBaseRegister)
          .def("getBitSize",          &triton::arch::MemoryAccess::getBitSize)
          .def("getDisplacement",     &triton::arch::MemoryAccess::getDisplacement)
          .def("getIndexRegister",    &triton::arch::MemoryAccess::getIndexRegister)
          .def("getLeaAst",           &triton::arch::MemoryAccess::getLeaAst)
          .def("getScale",            &triton::arch::MemoryAccess::getScale)
          .def("getSegmentRegister",  &triton::arch::MemoryAccess::getSegmentRegister)
          .def("getSize",             &triton::arch::MemoryAccess::getSize)
          .def("getType",             &triton::arch::MemoryAccess::getType)
          .def("isOverlapWith",       &triton::arch::MemoryAccess::isOverlapWith)
          .def("setBaseRegister",     &triton::arch::MemoryAccess::setBaseRegister)
          .def("setDisplacement",     &triton::arch::MemoryAccess::setDisplacement)
          .def("setIndexRegister",    &triton::arch::MemoryAccess::setIndexRegister)
          .def("setScale",            &triton::arch::MemoryAccess::setScale)
          .def("setSegmentRegister",  &triton::arch::MemoryAccess::setSegmentRegister)

          .def("getBitvector",
            [] (const triton::arch::MemoryAccess& self) -> triton::arch::BitsVector {
              return static_cast<triton::arch::BitsVector>(self);
            })

          .def("__repr__",
            [] (const triton::arch::MemoryAccess& mem) {
              std::ostringstream stream;
              stream << mem;
              return stream.str();
            })

          .def("__str__",
            [] (const triton::arch::MemoryAccess& mem) {
              std::ostringstream stream;
              stream << mem;
              return stream.str();
            });
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
