#include <stdio.h>
#include <stdlib.h>

int getDigitsSum(int number) {
  if (number == 0) {
    return 0;
  }

  return number % 10 + getDigitsSum(number / 10);
}

int main() {
  int myNum = 1111;
  printf("The sum of the digits of %d is %d\n", myNum, getDigitsSum(myNum));
  return 0;
}
