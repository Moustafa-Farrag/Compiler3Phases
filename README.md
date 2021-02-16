# Compiler3Phases
making a compiler generator to convert java to java-bytecode using this steps Lexical Analysis, Syntax Analysis, Syntax Directed Translation ,Code Generation.

# Compiling and running the code
you can use this command in linux environment.<br />
files=$(find . -name \*.h -print -o -name \*.cpp -print) <br />
g++ -o a $(echo $files) <br />
<br />

for running: <br />
./a > debugging.txt <br />

- you can but your code at codeInput.txt <br />
- result of javabyte code at byteCode.txt <br />
