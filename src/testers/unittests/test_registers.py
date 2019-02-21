#!/usr/bin/env python2
# coding: utf-8
"""Test register."""

import unittest
import random

from triton import (ARCH, REG, OPERAND, TritonContext)


class TestRAXRegister(unittest.TestCase):

    """Testing the Register class with RAX."""

    def setUp(self):
        """Define arch and register to check."""
        self.ctx = TritonContext()
        self.ctx.setArchitecture(ARCH.X86_64)
        self.reg = self.ctx.registers.x86_rax

    def test_name(self):
        """Check register name."""
        self.assertEqual(self.reg.getName(), "rax")

    def test_size(self):
        """Check register size."""
        self.assertEqual(self.reg.getSize(), 8)

    def test_bit_size(self):
        """Check register bit size."""
        self.assertEqual(self.reg.getBitSize(), 64)

    def test_parent(self):
        """Check parent register."""
        self.assertEqual(self.ctx.getParentRegister(self.reg).getName(), "rax")

    def test_type(self):
        """Check operand type."""
        self.assertEqual(self.reg.getType(), OPERAND.REG)

    def test_is_valid(self):
        """Check register validity."""
        self.assertTrue(self.ctx.isRegisterValid(self.reg))

    def test_is_flag(self):
        """Check register flag."""
        self.assertFalse(self.ctx.isFlag(self.reg))

    def test_is_register(self):
        """Check register detect."""
        self.assertTrue(self.ctx.isRegister(self.reg))

    def test_is_mutable(self):
        """Check register is mutable."""
        self.assertTrue(self.reg.isMutable())


class TestAHRegister(unittest.TestCase):

    """Testing the Register class with AH."""

    def setUp(self):
        """Define arch and register to check."""
        self.ctx = TritonContext()
        self.ctx.setArchitecture(ARCH.X86_64)
        self.reg = self.ctx.registers.x86_ah

    def test_size(self):
        """Check register size."""
        self.assertEqual(self.reg.getSize(), 1)

    def test_bitvector(self):
        """Check bitvector information."""
        self.assertEqual(self.reg.getBitvector().getHigh(), 15)
        self.assertEqual(self.reg.getBitvector().getLow(), 8)
        self.assertEqual(self.reg.getBitvector().getVectorSize(), 8)

    def test_parent(self):
        """Check parent register on multiple arch."""
        self.assertEqual(self.ctx.getParentRegister(self.reg).getName(), "rax")

        self.ctx.setArchitecture(ARCH.X86)
        self.reg = self.ctx.registers.x86_ah
        self.assertEqual(self.ctx.getParentRegister(self.reg).getName(), "eax")
        self.assertEqual(self.ctx.getParentRegister(self.reg).getBitSize(), 32)


class TestXmmRegister(unittest.TestCase):

    """Testing the Register class with FP/SIMD registers."""

    def setUp(self):
        """Define the arch."""
        self.ctx = TritonContext()
        self.ctx.setArchitecture(ARCH.X86_64)

    def test_xmm_on_x86(self):
        """Check xmm on 32 bits arch."""
        self.ctx.setArchitecture(ARCH.X86)
        xmm = self.ctx.registers.x86_xmm1
        self.assertEqual(xmm.getBitSize(), 128)

    def test_ymm(self):
        """Check ymm on 64 bits arch."""
        ymm = self.ctx.registers.x86_ymm1
        self.assertEqual(ymm.getBitSize(), 256)

    def test_zmm(self):
        """Check zmm on 64 bits arch."""
        zmm = self.ctx.registers.x86_zmm2
        self.assertEqual(zmm.getBitSize(), 512)


