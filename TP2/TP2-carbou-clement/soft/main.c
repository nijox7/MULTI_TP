
#include "stdio.h"

__attribute__((constructor)) void main() {
    char c;
    char s[] = "\n Hello World! \n";

    while(1) {
        // print helloworld
        tty_puts(s);
        // attend caractere de tty
        tty_getc(&c);
    }

} // end main

