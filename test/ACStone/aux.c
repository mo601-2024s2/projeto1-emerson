void _start() {
  int ret_val = main();
  exit(ret_val);
}
  
void exit(int code) {
    __asm__ __volatile__(
      "mv a0, %0           # return code\n"
      "li a7, 93           # syscall exit (93) \n"
      "ecall"
      :   // Output list
      :"r"(code)    // Input list
      : "a0", "a7"
    );
}

