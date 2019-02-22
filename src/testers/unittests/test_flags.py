#!/usr/bin/env python2
# coding: utf-8
"""Test flags."""

import unittest
import random

from triton import ARCH, REG, TritonContext


class TestFlags(unittest.TestCase):

    """Testing the concrete flag values."""

    def setUp(self):
        """Define the arch."""
        self.Triton = TritonContext()
        self.Triton.setArchitecture(ARCH.X86_64)

    def test_set_flags(self):
        """Check flags can be set in any order with a correct output result."""
        registers = [REG.X86_ZF, REG.X86_AF, REG.X86_IF, REG.X86_CF,
                     REG.X86_DF, REG.X86_PF, REG.X86_SF, REG.X86_OF,
                     REG.X86_TF]
        values = [0] * len(registers)

        rand_registers = list(registers)
        random.shuffle(rand_registers)

        # Randomnly set flags registers and check result is the one expected
        for reg in rand_registers:
            self.Triton.setConcreteRegisterValue(self.Triton.getRegister(reg), 1)
            values[registers.index(reg)] = 1
            self.assertListEqual([self.Triton.getConcreteRegisterValue(self.Triton.getRegister(r)) for r in registers], values)

    def test_unset_flags(self):
        """Check flags can be unset in any order with a correct result."""
        registers = [REG.X86_ZF, REG.X86_AF, REG.X86_IF, REG.X86_CF,
                     REG.X86_DF, REG.X86_PF, REG.X86_SF, REG.X86_OF,
                     REG.X86_TF]
        values = [1] * len(registers)
        for reg in registers:
            self.Triton.setConcreteRegisterValue(self.Triton.getRegister(reg), 1)

        rand_registers = list(registers)
        random.shuffle(rand_registers)

        # Randomnly unset flags registers and check result is the one expected
        for reg in rand_registers:
            self.Triton.setConcreteRegisterValue(self.Triton.getRegister(reg), 0)
            values[registers.index(reg)] = 0
            self.assertListEqual([self.Triton.getConcreteRegisterValue(self.Triton.getRegister(r)) for r in registers], values)
