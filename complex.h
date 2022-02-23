/*Header file for complex numbers and their aritchmatics*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*complex number struct definition*/
typedef struct {
char Name;
double R;
double I;
}complex;

/*Function Prototypes*/
void read_comp(complex*,double,double);
void print_comp(complex*);
void add_comp(complex*,complex*);
void sub_comp(complex*,complex*);
void mult_comp_real(complex*,float);
void mult_comp_img(complex*,float);
void mult_comp_comp(complex*,complex*);
void abs_comp(complex*);
void stop();

/*macros*/
#define power_of_2 2
