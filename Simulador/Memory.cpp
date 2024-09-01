//
// Created by emerson on 13/08/24.
//

#include "Memory.h"

#include <fstream>
#include <iterator>

Memory::Memory(uint32_t size) {
    memory.resize(size, 0);
}

uint8_t Memory::get_byte(uint32_t position) {
    const uint8_t value = memory[position];
    return value;
}

uint16_t Memory::get_halfword(uint32_t position) {
    uint16_t value = memory[position];
    value = (value) | (memory[position + 1] << 8);
    return value;
}

uint32_t Memory::get_word(uint32_t position) {
    uint32_t value = memory[position];
    value = (value) | (memory[position + 1] << 8);
    value = (value) | (memory[position + 2] << 16);
    value = (value) | (memory[position + 3] << 24);
    return value;
}

void Memory::set_byte(uint32_t position, int8_t value) {
    memory[position] = value;
}

void Memory::set_halfword(uint32_t position, int16_t value) {
    memory[position] = value & 0xFF;
    memory[position + 1] = (value >> 8) & 0xFF;
}

void Memory::set_word(uint32_t position, int32_t value) {
    memory[position] = value & 0xFF;
    memory[position + 1] = (value >> 8) & 0xFF;
    memory[position + 2] = (value >> 16) & 0xFF;
    memory[position + 3] = (value >> 24) & 0xFF;
}

void Memory::load_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    uint8_t byte;
    file.unsetf(std::ios::skipws);
    memory.insert(memory.begin(),
               std::istream_iterator<uint8_t>(file),
               std::istream_iterator<uint8_t>());
}
