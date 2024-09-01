//
// Created by emerson on 31/08/24.
//

#include "ReadElf.h"

#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

void ReadElf::read_elf(std::string filename, int &initial_pc, int &gp) {
    int fd = open(filename.c_str(), O_RDONLY);
    int counter = 0;
    char *strtab;
    int length = lseek(fd, 0, SEEK_END);;
    void* map_start = mmap(0, length, PROT_READ , MAP_SHARED, fd, 0);
    // Read file
    Elf32_Ehdr *elf_header = (Elf32_Ehdr*) map_start;
        // read the header
    Elf32_Shdr *section_headers = static_cast<Elf32_Shdr *>(map_start + elf_header->e_shoff);
    strtab = (char *)(map_start + section_headers[elf_header->e_shstrndx].sh_offset);
    initial_pc = elf_header->e_entry;
    while(counter < elf_header->e_shnum) {
        if (strcmp(&strtab[section_headers[counter].sh_name], ".data") == 0) {
            gp = section_headers[counter].sh_addr + 0x800;
            break;
        }
        counter++;
    }
}
