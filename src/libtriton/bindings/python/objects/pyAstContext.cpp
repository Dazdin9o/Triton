//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/pythonUtils.hpp>
#include <triton/astContext.hpp>
#include <triton/symbolicExpression.hpp>
#include <triton/symbolicVariable.hpp>
#ifdef Z3_INTERFACE
  #include <triton/tritonToZ3Ast.hpp>
#endif



/* setup doctest context

>>> from triton import REG, TritonContext, ARCH, Instruction, AST_REPRESENTATION
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

*/

/*! \page py_AstContext_page AstContext
    \brief [**python api**] All information about the AstContext python object.

\tableofcontents

\section ast_description Description
<hr>

Triton converts the x86, x86-64 and AArch64 instruction set architecture into an AST representation. The class is used
to build your own AST nodes.

\anchor ast
\section AstContext_py_api Python API - Methods of the AstContext class
<hr>

- <b>\ref py_AstNode_page bv(integer value, integer size)</b><br>
Creates a `bv` node (bitvector). The `size` must be in bits.<br>
e.g: `(_ bv<balue> size)`.

- <b>\ref py_AstNode_page bvadd(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvadd` node.<br>
e.g: `(bvadd expr1 epxr2)`.

- <b>\ref py_AstNode_page bvand(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvand` node.<br>
e.g: `(bvand expr1 epxr2)`.

- <b>\ref py_AstNode_page bvashr(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvashr` node (arithmetic shift right).<br>
e.g: `(bvashr expr1 epxr2)`.

- <b>\ref py_AstNode_page bvfalse(void)</b><br>
This is an alias on the `(_ bv0 1)` ast expression.

- <b>\ref py_AstNode_page bvlshr(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvlshr` node (logical shift right).<br>
e.g: `(lshr expr1 epxr2)`.

- <b>\ref py_AstNode_page bvmul(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvmul` node.<br>
e.g: `(bvmul expr1 expr2)`.

- <b>\ref py_AstNode_page bvnand(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvnand` node.<br>
e.g: `(bvnand expr1 expr2)`.

- <b>\ref py_AstNode_page bvneg(\ref py_AstNode_page expr1)</b><br>
Creates a `bvneg` node.<br>
e.g: `(bvneg expr1)`.

- <b>\ref py_AstNode_page bvnor(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvnor` node.<br>
e.g: `(bvnor expr1 expr2)`.

- <b>\ref py_AstNode_page bvnot(\ref py_AstNode_page expr1)</b><br>
Creates a `bvnot` node.<br>
e.g: `(bvnot expr1)`.

- <b>\ref py_AstNode_page bvor(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvor` node.<br>
e.g: `(bvor expr1 expr2)`.

- <b>\ref py_AstNode_page bvror(\ref py_AstNode_page expr, \ref py_AstNode_page rot)</b><br>
Creates a `bvror` node (rotate right).<br>
e.g: `((_ rotate_right rot) expr)`.

- <b>\ref py_AstNode_page bvrol(\ref py_AstNode_page expr, \ref py_AstNode_page rot)</b><br>
Creates a `bvrol` node (rotate left).<br>
e.g: `((_ rotate_left rot) expr)`.

- <b>\ref py_AstNode_page bvsdiv(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvsdiv` node.<br>
e.g: `(bvsdiv expr1 epxr2)`.

- <b>\ref py_AstNode_page bvsge(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvsge` node.<br>
e.g: `(bvsge expr1 epxr2)`.

- <b>\ref py_AstNode_page bvsgt(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvsgt` node.<br>
e.g: `(bvsgt expr1 epxr2)`.

- <b>\ref py_AstNode_page bvshl(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a Bvshl node (shift left).<br>
e.g: `(bvshl expr1 expr2)`.

- <b>\ref py_AstNode_page bvsle(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvsle` node.<br>
e.g: `(bvsle expr1 epxr2)`.

- <b>\ref py_AstNode_page bvslt(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvslt` node.<br>
e.g: `(bvslt expr1 epxr2)`.

- <b>\ref py_AstNode_page bvsmod(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvsmod` node (2's complement signed remainder, sign follows divisor).<br>
e.g: `(bvsmod expr1 expr2)`.

- <b>\ref py_AstNode_page bvsrem(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvsrem` node (2's complement signed remainder, sign follows dividend).<br>
e.g: `(bvsrem expr1 expr2)`.

- <b>\ref py_AstNode_page bvsub(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvsub` node.<br>
e.g: `(bvsub expr1 epxr2)`.

- <b>\ref py_AstNode_page bvtrue(void)</b><br>
This is an alias on the `(_ bv1 1)` ast expression.<br>

- <b>\ref py_AstNode_page bvudiv(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvudiv` node.<br>
e.g: `(bvudiv expr1 epxr2)`.

- <b>\ref py_AstNode_page bvuge(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvuge` node.<br>
e.g: `(bvuge expr1 epxr2)`.

- <b>\ref py_AstNode_page bvugt(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvugt` node.<br>
e.g: `(bvugt expr1 epxr2)`.

- <b>\ref py_AstNode_page bvule(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvule` node.<br>
e.g: `(bvule expr1 epxr2)`.

- <b>\ref py_AstNode_page bvult(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvult` node.<br>
e.g: `(bvult expr1 epxr2)`.

- <b>\ref py_AstNode_page bvurem(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvurem` node (unsigned remainder).<br>
e.g: `(bvurem expr1 expr2)`.

- <b>\ref py_AstNode_page bvxnor(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvxnor` node.<br>
e.g: `(bvxnor expr1 expr2)`.

- <b>\ref py_AstNode_page bvxor(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `bvxor` node.<br>
e.g: `(bvxor expr1 epxr2)`.

- <b>\ref py_AstNode_page concat([\ref py_AstNode_page, ...])</b><br>
Concatenates several nodes.

- <b>\ref py_AstNode_page distinct(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates a `distinct` node.<br>
e.g: `(distinct expr1 expr2)`

- <b>\ref py_AstNode_page equal(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates an `equal` node.<br>
e.g: `(= expr1 epxr2)`.

- <b>\ref py_AstNode_page extract(integer high, integer low, \ref py_AstNode_page expr1)</b><br>
Creates an `extract` node. The `high` and `low` fields represent the bits position.<br>
e.g: `((_ extract high low) expr1)`.

- <b>\ref py_AstNode_page iff(\ref py_AstNode_page expr1, \ref py_AstNode_page expr2)</b><br>
Creates an `iff` node (if and only if).<br>
e.g: `(iff expr1 expr2)`.

- <b>\ref py_AstNode_page ite(\ref py_AstNode_page ifExpr, \ref py_AstNode_page thenExpr, \ref py_AstNode_page elseExpr)</b><br>
Creates an `ite` node (if-then-else node).<br>
e.g: `(ite ifExpr thenExpr elseExpr)`.

- <b>\ref py_AstNode_page land([\ref py_AstNode_page, ...])</b><br>
Creates a logical `AND` on several nodes.
e.g: `(and expr1 expr2 expr3 expr4)`.

- <b>\ref py_AstNode_page let(string alias, \ref py_AstNode_page expr2, \ref py_AstNode_page expr3)</b><br>
Creates a `let` node.<br>
e.g: `(let ((alias expr2)) expr3)`.

- <b>\ref py_AstNode_page lnot(\ref py_AstNode_page expr)</b><br>
Creates a `lnot` node (logical NOT).<br>
e.g: `(not expr)`.

- <b>\ref py_AstNode_page lor([\ref py_AstNode_page, ...])</b><br>
Creates a logical `OR` on several nodes.
e.g: `(or expr1 expr2 expr3 expr4)`.

- <b>\ref py_AstNode_page reference(\ref py_SymbolicExpression_page expr)</b><br>
Creates a reference node (SSA-based).<br>
e.g: `ref!123`.

- <b>\ref py_AstNode_page string(string s)</b><br>
Creates a `string` node.

- <b>\ref py_AstNode_page sx(integer sizeExt, \ref py_AstNode_page expr1)</b><br>
Creates a `sx` node (sign extend).<br>
e.g: `((_ sign_extend sizeExt) expr1)`.

- <b>\ref py_AstNode_page variable(\ref py_SymbolicVariable_page symVar)</b><br>
Creates a `variable` node.

- <b>\ref py_AstNode_page zx(integer sizeExt, \ref py_AstNode_page expr1)</b><br>
Creates a `zx` node (zero extend).<br>
e.g: `((_ zero_extend sizeExt) expr1)`.


\section AstContext_convert_py_api Python API - Utility methods of the AstContext class
<hr>

- <b>\ref py_AstNode_page duplicate(\ref py_AstNode_page expr)</b><br>
Duplicates the node and returns a new instance as \ref py_AstNode_page.

- <b>[\ref py_AstNode_page, ...] lookingForNodes(\ref py_AstNode_page expr, \ref py_AST_NODE_page match)</b><br>
Returns a list of collected matched nodes via a depth-first pre order traversal.

- <b>z3::expr tritonToZ3(\ref py_AstNode_page expr)</b><br>
Convert a Triton AST to a Z3 AST.

- <b>\ref py_AstNode_page unrollAst(\ref py_AstNode_page node)</b><br>
Unrolls the SSA form of a given AST.


\section ast_py_examples_page_3 Python API - Operators
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

\section ast_smt_python_page The SMT or Python Syntax
<hr>

By default, Triton represents semantics into [SMT-LIB](http://smtlib.cs.uiowa.edu/) which is an international initiative aimed at facilitating research and development in Satisfiability Modulo Theories (SMT). However,
Triton allows you to display your AST via a Python syntax.

~~~~~~~~~~~~~{.py}
>>> ctxt = TritonContext()
>>> ctxt.setArchitecture(ARCH.X86_64)
>>> ctxt.setAstRepresentationMode(AST_REPRESENTATION.PYTHON)
>>> inst = Instruction()
>>> inst.setOpcode("\x48\x01\xd8") # add rax, rbx
>>> inst.setAddress(0x400000)
>>> ctxt.setConcreteRegisterValue(ctxt.registers.rax, 0x1122334455667788)
>>> ctxt.setConcreteRegisterValue(ctxt.registers.rbx, 0x8877665544332211)
>>> ctxt.processing(inst)
True
>>> print inst
0x400000: add rax, rbx

>>> for expr in inst.getSymbolicExpressions():
...     print expr
...
ref_0 = ((0x1122334455667788 + 0x8877665544332211) & 0xFFFFFFFFFFFFFFFF) # ADD operation
ref_1 = (0x1 if (0x10 == (0x10 & (ref_0 ^ (0x1122334455667788 ^ 0x8877665544332211)))) else 0x0) # Adjust flag
ref_2 = ((((0x1122334455667788 & 0x8877665544332211) ^ (((0x1122334455667788 ^ 0x8877665544332211) ^ ref_0) & (0x1122334455667788 ^ 0x8877665544332211))) >> 63) & 0x1) # Carry flag
ref_3 = ((((0x1122334455667788 ^ (~(0x8877665544332211) & 0xFFFFFFFFFFFFFFFF)) & (0x1122334455667788 ^ ref_0)) >> 63) & 0x1) # Overflow flag
ref_4 = ((((((((0x1 ^ (((ref_0 & 0xFF) >> 0x0) & 0x1)) ^ (((ref_0 & 0xFF) >> 0x1) & 0x1)) ^ (((ref_0 & 0xFF) >> 0x2) & 0x1)) ^ (((ref_0 & 0xFF) >> 0x3) & 0x1)) ^ (((ref_0 & 0xFF) >> 0x4) & 0x1)) ^ (((ref_0 & 0xFF) >> 0x5) & 0x1)) ^ (((ref_0 & 0xFF) >> 0x6) & 0x1)) ^ (((ref_0 & 0xFF) >> 0x7) & 0x1)) # Parity flag
ref_5 = ((ref_0 >> 63) & 0x1) # Sign flag
ref_6 = (0x1 if (ref_0 == 0x0) else 0x0) # Zero flag
ref_7 = 0x400003 # Program Counter

~~~~~~~~~~~~~

*/


