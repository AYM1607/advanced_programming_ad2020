#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "/usr/local/include/gmp.h"
#include <string.h>
#include <sys/time.h>

#define ITERATIONS 1000

struct threadArgs {
  double angle;
  int lowerRange;
  int upperRange;
  mpf_t result;
};

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
void cosFun(double angle, mpf_t res, int lowerRange, int upperRange) {
  // Init accumulator.
  mpf_set_ui(res, 0);
  
  // Initialize the required variables.
  mpf_t currentTerm, dividend, divisor;
  mpf_init(currentTerm);
  mpf_init(dividend);
  mpf_init(divisor);
  
  // Calculate cos using taylor seires.
  int i;
  for (i = lowerRange; i < upperRange; i++) {
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
void senFun(double angle, mpf_t res, int lowerRange, int upperRange) {
  // Init accumulator.
  mpf_set_ui(res, 0);
  
  // Initialize the required variables.
  mpf_t currentTerm, dividend, divisor;
  mpf_init(currentTerm);
  mpf_init(dividend);
  mpf_init(divisor);
  
  // Calculate cos using taylor seires.
  int i;
  for (i = lowerRange; i < upperRange; i++) {
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
  senFun(angle, sin, 0, 1000);
  cosFun(angle, cos, 0, 1000);

  mpf_div(res, sin, cos);

  mpf_clear(sin);
  mpf_clear(cos);
}

void *cosFunConcurrent(void *arg) {
  struct threadArgs *args = (struct threadArgs *) arg;
  cosFun(args->angle, args->result, args->lowerRange, args->upperRange);
  return NULL;
}

void calculateCosMultithread(double angle, mpf_t res) {
  int i;
  int threadCount = 4;
  struct threadArgs args[4];
  pthread_t handles[4];
  // Creating all threads.
  for (i = 0; i < threadCount; i++) {
    args[i].angle = angle;
    args[i].lowerRange = i * (ITERATIONS / threadCount);
    args[i].upperRange = (i + 1) * (ITERATIONS / threadCount);
    mpf_init(args[i].result);
    pthread_create((handles + i), NULL, cosFunConcurrent, (args + i));
  }
  // Waiting for all threads.
  for (i = 0; i < threadCount; i++) {
    pthread_join(handles[i], NULL);
  }
  // Adding all results.
  mpf_set_ui(res, 0);
  for (i = 0; i < threadCount; i++) {
    mpf_add(res, res, args[i].result);
  }
  
}

void *senFunConcurrent(void *arg) {
  struct threadArgs *args = (struct threadArgs *) arg;
  senFun(args->angle, args->result, args->lowerRange, args->upperRange);
  return NULL;
}

void calculateSenMultithread(double angle, mpf_t res) {
  int i;
  struct threadArgs args[4];
  pthread_t handles[4];
  // Creating all threads.
  for (i = 0; i < 4; i++) {
    args[i].angle = angle;
    args[i].lowerRange = i * (ITERATIONS / 4);
    args[i].upperRange = (i + 1) * (ITERATIONS / 4);
    mpf_init(args[i].result);
    pthread_create((handles + i), NULL, senFunConcurrent, (args + i));
  }
  // Waiting for all threads.
  for (i = 0; i < 4; i++) {
    pthread_join(handles[i], NULL);
  }
  // Adding all results.
  mpf_set_ui(res, 0);
  for (i = 0; i < 4; i++) {
    mpf_add(res, res, args[i].result);
  }
  
}

void calculateTanMultithread(double angle, mpf_t res) {
  mpf_set_ui(res, 0);
  mpf_t sin, cos;
  // Calculate sin and cos to get tan.
  mpf_init(sin);
  mpf_init(cos);
  calculateSenMultithread(angle, sin);
  calculateCosMultithread(angle, cos);

  mpf_div(res, sin, cos);

  mpf_clear(sin);
  mpf_clear(cos);
}

long long getCurrentTime() {
  long long result;
  struct timeval timecheck;

  gettimeofday(&timecheck, NULL);
  result = (long)timecheck.tv_sec * 1000 + (long)timecheck.tv_usec / 1000;
  return result;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Uso del programa: ./main.o operación angulo\nOperaciones disponibles: sen, cos, tan\n");
    return -1;
  }

  mpf_t res;
  mpf_init(res);
  double angleInRads = 0;
  long long start, end;
  if (strcmp("cos", argv[1]) == 0) {
    if (getAngle(argv[2], &angleInRads) != 0) {
      return -1;
    }

    // Calculate without multithreading.
    start = getCurrentTime(); 
    cosFun(angleInRads, res, 0 , ITERATIONS);  
    end = getCurrentTime();
    // Print with max accuracy
    printf("The cosine of %f radians is: ", angleInRads);
    mpf_out_str(stdout, 10, 0, res);
    printf(" and the calculation with 1 thread took ~%lld milliseconds\n", end - start);

    // Calculate using 4 threads.
    
    start = getCurrentTime(); 
    calculateCosMultithread(angleInRads, res);
    end = getCurrentTime();
    // Print with max accuracy
    printf("The cosine of %f radians is: ", angleInRads);
    mpf_out_str(stdout, 10, 0, res);
    printf(" and the calculation with 4 threads took ~%lld milliseconds\n", end - start);

    mpf_clear(res);
  } else if(strcmp("sen", argv[1]) == 0) {

    if (getAngle(argv[2], &angleInRads) != 0) {
      return -1;
    }

    // Calculate wihout multithreading.
    start = getCurrentTime();
    senFun(angleInRads, res, 0, ITERATIONS);
    end = getCurrentTime();
    // Print with max accuracy
    printf("The sine of %f radians is: ", angleInRads);
    mpf_out_str(stdout, 10, 0, res);
    printf(" and the calculation with 1 threads took ~%lld milliseconds\n", end - start);

    // Calculate using 4 threads.
    start = getCurrentTime();
    calculateSenMultithread(angleInRads, res);
    end = getCurrentTime();
    // Print with max accuracy
    printf("The sine of %f radians is: ", angleInRads);
    mpf_out_str(stdout, 10, 0, res);
    printf(" and the calculation with 4 threads took ~%lld milliseconds\n", end - start);

    mpf_clear(res);
  } else if (strcmp("tan", argv[1]) == 0) {
    if (getAngle(argv[2], &angleInRads) != 0) {
      return -1;
    }
    
    // Calculate using 4 threads.
    start = getCurrentTime();
    tanFun(angleInRads, res);
    end = getCurrentTime();
    // Print with max accuracy
    printf("The tangent of %f radians is: ", angleInRads);
    mpf_out_str(stdout, 10, 0, res);
    printf(" and the calculation with 1 threads took ~%lld milliseconds\n", end - start);

    // Calculate using 4 threads.
    start = getCurrentTime();
    calculateTanMultithread(angleInRads, res);
    end = getCurrentTime();
    // Print with max accuracy
    printf("The tangent of %f radians is: ", angleInRads);
    mpf_out_str(stdout, 10, 0, res);
    printf(" and the calculation with 4 threads took ~%lld milliseconds\n", end - start);

    mpf_clear(res);
  } else {
    printf("La opción que ingresaste no es correcta\n");
  }
  
  return 0;
}
