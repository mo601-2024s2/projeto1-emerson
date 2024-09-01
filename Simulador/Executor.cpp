//
// Created by emerson on 20/08/24.
//

#include "Executor.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <bits/stdint-intn.h>
#include <bits/stdint-uintn.h>

#include "Instruction.h"
#include "instruction_codes.h"

int32_t sign_extend(uint32_t value, uint8_t bit) {
    bool sign_bit = ((value & (1 << (bit - 1))) >> 1);
    uint32_t mask = ~((1 << bit) - 1) * sign_bit;
    return (value | mask);
}
void Executor::execute_addi(uint8_t rd, uint8_t rs1, uint32_t imm) {
    cpu_.set_register(rd, cpu_.registers()[rs1] + sign_extend(imm, 12));
    sprintf(dissasembly,"addi    %s, %s, %i", register_names[rd], register_names[rs1], sign_extend(imm, 12));
}

void Executor::execute_ori(uint8_t rd, uint8_t rs1, uint32_t imm) {
    cpu_.set_register(rd, cpu_.registers()[rs1] | sign_extend(imm, 12));
    sprintf(dissasembly,"ori     %s, %s, %i", register_names[rd], register_names[rs1], sign_extend(imm, 12));
}

void Executor::execute_slti(uint8_t rd, uint8_t rs1, uint32_t imm) {
    cpu_.set_register(rd, static_cast<int32_t>(cpu_.registers()[rs1]) < static_cast<int32_t>(sign_extend(imm, 12)) ? 1 :0);
    sprintf(dissasembly,"slti    %s, %s, %i", register_names[rd], register_names[rs1], sign_extend(imm, 12));
}

void Executor::execute_sltiu(uint8_t rd, uint8_t rs1, uint32_t imm) {
    cpu_.set_register(rd, cpu_.registers()[rs1] < sign_extend(imm, 12) ? 1 :0);
    sprintf(dissasembly,"sltiu   %s, %s, %i", register_names[rd], register_names[rs1], sign_extend(imm, 12));
}

void Executor::execute_xori(uint8_t rd, uint8_t rs1, uint32_t imm) {
    cpu_.set_register(rd, cpu_.registers()[rs1] ^ sign_extend(imm, 12));
    sprintf(dissasembly,"xori    %s, %s, %i", register_names[rd], register_names[rs1], sign_extend(imm, 12));
}

void Executor::execute_andi(uint8_t rd, uint8_t rs1, uint32_t imm) {
    cpu_.set_register(rd, cpu_.registers()[rs1] & sign_extend(imm, 12));
    sprintf(dissasembly,"andi    %s, %s, %i", register_names[rd], register_names[rs1], sign_extend(imm, 12));
}

void Executor::execute_slli(uint8_t rd, uint8_t rs1, uint8_t shamt) {
    uint32_t value = cpu_.registers()[rs1] << shamt;
    cpu_.set_register(rd, value);
    sprintf(dissasembly,"slli    %s, %s, %i", register_names[rd], register_names[rs1], shamt);
}

void Executor::execute_srai(uint8_t rd, uint8_t rs1, uint8_t shamt) {
    cpu_.set_register(rd, static_cast<int32_t>(cpu_.registers()[rs1]) >> shamt);
    sprintf(dissasembly,"srai    %s, %s, %i", register_names[rd], register_names[rs1], shamt);
}

void Executor::execute_srli(uint8_t rd, uint8_t rs1, uint8_t shamt) {
    cpu_.set_register(rd, cpu_.registers()[rs1] >> shamt);
    sprintf(dissasembly,"srli    %s, %s, %i", register_names[rd], register_names[rs1], shamt);
}

