# (Horace) a script for directly converting C to MIPS and printing the return code of the executed MIPS code
bin/print_mips > tmp/test_output.s
mips-linux-gnu-gcc -static -mfp32 -o tmp/test_output.o tmp/test_output.s
qemu-mips tmp/test_output.o
echo $?