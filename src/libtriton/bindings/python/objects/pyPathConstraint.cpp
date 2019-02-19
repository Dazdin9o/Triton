//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/pathConstraint.hpp>



/* setup doctest context

>>> from triton import TritonContext, ARCH
>>> ctxt = TritonContext()
>>> ctxt.setArchitecture(ARCH.X86_64)
>>> astCtxt = ctxt.getAstContext()

*/

/*! \page py_PathConstraint_page PathConstraint
    \brief [**python api**] All information about the PathConstraint python object.

\tableofcontents

\section py_PathConstraint_description Description
<hr>

This object is used to represent a path constraint.

~~~~~~~~~~~~~{.py}
>>> pcl = ctxt.getPathConstraints()
>>> for pc in pcl:
...     if pc.isMultipleBranches():
...         b1   =  pc.getBranchConstraints()[0]['constraint']
...         b2   =  pc.getBranchConstraints()[1]['constraint']
...
...         print 'Constraint branch 1:', b1
...         print 'Constraint branch 2:', b2
...
...         seed = list()
...
...         # Branch 1, we assume that the path constraint contains a symbolic variable
...         models  = ctxt.getModel(b)
...         for k, v in models.items():
...             seed.append(v)
...
...         # Branch 2, we assume that the path constraint contains a symbolic variable.
...         models  = ctxt.getModel(b2)
...         for k, v in models.items():
...             seed.append(v)
...
...         if seed:
...             print 'B1: %s (%c)  |  B2: %s (%c)' % (seed[0], chr(seed[0].getValue()), seed[1], chr(seed[1].getValue()))
...

~~~~~~~~~~~~~

A possible output is :

~~~~~~~~~~~~~{.py}
Constraint branch 1: (not (= (ite (= ((_ extract 0 0) ref!179) (_ bv1 1)) (_ bv4195769 64) (_ bv4195762 64)) (_ bv4195762 64)))
Constraint branch 2: (= (ite (= ((_ extract 0 0) ref!179) (_ bv1 1)) (_ bv4195769 64) (_ bv4195762 64)) (_ bv4195762 64))
B1: SymVar_0 = 65 (e)  |  B2: SymVar_0 = 0 ()
[...]
~~~~~~~~~~~~~

\section PathConstraint_py_api Python API - Methods of the PathConstraint class
<hr>

- <b>dict getBranchConstraints(void)</b><br>
Returns the branch constraints as list of dictionary `{isTaken, srcAddr, dstAddr, constraint}`. The source address is the location
of the branch instruction and the destination address is the destination of the jump. E.g: `"0x11223344: jne 0x55667788"`, 0x11223344
is the source address and 0x55667788 is the destination if and only if the branch is taken, otherwise the destination is the next
instruction address.

- <b>integer getTakenAddress(void)</b><br>
Returns the address of the taken branch.

- <b>\ref py_AstNode_page getTakenPathConstraintAst(void)</b><br>
Returns the path constraint AST of the taken branch.

- <b>bool isMultipleBranches(void)</b><br>
Returns true if it is not a direct jump.

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initPathConstraintObject(pybind11::module& pyTriton) {
        pybind11::class_<triton::engines::symbolic::PathConstraint>(pyTriton, "PathConstraint", "The PathConstraint class")
          .def("getBranchConstraints",      &triton::engines::symbolic::PathConstraint::getBranchConstraints)
          .def("getTakenAddress",           &triton::engines::symbolic::PathConstraint::getTakenAddress)
          .def("getTakenPathConstraintAst", &triton::engines::symbolic::PathConstraint::getTakenPathConstraintAst)
          .def("isMultipleBranches",        &triton::engines::symbolic::PathConstraint::isMultipleBranches);
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
