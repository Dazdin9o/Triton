//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/symbolicEnums.hpp>



/*! \page py_SYMBOLIC_page SYMBOLIC
    \brief [**python api**] All information about the SYMBOLIC python namespace.

\tableofcontents

\section SYMBOLIC_py_description Description
<hr>

The SYMBOLIC namespace contains all types of symbolic expressions and variables.

\section SYMBOLIC_py_api Python API - Items of the SYMBOLIC namespace
<hr>

- **SYMBOLIC.EXPRESSION.MEMORY**
- **SYMBOLIC.EXPRESSION.REGISTER**
- **SYMBOLIC.EXPRESSION.VOLATILE**

- **SYMBOLIC.VARIABLE.MEMORY**
- **SYMBOLIC.VARIABLE.REGISTER**
- **SYMBOLIC.VARIABLE.UNDEFINED**

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initSymbolicEnum(pybind11::module& pyTriton) {
        /* Define a submodule */
        pybind11::module symbolic = pyTriton.def_submodule("SYMBOLIC", "");

        /* SYMBOLIC.EXPRESSION Enum */
        pybind11::enum_<triton::engines::symbolic::expression_e>(symbolic, "EXPRESSION")
          .value("MEMORY",   triton::engines::symbolic::MEMORY_EXPRESSION)
          .value("REGISTER", triton::engines::symbolic::REGISTER_EXPRESSION)
          .value("VOLATILE", triton::engines::symbolic::VOLATILE_EXPRESSION);

        pybind11::enum_<triton::engines::symbolic::variable_e>(symbolic, "VARIABLE")
          .value("MEMORY",    triton::engines::symbolic::MEMORY_VARIABLE)
          .value("REGISTER",  triton::engines::symbolic::REGISTER_VARIABLE)
          .value("UNDEFINED", triton::engines::symbolic::UNDEFINED_VARIABLE);
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
