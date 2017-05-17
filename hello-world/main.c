#include<stdio.h>

#if __EMSCRIPTEN__
#include<emscripten.h>
#endif

int main(int argc, char **argv) {
    puts("Super advanced example!");

#if __EMSCRIPTEN__
	EM_ASM(alert('Inline JavaScript!'););
#endif

    return 0;
}

