#include<stdio.h>
#include<emscripten.h>

int main(int argc, char **argv) {
    puts("Super advanced example!");
    EM_ASM(alert('Inline JavaScript!'););

    return 0;
}

