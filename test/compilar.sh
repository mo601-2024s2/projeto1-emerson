cd ACStone
for arquivo in $(find . -type f -name "*.c"); do
   filename=$(basename -- "$arquivo")
   extension="${filename##*.}"
   filename="${filename%.*}"
   source_file="$filename"."c"
   bin_file="$filename"."bin"
   exec_file="$filename"."x"
   riscv32-unknown-elf-gcc -Ttext=0  -nostartfiles -march=rv32ima -o $exec_file $source_file aux.c
   riscv32-unknown-elf-objcopy -O binary $exec_file $bin_file
done
