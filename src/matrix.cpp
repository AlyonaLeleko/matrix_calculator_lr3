#include "matrix.h"

#include <iomanip>
#include <iostream>

Matrix create_matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Matrix dimensions must be positive");
  }

  Matrix mat;
  mat.rows = rows;
  mat.cols = cols;
  mat.data = new double*[rows];

  for (int i = 0; i < rows; i++) {
    mat.data[i] = new double[cols]();
  }

  return mat;
}

void free_matrix(Matrix m) {
  if (m.data == nullptr) return;

  for (int i = 0; i < m.rows; i++) {
    delete[] m.data[i];
  }
  delete[] m.data;
}

Matrix matrix_add(Matrix a, Matrix b) {
  if (a.rows != b.rows || a.cols != b.cols) {
    throw std::invalid_argument("Matrix dimensions must match for addition");
  }

  Matrix result = create_matrix(a.rows, a.cols);
  for (int i = 0; i < a.rows; i++) {
    for (int j = 0; j < a.cols; j++) {
      result.data[i][j] = a.data[i][j] + b.data[i][j];
    }
  }
  return result;
}

Matrix matrix_multiply(Matrix a, Matrix b) {
  if (a.cols != b.rows) {
    throw std::invalid_argument(
        "Incompatible matrix dimensions for multiplication");
  }

  Matrix result = create_matrix(a.rows, b.cols);
  for (int i = 0; i < a.rows; i++) {
    for (int j = 0; j < b.cols; j++) {
      for (int k = 0; k < a.cols; k++) {
        result.data[i][j] += a.data[i][k] * b.data[k][j];
      }
    }
  }
  return result;
}

Matrix matrix_vstack(Matrix a, Matrix b) {
  if (a.cols != b.cols) {
    throw std::invalid_argument(
        "Matrix columns must match for vertical stacking");
  }

  Matrix result = create_matrix(a.rows + b.rows, a.cols);

  for (int j = 0; j < a.cols; j++) {
    for (int i = 0; i < a.rows; i++) {
      result.data[i][j] = a.data[i][j];
    }
    for (int i = 0; i < b.rows; i++) {
      result.data[a.rows + i][j] = b.data[i][j];
    }
  }

  return result;
}

void print_matrix(Matrix m) {
  if (m.data == nullptr) {
    std::cout << "[Empty matrix]" << std::endl;
    return;
  }

  std::cout << std::fixed << std::setprecision(2);
  for (int i = 0; i < m.rows; i++) {
    std::cout << "[";
    for (int j = 0; j < m.cols; j++) {
      std::cout << std::setw(8) << m.data[i][j];
    }
    std::cout << "]" << std::endl;
  }
}

Matrix matrix_from_array(double* data, int rows, int cols) {
  Matrix mat = create_matrix(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      mat.data[i][j] = data[i * cols + j];
    }
  }
  return mat;
}