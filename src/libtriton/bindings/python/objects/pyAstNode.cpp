//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/pythonUtils.hpp>
#include <triton/ast.hpp>
#include <triton/astContext.hpp>
#include <triton/exceptions.hpp>
#include <triton/symbolicExpression.hpp>
#include <triton/symbolicVariable.hpp>



/* setup doctest context

>>> from triton import TritonContext, ARCH
>>> ctxt = TritonContext()
>>> ctxt.setArchitecture(ARCH.X86_64)

*/

/*! \page py_AstNode_page AstNode
    \brief [**python api**] All information about the AstNode python object.

\tableofcontents

\section py_AstNode_description Description
<hr>

This object is used to represent each AST node of an expression.

~~~~~~~~~~~~~{.py}
>>> astCtxt = ctxt.getAstContext()
>>> node = astCtxt.bvadd(astCtxt.bv(1, 8), astCtxt.bvxor(astCtxt.bv(10, 8), astCtxt.bv(20, 8)))
>>> print type(node)
<type 'AstNode'>

>>> print node
(bvadd (_ bv1 8) (bvxor (_ bv10 8) (_ bv20 8)))

# Python's opertors overloaded

>>> a = astCtxt.bv(1, 8)
>>> b = astCtxt.bv(2, 8)
>>> c = (a & ~b) | (~a & b)
>>> print c
(bvor (bvand (_ bv1 8) (bvnot (_ bv2 8))) (bvand (bvnot (_ bv1 8)) (_ bv2 8)))

~~~~~~~~~~~~~

\section AstNode_py_api Python API - Methods of the AstNode class
<hr>

- <b>bool equalTo(\ref py_AstNode_page)</b><br>
Compares the current tree to another one.

- <b>integer evaluate(void)</b><br>
Evaluates the tree and returns its value.

- <b>integer getBitvectorMask(void)</b><br>
Returns the mask of the node vector according to its size.<br>
e.g: `0xffffffff`

- <b>integer getBitvectorSize(void)</b><br>
Returns the node vector size.

- <b>[\ref py_AstNode_page, ...] getChildren(void)</b><br>
Returns the list of child nodes.

- <b>integer getHash(void)</b><br>
Returns the hash (signature) of the AST .

- <b>integer getInteger(void)</b><br>
Returns the integer of the node. Only available on `INTEGER_NODE`, raises an exception otherwise.

- <b>[\ref py_AstNode_page, ...] getParents(void)</b><br>
Returns the parents list nodes. The list is empty if there is still no parent defined.

- <b>string getString(void)</b><br>
Returns the string of the node. Only available on `STRING_NODE`, raises an exception otherwise.

- <b>\ref py_SymbolicExpression_page getSymbolicExpression(void)</b><br>
Returns the symbolic expression of the node. Only available on `REFERENCE_NODE`, raises an exception otherwise.

- <b>\ref py_SymbolicVariable_page getSymbolicVariable(void)</b><br>
Returns the symbolic variable of the node. Only available on `VARIABLE_NODE`, raises an exception otherwise.

- <b>\ref py_AST_NODE_page getType(void)</b><br>
Returns the kind of the node.<br>
e.g: `AST_NODE.BVADD`

- <b>bool isLogical(void)</b><br>
Returns true if it's a logical node.
e.g: `AST_NODE.EQUAL`, `AST_NODE.LNOT`, `AST_NODE.LAND`...

- <b>bool isSigned(void)</b><br>
According to the size of the expression, returns true if the MSB is 1.

- <b>bool isSymbolized(void)</b><br>
Returns true if the tree (and its sub-trees) contains a symbolic variable.

- <b>void setChild(integer index, \ref py_AstNode_page node)</b><br>
Replaces a child node.

\section AstNode_operator_py_api Python API - Operators
<hr>

As we can not overload all AST's operators only these following operators are overloaded:

Python's Operator | e.g: SMT2-Lib format
------------------|---------------------
a + b             | (bvadd a b)
a - b             | (bvsub a b)
a \* b            | (bvmul a b)
a / b             | (bvudiv a b)
a \| b            | (bvor a b)
a & b             | (bvand a b)
a ^ b             | (bvxor a b)
a % b             | (bvurem a b)
a << b            | (bvshl a b)
a \>> b           | (bvlshr a b)
~a                | (bvnot a)
-a                | (bvneg a)
a == b            | (= a b)
a != b            | (not (= a b))
a <= b            | (bvule a b)
a >= b            | (bvuge a b)
a < b             | (bvult a b)
a > b             | (bvugt a b)

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initAstNodeObject(pybind11::module& pyTriton) {
        pybind11::class_<triton::ast::AbstractNode, triton::ast::SharedAbstractNode>(pyTriton, "SharedAbstractNode", "The SharedAbstractNode class")

          .def("equalTo",               &triton::ast::AbstractNode::equalTo)
          .def("getBitvectorSize",      &triton::ast::AbstractNode::getBitvectorSize)
          .def("getChildren",           &triton::ast::AbstractNode::getChildren)
          .def("getParents",            &triton::ast::AbstractNode::getParents)
          .def("getType",               &triton::ast::AbstractNode::getType)
          .def("isLogical",             &triton::ast::AbstractNode::isLogical)
          .def("isSigned",              &triton::ast::AbstractNode::isSigned)
          .def("isSymbolized",          &triton::ast::AbstractNode::isSymbolized)
          .def("setChild",              &triton::ast::AbstractNode::setChild)

          .def("evaluate",
            [] (const triton::ast::SharedAbstractNode& self) -> pybind11::object {
              return pybind11::reinterpret_borrow<pybind11::object>(PyLong_FromUint512(self->evaluate()));
            })

          .def("getBitvectorMask",
            [] (const triton::ast::SharedAbstractNode& self) -> pybind11::object {
              return pybind11::reinterpret_borrow<pybind11::object>(PyLong_FromUint512(self->getBitvectorMask()));
            })

          .def("getHash",
            [] (const triton::ast::SharedAbstractNode& self) -> pybind11::object {
              return pybind11::reinterpret_borrow<pybind11::object>(PyLong_FromUint512(self->hash(1)));
            })

          .def("getInteger",
            [] (const triton::ast::SharedAbstractNode& self) -> pybind11::object {
              if (self->getType() != triton::ast::INTEGER_NODE)
                throw triton::exceptions::Ast("AbstractNode::getInteger(): Only available on INTEGER_NODE type.");

              triton::uint512 value = reinterpret_cast<triton::ast::IntegerNode*>(self.get())->getInteger();
              return pybind11::reinterpret_borrow<pybind11::object>(PyLong_FromUint512(value));
            })

          .def("getString",
            [] (const triton::ast::SharedAbstractNode& self) -> pybind11::object {
              if (self->getType() != triton::ast::STRING_NODE)
                throw triton::exceptions::Ast("AbstractNode::getString(): Only available on STRING_NODE type.");

              std::string s = reinterpret_cast<triton::ast::StringNode*>(self.get())->getString();
              return pybind11::cast(s);
            })

          .def("getSymbolicExpression",
            [] (const triton::ast::SharedAbstractNode& self) -> pybind11::object {
              if (self->getType() != triton::ast::REFERENCE_NODE)
                throw triton::exceptions::Ast("AbstractNode::getSymbolicExpression(): Only available on REFERENCE_NODE type.");

              auto expr = reinterpret_cast<triton::ast::ReferenceNode*>(self.get())->getSymbolicExpression();
              return pybind11::cast(expr);
            })

          .def("getSymbolicVariable",
            [] (const triton::ast::SharedAbstractNode& self) -> pybind11::object {
              if (self->getType() != triton::ast::VARIABLE_NODE)
                throw triton::exceptions::Ast("AbstractNode::getSymbolicVariable(): Only available on VARIABLE_NODE type.");

              auto var = reinterpret_cast<triton::ast::VariableNode*>(self.get())->getSymbolicVariable();
              return pybind11::cast(var);
            })

          .def("__repr__",
            [] (const triton::ast::SharedAbstractNode& node) {
              std::ostringstream stream;
              stream << node.get();
              return stream.str();
            })

          .def("__str__",
            [] (const triton::ast::SharedAbstractNode& node) {
              std::ostringstream stream;
              stream << node.get();
              return stream.str();
            })

          /* Operators ******************************************************/

          .def("__add__",
            [](const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              triton::ast::AstContext& ast = node1->getContext();
              return ast.bvadd(node1, node2);
            }, pybind11::is_operator())

          .def("__add__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvadd(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          .def("__radd__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvadd(ast.bv(value, node->getBitvectorSize()), node);
            }, pybind11::is_operator())

          /******************************************************************/

          .def("__and__",
            [](const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              triton::ast::AstContext& ast = node1->getContext();
              return ast.bvand(node1, node2);
            }, pybind11::is_operator())

          .def("__and__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvand(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          .def("__rand__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvand(ast.bv(value, node->getBitvectorSize()), node);
            }, pybind11::is_operator())

          /******************************************************************/

          .def("__div__",
            [](const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              triton::ast::AstContext& ast = node1->getContext();
              return ast.bvudiv(node1, node2);
            }, pybind11::is_operator())

          .def("__div__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvudiv(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          .def("__rdiv__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvudiv(ast.bv(value, node->getBitvectorSize()), node);
            }, pybind11::is_operator())

          /******************************************************************/

          .def("__mul__",
            [](const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              triton::ast::AstContext& ast = node1->getContext();
              return ast.bvmul(node1, node2);
            }, pybind11::is_operator())

          .def("__mul__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvmul(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          .def("__rmul__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvmul(ast.bv(value, node->getBitvectorSize()), node);
            }, pybind11::is_operator())

          /******************************************************************/

          .def("__neg__",
            [](const triton::ast::SharedAbstractNode& node) {
              triton::ast::AstContext& ast = node->getContext();
              return ast.bvneg(node);
            }, pybind11::is_operator())

          /******************************************************************/

          .def("__invert__",
            [](const triton::ast::SharedAbstractNode& node) {
              triton::ast::AstContext& ast = node->getContext();
              return ast.bvnot(node);
            }, pybind11::is_operator())

          /******************************************************************/

          .def("__or__",
            [](const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              triton::ast::AstContext& ast = node1->getContext();
              return ast.bvor(node1, node2);
            }, pybind11::is_operator())

          .def("__or__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvor(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          .def("__ror__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvor(ast.bv(value, node->getBitvectorSize()), node);
            }, pybind11::is_operator())

          /******************************************************************/

          .def("__mod__",
            [](const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              triton::ast::AstContext& ast = node1->getContext();
              return ast.bvurem(node1, node2);
            }, pybind11::is_operator())

          .def("__mod__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvurem(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          .def("__rmod__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvurem(ast.bv(value, node->getBitvectorSize()), node);
            }, pybind11::is_operator())

          /******************************************************************/

          .def("__lshift__",
            [](const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              triton::ast::AstContext& ast = node1->getContext();
              return ast.bvshl(node1, node2);
            }, pybind11::is_operator())

          .def("__lshift__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvshl(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          .def("__rlshift__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvshl(ast.bv(value, node->getBitvectorSize()), node);
            }, pybind11::is_operator())

          /******************************************************************/

          .def("__rshift__",
            [](const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              triton::ast::AstContext& ast = node1->getContext();
              return ast.bvlshr(node1, node2);
            }, pybind11::is_operator())

          .def("__rshift__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvlshr(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          .def("__rrshift__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvlshr(ast.bv(value, node->getBitvectorSize()), node);
            }, pybind11::is_operator())

          /******************************************************************/

          .def("__sub__",
            [](const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              triton::ast::AstContext& ast = node1->getContext();
              return ast.bvsub(node1, node2);
            }, pybind11::is_operator())

          .def("__sub__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvsub(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          .def("__rsub__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvsub(ast.bv(value, node->getBitvectorSize()), node);
            }, pybind11::is_operator())

          /******************************************************************/

          .def("__xor__",
            [](const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              triton::ast::AstContext& ast = node1->getContext();
              return ast.bvxor(node1, node2);
            }, pybind11::is_operator())

          .def("__xor__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvxor(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          .def("__rxor__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvxor(ast.bv(value, node->getBitvectorSize()), node);
            }, pybind11::is_operator())

          /******************************************************************/

          .def("__lt__",
            [](const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              triton::ast::AstContext& ast = node1->getContext();
              return ast.bvult(node1, node2);
            }, pybind11::is_operator())

          .def("__lt__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvult(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          .def("__rlt__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvult(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          /******************************************************************/

          .def("__le__",
            [](const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              triton::ast::AstContext& ast = node1->getContext();
              return ast.bvule(node1, node2);
            }, pybind11::is_operator())

          .def("__le__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvule(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          .def("__rle__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvule(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          /******************************************************************/

          .def("__eq__",
            [](const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              triton::ast::AstContext& ast = node1->getContext();
              return ast.equal(node1, node2);
            }, pybind11::is_operator())

          .def("__eq__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.equal(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          .def("__req__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.equal(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          /******************************************************************/

          .def("__ne__",
            [](const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              triton::ast::AstContext& ast = node1->getContext();
              return ast.lnot(ast.equal(node1, node2));
            }, pybind11::is_operator())

          .def("__ne__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.lnot(ast.equal(node, ast.bv(value, node->getBitvectorSize())));
            }, pybind11::is_operator())

          .def("__rne__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.lnot(ast.equal(node, ast.bv(value, node->getBitvectorSize())));
            }, pybind11::is_operator())

          /******************************************************************/

          .def("__gt__",
            [](const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              triton::ast::AstContext& ast = node1->getContext();
              return ast.bvugt(node1, node2);
            }, pybind11::is_operator())

          .def("__gt__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvugt(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          .def("__rgt__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvugt(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          /******************************************************************/

          .def("__ge__",
            [](const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              triton::ast::AstContext& ast = node1->getContext();
              return ast.bvuge(node1, node2);
            }, pybind11::is_operator())

          .def("__ge__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvuge(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator())

          .def("__rge__",
            [](const triton::ast::SharedAbstractNode& node, pybind11::int_ o) {
              triton::ast::AstContext& ast = node->getContext();
              triton::uint512 value = PyLong_AsUint512(o.ptr());
              return ast.bvuge(node, ast.bv(value, node->getBitvectorSize()));
            }, pybind11::is_operator());
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
