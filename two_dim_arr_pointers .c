
// working with Two-Dimensional Arrays Using a Pointer to Pointer 
#include <stdio.h>


void main (void)
{
	
char ch1 [] = {1,2,3,4};
char * Pch1 = ch1;

int int1 [] = {10,20,30,40,50,60};
int * Pint1 = int1;               //инициализация указателя на первый элемент одномерного массива из 3-ех эл. в строке

double double1 [] = {100.1,200.2,300.3,400.4, 500.5, 600.6};
double * Pouble1 = double1;       




int int2 [] [3]= {10,20,30,40,50,60};
int (* Pint2) [3] = int2;        //инициализация указателя на первый элемент массива из 3-ех элементов в строке (для исходно двухмерного массива )

double double2 [][3] = {100.1,200.2,300.3,400.4,500.5,600.6};
double (* Pdouble2) [3] = double2;




printf("=====&[]=================================================\n");
printf("char ch1 adress 1 line %d %d %d %d\n", &ch1[0], &ch1[1], &ch1[2], &ch1[3]);
printf("======ch+i=================================================\n");
printf("char ch1 adress 1 line %d %d %d %d\n\n", Pch1+0, Pch1+1, Pch1+2, Pch1+3);


printf("=====&[]=================================================\n");
printf("int int1 adress 1 line %d %d %d %d %d %d\n", &int1[0], &int1[1], &int1[2], &int1[3], &int1[4], &int1[5]);
printf("======int1+i=================================================\n");
printf("int int1 adress 1 line %d %d %d %d %d %d\n\n", Pint1+0, Pint1+1, Pint1+2, Pint1+3, Pint1+4,Pint1+5);


printf("=====&[][]=================================================\n");
printf("int int2 adress 1 line %d %d %d\n", &int2[0][0], &int2[0][1], &int2[0][2]);
printf("int int2 adress 2 line %d %d %d\n", &int2[1][0], &int2[1][1], &int2[1][2]);
printf("======*int2+i=================================================\n");
printf("int int2 adress 1 line %d %d %d\n", *int2+0, *int2+1, *int2+2);
printf("int int2 adress 2 line %d %d %d\n\n", *int2+3, *int2+4, *int2+5);

printf("======*(int2+i)+j=================================================\n");
printf("int int2 adress 2 line %d %d %d\n\n", *(int2+1)+0, *(int2+1)+1, *(int2+1)+2);


printf("=====&[][]=================================================\n");
printf("double double2 adress 1 line %d %d %d\n", &double2[0][0], &double2[0][1], &double2[0][2]);
printf("double double2 adress 2 line %d %d %d\n", &double2[1][0], &double2[1][1], &double2[1][2]);
printf("======*double2+i=================================================\n");
printf("double double2 adress 1 line %d %d %d\n", *double2+0, *double2+1, *double2+2);
printf("double double2 adress 2 line %d %d %d\n\n", *double2+3, *double2+4, *double2+5);






	return;
}