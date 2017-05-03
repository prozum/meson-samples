#include <math.h>
#include <stdio.h>
#include <SDL/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

typedef enum fractal { MANDELBROT, JULIA, NEWTON } fractal;

typedef struct complex {
    double r;
    double i;
} complex;

typedef struct setting {
    fractal type;
    int max;
    int width;
    int height;
    double zoom;
    double x_offset;
    double y_offset;
} setting;

void ccprint(complex op);
double ccabs(complex op);
void ccadd(complex *rop, complex op1, complex op2);
void ccmul(complex *rop, complex op1, complex op2);
void ccmin(complex *rop, complex op1, complex op2);
void ccdiv(complex *rop, complex op1, complex op2);
void ccpow(complex *rop, complex op1, int op2);
void ccsqrt(complex *rop, complex op);

void calc_complex(complex *rop, int x, int y, setting set);
void calc_color(int color[], int n, int max);

int mandelbrot(complex z, complex c, int max);
int newton(complex z, complex c, complex s, int max);

void loop() {
    //SDL_RenderPresent(renderer);
}

int main(int argc, char *argv[]) {
    int n, x, y;
    int color[3];
    complex rop, op1, op2;
    setting set;
    set.width = 800;
    set.height= 600;

    puts("0: Mandelbrot");
    puts("1: Julia");
    puts("2: Newton");
    puts("Choose fractal:");
    scanf("%i", &set.type);
    //set.type = 2;

    // Setup nice defaults for fractal types
    switch (set.type) {

    case MANDELBROT:
        set.max = 100;
        set.zoom = 0.004;
        set.x_offset = -0.5;
        set.y_offset = 0;

        op1.r = 0;
        op1.i = 0;
        break;

    case JULIA:
        set.max = 100;
        set.zoom = 0.005;
        set.x_offset = 0;
        set.y_offset = 0;

        op1.r = 0.3;
        op1.i = 0.6;
        break;

    case NEWTON:
        set.max = 20;
        set.zoom = 0.004;
        set.x_offset = 0;
        set.y_offset = 0;

        op1.r = -1;
        op1.i = 0;

        op2.r = 0.000001;
        op2.i = 0.000001;
        break;
    default:
        printf("Invalid type.\n");
        return -1;
    }

    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;

    win = SDL_CreateWindow("cfrac", 0, 0, set.width, set.height, 0);
    renderer = SDL_CreateRenderer(win, -1,0);

    for (y = 0; set.height > y; y++) {
        for (x = 0; set.width > x; x++) {

            // Calc complex number for x,y coordinate
            calc_complex(&rop, x, y, set);

            // Find iterations for fractal types
            switch (set.type) {

            case MANDELBROT:
                n = mandelbrot(op1, rop, set.max);
                break;

            case JULIA:
                n = mandelbrot(rop, op1, set.max);
                break;

            case NEWTON:
                n = newton(rop, op1, op2, set.max);
                break;
            }

            // Calc rainbow color for iteration
            if (n != set.max) {
                calc_color(color, n, set.max);

                SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 0);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
        SDL_RenderPresent(renderer);
    }

    emscripten_set_main_loop(loop, 60, 1);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    
    return 0;
}

int mandelbrot(complex z, complex c, int max) {
    /**
       Calc number of iterations needed to determime
       infinity properties of f(z,c) = z^2+c.
     */

    int i;
    for (i = 0; max > i; i++) {
        if (ccabs(z) > 2)
            return i;

        ccmul(&z, z, z);
        ccadd(&z, z, c);
    }
    return max;
}

int newton(complex z, complex c, complex s, int max) {
    /**
       Calc number of iterations needed to determime
       root for f(z)=z^3-1.
      */
    complex fz, fs, dz, z0, tmp;

    int i;
    for (i = 0; max > i; i++) {
        // fz=z^3-c
        ccpow(&tmp, z, 3);
        ccmin(&fz, tmp, c);

        // fs=(z+s)^3-c
        ccadd(&tmp, z, s);
        ccpow(&tmp, tmp, 3);
        ccmin(&fs, tmp, c);

        // dz = (fs-fz)/s
        ccmin(&tmp, fs, fz);
        ccdiv(&dz, tmp, s);

        // z0 = z - fz/dz
        ccdiv(&tmp, fz, dz);
        ccmin(&z0, z, tmp);

        // if (0.001 > abs(z0-z)) return i;
        ccmin(&tmp, z0, z);
        if (0.001 > ccabs(tmp)) {
            return i;
        }
        z = z0;
    }

    return max;
}

void calc_complex(complex *rop, int x, int y, setting set) {
    /**
       Calculate complex number for x,y pixel
     */

    rop->r = (x - set.width / 2) * set.zoom + set.x_offset;
    rop->i = (-y + set.height / 2) * set.zoom + set.y_offset;
}

void calc_color(int color[], int n, int max) {
    /**
       Calculate rainbow color for number n in interval 0 to max.
     */

    double tn = n * 6.0 / max;

    if (1 >= tn || tn >= 5)
        color[0] = 255;
    else if (5 > tn && tn > 4)
        color[0] = (int)((tn - 4) * 255);
    else if (2 > tn && tn > 1)
        color[0] = (int)(255 - (tn - 1) * 255);
    else
        color[0] = 0;

    if (3 >= tn && tn >= 1)
        color[1] = 255;
    else if (1 > tn)
        color[1] = (int)(tn * 255);
    else if (4 > tn && tn > 3)
        color[1] = (int)(255 - (tn - 3) * 255);
    else
        color[1] = 0;

    if (5 >= tn && tn >= 3)
        color[2] = 255;
    else if (3 > tn && tn > 2)
        color[2] = (int)((tn - 2) * 255);
    else if (tn > 5)
        color[2] = (int)(255 - (tn - 5) * 255);
    else
        color[2] = 0;
}

// Functions for complex arithmetic
void ccprint(complex op) { printf("(%fl i%fl)", op.r, op.i); }

double ccabs(complex op) { return sqrt(pow(op.r, 2) + pow(op.i, 2)); }

void ccadd(complex *rop, complex op1, complex op2) {
    rop->r = op1.r + op2.r;
    rop->i = op1.i + op2.i;
}

void ccmin(complex *rop, complex op1, complex op2) {
    rop->r = op1.r - op2.r;
    rop->i = op1.i - op2.i;
}

void ccmul(complex *rop, complex op1, complex op2) {
    rop->r = op1.r * op2.r - op1.i * op2.i;
    rop->i = op2.i * op1.r + op2.r * op1.i;
}

void ccdiv(complex *rop, complex op1, complex op2) {
    rop->r = (op1.r * op2.r + op1.i * op2.i) / (pow(op2.r, 2) + pow(op2.i, 2));
    rop->i = (op1.i * op2.r - op1.r * op2.i) / (pow(op2.r, 2) + pow(op2.i, 2));
}

void ccpow(complex *rop, complex op1, int op2) {
    /**
     Only works if op2 is a positive integer.
    */
    complex tmp = op1;

    int i;
    for (i = 1; op2 > i; i++) {
        ccmul(&tmp, tmp, op1);
    }

    *rop = tmp;
}

void ccsqrt(complex *rop, complex op) {
    rop->r = 1 / sqrt(2) * sqrt(ccabs(op) + op.r);
    rop->i = (op.i / fabs(op.i)) / sqrt(2) * sqrt(ccabs(op) - op.r);
}