void Executor::execute_add(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    cpu_.set_register(rd, cpu_.registers()[rs1] + cpu_.registers()[rs2]);
    sprintf(dissasembly,"add     %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::execute_sub(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    cpu_.set_register(rd, cpu_.registers()[rs1] - cpu_.registers()[rs2]);
    sprintf(dissasembly,"sub     %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::execute_sll(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    cpu_.set_register(rd, cpu_.registers()[rs1] << cpu_.registers()[rs2]);
    sprintf(dissasembly,"sll     %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::execute_slt(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    cpu_.set_register(rd, static_cast<int32_t>(cpu_.registers()[rs1]) +
        static_cast<int32_t>(cpu_.registers()[rs2])? 1 :0);
    sprintf(dissasembly,"slt     %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::execute_sltu(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    cpu_.set_register(rd, cpu_.registers()[rs1] < cpu_.registers()[rs2]? 1 : 0);
    sprintf(dissasembly,"sltu    %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::execute_xor(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    cpu_.set_register(rd, cpu_.registers()[rs1] ^ cpu_.registers()[rs2]);
    sprintf(dissasembly,"xor     %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::execute_srl(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    cpu_.set_register(rd, cpu_.registers()[rs1] >> cpu_.registers()[rs2]);
    sprintf(dissasembly,"srl     %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::execute_sra(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    cpu_.set_register(rd, static_cast<int32_t>(cpu_.registers()[rs1]) >> static_cast<int32_t>(cpu_.registers()[rs2]));
    sprintf(dissasembly,"sra     %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::execute_or(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    cpu_.set_register(rd, cpu_.registers()[rs1] | cpu_.registers()[rs2]);
    sprintf(dissasembly,"or      %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::execute_and(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    cpu_.set_register(rd, cpu_.registers()[rs1] & cpu_.registers()[rs2]);
    sprintf(dissasembly,"and     %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::decode_and_execute_IType(Instruction inst) {
    switch (inst.func3) {
        case ADDSUB_FUNC3:
            execute_addi(inst.rd, inst.rs1, inst.imm);
            break;
        case OR_FUNC3:
            execute_ori(inst.rd, inst.rs1, inst.imm);
            break;
        case SLT_FUNC3:
            execute_slti(inst.rd, inst.rs1, inst.imm);
            break;
        case SLTU_FUNC3:
            execute_sltiu(inst.rd, inst.rs1, inst.imm);
            break;
        case XOR_FUNC3:
            execute_xori(inst.rd, inst.rs1, inst.imm);
            break;
        case AND_FUNC3:
            execute_andi(inst.rd, inst.rs1, inst.imm);
            break;
        case SLL_FUNC3:
            execute_slli(inst.rd, inst.rs1, inst.shamt);
            break;
        case SRX_FUNC3:
            switch (inst.func7) {
                case SRA_FUNC7:
                    execute_srai(inst.rd, inst.rs1, inst.shamt);
                    break;
                case SRL_FUNC7:
                    execute_srli(inst.rd, inst.rs1, inst.shamt);
                    break;
                default:
                    state_ = ERROR;
                    break;
            }
            break;
        default:
            state_ = ERROR;
            break;
    }
}

void Executor::decode_and_execute_RType(Instruction inst) {
        switch (inst.func3) {
            case ADDSUB_FUNC3:
                switch (inst.func7) {
                    case ADD_FUNC7:
                        execute_add(inst.rd, inst.rs1, inst.rs2);
                        break;
                    case SUB_FUNC7:
                        execute_sub(inst.rd, inst.rs1, inst.rs2);
                        break;
                    default:
                        state_ = ERROR;
                        break;
                }
                break;
            case SLL_FUNC3:
                execute_sll(inst.rd, inst.rs1, inst.rs2);
                break;
            case SLT_FUNC3:
                execute_slt(inst.rd, inst.rs1, inst.rs2);
                break;
            case SLTU_FUNC3:
                execute_sltu(inst.rd, inst.rs1, inst.rs2);
                break;
            case XOR_FUNC3:
                execute_xor(inst.rd, inst.rs1, inst.rs2);
                break;
            case SRX_FUNC3:
                switch (inst.func7) {
                    case SRL_FUNC7:
                        execute_srl(inst.rd, inst.rs1, inst.rs2);
                        break;
                    case SRA_FUNC7:
                        execute_sra(inst.rd, inst.rs1, inst.rs2);
                        break;
                    default:
                        state_ = ERROR;
                    break;
                }
                break;
            case OR_FUNC3:
                execute_or(inst.rd, inst.rs1, inst.rs2);
                break;
            case AND_FUNC3:
                execute_and(inst.rd, inst.rs1, inst.rs2);
                break;
            default:
                state_ = ERROR;
                break;
        }
}

void Executor::execute_lui(uint8_t rd, uint32_t imm) {
    imm = imm << 12;
    cpu_.set_register(rd, imm);
    sprintf(dissasembly,"lui     %s, %i", register_names[rd], imm >> 12);
}

void Executor::execute_auipc(uint8_t rd, uint32_t imm) {
    imm = (imm << 12);
    cpu_.set_register(rd, cpu_.pc() + imm);
    sprintf(dissasembly,"auipc   %s, %i", register_names[rd], imm >> 12);
}

void Executor::execute_jal(uint8_t rd, uint32_t imm) {
    cpu_.set_register(rd, cpu_.pc() + 4);
    imm = sign_extend(imm, 20) << 1;
    cpu_.set_pc(cpu_.pc() + imm);
    sprintf(dissasembly,"jal     %s, %i", register_names[rd], imm);
    state_ = JUMP;
}

void Executor::execute_jalr(uint8_t rd, uint8_t rs1, uint32_t imm) {
    cpu_.set_register(rd, cpu_.pc() + 4);
    cpu_.set_pc(cpu_.registers()[rs1] + sign_extend(imm, 12));
    sprintf(dissasembly,"jalr    %s, %i(%s)", register_names[rd], sign_extend(imm, 12), register_names[rs1]);
    state_ = JUMP;
}

void Executor::execute_beq(uint8_t rs1, uint8_t rs2, uint32_t imm, uint8_t rd) {
    imm = sign_extend(imm, 12) << 1;
    if (cpu_.registers()[rs1] == cpu_.registers()[rs2]) {
        cpu_.set_pc(cpu_.pc() + imm);
        state_ = JUMP;
    }
    sprintf(dissasembly,"beq     %s, %s, %i", register_names[rs1], register_names[rs2], imm);
}

void Executor::execute_bne(uint8_t rs1, uint8_t rs2, uint32_t imm, uint8_t rd) {
    imm = sign_extend(imm, 12) << 1;
    if (cpu_.registers()[rs1] != cpu_.registers()[rs2]) {
        cpu_.set_pc(cpu_.pc() + imm);
        state_ = JUMP;
    }
    sprintf(dissasembly,"bne     %s, %s, %i", register_names[rs1], register_names[rs2], imm);
}

void Executor::execute_blt(uint8_t rs1, uint8_t rs2, uint32_t imm, uint8_t rd) {
    imm = sign_extend(imm, 12) << 1;
    int32_t rs1_val= cpu_.registers()[rs1];
    int32_t rs2_val = cpu_.registers()[rs2];
    if (rs1_val < rs2_val) {
        cpu_.set_pc(cpu_.pc() + imm);
        state_ = JUMP;
    }
    sprintf(dissasembly,"blt     %s, %s, %i", register_names[rs1], register_names[rs2], imm);
}

void Executor::execute_bge(uint8_t rs1, uint8_t rs2, uint32_t imm, uint8_t rd) {
    imm = sign_extend(imm, 12) << 1;
    int32_t rs1_val= cpu_.registers()[rs1];
    int32_t rs2_val = cpu_.registers()[rs2];
    if (rs1_val >= rs2_val) {
        cpu_.set_pc(cpu_.pc() + imm);
        state_ = JUMP;
    }
    sprintf(dissasembly,"bge     %s, %s, %i", register_names[rs1], register_names[rs2], imm);
}

void Executor::execute_bltu(uint8_t rs1, uint8_t rs2, uint32_t imm, uint8_t rd) {
    imm = sign_extend(imm, 12) << 1;
    uint32_t rs1_val= cpu_.registers()[rs1];
    uint32_t rs2_val = cpu_.registers()[rs2];
    if (rs1_val < rs2_val) {
        cpu_.set_pc(cpu_.pc() + imm);
        state_ = JUMP;
    }
    sprintf(dissasembly,"bltu    %s, %s, %i", register_names[rs1], register_names[rs2], imm);
}

void Executor::execute_bgeu(uint8_t rs1, uint8_t rs2, uint32_t imm, uint8_t rd) {

    imm = sign_extend(imm, 12) << 1;
    uint32_t rs1_val= cpu_.registers()[rs1];
    uint32_t rs2_val = cpu_.registers()[rs2];
    if (rs1_val >= rs2_val) {
        cpu_.set_pc(cpu_.pc() + imm);
        state_ = JUMP;
    }
    sprintf(dissasembly,"bgeu    %s, %s, %i", register_names[rs1], register_names[rs2], imm);
}

void Executor::decode_and_execute_BType(const Instruction &inst) {
    switch (inst.func3) {
        case BEQ_FUNC3:
            execute_beq(inst.rs1, inst.rs2, inst.imm_b, inst.rd);
        break;
        case BNE_FUNC3:
            execute_bne(inst.rs1, inst.rs2, inst.imm_b, inst.rd);
        break;
        case BLT_FUNC3:
            execute_blt(inst.rs1, inst.rs2, inst.imm_b, inst.rd);
            break;
        case BGE_FUNC3:
            execute_bge(inst.rs1, inst.rs2, inst.imm_b, inst.rd);
        break;
        case BLTU_FUNC3:
            execute_bltu(inst.rs1, inst.rs2, inst.imm_b, inst.rd);
        break;
        case BGEU_FUNC3:
            execute_bgeu(inst.rs1, inst.rs2, inst.imm_b, inst.rd);
        break;
        default:
            state_ = ERROR;
    }
}

void Executor::execute_lb(uint8_t rd, uint8_t rs1, uint32_t imm) {
    uint32_t rs1_val= cpu_.registers()[rs1];
    imm = sign_extend(imm, 12);
    uint32_t byte_val = sign_extend(cpu_.memory_.get_byte(rs1_val + imm), 8);
    cpu_.set_register(rd, byte_val);
    sprintf(dissasembly,"lb      %s, %i(%s)", register_names[rd], imm, register_names[rs1]);

}

void Executor::execute_lh(uint8_t rd, uint8_t rs1, uint32_t imm) {
    uint32_t rs1_val= cpu_.registers()[rs1];
    imm = sign_extend(imm, 12);
    uint32_t half_val = sign_extend(cpu_.memory_.get_byte(rs1_val + imm), 16);
    cpu_.set_register(rd, half_val);
    sprintf(dissasembly,"lh      %s, %i(%s)", register_names[rd], imm, register_names[rs1]);

}

void Executor::execute_lw(uint8_t rd, uint8_t rs1, uint32_t imm) {
    uint32_t rs1_val= cpu_.registers()[rs1];
    imm = sign_extend(imm, 12);
    uint32_t word_val = cpu_.memory_.get_word(rs1_val + imm);
    cpu_.set_register(rd, word_val);
    sprintf(dissasembly,"lw      %s, %i(%s)", register_names[rd], imm, register_names[rs1]);

}

void Executor::execute_lbu(uint8_t rd, uint8_t rs1, uint32_t imm) {
    uint32_t rs1_val= cpu_.registers()[rs1];
    imm = sign_extend(imm, 12);
    uint32_t byte_val = cpu_.memory_.get_byte(rs1_val + imm);
    cpu_.set_register(rd, byte_val);
    sprintf(dissasembly,"lbu     %s, %i(%s)", register_names[rd], imm, register_names[rs1]);

}

void Executor::execute_lhu(uint8_t rd, uint8_t rs1, uint32_t imm) {
    uint32_t rs1_val= cpu_.registers()[rs1];
    imm = sign_extend(imm, 12);
    uint32_t half_val = cpu_.memory_.get_halfword(rs1_val + imm);
    cpu_.set_register(rd, half_val);
    sprintf(dissasembly,"lhu     %s, %i(%s)", register_names[rd], imm, register_names[rs1]);
}

void Executor::decode_and_execute_Load(const Instruction &inst) {
    switch (inst.func3) {
        case SLB_FUNC3:
            execute_lb(inst.rd, inst.rs1, inst.imm);
            break;
        case SLH_FUNC3:
            execute_lh(inst.rd, inst.rs1, inst.imm);
        break;
        case SLW_FUNC3:
            execute_lw(inst.rd, inst.rs1, inst.imm);
        break;
        case LBU_FUNC3:
            execute_lbu(inst.rd, inst.rs1, inst.imm);
        break;
        case LHU_FUNC3:
            execute_lhu(inst.rd, inst.rs1, inst.imm);
        break;
        default:
            state_ = ERROR;
    }
}

void Executor::execute_sb(uint8_t rs1, uint8_t rs2, uint32_t imm) {
    imm = sign_extend(imm, 12);
    uint32_t pos = cpu_.registers()[rs1] + sign_extend(imm, 12);
    uint32_t reg_val = cpu_.registers()[rs2];
    cpu_.memory_.set_byte(pos, reg_val );
    sprintf(dissasembly,"sb      %s, %i(%s)", register_names[rs1], sign_extend(imm, 12), register_names[rs2]);
}

void Executor::execute_sh(uint8_t rs1, uint8_t rs2, uint32_t imm) {
    imm = sign_extend(imm, 12);
    uint32_t pos = cpu_.registers()[rs1] + sign_extend(imm, 12);
    uint32_t reg_val = cpu_.registers()[rs2];
    cpu_.memory_.set_halfword(pos, reg_val );
    sprintf(dissasembly,"sh      %s, %i(%s)", register_names[rs1], sign_extend(imm, 12), register_names[rs2]);

}

void Executor::execute_sw(uint8_t rs1, uint8_t rs2, uint32_t imm) {
    imm = sign_extend(imm, 12);
    uint32_t pos = cpu_.registers()[rs1] + sign_extend(imm, 12);
    uint32_t reg_val = cpu_.registers()[rs2];
    cpu_.memory_.set_word(pos, reg_val );
    sprintf(dissasembly,"sw      %s, %i(%s)", register_names[rs1], sign_extend(imm, 12), register_names[rs2]);

}

void Executor::decode_and_execute_Store(const Instruction &inst) {
    switch (inst.func3) {
        case SLB_FUNC3:
            execute_sb(inst.rs1, inst.rs2, inst.imm_s);
            break;
        case SLH_FUNC3:
            execute_sh(inst.rs1, inst.rs2, inst.imm_s);
            break;
        case SLW_FUNC3:
            execute_sw(inst.rs1, inst.rs2, inst.imm_s);
            break;
        default:
            state_ = ERROR;
    }
}

void Executor::execute_ecall() {
    if (cpu_.registers()[17] == 93) {
        state_ = FINISH;
    } else if (cpu_.registers()[17] == 80) {
        cpu_.set_register(10, 0);
    } else if (cpu_.registers()[17] == 214) {
        cpu_.set_register(10, 0);
    } else if (cpu_.registers()[17] == 64) {
        int ret_val = write(0, cpu_.memory_.memory.data() + cpu_.registers()[11], cpu_.registers()[12]);
        cpu_.set_register(10, ret_val);
    } else if (cpu_.registers()[17] == 63) {
        int ret_val = read(cpu_.registers()[10], cpu_.memory_.memory.data() + cpu_.registers()[11], cpu_.registers()[12]);
        cpu_.set_register(10, ret_val);
    }
    sprintf(dissasembly, "ecall   ");
}

void Executor::execute_ebreak() {
    sprintf(dissasembly, "ebreak  ");
}

void Executor::decode_and_execute_Einst(const Instruction &inst) {
    switch (inst.imm) {
        case 0:
            execute_ecall();
            break;
        case 1:
            execute_ebreak();
            break;
        default:
            state_ = ERROR;
    }
}

void Executor::execute_mul(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    cpu_.set_register(rd, cpu_.registers()[rs1] * cpu_.registers()[rs2]);
    sprintf(dissasembly,"mul     %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::execute_mulh(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    int32_t rs1_val_signed = int32_t(cpu_.registers()[rs1]);
    int32_t rs2_val_signed = int32_t(cpu_.registers()[rs2]);
    int64_t res = int64_t(rs1_val_signed) * int64_t(rs2_val_signed);
    uint32_t res_higher = uint64_t(res) >> 32;
    cpu_.set_register(rd, res_higher);
    sprintf(dissasembly,"mulh    %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::execute_mulhu(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    uint32_t rs1_val = cpu_.registers()[rs1];
    uint32_t rs2_val = cpu_.registers()[rs2];
    uint64_t res = uint64_t(rs1_val) * uint64_t(rs2_val);
    uint32_t res_higher = uint64_t(res) >> 32;
    cpu_.set_register(rd, res_higher);
    sprintf(dissasembly,"mulhu   %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::execute_mulhsu(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    uint32_t rs1_val_signed = cpu_.registers()[rs1];
    uint32_t rs2_val = int32_t(cpu_.registers()[rs2]);
    uint64_t res = int64_t(rs1_val_signed) * uint64_t(rs2_val);
    uint32_t res_higher = uint64_t(res) >> 32;
    cpu_.set_register(rd, res_higher);
    sprintf(dissasembly,"mulhsu  %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::execute_div(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    int32_t rs1_val = int32_t(cpu_.registers()[rs1]);
    int32_t rs2_val = int32_t(cpu_.registers()[rs2]);
    cpu_.set_register(rd, rs1_val / rs2_val);
    sprintf(dissasembly,"div     %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::execute_divu(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    uint32_t rs1_val = cpu_.registers()[rs1];
    uint32_t rs2_val = cpu_.registers()[rs2];
    cpu_.set_register(rd, rs1_val / rs2_val);
    sprintf(dissasembly,"divu    %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::execute_rem(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    int32_t rs1_val = int32_t(cpu_.registers()[rs1]);
    int32_t rs2_val = int32_t(cpu_.registers()[rs2]);
    cpu_.set_register(rd, rs1_val % rs2_val);
    sprintf(dissasembly,"rem     %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::execute_remu(uint8_t rd, uint8_t rs1, uint8_t rs2) {
    uint32_t rs1_val = cpu_.registers()[rs1];
    uint32_t rs2_val = cpu_.registers()[rs2];
    cpu_.set_register(rd, rs1_val % rs2_val);
    sprintf(dissasembly,"remu    %s, %s, %s", register_names[rd], register_names[rs1], register_names[rs2]);
}

void Executor::decode_and_execute_muldiv(const Instruction &inst) {
    switch (inst.func3) {
        case MUL_FUNC3:
            execute_mul(inst.rd, inst.rs1, inst.rs2);
            break;
        case MULH_FUNC3:
            execute_mulh(inst.rd, inst.rs1, inst.rs2);
            break;
        case MULHU_FUNC3:
            execute_mulhu(inst.rd, inst.rs1, inst.rs2);
            break;
        case MULHSU_FUNC3:
            execute_mulhsu(inst.rd, inst.rs1, inst.rs2);
            break;
        case DIV_FUNC3:
            execute_div(inst.rd, inst.rs1, inst.rs2);
            break;
        case DIVU_FUNC3:
            execute_divu(inst.rd, inst.rs1, inst.rs2);
            break;
        case REM_FUNC3:
            execute_rem(inst.rd, inst.rs1, inst.rs2);
            break;
        case REMU_FUNC3:
            execute_remu(inst.rd, inst.rs1, inst.rs2);
            break;
        default:
            state_ = ERROR;
    }
}

void Executor::execute_fence(const Instruction &inst) {
    sprintf(dissasembly, "fence   ");
}


void Executor::decode_and_execute(uint32_t instruction_word) {
    Instruction inst(instruction_word);
    cpu_.set_register(0, 0);
    uint32_t curr_pc = cpu_.pc();
    uint32_t rs1_val = cpu_.registers()[inst.rs1];
    uint32_t rs2_val = cpu_.registers()[inst.rs2];
    state_ = CONTINUE;
    switch (inst.opcode) {
        case I_OPCODE:
            decode_and_execute_IType(inst);
            break;
        case R_OPCODE:
            if (inst.func7 == MULDIV_FUNC7) {
                decode_and_execute_muldiv(inst);
            } else {
                decode_and_execute_RType(inst);
            }
            break;
        case LUI_OPCODE:
            execute_lui(inst.rd, inst.imm_u);
            break;
        case AUIPC_OPCODE:
            execute_auipc(inst.rd, inst.imm_u);
            break;
        case JAL_OPCODE:
            execute_jal(inst.rd, inst.imm_jal);
            break;
        case JALR_OPCODE:
            execute_jalr(inst.rd, inst.rs1, inst.imm);
            break;
        case B_OPCODE:
            decode_and_execute_BType(inst);
            break;
        case LOAD_OPCODE:
            decode_and_execute_Load(inst);
            break;
        case STORE_OPCODE:
            decode_and_execute_Store(inst);
            break;
        case PAUSE_FENCE_OPCODE:
            execute_fence(inst);
            break;
        case ECALL_EBREAK_OPCODE:
            decode_and_execute_Einst(inst);
            break;
        default:
            state_ = ERROR;;
    }
    if (state_ != JUMP) {
        cpu_.set_pc(cpu_.pc() +4);
    }
    cpu_.set_register(0, 0);
    uint32_t rd_val = cpu_.registers()[inst.rd];
    fprintf(log, "PC=%08X [%08X] x%02i=%08X x%02i=%08X x%02i=%08X %s\n", curr_pc, inst.instruction_word, inst.rd, rd_val, inst.rs1, rs1_val, inst.rs2, rs2_val, dissasembly);
}

void Executor::execute() {
    cpu_.set_register(2, cpu_.memory_.memory.size());
    while (state_ != ERROR && state_ != FINISH) {
        uint32_t inst;
        inst = cpu_.memory_.get_word(cpu_.pc());
        decode_and_execute(inst);
    }
}
