#include <iostream>

#include "matrix.h"

int main() {
  double arr1[] = {1, 2, 3, 4};
  double arr2[] = {5, 6, 7, 8};

  Matrix A = matrix_from_array(arr1, 2, 2);
  Matrix B = matrix_from_array(arr2, 2, 2);

  std::cout << "Matrix A:" << std::endl;
  print_matrix(A);

  std::cout << "Matrix B:" << std::endl;
  print_matrix(B);

  Matrix C = matrix_vstack(A, B);
  std::cout << "Vertical stack (A over B):" << std::endl;
  print_matrix(C);

  free_matrix(A);
  free_matrix(B);
  free_matrix(C);

  return 0;
}