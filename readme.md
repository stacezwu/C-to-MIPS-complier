C to MIPS Compiler
========

- [*C-compiler*](spec/c_compiler.md) : partial compiler from C to MIPS assembly

- Run `make bin/c_compiler` to build the translator

- Run `bin/c_compiler --translate [source-file.c] -o [dest-file.py]` for specific source file and output file

- Run `./c_translator_formative.sh ` to test against sample tests


C to Python Translator
========

- [*C-translator*](spec/c_translator.md) : partial translator of C to Python

- Run `bin/c_compiler -S [source-file.c] -o [dest-file.s]` for for specific source file and output file

- Run `python testbench.py` to test against sample tests

Environment
========
- Run `vagrant up` to download, install, and configure the VM.

- Run `vagrant ssh` to log into the VM.

- Run `cd /vagrant` : This will put you in the same directory, with
  your host files shared with the VM.

Acknowledgement
========
This is a [coursework](https://github.com/LangProc/langproc-2019-cw.git) for Language Processor 2019/20 at Imperial College London.
