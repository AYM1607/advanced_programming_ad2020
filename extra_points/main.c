#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "/usr/local/include/gmp.h"
#include <string.h>

void fact(int n, mpf_t res) {
  int i;

  mpf_set_ui(res, 1);
  for (i = 1; i <= n; i++) {
    mpf_mul_ui(res, res, i);
  }
}

// Get angle from command line arguments.
// Returns by reference and signifies an error if a negative number is returned.
int getAngle(const char* str, double *result) {
  int angle = atoi(str);

  if (angle > 90 || angle < 0) {
    printf("The provided angle must be between 0 and 90 (inclusive)\n");
    return -1; 
  }

  // Convert degrees to radians.
  double angleInRads = angle * 0.01745329252;

  *result = angleInRads;
  return 0;

}

// mpf_t is an array type so any modification will affect the argument.
void cosFun(double angle, mpf_t res) {
  // Init accumulator.
  mpf_set_ui(res, 0);
  
  // Initialize the required variables.
  mpf_t currentTerm, dividend, divisor;
  mpf_init(currentTerm);
  mpf_init(dividend);
  mpf_init(divisor);
  
  // Calculate cos using taylor seires.
  int i;
  for (i = 0; i < 1000; i++) {
    // Calculate dividend.
    mpf_set_d(dividend, angle);
    mpf_pow_ui(dividend, dividend, 2 * i);
    // Calculate divisor.
    fact(2 * i, divisor);
    mpf_div(currentTerm, dividend, divisor);
    // Flip sign if neccessary.
    if (i % 2 == 1) {
      mpf_neg(currentTerm, currentTerm);
    }

    // Add term to result.
    mpf_add(res, res, currentTerm);
  }
}

// mpf_t is an array type so any modification will affect the argument.
void senFun(double angle, mpf_t res) {
  // Init accumulator.
  mpf_set_ui(res, 0);
  
  // Initialize the required variables.
  mpf_t currentTerm, dividend, divisor;
  mpf_init(currentTerm);
  mpf_init(dividend);
  mpf_init(divisor);
  
  // Calculate cos using taylor seires.
  int i;
  for (i = 0; i < 1000; i++) {
    // Calculate dividend.
    mpf_set_d(dividend, angle);
    mpf_pow_ui(dividend, dividend, (2 * i) + 1);
    // Calculate divisor.
    fact((2 * i) + 1, divisor);
    mpf_div(currentTerm, dividend, divisor);
    // Flip sign if neccessary.
    if (i % 2 == 1) {
      mpf_neg(currentTerm, currentTerm);
    }

    // Add term to result.
    mpf_add(res, res, currentTerm);
  }
}

void tanFun(double angle, mpf_t res) {
  mpf_set_ui(res, 0);
  mpf_t sin, cos;
  // Calculate sin and cos to get tan.
  mpf_init(sin);
  mpf_init(cos);
  senFun(angle, sin);
  cosFun(angle, cos);

  mpf_div(res, sin, cos);

  mpf_clear(sin);
  mpf_clear(cos);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Uso del programa: ./main.o operación angulo\nOperaciones disponibles: sen, cos, tan\n");
    return -1;
  }

  mpf_t res;
  mpf_init(res);
  double angleInRads = 0;

  if (strcmp("cos", argv[1]) == 0) {
    if (getAngle(argv[2], &angleInRads) != 0) {
      return -1;
    }
    cosFun(angleInRads, res);

    // Print with max accuracy
    printf("The cosine of %f radians is: ", angleInRads);
    mpf_out_str(stdout, 10, 0, res);
    printf("\n");

    mpf_clear(res);
  } else if(strcmp("sen", argv[1]) == 0) {

    if (getAngle(argv[2], &angleInRads) != 0) {
      return -1;
    }
    senFun(angleInRads, res);

    // Print with max accuracy
    printf("The sine of %f radians is: ", angleInRads);
    mpf_out_str(stdout, 10, 0, res);
    printf("\n");

    mpf_clear(res);
  } else if (strcmp("tan", argv[1]) == 0) {
    if (getAngle(argv[2], &angleInRads) != 0) {
      return -1;
    }
    tanFun(angleInRads, res);

    // Print with max accuracy
    printf("The tangent of %f radians is: ", angleInRads);
    mpf_out_str(stdout, 10, 0, res);
    printf("\n");

    mpf_clear(res);
  } else {
    printf("La opción que ingresaste no es correcta\n");
  }
  
  return 0;
}
