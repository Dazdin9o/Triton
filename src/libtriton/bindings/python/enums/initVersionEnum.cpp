//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/version.hpp>



/*! \page py_VERSION_page VERSION
    \brief [**python api**] All information about the VERSION python namespace.

\tableofcontents

\section VERSION_py_description Description
<hr>

The VERSION namespace contains all version numbers.

\section VERSION_py_api Python API - Items of the VERSION namespace
<hr>

- **VERSION.MAJOR**
- **VERSION.MINOR**
- **VERSION.BUILD**

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initVersionEnum(pybind11::module& pyTriton) {
        /* VERSION Enum */
        pybind11::enum_<triton::version_e>(pyTriton, "VERSION")
          .value("MAJOR", triton::MAJOR)
          .value("MINOR", triton::MINOR)
          .value("BUILD", triton::BUILD);
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