namespace triton {
  namespace bindings {
    namespace python {

      void initAstContextObject(pybind11::module& pyTriton) {
        pybind11::class_<triton::ast::AstContext>(pyTriton, "AstContext", "The AstContext class")

          .def("assert_",   &triton::ast::AstContext::assert_)
          .def("bvadd",     &triton::ast::AstContext::bvadd)
          .def("bvand",     &triton::ast::AstContext::bvand)
          .def("bvashr",    &triton::ast::AstContext::bvashr)
          .def("bvfalse",   &triton::ast::AstContext::bvfalse)
          .def("bvlshr",    &triton::ast::AstContext::bvlshr)
          .def("bvmul",     &triton::ast::AstContext::bvmul)
          .def("bvnand",    &triton::ast::AstContext::bvnand)
          .def("bvneg",     &triton::ast::AstContext::bvneg)
          .def("bvnor",     &triton::ast::AstContext::bvnor)
          .def("bvnot",     &triton::ast::AstContext::bvnot)
          .def("bvor",      &triton::ast::AstContext::bvor)
          .def("bvsdiv",    &triton::ast::AstContext::bvsdiv)
          .def("bvsge",     &triton::ast::AstContext::bvsge)
          .def("bvsgt",     &triton::ast::AstContext::bvsgt)
          .def("bvshl",     &triton::ast::AstContext::bvshl)
          .def("bvsle",     &triton::ast::AstContext::bvsle)
          .def("bvslt",     &triton::ast::AstContext::bvslt)
          .def("bvsmod",    &triton::ast::AstContext::bvsmod)
          .def("bvsrem",    &triton::ast::AstContext::bvsrem)
          .def("bvsub",     &triton::ast::AstContext::bvsub)
          .def("bvtrue",    &triton::ast::AstContext::bvtrue)
          .def("bvudiv",    &triton::ast::AstContext::bvudiv)
          .def("bvuge",     &triton::ast::AstContext::bvuge)
          .def("bvugt",     &triton::ast::AstContext::bvugt)
          .def("bvule",     &triton::ast::AstContext::bvule)
          .def("bvult",     &triton::ast::AstContext::bvult)
          .def("bvurem",    &triton::ast::AstContext::bvurem)
          .def("bvxnor",    &triton::ast::AstContext::bvxnor)
          .def("bvxor",     &triton::ast::AstContext::bvxor)
          .def("declare",   &triton::ast::AstContext::declare)
          .def("distinct",  &triton::ast::AstContext::distinct)
          .def("equal",     &triton::ast::AstContext::equal)
          .def("extract",   &triton::ast::AstContext::extract)
          .def("iff",       &triton::ast::AstContext::iff)
          .def("ite",       &triton::ast::AstContext::ite)
          .def("let",       &triton::ast::AstContext::let)
          .def("lnot",      &triton::ast::AstContext::lnot)
          .def("string",    &triton::ast::AstContext::string)
          .def("sx",        &triton::ast::AstContext::sx)
          .def("zx",        &triton::ast::AstContext::zx)

          .def("bv",
            [] (triton::ast::AstContext& self, pybind11::object value, triton::uint32 size) {
              return self.bv(PyLong_AsUint512(value.ptr()), size);
            })

          .def("bvrol",
            [] (triton::ast::AstContext& self, const triton::ast::SharedAbstractNode& node, triton::uint32 rot) {
              return self.bvrol(node, rot);
            })

          .def("bvrol",
            [] (triton::ast::AstContext& self, const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              return self.bvrol(node1, node2);
            })

          .def("bvror",
            [] (triton::ast::AstContext& self, const triton::ast::SharedAbstractNode& node, triton::uint32 rot) {
              return self.bvror(node, rot);
            })

          .def("bvror",
            [] (triton::ast::AstContext& self, const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              return self.bvror(node1, node2);
            })

          .def("compound",
            [] (triton::ast::AstContext& self, const std::list<triton::ast::SharedAbstractNode>& nodes) {
              return self.compound(nodes);
            })

          .def("concat",
            [] (triton::ast::AstContext& self, const std::list<triton::ast::SharedAbstractNode>& nodes) {
              return self.concat(nodes);
            })

          .def("land",
            [] (triton::ast::AstContext& self, const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              return self.land(node1, node2);
            })

          .def("land",
            [] (triton::ast::AstContext& self, const std::list<triton::ast::SharedAbstractNode>& nodes) {
              return self.land(nodes);
            })

          .def("lor",
            [] (triton::ast::AstContext& self, const triton::ast::SharedAbstractNode& node1, const triton::ast::SharedAbstractNode& node2) {
              return self.lor(node1, node2);
            })

          .def("lor",
            [] (triton::ast::AstContext& self, const std::list<triton::ast::SharedAbstractNode>& nodes) {
              return self.lor(nodes);
            })

          .def("variable",
            [] (triton::ast::AstContext& self, const triton::engines::symbolic::SharedSymbolicVariable& var) {
              return self.variable(var);
            })

          .def("reference",
            [] (triton::ast::AstContext& self, const triton::engines::symbolic::SharedSymbolicExpression& expr) {
              return self.reference(expr);
            })

          .def("duplicate",
            [] (triton::ast::AstContext& self, const triton::ast::SharedAbstractNode& node) {
              return triton::ast::newInstance(node.get());
            })

          .def("lookingForNodes",
            [] (triton::ast::AstContext& self, const triton::ast::SharedAbstractNode& node, triton::ast::ast_e match) {
              return triton::ast::lookingForNodes(node, match);
            })

          // TODO
          //#ifdef Z3_INTERFACE
          //.def("tritonToZ3",
          //  [] (triton::ast::AstContext& self, const triton::ast::SharedAbstractNode& node) {
          //    triton::ast::TritonToZ3Ast tritonToZ3Ast{false};

          //    pybind11::object pyz3 = pybind11::module::import("z3");

          //    PyObject* z3MainCtx = PyObject_CallObject(PyObject_GetAttrString(pyz3.ptr(), "main_ctx"), nullptr);
          //    PyObject* z3CtxPtr  = PyObject_GetAttrString(PyObject_GetAttrString(z3MainCtx, "ctx"), "value");
          //    Z3_context z3Ctx    = reinterpret_cast<Z3_context>(PyLong_AsVoidPtr(z3CtxPtr));
          //    Py_DECREF(z3CtxPtr);
          //    Py_DECREF(z3MainCtx);

          //    z3::expr expr = tritonToZ3Ast.convert(node);
          //    Z3_ast ast    = Z3_translate(expr.ctx(), expr, z3Ctx);

          //    PyObject* pyArgs = Py_BuildValue("(O)", PyLong_FromVoidPtr(ast));
          //    PyObject* retAst = PyObject_CallObject(PyObject_GetAttrString(pyz3.ptr(), "c_void_p"), pyArgs);
          //    PyObject_SetAttrString(retAst, "__class__", PyObject_GetAttrString(pyz3.ptr(), "Ast"));
          //    Py_DECREF(pyArgs);

          //    PyObject* z3ExprRef = PyObject_GetAttrString(pyz3.ptr(), "ExprRef");
          //    pyArgs = Py_BuildValue("(O)", retAst);
          //    PyObject* retExpr = PyInstance_New(z3ExprRef, pyArgs, nullptr);
          //    Py_DECREF(pyArgs);
          //    Py_DECREF(retAst);
          //    Py_DECREF(z3ExprRef);

          //    return retExpr;
          //  })
          //#endif

          .def("unrollAst",
            [] (triton::ast::AstContext& self, const triton::ast::SharedAbstractNode& node) {
              return triton::ast::unrollAst(node);
            });
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
