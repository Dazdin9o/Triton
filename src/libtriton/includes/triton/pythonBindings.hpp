//! \file
/*
**  Copyright (C) - Triton
**
**  This program is under the terms of the BSD License.
*/

#ifndef TRITONPYTHONBINDINGS_H
#define TRITONPYTHONBINDINGS_H

#include <triton/pybind11/pybind11.h>
#include <triton/pybind11/stl.h>
#include <triton/pybind11/operators.h>



//! The Triton namespace
namespace triton {
/*!
 *  \addtogroup triton
 *  @{
 */

  //! The Bindings namespace
  namespace bindings {
  /*!
   *  \ingroup triton
   *  \addtogroup bindings
   *  @{
   */

    //! The Python namespace
    namespace python {
    /*!
     *  \ingroup bindings
     *  \addtogroup python
     *  @{
     */

      void initArchEnum(pybind11::module& pyTriton);
      void initAstNodeEnum(pybind11::module& pyTriton);
      void initAstRepresentationEnum(pybind11::module& pyTriton);
      void initCallbackEnum(pybind11::module& pyTriton);
      void initConditionEnum(pybind11::module& pyTriton);
      void initCpuSizeEnum(pybind11::module& pyTriton);
      void initExtendEnum(pybind11::module& pyTriton);
      void initModeEnum(pybind11::module& pyTriton);
      void initOpcodeEnum(pybind11::module& pyTriton);
      void initOperandEnum(pybind11::module& pyTriton);
      void initPrefixEnum(pybind11::module& pyTriton);
      void initRegisterEnum(pybind11::module& pyTriton);
      void initShiftEnum(pybind11::module& pyTriton);
      void initSymbolicEnum(pybind11::module& pyTriton);
      #if defined(__unix__) || defined(__APPLE__)
      void initSyscallEnum(pybind11::module& pyTriton);
      #endif
      void initVersionEnum(pybind11::module& pyTriton);

      void initAstContextObject(pybind11::module& pyTriton);
      void initAstNodeObject(pybind11::module& pyTriton);
      void initBitsVectorObject(pybind11::module& pyTriton);
      void initImmediateObject(pybind11::module& pyTriton);
      void initInstructionObject(pybind11::module& pyTriton);
      void initMemoryAccessObject(pybind11::module& pyTriton);
      void initPathConstraintObject(pybind11::module& pyTriton);
      void initRegisterObject(pybind11::module& pyTriton);
      void initShortcutRegisterObject(pybind11::module& pyTriton);
      void initSolverModelObject(pybind11::module& pyTriton);
      void initSymbolicExpressionObject(pybind11::module& pyTriton);
      void initSymbolicVariableObject(pybind11::module& pyTriton);
      void initTritonContextObject(pybind11::module& pyTriton);

    /*! @} End of python namespace */
    };
  /*! @} End of bindings namespace */
  };
/*! @} End of triton namespace */
};

#endif /* TRITONPYTHONBINDINGS_H */
