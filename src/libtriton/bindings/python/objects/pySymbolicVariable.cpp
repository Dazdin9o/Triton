//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/symbolicVariable.hpp>



/* setup doctest context

>>> from triton import TritonContext, REG, ARCH
>>> ctxt = TritonContext()
>>> ctxt.setArchitecture(ARCH.X86_64)

*/

/*! \page py_SymbolicVariable_page SymbolicVariable
    \brief [**python api**] All information about the SymbolicVariable python object.

\tableofcontents

\section py_SymbolicVariable_description Description
<hr>

This object is used to represent a symbolic variable.

~~~~~~~~~~~~~{.py}
>>> symvar = ctxt.convertRegisterToSymbolicVariable(ctxt.registers.rax)
>>> print symvar
SymVar_0:64

~~~~~~~~~~~~~

\section SymbolicVariable_py_api Python API - Methods of the SymbolicVariable class
<hr>

- <b>string getAlias(void)</b><br>
Returns the alias (if exists) of the symbolic variable.

- <b>string getComment(void)</b><br>
Returns the comment (if exists) of the symbolic variable.

- <b>integer getId(void)</b><br>
Returns the id of the symbolic variable. This id is always unique.<br>
e.g: `18`

- <b>string getName(void)</b><br>
Returns name of the the symbolic variable.<br>
e.g: `SymVar_18`

- <b>integer getOrigin(void)</b><br>
Returns the origin according to the \ref py_SYMBOLIC_page value.<br>
If `getType()` returns triton::engines::symbolic::REGISTER_VARIABLE, so `getOrigin()` returns the id of the register.<br>
Otherwise, if `getType()` returns triton::engines::symbolic::MEMORY_VARIABLE, so `getOrigin()` returns the address of the memory access.<br>
Then, if `getType()` returns triton::engines::symbolic::UNDEFINED_VARIABLE, so `getOrigin()` returns `0`.

- <b>integer getSize(void)</b><br>
Returns the size (in bits) of the symbolic variable.

- <b>\ref py_SYMBOLIC_page getType(void)</b><br>
Returns the type of the symbolic variable.<br>
e.g: `SYMBOLIC.REGISTER_VARIABLE`

- <b>void setAlias(string alias)</b><br>
Sets an alias to the symbolic variable.

- <b>void setComment(string comment)</b><br>
Sets a comment to the symbolic variable.

*/



using namespace triton::engines::symbolic;

namespace triton {
  namespace bindings {
    namespace python {

      void initSymbolicVariableObject(pybind11::module& pyTriton) {
        pybind11::class_<SymbolicVariable, SharedSymbolicVariable>(pyTriton, "SymbolicVariable", "The SymbolicVariable class")

          .def("getAlias",    &SymbolicVariable::getAlias, pybind11::return_value_policy::copy)
          .def("getComment",  &SymbolicVariable::getComment, pybind11::return_value_policy::copy)
          .def("getId",       &SymbolicVariable::getId)
          .def("getName",     &SymbolicVariable::getName, pybind11::return_value_policy::copy)
          .def("getOrigin",   &SymbolicVariable::getOrigin)
          .def("getSize",     &SymbolicVariable::getSize)
          .def("getType",     &SymbolicVariable::getType)
          .def("setAlias",    &SymbolicVariable::setAlias)
          .def("setComment",  &SymbolicVariable::setComment)

          .def("__repr__",
            [] (const SharedSymbolicVariable& var) {
              std::ostringstream stream;
              stream << var;
              return stream.str();
            })

          .def("__str__",
            [] (const SharedSymbolicVariable& var) {
              std::ostringstream stream;
              stream << var;
              return stream.str();
            });
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
