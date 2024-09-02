//
// Created by emerson on 20/08/24.
//

#include "Instruction.h"

#include <cstdio>

int sign_extend2(uint32_t value, uint8_t bit) {
    bool sign_bit = ((value & (1 << (bit - 1))) >> 1);
    uint32_t mask = ~((1 << bit) - 1) * sign_bit;
    return (value | mask);
}

Instruction::Instruction(uint32_t instruction_word) {
    this->instruction_word = instruction_word;
    opcode = instruction_word & 0x7F;
    rd = (instruction_word >> 7) & 0x1F;
    rs1 = (instruction_word >> 15) & 0x1F;
    shamt = rs2 = (instruction_word >> 20) & 0x1F;
    func3 = (instruction_word >> 12) & 0x7;
    func7 = (instruction_word >> 25) & 0x7F;
    imm = (instruction_word >> 20) & 0xFFF;
    uint32_t imm_jalbits = (instruction_word >> 12) & 0xFFFFF;
    uint32_t imm_20 = (imm_jalbits & 0x80000);
    uint32_t imm_19_12 = (imm_jalbits & 0xFF) << 11;
    uint32_t imm_11 = (imm_jalbits & 0x100) << 2;
    uint32_t imm_10_1 = (imm_jalbits & 0x7FE00) >> 9;
    imm_jal = (imm_20 | imm_19_12 | imm_11 | imm_10_1);

    uint32_t imm_bbits = imm_s = (func7 << 5) | rd;
    uint32_t imm_b12 = (imm_bbits & 0x800);
    uint32_t imm_b11 = (imm_bbits & 0x1) << 10;
    uint32_t imm_b10_1 = (imm_bbits & 0x7FE) >> 1;
    imm_b = (imm_b12 |  imm_b11 | imm_b10_1);
    imm_u = (instruction_word >> 12) & 0xFFFFF;

}

