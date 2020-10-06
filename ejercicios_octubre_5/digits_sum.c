#include "stdio.h"
#include "stdlib.h"

int digitSum(int number) {
  if (number == 0) {
    return 0;
  }
  return (number % 10) + digitSum(number / 10);
}

int main() {
  int number;
  printf("Enter a number to calculate the sum of its digits:\n");
  scanf(" %d", &number);
  printf("The sum of its digits is: %d\n", digitSum(number));
  return 0;
}
