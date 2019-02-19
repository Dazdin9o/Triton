//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/modesEnums.hpp>



/*! \page py_MODE_page MODE
    \brief [**python api**] All information about the MODE python namespace.

\tableofcontents

\section MODE_py_description Description
<hr>

The MODE namespace contains all kinds of mode.

\subsection MODE_py_example Example

~~~~~~~~~~~~~{.py}
>>> enableMode(MODE.ONLY_ON_TAINTED, True)
~~~~~~~~~~~~~

\section MODE_py_api Python API - Items of the MODE namespace
<hr>

- **MODE.ALIGNED_MEMORY**<br>
Enabled, Triton will keep a map of aligned memory to reduce the symbolic memory explosion of `LOAD` and `STORE` acceess.

- **MODE.AST_OPTIMIZATIONS**<br>
Enabled, Triton will reduces the depth of the trees using classical arithmetic optimisations.

- **MODE.CONCRETIZE_UNDEFINED_REGISTERS**<br>
Enabled, Triton will concretize every registers tagged as undefined (see #750).

- **MODE.ONLY_ON_SYMBOLIZED**<br>
Enabled, Triton will perform symbolic execution only on symbolized expressions.

- **MODE.ONLY_ON_TAINTED**<br>
Enabled, Triton will perform symbolic execution only on tainted instructions.

- **MODE.PC_TRACKING_SYMBOLIC**<br>
Enabled, Triton will track path constraints only if they are symbolized. This mode is enabled by default.

- **MODE.SYMBOLIZE_INDEX_ROTATION**<br>
Enabled, Triton will symbolize the index of rotation for `bvror` and `bvrol` nodes. This mode increases the complexity of solving.

- **MODE.TAINT_THROUGH_POINTERS**<br>
Enabled, the taint is spread if an index pointer is already tainted (see #725).
*/



namespace triton {
  namespace bindings {
    namespace python {

      void initModeEnum(pybind11::module& pyTriton) {
        /* MODE Enum */
        pybind11::enum_<triton::modes::mode_e>(pyTriton, "MODE")
          .value("ALIGNED_MEMORY",                 triton::modes::ALIGNED_MEMORY)
          .value("AST_OPTIMIZATIONS",              triton::modes::AST_OPTIMIZATIONS)
          .value("CONCRETIZE_UNDEFINED_REGISTERS", triton::modes::CONCRETIZE_UNDEFINED_REGISTERS)
          .value("ONLY_ON_SYMBOLIZED",             triton::modes::ONLY_ON_SYMBOLIZED)
          .value("ONLY_ON_TAINTED",                triton::modes::ONLY_ON_TAINTED)
          .value("PC_TRACKING_SYMBOLIC",           triton::modes::PC_TRACKING_SYMBOLIC)
          .value("SYMBOLIZE_INDEX_ROTATION",       triton::modes::SYMBOLIZE_INDEX_ROTATION)
          .value("TAINT_THROUGH_POINTERS",         triton::modes::TAINT_THROUGH_POINTERS);
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