class TestRegisterValues(unittest.TestCase):

    """Check register values with hierarchies."""

    def setUp(self):
        """Define the arch."""
        self.ctx = TritonContext()
        self.ctx.setArchitecture(ARCH.X86_64)

    def test_set_concrete_value(self):
        """Check register value modification."""
        for reg in (REG.X86_AH, REG.X86_AL):
            # OK
            reg = self.ctx.getRegister(reg)
            self.ctx.setConcreteRegisterValue(reg, 0xff)
            # Not OK
            # TODO : Be more specific on the raise exception type
            with self.assertRaises(Exception):
                self.ctx.setConcreteRegisterValue(reg, 0xff+1)

        reg = self.ctx.registers.x86_zf
        self.ctx.setConcreteRegisterValue(reg, 1)
        with self.assertRaises(Exception):
            self.ctx.setConcreteRegisterValue(reg, 2)

    def test_overlap(self):
        """Check register overlapping."""
        self.assertTrue(self.ctx.registers.x86_ax.isOverlapWith(self.ctx.registers.x86_eax), "overlap with upper")
        self.assertTrue(self.ctx.registers.x86_ax.isOverlapWith(self.ctx.registers.x86_rax), "overlap with parent")
        self.assertTrue(self.ctx.registers.x86_rax.isOverlapWith(self.ctx.registers.x86_ax), "overlap with lower")
        self.assertFalse(self.ctx.registers.x86_ah.isOverlapWith(self.ctx.registers.x86_al))
        self.assertTrue(self.ctx.registers.x86_ah.isOverlapWith(self.ctx.registers.x86_eax))
        self.assertTrue(self.ctx.registers.x86_eax.isOverlapWith(self.ctx.registers.x86_ah))
        self.assertTrue(self.ctx.registers.x86_ax.isOverlapWith(self.ctx.registers.x86_al))
        self.assertTrue(self.ctx.registers.x86_al.isOverlapWith(self.ctx.registers.x86_ax))
        self.assertFalse(self.ctx.registers.x86_eax.isOverlapWith(self.ctx.registers.x86_edx))


class TestAArch64Registers(unittest.TestCase):
    """Test AArch64 registers"""

    def setUp(self):
        """Define the arch."""
        self.ctx = TritonContext()
        self.ctx.setArchitecture(ARCH.AARCH64)

    def test_set_concrete_value(self):
        """Check register value modification."""
        for reg in self.ctx.getParentRegisters():
            if reg.isMutable() == False:
                # XZR
                continue
            i = random.randrange(0, 0xffffffffffffffff) & reg.getBitvector().getMaxValue()
            self.assertEqual(self.ctx.getConcreteRegisterValue(reg), 0)
            self.ctx.setConcreteRegisterValue(reg, i)
            self.assertEqual(self.ctx.getConcreteRegisterValue(reg), i)
            self.ctx.setConcreteRegisterValue(reg, 0)
            self.assertEqual(self.ctx.getConcreteRegisterValue(reg), 0)

        regs = [
            self.ctx.registers.aarch64_w0, self.ctx.registers.aarch64_w1, self.ctx.registers.aarch64_w2,
            self.ctx.registers.aarch64_w3, self.ctx.registers.aarch64_w4, self.ctx.registers.aarch64_w5,
            self.ctx.registers.aarch64_w6, self.ctx.registers.aarch64_w7, self.ctx.registers.aarch64_w8,
            self.ctx.registers.aarch64_w9, self.ctx.registers.aarch64_w10, self.ctx.registers.aarch64_w11,
            self.ctx.registers.aarch64_w12, self.ctx.registers.aarch64_w13, self.ctx.registers.aarch64_w14,
            self.ctx.registers.aarch64_w15, self.ctx.registers.aarch64_w16, self.ctx.registers.aarch64_w17,
            self.ctx.registers.aarch64_w18, self.ctx.registers.aarch64_w19, self.ctx.registers.aarch64_w20,
            self.ctx.registers.aarch64_w21, self.ctx.registers.aarch64_w22, self.ctx.registers.aarch64_w23,
            self.ctx.registers.aarch64_w24, self.ctx.registers.aarch64_w25, self.ctx.registers.aarch64_w26,
            self.ctx.registers.aarch64_w27, self.ctx.registers.aarch64_w28, self.ctx.registers.aarch64_w29,
            self.ctx.registers.aarch64_w30, self.ctx.registers.aarch64_wsp, self.ctx.registers.aarch64_spsr,
        ]

        for reg in regs:
            i = random.randrange(0, 0xffffffff) & reg.getBitvector().getMaxValue()
            self.ctx.setConcreteRegisterValue(reg, i)
            self.assertEqual(self.ctx.getConcreteRegisterValue(reg), i)
            self.ctx.setConcreteRegisterValue(reg, 0)
            self.assertEqual(self.ctx.getConcreteRegisterValue(reg), 0)
