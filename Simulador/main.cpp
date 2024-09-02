#include <fstream>
#include <iostream>
#include <iterator>

#include "Executor.h"

int main(int argc, char *argv[]) {
    Executor ex(argv[1], std::stoi(argv[2], 0, 16), std::stoi(argv[3], 0, 16), 128*1024*1024);
    ex.execute();
    return 0;
}
