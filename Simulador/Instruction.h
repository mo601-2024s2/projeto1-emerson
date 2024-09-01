//
// Created by emerson on 20/08/24.
//

#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <cstdint>


class Instruction {
public:
    uint32_t instruction_word;
    uint8_t opcode;
    uint8_t rs1, rs2, rd;
    uint32_t imm;
    uint8_t shamt;
    uint8_t func3, func7;
    uint32_t imm_u;
    uint32_t imm_jal;
    uint32_t imm_b;
    uint32_t imm_s;
    Instruction(uint32_t instruction_word);
};



#endif //INSTRUCTION_H
