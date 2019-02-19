//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/archEnums.hpp>



/*! \page py_OPERAND_page OPERAND
    \brief [**python api**] All information about the OPERAND python namespace.

\tableofcontents

\section OPERAND_py_description Description
<hr>

The OPERAND namespace contains all kinds of operand.

\section OPERAND_py_api Python API - Items of the OPERAND namespace
<hr>

- **OPERAND.INVALID**
- **OPERAND.IMM**
- **OPERAND.MEM**
- **OPERAND.REG**

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initOperandEnum(pybind11::module& pyTriton) {
        /* OPERAND Enum */
        pybind11::enum_<triton::arch::operand_e>(pyTriton, "OPERAND")
          .value("OP_INVALID", triton::arch::OP_INVALID)
          .value("OP_IMM",     triton::arch::OP_IMM)
          .value("OP_REG",     triton::arch::OP_REG)
          .value("OP_MEM",     triton::arch::OP_MEM);
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
