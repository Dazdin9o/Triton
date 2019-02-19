//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/archEnums.hpp>



/*! \page py_EXTEND_page EXTEND
    \brief [**python api**] All information about the EXTEND python namespace.

\tableofcontents

\section EXTEND_py_description Description
<hr>

The EXTEND namespace contains all kinds of extend operand for AArch64.

\section EXTEND_py_api Python API - Items of the EXTEND namespace
<hr>

- **EXTEND.AARCH64.INVALID**<br>
Invalid extend operand.

- **EXTEND.AARCH64.UXTB**<br>
Extracts a byte (8-bit) value from a register and zero extends it to the size of the register.

- **EXTEND.AARCH64.UXTH**<br>
Extracts a halfword (16-bit) value from a register and zero extends it to the size of the register.

- **EXTEND.AARCH64.UXTW**<br>
Extracts a word (32-bit) value from a register and zero extends it to the size of the register

- **EXTEND.AARCH64.UXTX**<br>
Use the whole 64-bit register

- **EXTEND.AARCH64.SXTB**<br>
Extracts a byte (8-bit) value from a register and zero extends it to the size of the register

- **EXTEND.AARCH64.SXTH**<br>
Extracts a halfword (16-bit) value from a register and zero extends it to the size of the register

- **EXTEND.AARCH64.SXTW**<br>
Extracts a word (32-bit) value from a register and zero extends it to the size of the register

- **EXTEND.AARCH64.SXTX**<br>
Use the whole 64-bit register

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initExtendEnum(pybind11::module& pyTriton) {
        /* Define a submodule */
        pybind11::module extend = pyTriton.def_submodule("EXTEND", "");

        /* EXTEND Enum */
        pybind11::enum_<triton::arch::aarch64::extend_e>(extend, "AARCH64")
          .value("INVALID", triton::arch::aarch64::ID_EXTEND_INVALID)
          .value("UXTB",    triton::arch::aarch64::ID_EXTEND_UXTB)
          .value("UXTH",    triton::arch::aarch64::ID_EXTEND_UXTH)
          .value("UXTW",    triton::arch::aarch64::ID_EXTEND_UXTW)
          .value("UXTX",    triton::arch::aarch64::ID_EXTEND_UXTX)
          .value("SXTB",    triton::arch::aarch64::ID_EXTEND_SXTB)
          .value("SXTH",    triton::arch::aarch64::ID_EXTEND_SXTH)
          .value("SXTW",    triton::arch::aarch64::ID_EXTEND_SXTW)
          .value("SXTX",    triton::arch::aarch64::ID_EXTEND_SXTX);
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
