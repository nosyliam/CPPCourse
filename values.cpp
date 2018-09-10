#include <iostream>
#include <cmath>

float byValue(float val, int pow) {
  return std::pow(val, pow);
}

void byRef(float& val, int& pow) {
  val = std::pow(val, pow);
}

void byPtr(float* val, int* pow) {
  *val = std::pow(*val, *pow);
}

int main() {
  float val, ret = 0.0;
  int pow = 0;
  char buffer[255];

  std::cout << "Value: ";
  while (val != val) {
    std::cin.getline(buffer, sizeof(buffer));
    val = atof(buffer);
  }

  std::cout << "Power: ";
  while (!pow) {
    std::cin.getline(buffer, sizeof(buffer));
    pow = atoi(buffer);
  }

  ret = byValue(val, pow);
  std::cout << "By value: val = " << val << ", pow = " << pow << ", ret = " << ret << std::endl;

  byRef(val, pow);
  std::cout << "By reference: val = " << val << ", pow = " << pow << std::endl;

  byPtr(&val, &pow);
  std::cout << "By pointer: val = " << val << ", pow = " << pow << std::endl;

  return 0;
}
