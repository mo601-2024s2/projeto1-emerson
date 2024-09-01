//
// Created by emerson on 31/08/24.
//

#ifndef READELF_H
#define READELF_H


#include <libelf.h>
#include <string>

class ReadElf {
public:
    void read_elf(std::string filename, int &initial_pc, int &gp);
};



#endif //READELF_H
