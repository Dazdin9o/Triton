//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/archEnums.hpp>



/*! \page py_PREFIX_page PREFIX
    \brief [**python api**] All information about the PREFIX python namespace.

\tableofcontents

\section PREFIX_py_description Description
<hr>

According to the CPU architecture, the PREFIX namespace contains all kinds of instruction prefixes.

\section PREFIX_py_api Python API - Items of the PREFIX namespace
<hr>

\subsection PREFIX_x86_py_api x86 and x86_64

- **PREFIX.X86.INVALID**<br>
- **PREFIX.X86.LOCK**<br>
- **PREFIX.X86.REP**<br>
- **PREFIX.X86.REPE**<br>
- **PREFIX.X86.REPNE**<br>

*/


namespace triton {
  namespace bindings {
    namespace python {

      void initPrefixEnum(pybind11::module& pyTriton) {
        /* Define a submodule */
        pybind11::module prefix = pyTriton.def_submodule("PREFIX", "");

        /* PREFIX.X86 Enum */
        pybind11::enum_<triton::arch::x86::prefix_e>(prefix, "X86")
          .value("INVALID", triton::arch::x86::ID_PREFIX_INVALID)
          .value("LOCK",    triton::arch::x86::ID_PREFIX_LOCK)
          .value("REP",     triton::arch::x86::ID_PREFIX_REP)
          .value("REPE",    triton::arch::x86::ID_PREFIX_REPE)
          .value("REPNE",   triton::arch::x86::ID_PREFIX_REPNE);
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
