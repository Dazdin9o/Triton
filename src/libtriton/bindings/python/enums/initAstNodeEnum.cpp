//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/astEnums.hpp>



/*! \page py_AST_NODE_page AST_NODE
    \brief [**python api**] All information about the AST_NODE python namespace.

\tableofcontents

\section AST_NODE_py_description Description
<hr>

The AST_NODE namespace contains all kinds of node.

\section AST_NODE_py_api Python API - Items of the AST_NODE namespace
<hr>

- **AST_NODE.ANY**
- **AST_NODE.ASSERT**
- **AST_NODE.BV**
- **AST_NODE.BVADD**
- **AST_NODE.BVAND**
- **AST_NODE.BVASHR**
- **AST_NODE.BVLSHR**
- **AST_NODE.BVMUL**
- **AST_NODE.BVNAND**
- **AST_NODE.BVNEG**
- **AST_NODE.BVNOR**
- **AST_NODE.BVNOT**
- **AST_NODE.BVOR**
- **AST_NODE.BVROL**
- **AST_NODE.BVROR**
- **AST_NODE.BVSDIV**
- **AST_NODE.BVSGE**
- **AST_NODE.BVSGT**
- **AST_NODE.BVSHL**
- **AST_NODE.BVSLE**
- **AST_NODE.BVSLT**
- **AST_NODE.BVSMOD**
- **AST_NODE.BVSREM**
- **AST_NODE.BVSUB**
- **AST_NODE.BVUDIV**
- **AST_NODE.BVUGE**
- **AST_NODE.BVUGT**
- **AST_NODE.BVULE**
- **AST_NODE.BVULT**
- **AST_NODE.BVUREM**
- **AST_NODE.BVXNOR**
- **AST_NODE.BVXOR**
- **AST_NODE.COMPOUND**
- **AST_NODE.CONCAT**
- **AST_NODE.DECLARE**
- **AST_NODE.DISTINCT**
- **AST_NODE.EQUAL**
- **AST_NODE.EXTRACT**
- **AST_NODE.IFF**
- **AST_NODE.INTEGER**
- **AST_NODE.INVALID**
- **AST_NODE.ITE**
- **AST_NODE.LAND**
- **AST_NODE.LET**
- **AST_NODE.LNOT**
- **AST_NODE.LOR**
- **AST_NODE.REFERENCE**
- **AST_NODE.STRING**
- **AST_NODE.SX**
- **AST_NODE.VARIABLE**
- **AST_NODE.ZX**

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initAstNodeEnum(pybind11::module& pyTriton) {
        /* AST_NODE Enum */
        pybind11::enum_<triton::ast::ast_e>(pyTriton, "AST_NODE")
          .value("ANY",       triton::ast::ANY_NODE)
          .value("ASSERT",    triton::ast::ASSERT_NODE)
          .value("BV",        triton::ast::BV_NODE)
          .value("BVADD",     triton::ast::BVADD_NODE)
          .value("BVAND",     triton::ast::BVAND_NODE)
          .value("BVASHR",    triton::ast::BVASHR_NODE)
          .value("BVLSHR",    triton::ast::BVLSHR_NODE)
          .value("BVMUL",     triton::ast::BVMUL_NODE)
          .value("BVNAND",    triton::ast::BVNAND_NODE)
          .value("BVNEG",     triton::ast::BVNEG_NODE)
          .value("BVNOR",     triton::ast::BVNOR_NODE)
          .value("BVNOT",     triton::ast::BVNOT_NODE)
          .value("BVOR",      triton::ast::BVOR_NODE)
          .value("BVROL",     triton::ast::BVROL_NODE)
          .value("BVROR",     triton::ast::BVROR_NODE)
          .value("BVSDIV",    triton::ast::BVSDIV_NODE)
          .value("BVSGE",     triton::ast::BVSGE_NODE)
          .value("BVSGT",     triton::ast::BVSGT_NODE)
          .value("BVSHL",     triton::ast::BVSHL_NODE)
          .value("BVSLE",     triton::ast::BVSLE_NODE)
          .value("BVSLT",     triton::ast::BVSLT_NODE)
          .value("BVSMOD",    triton::ast::BVSMOD_NODE)
          .value("BVSREM",    triton::ast::BVSREM_NODE)
          .value("BVSUB",     triton::ast::BVSUB_NODE)
          .value("BVUDIV",    triton::ast::BVUDIV_NODE)
          .value("BVUGE",     triton::ast::BVUGE_NODE)
          .value("BVUGT",     triton::ast::BVUGT_NODE)
          .value("BVULE",     triton::ast::BVULE_NODE)
          .value("BVULT",     triton::ast::BVULT_NODE)
          .value("BVUREM",    triton::ast::BVUREM_NODE)
          .value("BVXNOR",    triton::ast::BVXNOR_NODE)
          .value("BVXOR",     triton::ast::BVXOR_NODE)
          .value("COMPOUND",  triton::ast::COMPOUND_NODE)
          .value("CONCAT",    triton::ast::CONCAT_NODE)
          .value("DECLARE",   triton::ast::DECLARE_NODE)
          .value("DISTINCT",  triton::ast::DISTINCT_NODE)
          .value("EQUAL",     triton::ast::EQUAL_NODE)
          .value("EXTRACT",   triton::ast::EXTRACT_NODE)
          .value("IFF",       triton::ast::IFF_NODE)
          .value("INTEGER",   triton::ast::INTEGER_NODE)
          .value("INVALID",   triton::ast::INVALID_NODE)
          .value("ITE",       triton::ast::ITE_NODE)
          .value("LAND",      triton::ast::LAND_NODE)
          .value("LET",       triton::ast::LET_NODE)
          .value("LNOT",      triton::ast::LNOT_NODE)
          .value("LOR",       triton::ast::LOR_NODE)
          .value("REFERENCE", triton::ast::REFERENCE_NODE)
          .value("STRING",    triton::ast::STRING_NODE)
          .value("SX",        triton::ast::SX_NODE)
          .value("VARIABLE",  triton::ast::VARIABLE_NODE)
          .value("ZX",        triton::ast::ZX_NODE);
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
