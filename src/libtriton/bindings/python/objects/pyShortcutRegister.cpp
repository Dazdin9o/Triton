//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/archEnums.hpp>
#include <triton/register.hpp>
#include <triton/shortcutRegister.hpp>

#include <string>



namespace triton {
  namespace bindings {
    namespace python {

      void initShortcutRegisterObject(pybind11::module& pyTriton) {
        std::string s;

        auto reg = pybind11::class_<triton::arch::ShortcutRegister>(pyTriton, "ShortcutRegister", "The ShortcutRegister class");
        #define REG_SPEC(_0, LOWER_NAME, _2, _3, _4, _5, _6, _7, _8) \
        s = std::string("x86_") + #LOWER_NAME; \
        reg.def_readonly(s.c_str(), &triton::arch::ShortcutRegister::x86_##LOWER_NAME);
        #define REG_SPEC_NO_CAPSTONE REG_SPEC
        #include "triton/x86.spec"

        #define REG_SPEC(_0, LOWER_NAME, _2, _3, _4, _5) \
        s = std::string("aarch64_") + #LOWER_NAME; \
        reg.def_readonly(s.c_str(), &triton::arch::ShortcutRegister::aarch64_##LOWER_NAME);
        #define REG_SPEC_NO_CAPSTONE REG_SPEC
        #include "triton/aarch64.spec"
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
