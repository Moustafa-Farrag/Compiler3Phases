# Compiler3Phases
making a compiler generator to convert java to java-bytecode using this steps Lexical Analysis, Syntax Analysis, Syntax Directed Translation ,Code Generation.

# Compiling and running the code
you can use this command in linux environment.
files=$(find . -name \*.h -print -o -name \*.cpp -print)
g++ -o a $(echo $files) 

for running:
./a > debugging.txt

- you can but your code at codeInput.txt
- result of javabyte code at byteCode.txt
