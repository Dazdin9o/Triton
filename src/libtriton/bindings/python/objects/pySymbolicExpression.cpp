//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/symbolicExpression.hpp>



/*! \page py_SymbolicExpression_page SymbolicExpression
    \brief [**python api**] All information about the SymbolicExpression python object.

\tableofcontents

\section py_SymbolicExpression_description Description
<hr>

This object is used to represent a symbolic expression.

~~~~~~~~~~~~~{.py}
>>> from triton import TritonContext, ARCH, Instruction, REG

>>> ctxt = TritonContext()
>>> ctxt.setArchitecture(ARCH.X86_64)

>>> opcode = "\x48\x31\xD0"
>>> inst = Instruction()

>>> inst.setOpcode(opcode)
>>> inst.setAddress(0x400000)
>>> ctxt.setConcreteRegisterValue(ctxt.registers.rax, 12345)
>>> ctxt.setConcreteRegisterValue(ctxt.registers.rdx, 67890)

>>> ctxt.processing(inst)
True
>>> print inst
0x400000: xor rax, rdx

>>> for expr in inst.getSymbolicExpressions():
...     print expr
...
(define-fun ref!0 () (_ BitVec 64) (bvxor (_ bv12345 64) (_ bv67890 64))) ; XOR operation
(define-fun ref!1 () (_ BitVec 1) (_ bv0 1)) ; Clears carry flag
(define-fun ref!2 () (_ BitVec 1) (_ bv0 1)) ; Clears overflow flag
(define-fun ref!3 () (_ BitVec 1) (bvxor (bvxor (bvxor (bvxor (bvxor (bvxor (bvxor (bvxor (_ bv1 1) ((_ extract 0 0) (bvlshr ((_ extract 7 0) ref!0) (_ bv0 8)))) ((_ extract 0 0) (bvlshr ((_ extract 7 0) ref!0) (_ bv1 8)))) ((_ extract 0 0) (bvlshr ((_ extract 7 0) ref!0) (_ bv2 8)))) ((_ extract 0 0) (bvlshr ((_ extract 7 0) ref!0) (_ bv3 8)))) ((_ extract 0 0) (bvlshr ((_ extract 7 0) ref!0) (_ bv4 8)))) ((_ extract 0 0) (bvlshr ((_ extract 7 0) ref!0) (_ bv5 8)))) ((_ extract 0 0) (bvlshr ((_ extract 7 0) ref!0) (_ bv6 8)))) ((_ extract 0 0) (bvlshr ((_ extract 7 0) ref!0) (_ bv7 8))))) ; Parity flag
(define-fun ref!4 () (_ BitVec 1) ((_ extract 63 63) ref!0)) ; Sign flag
(define-fun ref!5 () (_ BitVec 1) (ite (= ref!0 (_ bv0 64)) (_ bv1 1) (_ bv0 1))) ; Zero flag
(define-fun ref!6 () (_ BitVec 64) (_ bv4194307 64)) ; Program Counter

>>> expr_1 = inst.getSymbolicExpressions()[0]
>>> expr_1 # doctest: +ELLIPSIS
<SymbolicExpression object at 0x...>
>>> print expr_1
(define-fun ref!0 () (_ BitVec 64) (bvxor (_ bv12345 64) (_ bv67890 64))) ; XOR operation

>>> print expr_1.getId()
0

>>> ast = expr_1.getAst()
>>> ast # doctest: +ELLIPSIS
<AstNode object at 0x...>
>>> print ast
(bvxor (_ bv12345 64) (_ bv67890 64))


>>> expr_1.isMemory()
False

>>> expr_1.isRegister()
True

>>> print expr_1.getOrigin()
rax:64 bv[63..0]

~~~~~~~~~~~~~

\section SymbolicExpression_py_api Python API - Methods of the SymbolicExpression class
<hr>

- <b>\ref py_AstNode_page getAst(void)</b><br>
Returns the AST root node of the symbolic expression.

- <b>string getComment(void)</b><br>
Returns the comment (if exists) of the symbolic expression.

- <b>integer getId(void)</b><br>
Returns the if of the symbolic expression. This id is always unique.<br>
e.g: `2387`

- <b>\ref py_AstNode_page getNewAst(void)</b><br>
Returns a new AST root node of the symbolic expression. This new instance is a duplicate of the original node and may be changed without changing the original semantics.

- <b>\ref py_MemoryAccess_page / \ref py_Register_page getOrigin(void)</b><br>
Returns the origin of the symbolic expression. For example, if the symbolic expression is assigned to a memory cell, this function returns
a \ref py_MemoryAccess_page, else if it is assigned to a register, this function returns a \ref py_Register_page otherwise it returns None. Note that
for a \ref py_MemoryAccess_page all information about LEA are lost at this level.

- <b>\ref py_SYMBOLIC_page getType(void)</b><br>
Returns the type of the symbolic expression.<br>
e.g: `SYMBOLIC.REGISTER_EXPRESSION`

- <b>bool isMemory(void)</b><br>
Returns true if the expression is assigned to a memory.

- <b>bool isRegister(void)</b><br>
Returns true if the expression is assigned to a register.

- <b>bool isSymbolized(void)</b><br>
Returns true if the expression contains a symbolic variable.

- <b>bool isTainted(void)</b><br>
Returns true if the expression is tainted.

- <b>void setAst(\ref py_AstNode_page node)</b><br>
Sets a root node.

- <b>void setComment(string comment)</b><br>
Sets a comment to the symbolic expression.

*/



using namespace triton::engines::symbolic;

namespace triton {
  namespace bindings {
    namespace python {

      void initSymbolicExpressionObject(pybind11::module& pyTriton) {
        pybind11::class_<SymbolicExpression, SharedSymbolicExpression>(pyTriton, "SymbolicExpression", "The SymbolicExpression class")

          .def("getAst",        &SymbolicExpression::getAst)
          .def("getComment",    &SymbolicExpression::getComment)
          .def("getId",         &SymbolicExpression::getId)
          .def("getNewAst",     &SymbolicExpression::getNewAst)
          .def("getType",       &SymbolicExpression::getType)
          .def("isMemory",      &SymbolicExpression::isMemory)
          .def("isRegister",    &SymbolicExpression::isRegister)
          .def("isSymbolized",  &SymbolicExpression::isSymbolized)
          .def("setAst",        &SymbolicExpression::setAst)
          .def("setComment",    &SymbolicExpression::setComment)

          .def("getOrigin",
            [] (const SharedSymbolicExpression& self) -> pybind11::object {
              if (self->getType() == MEMORY_EXPRESSION)
                return pybind11::cast(self->getOriginMemory());

              if (self->getType() == REGISTER_EXPRESSION)
                return pybind11::cast(self->getOriginRegister());

              return pybind11::cast<pybind11::none>(Py_None);
            })

          .def("isTainted",
            [] (const SharedSymbolicExpression& self) {
              return self->isTainted;
            })

          .def("__repr__",
            [] (const SharedSymbolicExpression& expr) {
              std::ostringstream stream;
              stream << expr;
              return stream.str();
            })

          .def("__str__",
            [] (const SharedSymbolicExpression& expr) {
              std::ostringstream stream;
              stream << expr;
              return stream.str();
            });
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
