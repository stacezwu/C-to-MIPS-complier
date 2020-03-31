# Testbench to run compiler tests

import os
import sys
import subprocess
import glob


c_compiler = 'bin/c_compiler'

tests = map(lambda x: {'test_program': x.replace('_driver', ''), 'test_driver': x}, glob.glob('compiler_tests/*/*_driver.c'))
# tests = map(lambda x: {'test_program': x.replace('_driver', ''), 'test_driver': x}, glob.glob('compiler_tests/misc/*_driver.c'))

os.system('mkdir -p tmp/compiler/; rm tmp/compiler/*')
pass_count = 0
for index, test in enumerate(tests):
    output_path = 'tmp/compiler/'+'_'.join([test['test_program'].split('/')[-2], test['test_program'].split('/')[-1]]).replace('.c', '.s')
    os.system('{} -S {} -o {}'.format(c_compiler, test["test_program"], output_path));
    os.system('mips-linux-gnu-gcc -w -mfp32 -o tmp/compiler/test_program.o -c {}'.format(output_path)) # warnings disabled using "-w"
    os.system('mips-linux-gnu-gcc -w -mfp32 -static -o tmp/compiler/test_program tmp/compiler/test_program.o {}'.format(test["test_driver"])) # warnings disabled using "-w"
    p = subprocess.run(['qemu-mips', 'tmp/compiler/test_program'], stdout=subprocess.PIPE, timeout=5000)
    
    if p.returncode == 0:
        print('PASS ' + test['test_program'])
        pass_count += 1
    else:
        print('FAIL {}; got retcode {}'.format(test["test_program"], p.returncode))
    
    # if index == 5:
    #     break
    
print()
print('Passed {} of {} tests'.format(pass_count, index+1))
