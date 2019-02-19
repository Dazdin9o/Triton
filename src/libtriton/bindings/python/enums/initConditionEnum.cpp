//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/archEnums.hpp>



/*! \page py_CONDITION_page CONDITION
    \brief [**python api**] All information about the CONDITION python namespace.

\tableofcontents

\section CONDITION_py_description Description
<hr>

The CONDITION namespace contains all kinds of instruction condition for AArch64.

\section CONDITION_py_api Python API - Items of the CONDITION namespace
<hr>

- **CONDITION.AARCH64.INVALID**<br>
Invalid code condition.

- **CONDITION.AARCH64.AL**<br>
Always. Any flags. This suffix is normally omitted.

- **CONDITION.AARCH64.EQ**<br>
Equal. Z set.

- **CONDITION.AARCH64.GE**<br>
Signed >=. N and V the same.

- **CONDITION.AARCH64.GT**<br>
Signed >. Z clear, N and V the same.

- **CONDITION.AARCH64.HI**<br>
Higher (unsigned >). C set and Z clear.

- **CONDITION.AARCH64.HS**<br>
Higher or same (unsigned >=). C set.

- **CONDITION.AARCH64.LE**<br>
Signed <=. Z set, N and V differ.

- **CONDITION.AARCH64.LO**<br>
Lower (unsigned <). C clear.

- **CONDITION.AARCH64.LS**<br>
Lower or same (unsigned <=). C clear or Z set.

- **CONDITION.AARCH64.LT**<br>
Signed <. N and V differ.

- **CONDITION.AARCH64.MI**<br>
Negative. N set.

- **CONDITION.AARCH64.NE**<br>
Not equal. Z clear.

- **CONDITION.AARCH64.PL**<br>
Positive or zero. N clear.

- **CONDITION.AARCH64.VC**<br>
No overflow. V clear.

- **CONDITION.AARCH64.VS**<br>
Overflow. V set.

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initConditionEnum(pybind11::module& pyTriton) {
        /* Define a submodule */
        pybind11::module condition = pyTriton.def_submodule("CONDITION", "");

        /* CONDITION Enum */
        pybind11::enum_<triton::arch::aarch64::condition_e>(condition, "AARCH64")
          .value("INVALID", triton::arch::aarch64::ID_CONDITION_INVALID)
          .value("AL",      triton::arch::aarch64::ID_CONDITION_AL)
          .value("EQ",      triton::arch::aarch64::ID_CONDITION_EQ)
          .value("GE",      triton::arch::aarch64::ID_CONDITION_GE)
          .value("GT",      triton::arch::aarch64::ID_CONDITION_GT)
          .value("HI",      triton::arch::aarch64::ID_CONDITION_HI)
          .value("HS",      triton::arch::aarch64::ID_CONDITION_HS)
          .value("LE",      triton::arch::aarch64::ID_CONDITION_LE)
          .value("LO",      triton::arch::aarch64::ID_CONDITION_LO)
          .value("LS",      triton::arch::aarch64::ID_CONDITION_LS)
          .value("LT",      triton::arch::aarch64::ID_CONDITION_LT)
          .value("MI",      triton::arch::aarch64::ID_CONDITION_MI)
          .value("NE",      triton::arch::aarch64::ID_CONDITION_NE)
          .value("PL",      triton::arch::aarch64::ID_CONDITION_PL)
          .value("VC",      triton::arch::aarch64::ID_CONDITION_VC)
          .value("VS",      triton::arch::aarch64::ID_CONDITION_VS);
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
