//
// Created by emerson on 21/08/24.
//

#ifndef INSTRUCTION_CODES_H
#define INSTRUCTION_CODES_H

#define I_OPCODE            0b0010011
#define R_OPCODE            0b0110011
#define LUI_OPCODE          0b0110111
#define AUIPC_OPCODE        0b0010111
#define JAL_OPCODE          0b1101111
#define JALR_OPCODE         0b1100111
#define B_OPCODE            0b1100011
#define LOAD_OPCODE         0b0000011
#define STORE_OPCODE        0b0100011
#define PAUSE_FENCE_OPCODE  0b0001111
#define ECALL_EBREAK_OPCODE 0b1110011

#define ADDSUB_FUNC3 0b000
#define SLL_FUNC3 0b001
#define SLT_FUNC3 0b010
#define SLTU_FUNC3 0b011
#define XOR_FUNC3 0b100
#define SRX_FUNC3 0b101
#define OR_FUNC3 0b110
#define AND_FUNC3 0b111
#define ADD_FUNC7 0b0000000
#define SUB_FUNC7 0b0100000

#define BEQ_FUNC3 0b000
#define BNE_FUNC3 0b001
#define BLT_FUNC3 0b100
#define BGE_FUNC3 0b101
#define BLTU_FUNC3 0b110
#define BGEU_FUNC3 0b111

#define SLB_FUNC3 0b000
#define SLH_FUNC3 0b001
#define SLW_FUNC3 0b010
#define LBU_FUNC3 0b100
#define LHU_FUNC3 0b101

#define MUL_FUNC3  0b000
#define MULH_FUNC3 0b001
#define MULHSU_FUNC3 0b010
#define MULHU_FUNC3 0b011
#define DIV_FUNC3  0b100
#define DIVU_FUNC3 0b101
#define REM_FUNC3 0b110
#define REMU_FUNC3 0b111

#define SRL_FUNC7    0b0000000
#define SRA_FUNC7    0b0100000
#define MULDIV_FUNC7 0b0000001




#endif //INSTRUCTION_CODES_H
