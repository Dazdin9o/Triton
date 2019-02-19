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
        enum cpuSize {};

        pybind11::enum_<cpuSize>(pyTriton, "CPU_SIZE")
          .value("BYTE",        static_cast<cpuSize>(BYTE_SIZE))
          .value("BYTE_BIT",    static_cast<cpuSize>(BYTE_SIZE_BIT))
          .value("WORD",        static_cast<cpuSize>(WORD_SIZE))
          .value("WORD_BIT",    static_cast<cpuSize>(WORD_SIZE_BIT))
          .value("DWORD",       static_cast<cpuSize>(DWORD_SIZE))
          .value("DWORD_BIT",   static_cast<cpuSize>(DWORD_SIZE_BIT))
          .value("QWORD",       static_cast<cpuSize>(QWORD_SIZE))
          .value("QWORD_BIT",   static_cast<cpuSize>(QWORD_SIZE_BIT))
          .value("DQWORD",      static_cast<cpuSize>(DQWORD_SIZE))
          .value("DQWORD_BIT",  static_cast<cpuSize>(DQWORD_SIZE_BIT))
          .value("QQWORD",      static_cast<cpuSize>(QQWORD_SIZE))
          .value("QQWORD_BIT",  static_cast<cpuSize>(QQWORD_SIZE_BIT))
          .value("DQQWORD",     static_cast<cpuSize>(DQQWORD_SIZE))
          .value("DQQWORD_BIT", static_cast<cpuSize>(DQQWORD_SIZE_BIT));
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
