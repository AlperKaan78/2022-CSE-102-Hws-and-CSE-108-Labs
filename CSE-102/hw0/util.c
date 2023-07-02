#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator) {
    printf("%d//%d", numerator, denominator);
}  /* end fraction_print */

void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 + n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_add */

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3) {
	int temp = n1*d2 - n2*d1;
	*d3 = d1*d2;
	if(temp < 0 ){  /*We do not consider which number is greater before. Therefore we must do these steps. */
		*n3 = (-1) * temp;
	}
	else{
		*n3 = temp;
	}
    fraction_simplify(n3, d3);
} /* end fraction_sub */

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3) {
	*n3 = n1*n2;
	*d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_mul */

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2;
    *d3 = n2*d1;
    fraction_simplify(n3, d3);
} /* end fraction_div */

/* Simplify the given fraction such that they are divided by their GCD */
void fraction_simplify(int * n, int * d) {
	int gcd = 1;
	int tempn = *n;
	int tempd = *d;
	for(int k = 2; k<=tempn; k++){ /* I do not choose small one before. Because I think it does not matter. */
		if((tempd%k == 0) & (tempn%k == 0)){
			gcd=k;
		}
	}
	*n = tempn/gcd;
	*d = tempd/gcd;
	 
} /* end fraction_div */


