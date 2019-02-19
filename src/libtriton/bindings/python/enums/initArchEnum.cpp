//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/archEnums.hpp>



/*! \page py_ARCH_page ARCH
    \brief [**python api**] All information about the ARCH python namespace.

\tableofcontents

\section ARCH_py_description Description
<hr>

The ARCH namespace contains all kinds of architecture supported by Triton.

\section ARCH_py_api Python API - Items of the ARCH namespace
<hr>

- **ARCH.AARCH64**
- **ARCH.X86**
- **ARCH.X86_64**

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initArchEnum(pybind11::module& pyTriton) {
        /* ARCH Enum */
        pybind11::enum_<triton::arch::architecture_e>(pyTriton, "ARCH")
          .value("AARCH64", triton::arch::ARCH_AARCH64)
          .value("X86",     triton::arch::ARCH_X86)
          .value("X86_64",  triton::arch::ARCH_X86_64);
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
