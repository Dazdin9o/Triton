//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/pythonUtils.hpp>
#include <triton/solverModel.hpp>



/*! \page py_SolverModel_page SolverModel
    \brief [**python api**] All information about the SolverModel python object.

\tableofcontents

\section py_SolverModel_description Description
<hr>

This object is used to represent a model from an SMT solver.

~~~~~~~~~~~~~{.py}
>>> from triton import TritonContext, ARCH, Instruction, REG

>>> ctxt = TritonContext()
>>> ctxt.setArchitecture(ARCH.X86_64)
>>> inst = Instruction()
>>> inst.setOpcode("\x48\x35\x44\x33\x22\x11") # xor rax, 0x11223344

>>> symvar = ctxt.convertRegisterToSymbolicVariable(ctxt.registers.rax)
>>> print symvar
SymVar_0:64

>>> ctxt.processing(inst)
True
>>> print inst
0x0: xor rax, 0x11223344

>>> ast = ctxt.getAstContext()
>>> raxAst = ast.unrollAst(ctxt.getSymbolicRegister(ctxt.registers.rax).getAst())
>>> print raxAst
(bvxor SymVar_0 (_ bv287454020 64))

>>> astCtxt = ctxt.getAstContext()
>>> constraint = astCtxt.equal(raxAst, astCtxt.bv(0, raxAst.getBitvectorSize()))
>>> print constraint
(= (bvxor SymVar_0 (_ bv287454020 64)) (_ bv0 64))

>>> model = ctxt.getModel(constraint)
>>> print model #doctest: +ELLIPSIS
{0L: <SolverModel object at 0x...>}

>>> symvarModel =  model[symvar.getId()] # Model from the symvar's id
>>> print symvarModel
SymVar_0:64 = 0x11223344
>>> hex(symvarModel.getValue())
'0x11223344L'

~~~~~~~~~~~~~

\section SolverModel_py_api Python API - Methods of the SolverModel class
<hr>

- <b>integer getId(void)</b><br>
Returns the id of the model. This id is the same that the variable id.

- <b>integer getValue(void)</b><br>
Returns the value of the model.

- <b>\ref py_SymbolicVariable_page getVariable(void)</b><br>
Returns the symbolic variable.

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initSolverModelObject(pybind11::module& pyTriton) {
        pybind11::class_<triton::engines::solver::SolverModel>(pyTriton, "SolverModel", "The SolverModel class")

          .def("getId",       &triton::engines::solver::SolverModel::getId)
          .def("getVariable", &triton::engines::solver::SolverModel::getVariable, pybind11::return_value_policy::reference_internal)

          .def("getValue",
            [] (const triton::engines::solver::SolverModel& self) -> pybind11::object {
              return pybind11::reinterpret_borrow<pybind11::object>(PyLong_FromUint512(self.getValue()));
            })

          .def("__repr__",
            [] (const triton::engines::solver::SolverModel& model) {
              std::ostringstream stream;
              stream << model;
              return stream.str();
            })

          .def("__str__",
            [] (const triton::engines::solver::SolverModel& model) {
              std::ostringstream stream;
              stream << model;
              return stream.str();
            });
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
