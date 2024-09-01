//
// Created by emerson on 20/08/24.
//

#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "CPU.h"
#include "Instruction.h"
#include <filesystem>
#include <iostream>


enum STATE {CONTINUE, STOP, JUMP, ERROR, FINISH};
class Executor {
public:
    [[nodiscard]] const CPU & cpu() const {
        return cpu_;
    }

    [[nodiscard]] STATE state() const {
        return state_;
    }

    explicit Executor(const std::string &program_file, uint32_t start_pc, uint32_t gp, uint32_t size)
        : cpu_(size)
    {

        std::filesystem::path path(program_file);
        path.replace_extension("log");
        log = fopen(path.c_str(), "w");
        //ReadElf reader;
        //int start_pc = 0, gp = 0;
        //reader.read_elf(program_file, start_pc, gp);
        cpu_.set_register(3, gp);
        //char command[500];
        /*std::filesystem::path original_program(program_file);
        std::filesystem::path flat_program(program_file);
        flat_program.replace_extension("bin");
        sprintf(command, "riscv32-unknown-elf-objcopy -O binary %s %s", original_program.c_str(), flat_program.c_str());
        system(command);*/
        cpu_.memory_.load_file(program_file);
        cpu_.set_pc(start_pc);

    }

private:
    FILE *log;
    char dissasembly[30];
    const char *register_names[32] = {"zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1",
        "a0", "a1", "a2", R"(a3)", "a4", "a5", "a6", "a7", "s2", "s3", "s4", "s5", "s6",
        "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};
    STATE state_ = CONTINUE;
public:
    CPU cpu_;
    void execute_addi(uint8_t rd, uint8_t rs1, uint32_t imm);

    void execute_ori(uint8_t rd, uint8_t rs1, uint32_t imm);

    void execute_slti(uint8_t rd, uint8_t rs1, uint32_t imm);

    void execute_sltiu(uint8_t rd, uint8_t rs1, uint32_t imm);

    void execute_xori(uint8_t rd, uint8_t rs1, uint32_t imm);

    void execute_andi(uint8_t rd, uint8_t rs1, uint32_t imm);

    void execute_slli(uint8_t rd, uint8_t rs1, uint8_t shamt);

    void execute_srai(uint8_t rd, uint8_t rs1, uint8_t shamt);

    void execute_srli(uint8_t rd, uint8_t rs1, uint8_t shamt);

    void decode_and_execute_IType(Instruction inst);

    void execute_add(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void execute_sub(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void execute_sll(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void execute_slt(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void execute_sltu(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void execute_xor(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void execute_srl(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void execute_sra(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void execute_or(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void execute_and(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void decode_and_execute_RType(Instruction inst);

    void execute_lui(uint8_t rd, uint32_t imm);

    void execute_auipc(uint8_t rd, uint32_t imm);

    void execute_jal(uint8_t rd, uint32_t imm);

    void execute_jalr(uint8_t rd, uint8_t rs1, uint32_t imm);

    void execute_beq(uint8_t rs1, uint8_t rs2, uint32_t imm, uint8_t rd);

    void execute_bne(uint8_t rs1, uint8_t rs2, uint32_t imm, uint8_t rd);

    void execute_blt(uint8_t rs1, uint8_t rs2, uint32_t imm, uint8_t rd);

    void execute_bge(uint8_t rs1, uint8_t rs2, uint32_t imm, uint8_t rd);

    void execute_bltu(uint8_t rs1, uint8_t rs2, uint32_t imm, uint8_t rd);

    void execute_bgeu(uint8_t rs1, uint8_t rs2, uint32_t imm, uint8_t rd);

    void decode_and_execute_BType(const Instruction & inst);

    void execute_lb(uint8_t rd, uint8_t rs1, uint32_t imm);

    void execute_lh(uint8_t rd, uint8_t rs1, uint32_t imm);

    void execute_lw(uint8_t rd, uint8_t rs1, uint32_t imm);

    void execute_lbu(uint8_t rd, uint8_t rs1, uint32_t imm);

    void execute_lhu(uint8_t rd, uint8_t rs1, uint32_t imm);

    void decode_and_execute_Load(const Instruction & inst);

    void execute_sb(uint8_t rs1, uint8_t rs2, uint32_t imm);

    void execute_sh(uint8_t rs1, uint8_t rs2, uint32_t imm);

    void execute_sw(uint8_t rs1, uint8_t rs2, uint32_t imm);

    void decode_and_execute_Store(const Instruction & inst);

    void execute_ecall();

    void execute_ebreak();

    void decode_and_execute_Einst(const Instruction & inst);

    void execute_mul(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void execute_mulh(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void execute_mulhu(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void execute_mulhsu(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void execute_div(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void execute_divu(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void execute_rem(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void execute_remu(uint8_t rd, uint8_t rs1, uint8_t rs2);

    void decode_and_execute_muldiv(const Instruction & inst);

    void execute_fence(const Instruction & inst);

    void decode_and_execute(uint32_t inst);
    void execute();
};



#endif //EXECUTOR_H
