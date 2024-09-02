
#ifndef MEMORY_H
#define MEMORY_H
#include <cstdint>
#include <string>
#include <vector>


class Memory {
public:
    [[nodiscard]] const std::vector<uint8_t> & memory1() const {
        return memory;
    }
    std::vector<uint8_t> memory;
private:

public:
    explicit Memory(uint32_t size);
    uint8_t get_byte(uint32_t position);
    uint16_t get_halfword(uint32_t position);
    uint32_t get_word(uint32_t position);
    void set_byte(uint32_t position, int8_t value);
    void set_halfword(uint32_t position, int16_t value);
    void set_word(uint32_t position, int32_t value);
    void load_file(const std::string &filename);
};



#endif //MEMORY_H
