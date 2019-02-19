//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/archEnums.hpp>

#include <string>


/* setup doctest context

>>> from triton import ARCH, TritonContext, REG
>>> ctxt = TritonContext()
>>> ctxt.setArchitecture(ARCH.X86_64)

*/

/*! \page py_REG_page REG
    \brief [**python api**] All information about the REG python namespace.

\tableofcontents

\section REG_py_description Description
<hr>

According to the CPU architecture, the REG namespace contains all enums of register.
It's possible to create a \ref py_Register_page from a register id using `getRegister`
like this:

~~~~~~~~~~~~~{.py}
>>> ah = ctxt.getRegister(REG.X86_AH)
>>> print ah
ah:8 bv[15..8]

~~~~~~~~~~~~~

Note that creating a \ref py_TritonContext_page, you can directly access to constructed
\ref py_Register_page according to your defined architecture.

~~~~~~~~~~~~~{.py}
>>> ctxt.setArchitecture(ARCH.X86_64)
>>> print ctxt.registers.zmm1
zmm1:512 bv[511..0]

~~~~~~~~~~~~~

\section REG_py_api Python API - Items of the REG namespace
<hr>

\subsection REG_X86_py_api x86 registers

\htmlinclude x86_reg

\subsection REG_X8664_py_api x86-64 registers

\htmlinclude x8664_reg

\subsection REG_AArch64_py_api AArch64 registers

\htmlinclude aarch64_reg

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initRegisterEnum(pybind11::module& pyTriton) {
        std::string s;

        auto reg = pybind11::enum_<triton::arch::register_e>(pyTriton, "REG");
        #define REG_SPEC(UPPER_NAME, _1, _2, _3, _4, _5, _6, _7, _8) \
        s = std::string("X86_") + #UPPER_NAME; \
        reg.value(s.c_str(), triton::arch::ID_REG_X86_##UPPER_NAME);
        #define REG_SPEC_NO_CAPSTONE REG_SPEC
        #include "triton/x86.spec"

        #define REG_SPEC(UPPER_NAME, _1, _2, _3, _4, _5) \
        s = std::string("ARCH64_") + #UPPER_NAME; \
        reg.value(s.c_str(), triton::arch::ID_REG_AARCH64_##UPPER_NAME);
        #define REG_SPEC_NO_CAPSTONE REG_SPEC
        #include "triton/aarch64.spec"
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
