//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#include <triton/pythonBindings.hpp>
#include <triton/pythonUtils.hpp>
#include <triton/bitsVector.hpp>



/* setup doctest context

>>> from triton import ARCH, TritonContext, REG
>>> ctxt = TritonContext()
>>> ctxt.setArchitecture(ARCH.X86_64)

*/

/*! \page py_BitsVector_page BitsVector
    \brief [**python api**] All information about the BitsVector python object.

\tableofcontents

\section py_BitsVector_description Description
<hr>

This object is used to represent a bits vector. Mainly used by \ref py_Register_page, \ref py_MemoryAccess_page and \ref py_Immediate_page.

~~~~~~~~~~~~~{.py}
>>> ah = ctxt.registers.ah
>>> bv = ah.getBitvector()
>>> bv.getHigh()
15L
>>> bv.getLow()
8L
>>> bv.getVectorSize()
8L
>>> bv.getMaxValue()
255L

~~~~~~~~~~~~~

\section BitsVector_py_api Python API - Methods of the BitsVector class
<hr>

- <b>integer getHigh(void)</b><br>
Returns the highest bit position.

- <b>integer getLow(void)</b><br>
Returns the lower bit position.

- <b>integer getMaxValue(void)</b><br>
Returns the max value of the vector.

- <b>integer getVectorSize(void)</b><br>
Returns the size of the vector.

*/



namespace triton {
  namespace bindings {
    namespace python {

      void initBitsVectorObject(pybind11::module& pyTriton) {
        pybind11::class_<triton::arch::BitsVector>(pyTriton, "BitsVector", "The BitsVector class")

          .def("getHigh",       &triton::arch::BitsVector::getHigh)
          .def("getLow",        &triton::arch::BitsVector::getLow)
          .def("getVectorSize", &triton::arch::BitsVector::getVectorSize)

          .def("getMaxValue",
            [] (const triton::arch::BitsVector& self) -> pybind11::object {
              return pybind11::reinterpret_borrow<pybind11::object>(PyLong_FromUint512(self.getMaxValue()));
            })

          .def("__repr__",
            [] (const triton::arch::BitsVector& bv) {
              std::ostringstream stream;
              stream << bv;
              return stream.str();
            })

          .def("__str__",
            [] (const triton::arch::BitsVector& bv) {
              std::ostringstream stream;
              stream << bv;
              return stream.str();
            });
      }

    }; /* python namespace */
  }; /* bindings namespace */
}; /* triton namespace */
