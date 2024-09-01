#include <iostream>

#include "ReadElf.h"

int main(int argc, char *argv[])
{
    if (argc == 2) {
        int pc, gp;
        ReadElf reader;
        reader.read_elf(argv[1], pc, gp);
        printf("0X%X 0X%X", pc, gp);
        return 0;
    }
    printf("Usage: %s [elf_file]\n", argv[0]);
    return -1;
}
