/*this file holds arithmetic functions for complex type variables.*/
#include "complex.h"

/*this function gets a complex variable pointer and 2 numbers to assign in it*/
void read_comp(complex* myComp,double Real,double Imaginary){
(*myComp).R = Real;
(*myComp).I = Imaginary;
}

/*this function gets a complex variable pointer and prints it in a nice manner*/
void print_comp(complex* myComp){
float LocalR=(*myComp).R;
float LocalI=(*myComp).I;
if ( LocalI>=0)
    printf("%.2f + (%.2f)i\n",LocalR,LocalI);
else
    printf("%.2f - (%.2f)i\n",LocalR,(-1*LocalI));
}

/*this function gets 2 complex variable pointers prints their addition*/
void add_comp(complex* comp1,complex* comp2){
complex Temp;
Temp.R=(*comp1).R+(*comp2).R;
Temp.I=(*comp1).I+(*comp2).I;

print_comp(&Temp);
}

/*this function gets 2 complex variable pointers prints their subtraction*/
void sub_comp(complex* comp1,complex* comp2){
complex Temp;
Temp.R=(*comp1).R-(*comp2).R;
Temp.I=(*comp1).I-(*comp2).I;

print_comp(&Temp);
}
/*this function gets a complex variable pointer and a real number, and prints their multiplication*/
void mult_comp_real(complex* comp,float real){
complex Temp;
Temp.R=(*comp).R*real;
Temp.I=(*comp).I*real;

print_comp(&Temp);
}

/*this function gets a complex variable pointer and an imaginary number, and prints their multiplication*/
void mult_comp_img(complex* comp,float img){
complex Temp;
Temp.R=(-1)*(*comp).I*img;
Temp.I=(*comp).R*img;

print_comp(&Temp);
}
/*this function gets 2 complex variable pointers and prints their multiplication*/
void mult_comp_comp(complex* comp1,complex* comp2){
complex Temp;
Temp.R=((*comp1).R * (*comp2).R) - ((*comp1).I * (*comp2).I);
Temp.I=((*comp1).R * (*comp2).I) + ((*comp1).I * (*comp2).R);

print_comp(&Temp);
}
/*this function gets a complex variable pointer and prints its absolute value*/
void abs_comp(complex* comp){
complex Temp;
Temp.I=0;
Temp.R=sqrt(pow((*comp).R,power_of_2)+pow((*comp).I,power_of_2));

print_comp(&Temp);
}

/*this function stops the program*/
void stop(){
exit(0);
}
