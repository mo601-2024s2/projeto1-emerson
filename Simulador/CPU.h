//
// Created by emerson on 20/08/24.
//

#ifndef CPU_H
#define CPU_H
#include <array>
#include <cstdint>

#include "Memory.h"


class CPU {
public:
    [[nodiscard]] const Memory & memory() const {
        return memory_;
    }

    void set_memory(const Memory &memory) {
        memory_ = memory;
    }

    [[nodiscard]] const std::array<uint32_t, 32> & registers() const {
        return registers_;
    }

    void set_registers(const std::array<uint32_t, 32> &registers) {
        registers_ = registers;
    }

    [[nodiscard]] uint32_t pc() const {
        return pc_;
    }

    void set_pc(uint32_t pc) {
        pc_ = pc;
    }

    void set_register(uint8_t register_number, uint32_t value) {
        registers_[register_number] = value;
    }

    explicit CPU(uint32_t memory_size): memory_(memory_size), pc_(0) {
    }

    CPU() = delete;

    Memory memory_;

private:

    std::array<uint32_t, 32> registers_ = {};
    uint32_t pc_ = 0;
};



#endif //CPU_H
