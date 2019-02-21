//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/cpuSize.hpp>



/*! \page py_CPUSIZE_page CPUSIZE
    \brief [**python api**] All information about the CPUSIZE python namespace.

\tableofcontents

\section CPUSIZE_py_description Description
<hr>

According to the CPU architecture, the CPUSIZE namespace contains all kinds of size.

\section CPUSIZE_py_api Python API - Items of the CPUSIZE namespace
<hr>

- **CPUSIZE.BYTE**<br>
Returns `1`

- **CPUSIZE.BYTE_BIT**<br>
Returns `8`

- **CPUSIZE.WORD**<br>
Returns `2`

- **CPUSIZE.WORD_BIT**<br>
Returns `16`

- **CPUSIZE.DWORD**<br>
Returns `4`

- **CPUSIZE.DWORD_BIT**<br>
Returns `32`

- **CPUSIZE.QWORD**<br>
Returns `8`

- **CPUSIZE.QWORD_BIT**<br>
Returns `64`

- **CPUSIZE.DQWORD**<br>
Returns `16`

- **CPUSIZE.DQWORD_BIT**<br>
Returns `128`

- **CPUSIZE.QQWORD**<br>
Returns `32`

- **CPUSIZE.QQWORD_BIT**<br>
Returns `256`

- **CPUSIZE.DQQWORD**<br>
Returns `64`

- **CPUSIZE.DQQWORD_BIT**<br>
Returns `512`

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initCpuSizeEnum(pybind11::module& pyTriton) {
        /* Define a submodule */
        pybind11::module cpusize = pyTriton.def_submodule("CPU_SIZE", "");
        cpusize.attr("BYTE") = BYTE_SIZE;
        cpusize.attr("BYTE_BIT") = BYTE_SIZE_BIT;
        cpusize.attr("WORD") = WORD_SIZE;
        cpusize.attr("WORD_BIT") = WORD_SIZE_BIT;
        cpusize.attr("DWORD") = DWORD_SIZE;
        cpusize.attr("DWORD_BIT") = DWORD_SIZE_BIT;
        cpusize.attr("QWORD") = QWORD_SIZE;
        cpusize.attr("QWORD_BIT") = QWORD_SIZE_BIT;
        cpusize.attr("DQWORD") = DQWORD_SIZE;
        cpusize.attr("DQWORD_BIT") = DQWORD_SIZE_BIT;
        cpusize.attr("QQWORD") = QQWORD_SIZE;
        cpusize.attr("QQWORD_BIT") = QQWORD_SIZE_BIT;
        cpusize.attr("DQQWORD") = DQQWORD_SIZE;
        cpusize.attr("DQQWORD_BIT") = DQQWORD_SIZE_BIT;
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
