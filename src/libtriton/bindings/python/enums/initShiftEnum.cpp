//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/archEnums.hpp>



/*! \page py_SHIFT_page SHIFT
    \brief [**python api**] All information about the SHIFT python namespace.

\tableofcontents

\section SHIFT_py_description Description
<hr>

The SHIFT namespace contains all kinds of shift operand for AArch64.

\section SHIFT_py_api Python API - Items of the SHIFT namespace
<hr>

- **SHIFT.AARCH64.INVALID**<br>
Invalid shift operand.

- **SHIFT.AARCH64.ASR**<br>
Arithmetic Shift Right operand.

- **SHIFT.AARCH64.LSL**<br>
Logical Shift Left operand.

- **SHIFT.AARCH64.LSR**<br>
Logical Shift Right operand.

- **SHIFT.AARCH64.ROR**<br>
Rotate Right operand.

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initShiftEnum(pybind11::module& pyTriton) {
        /* Define a submodule */
        pybind11::module shift = pyTriton.def_submodule("SHIFT", "");

        /* SHIFT Enum */
        pybind11::enum_<triton::arch::aarch64::shift_e>(shift, "AARCH64")
          .value("INVALID", triton::arch::aarch64::ID_SHIFT_INVALID)
          .value("ASR",     triton::arch::aarch64::ID_SHIFT_ASR)
          .value("LSL",     triton::arch::aarch64::ID_SHIFT_LSL)
          .value("LSR",     triton::arch::aarch64::ID_SHIFT_LSR)
          .value("ROR",     triton::arch::aarch64::ID_SHIFT_ROR);
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
