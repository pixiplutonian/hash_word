![alt text](https://pixiplutonian.nekoweb.org/assets/hash_word.png "HASH_WORD")

"hash_word" is a simple utility written in C. Its purpose is to calculate a hash of whatever word chosen by the user in the same way as the Dave Strider's 'Hash Map' fetch modus from Andrew Hussie's "Homestuck" webcomic.

The program was written in C23 standard, with Windows operating system in mind. The utility was made for reasons of curiosity, practice, and boredom.

Licensed under MIT. Do whatever you want; I do not care.

## How to run
Simply download the .exe binary from the Releases section. Run it in the terminal.

## How to compile
1. Copy the repository or downloadd the source code .zip archive from the Releases section.
2. Install MSYS2 and GCC via UCRT64 environment. MSYS2 themselves provide a simple tutorial for just that on their main page: https://www.msys2.org/
3. In MSYS2 or PowerShell (if environmental variables of your OS are configured to work with MSYS2), navigate to the source tree directory.
4. Compile using this command: ```gcc -std=c23 -Wall -Wextra -O2 hash_word.c -o hash_word.exe```
5. Run 'hash_word.exe' inside the terminal.
