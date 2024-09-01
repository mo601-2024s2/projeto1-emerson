cd test
cd ACStone
for arquivo in $(find . -type f -name "*.x"); do
   filename=$(basename -- "$arquivo")
   extension="${filename##*.}"
   filename="${filename%.*}"
   exec_file="$filename"."x"
   bin_file="$filename"."bin"
   echo "Executando $filename"
   parametros=$(./../../ElfReader/build/ReadElf $exec_file)
   ./../../Simulador/build/Simulador $bin_file $parametros
done
